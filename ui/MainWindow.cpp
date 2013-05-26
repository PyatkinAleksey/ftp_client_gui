/*
 * File:   MainWindow.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#include "MainWindow.h"

/**
 * Инициализация главного окна и описание обработчиков событий.
 * 
 * @param csw Объект окна свойств соединения.
 */
MainWindow::MainWindow(ConnectionSettings *csw) {
    list<string> globalEntities;
    int i;

    pi = new ProtocolInterpreter();
    service = new Service();
    globalEntity = options.getParameter("paths", "globalEntity", "A:");
    localPath = options.getParameter("paths", "localPath", globalEntity);
    remotePath = "";
    widget.setupUi(this);
    service->setOutputArea(widget.logs);
    csWindow = csw;
    csWindow->setModal(true);
    apWindow = new AboutProgram();
    apWindow->setModal(true);
    globalEntities = fs.getGlobalEntities();
    i = 0;
    for (list<string>::iterator iter = globalEntities.begin(); iter != globalEntities.end(); iter++) {
        widget.globalEntities->addItem(QString::fromStdString(*iter));
        if (*iter == globalEntity) {
            widget.globalEntities->setCurrentIndex(i);
        }
        i++;
    }
    openPath(QString::fromStdString(globalEntity));
    connect(widget.actionConnectionSettings, SIGNAL(triggered()), csWindow, SLOT(show()));
    connect(widget.globalEntities, SIGNAL(currentIndexChanged(QString)), this, SLOT(openPath(QString)));
    connect(widget.localFiles, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openPath(QListWidgetItem*)));
    connect(widget.localFiles, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(renamedLocal(QListWidgetItem*)));
    connect(widget.remoteFiles, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openRemotePath(QListWidgetItem*)));
    connect(widget.remoteFiles, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(renamedRemote(QListWidgetItem*)));
    connect(widget.actionConnect, SIGNAL(triggered()), this, SLOT(ftpConnect()));
    connect(widget.actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(widget.actionRename, SIGNAL(triggered()), this, SLOT(rename()));
    connect(widget.actionDelete, SIGNAL(triggered()), this, SLOT(deleteFiles()));
    connect(widget.actionMakeDirectory, SIGNAL(triggered()), this, SLOT(makeDir()));
    connect(widget.actionAboutProgram, SIGNAL(triggered()), apWindow, SLOT(show()));
}

/**
 * Вывод списка файлов и каталогов при выборе глобальной сущности.
 * 
 * @param item Выбранная глобальная сущность.
 */
void MainWindow::openPath(QString item) {
    list<string> files;
    
    globalEntity = item.toStdString();
    localPath = globalEntity;
    getLocalFileList();
}

/**
 * Вывод списка файлов и директорий при навигации по каталогам.
 * 
 * @param item Выбранный каталог.
 */
void MainWindow::openPath(QListWidgetItem *item) {
    list<string> files;
    string dir = item->text().toStdString();
    int pos;

    localPath += "/" + dir;
    getLocalFileList();
    if (dir == "..") {
        localPath.erase(localPath.find("/..", 0), 3);
        pos = localPath.find_last_of("/", localPath.length());
        localPath.erase(pos, localPath.length() - pos);
    }
}

/**
 * Вывод списка файлов и директорий при навигации по каталогам сервера.
 * 
 * @param item Выбранный каталог.
 */
void MainWindow::openRemotePath(QListWidgetItem* item) {
    int pos;
    
    if (item->text() == "..") {
        nestingCounter--;
        pos = remotePath.find_last_of("/", remotePath.length());
        remotePath.erase(pos, remotePath.length() - pos);
    } else {
        nestingCounter++;
        remotePath += "/" + item->text().toStdString();
    }
    pi->setPath(item->text().toStdString());
    pi->sendCommand("CWD");
    widget.remoteFiles->clear();
    if (nestingCounter) {
        widget.remoteFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/up.ico"), ".."));
    }
    getRemoteFileList();
}

/**
 * Осуществление соединения и получения списка файлов и директорий корневого каталога.
 */
void MainWindow::ftpConnect() {
    bool ok;
    string password;
    
    nestingCounter = 0;
    pi->setAddress(options.getParameter("connection", "address", "127.0.0.1"));
    if (!pi->openControlConnection()) {
        QMessageBox::critical(this, "Error!", "Connection error! Check your connection settings.");
        csWindow->show();
        return;
    }
    pi->setUser(options.getParameter("connection", "user", "anonymous"));
    if (pi->sendCommand("USER") == 1) { // Требуется пароль
        if (options.getParameter("connection", "password", "") == "") { // В конфиге пароль не установлен
            password = QInputDialog::getText(this, "Enter your password",
                    "Password:", QLineEdit::Normal, QDir::home().dirName(), &ok).toStdString();
            if (!ok || password.empty()) {
                return;
            }
        } else {
            password = options.getParameter("connection", "password", "");
        }
        pi->setPassword(password);
        pi->sendCommand("PASS");
    }
    pi->setType(options.getParameter("modes", "type", "A N"));
    pi->sendCommand("TYPE");
    getRemoteFileList();
}

/**
 * Копирование файлов и директорий.
 */
void MainWindow::copy() {
    int passive;
    string path;
    int pos;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        for (int i = 0; i < widget.localFiles->selectedItems().size(); i++) {
            path = widget.localFiles->selectedItems().at(i)->text().toStdString();
            if (fs.isFile(localPath + "/" + path)) {
                passive = options.getParameter("modes", "passive", 1);
                pi->setPassive(passive);
                if (passive) {
                    pi->sendCommand("PASV");
                } else {
                    pi->sendCommand("PORT");
                }
                pi->setLocalPath(localPath + "/" + path);
                pi->setPath(remotePath + "/" + path);
                pi->sendCommand("STOR");
            } else {
                // Создаем каталог и переходим в него
                pi->setPath(remotePath + "/" + path);
                pi->sendCommand("MKD");
                pi->sendCommand("CWD");
                remotePath += "/" + path;
                storeFolder(localPath + "/" + path); // Отправка содержимого выбранного каталога
                // Возвращение в исходный каталог
                pi->setPath(remotePath + "/..");
                pi->sendCommand("CWD");
                pos = remotePath.find_last_of("/", remotePath.length());
                remotePath.erase(pos, remotePath.length() - pos);
            }
        }
        getRemoteFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        for (int i = 0; i < widget.remoteFiles->selectedItems().size(); i++) {
            path = widget.remoteFiles->selectedItems().at(i)->text().toStdString();
            if (widget.remoteFiles->selectedItems().at(i)->type()) { // Файл
                passive = options.getParameter("modes", "passive", 1);
                pi->setPassive(passive);
                if (passive) {
                    pi->sendCommand("PASV");
                } else {
                    pi->sendCommand("PORT");
                }
                pi->setLocalPath(localPath + "/" + path);
                pi->setPath(remotePath + "/" + path);
                pi->sendCommand("RETR");
            } else { // Каталог
                // Создаем каталог и переходим в него
                if (fs.makeDirectory(localPath + "/" + path)) {
                    localPath += "/" + path;
                }
                // Копирование содержимого выбранного каталога
                remotePath += "/" + path;
                pi->setPath(remotePath);
                pi->sendCommand("CWD");
                retrieveFolder(remotePath);
                pos = remotePath.find_last_of("/", remotePath.length());
                remotePath.erase(pos, remotePath.length() - pos);
                pi->setPath("..");
                pi->sendCommand("CWD");
                // Возвращение в исходный каталог
                pos = localPath.find_last_of("/", localPath.length());
                localPath.erase(pos, localPath.length() - pos);
            }
        }
        getLocalFileList();
    } else {
        QMessageBox::information(this, "Information", "You should select a file or directory!");
    }
}

/**
 * Переименование выделенного файла или директории.
 */
void MainWindow::rename() {   
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        QListWidgetItem *item = *widget.localFiles->selectedItems().begin();
        oldName = item->text().toStdString();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        widget.localFiles->editItem(item);
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        QListWidgetItem *item = *widget.remoteFiles->selectedItems().begin();
        oldName = item->text().toStdString();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        widget.remoteFiles->editItem(item);
    } else {
        QMessageBox::information(this, "Information", "You should select a file or directory!");
    }
}

/**
 * Переименован локальный файл или директория.
 * 
 * @param item Файла или директория.
 */
void MainWindow::renamedLocal(QListWidgetItem *item) {
    QFile::rename(QString::fromStdString(localPath + "/" + oldName),
            QString::fromStdString(localPath + "/" + item->text().toStdString())); // Переименование
}

/**
 * Переименован файл или директория на сервере.
 * 
 * @param item Файл или директория.
 */
void MainWindow::renamedRemote(QListWidgetItem *item) {
    pi->setPath(localPath + "/" + oldName);
    pi->setNewPath(localPath + "/" + item->text().toStdString());
    if (pi->sendCommand("RNFR")) {
        pi->sendCommand("RNTO");
    }
}

/**
 * Удаление выбранных файлов и директорий.
 */
void MainWindow::deleteFiles() {
    QList<QListWidgetItem*> files;
    string path;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        files = widget.localFiles->selectedItems();
        for (int i = 0; i < files.size(); i++) {
            path = files.at(i)->text().toStdString();
            if (fs.isFile(localPath + "/" + path)) {
                if (fs.deleteFile(localPath + "/" + path)) {
                    service->printMessage(1, "File '" + localPath + "/" + path + "' successfully removed.");
                } else {
                    service->printMessage(1, "File '" + localPath + "/" + path + "' was not removed.");
                }
            } else {
                if (fs.deleteDirectory(localPath + "/" + files.at(i)->text().toStdString())) {
                    service->printMessage(1, "Folder '" + localPath + "/" + path + "' successfully removed.");
                } else {
                    service->printMessage(1, "Folder '" + localPath + "/" + path + "' was not removed.");
                }
            }
        }
        getLocalFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        for (int i = 0; i < widget.remoteFiles->selectedItems().size(); i++) {
            path = widget.remoteFiles->selectedItems().at(i)->text().toStdString();
            if (widget.remoteFiles->selectedItems().at(i)->type()) { // Файл
                pi->setPath(remotePath + "/" + path);
                if (pi->sendCommand("DELE")) {
                    service->printMessage(1, "File '" + remotePath + "/" + path + "' successfully removed.");
                } else {
                    service->printMessage(1, "File '" + localPath + "/" + path + "' was not removed.");
                }
            } else { // Директория
                if (deleteRemoteFolder(remotePath + "/" + path)) {
                    service->printMessage(1, "Folder '" + remotePath + "/" + path + "' successfully removed.");
                } else {
                    service->printMessage(1, "Folder '" + remotePath + "/" + path + "' was not removed.");
                }
            }
        }
        getRemoteFileList();
    } else {
        QMessageBox::information(this, "Information", "You should select a file or directory!");
    }
}

/**
 * Создание директорий.
 */
void MainWindow::makeDir() {
    string name;
    bool ok;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        name = QInputDialog::getText(this, "Enter directory's name",
                "Name:", QLineEdit::Normal, QDir::home().dirName(), &ok).toStdString();
        if (!ok || name.empty()) {
            return;
        }
        fs.makeDirectory(localPath + "/" + name);
        getLocalFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        name = QInputDialog::getText(this, "Enter directory's name",
                "Name:", QLineEdit::Normal, QDir::home().dirName(), &ok).toStdString();
        if (!ok || name.empty()) {
            return;
        }
        pi->setPath(remotePath + "/" + name);
        pi->sendCommand("MKD");
        getRemoteFileList();
    } else {
        QMessageBox::information(this, "Information", "You should select a file or directory!");
    }
}

/**
 * Вывести список локальных файлов и каталогов в текущей директории.
 */
void MainWindow::getLocalFileList() {
    list<string> files;
    
    widget.localFiles->clear();
    files = fs.getFileNames(localPath);
    files.sort();
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        if (*iter == "..") {
            widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/up.ico"),
                    QString::fromStdString(*iter)));
        } else {
            if (fs.isFile(localPath + "/" + *iter)) {
                widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/file.ico"),
                        QString::fromStdString(*iter)));
            } else {
                widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/folder.ico"),
                        QString::fromStdString(*iter)));
            }
        }
    }
}

/**
 * Вывести список файлов и каталогов сервера в текущей директории.
 */
void MainWindow::getRemoteFileList() {
    int passive;
    list<string> nameList;
    list<string> fullList;
    
    widget.remoteFiles->clear();
    if (nestingCounter) {
        widget.remoteFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/up.ico"), ".."));
    }
    passive = options.getParameter("modes", "passive", 1);
    pi->setPassive(passive);
    if (passive) {
        pi->sendCommand("PASV");
    } else {
        pi->sendCommand("PORT");
    }
    pi->setPath("#");
    if (pi->sendCommand("LIST")) {
        fullList = pi->getFileList();
        if (passive) {
            pi->sendCommand("PASV");
        } else {
            pi->sendCommand("PORT");
        }
        if (pi->sendCommand("NLST")) {
            nameList = pi->getFileList();
            list<string>::iterator fullIter = fullList.begin();
            for (list<string>::iterator iterator = nameList.begin(); iterator != nameList.end(); ++iterator) {
                if ((*fullIter)[0] == 'd') {
                    widget.remoteFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/folder.ico"),
                            QString::fromStdString(*iterator), 0, 0));
                } else {
                    widget.remoteFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/file.ico"),
                            QString::fromStdString(*iterator), 0, 1));
                }
                fullIter++;
            }
            widget.actionConnect->setDisabled(true); // Деактивируем кнопку
        }
    } else {
        widget.remoteFiles->addItem("Directory is empty.");
    }
}

/**
 * Отправить каталог на сервер.
 * 
 * @param path Путь до каталога.
 */
void MainWindow::storeFolder(string path) {
    list<string> files;
    int passive;
    int pos;
    
    files = fs.getFileNames(path);
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        if (fs.isFile(path + "/" + *iter)) {
            passive = options.getParameter("modes", "passive", 1);
            pi->setPassive(passive);
            if (passive) {
                pi->sendCommand("PASV");
            } else {
                pi->sendCommand("PORT");
            }
            pi->setLocalPath(path + "/" + *iter);
            pi->setPath(remotePath + "/" + *iter);
            pi->sendCommand("STOR");
        } else {
            if (*iter != "..") {
                // Создаем каталог и переходим в него
                pi->setPath(*iter);
                pi->sendCommand("MKD");
                pi->sendCommand("CWD");
                remotePath += "/" + *iter;
                storeFolder(path + "/" + *iter); // Отправка содержимого текущего каталога
                // Возвращение в исходный каталог
                pi->setPath(remotePath + "/..");
                pi->sendCommand("CWD");
                pos = remotePath.find_last_of("/", remotePath.length());
                remotePath.erase(pos, remotePath.length() - pos);
            }
        }
    }
}

/**
 * Скопировать с сервера содержимое каталога.
 * 
 * @param path Путь до каталога, который копируется.
 */
void MainWindow::retrieveFolder(string path) {
    list<string> files;
    list<string> fullList;
    int passive;
    int pos;
    
    passive = options.getParameter("modes", "passive", 1);
    if (passive) {
        pi->sendCommand("PASV");
    } else {
        pi->sendCommand("PORT");
    }
    pi->setPath(path);
    if (pi->sendCommand("LIST")) {
        fullList = pi->getFileList();
        if (passive) {
            pi->sendCommand("PASV");
        } else {
            pi->sendCommand("PORT");
        }
        if (pi->sendCommand("NLST")) {
            files = pi->getFileList();
            list<string>::iterator fullListIter = fullList.begin();
            for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
                if ((*fullListIter)[0] == 'd') { // Директория
                    // Создаем каталог и переходим в него
                    if (fs.makeDirectory(localPath + "/" + *iter)) {
                        localPath += "/" + *iter;
                    }
                    // Копирование содержимого выбранного каталога
                    remotePath += "/" + *iter;
                    pi->setPath(remotePath);
                    pi->sendCommand("CWD");
                    retrieveFolder(remotePath);
                    pos = remotePath.find_last_of("/", remotePath.length());
                    remotePath.erase(pos, remotePath.length() - pos);
                    pi->setPath("..");
                    pi->sendCommand("CWD");
                    // Возвращение в исходный каталог
                    pos = localPath.find_last_of("/", localPath.length());
                    localPath.erase(pos, localPath.length() - pos);
                } else { // Файл
                    pi->setPassive(passive);
                    if (passive) {
                        pi->sendCommand("PASV");
                    } else {
                        pi->sendCommand("PORT");
                    }
                    pi->setLocalPath(localPath + "/" + *iter);
                    pi->setPath(path + "/" + *iter);
                    pi->sendCommand("RETR");
                }
                fullListIter++;
            }
        }
    }
}

/**
 * Рекурсивное удаление содержимого директорий.
 * 
 * @param path Имя директории.
 * 
 * @return 0 -не удалось удалить, другое - успешно удалена.
 */
int MainWindow::deleteRemoteFolder(string path) {
    list<string> files;
    list<string> fullList;
    int passive;
    int success = 1;

    pi->setPath(path);
    pi->sendCommand("CWD");
    passive = options.getParameter("modes", "passive", 1);
    if (passive) {
        pi->sendCommand("PASV");
    } else {
        pi->sendCommand("PORT");
    }
    if (pi->sendCommand("LIST")) {
        fullList = pi->getFileList();
        if (passive) {
            pi->sendCommand("PASV");
        } else {
            pi->sendCommand("PORT");
        }
        if (pi->sendCommand("NLST")) {
            files = pi->getFileList();
            list<string>::iterator fullListIter = fullList.begin();
            for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
                if ((*fullListIter)[0] == 'd') { // Директория
                    if (deleteRemoteFolder(path + "/" + *iter)) {
                        service->printMessage(1, "Folder '" + path + "/" + *iter + "' successfully removed.");
                    } else {
                        service->printMessage(1, "Folder '" + path + "/" + *iter + "' was not removed.");
                        success = 0;
                    }
                } else { // Файл
                    pi->setPath(path + "/" + *iter);
                    if (pi->sendCommand("DELE")) {
                        service->printMessage(1, "File '" + path + "/" + *iter + "' successfully removed.");
                    } else {
                        service->printMessage(1, "File '" + path + "/" + *iter + "' was not removed.");
                        success = 0;
                    }
                }
                fullListIter++;
            }
        }
    }
    pi->setPath("..");
    pi->sendCommand("CWD");
    if (success) {
        pi->setPath(path);
        return (pi->sendCommand("RMD"));
    } else {
        return 0;
    }
}

/**
 * Сохранение параметров в конфиг и освобождение памяти.
 */
MainWindow::~MainWindow() {
    options.setParameter("paths", "globalEntity", globalEntity);
    options.setParameter("paths", "localPath", localPath);
    
    delete pi;
    delete csWindow;
    delete service;
}
