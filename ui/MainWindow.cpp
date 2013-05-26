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
    QFileInfoList drives;
    int i;

    widget.setupUi(this);
    pi = new ProtocolInterpreter();
    service = new Service();
    drive = QString::fromStdString(options.getParameter("paths", "drive", QDir::rootPath().toStdString()));
    currentDir = QDir(QString::fromStdString(options.getParameter("paths", "localPath", drive.toStdString())));
    remotePath = "";
    passive = options.getParameter("modes", "passive", 1);
    service->setOutputArea(widget.logs);
    csWindow = csw;
    csWindow->setModal(true);
    apWindow = new AboutProgram();
    apWindow->setModal(true);
    drives = QDir::drives();
    i = 0;
    for (QFileInfoList::Iterator iter = drives.begin(); iter != drives.end(); iter++) {
        widget.drives->addItem((*iter).absoluteFilePath());
        if ((*iter).absoluteFilePath() == drive) {
            widget.drives->setCurrentIndex(i);
        }
        i++;
    }
    getLocalFileList();
    
    connect(widget.actionConnectionSettings, SIGNAL(triggered()), csWindow, SLOT(show()));
    connect(widget.drives, SIGNAL(currentIndexChanged(QString)), this, SLOT(openPath(QString)));
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
 * Вывод списка файлов и каталогов при выборе диска.
 * 
 * @param item Выбранный диск.
 */
void MainWindow::openPath(QString item) {
    currentDir = QDir(item);
    drive = item;
    getLocalFileList();
}

/**
 * Вывод списка файлов и директорий при навигации по каталогам.
 * 
 * @param item Выбранный каталог.
 */
void MainWindow::openPath(QListWidgetItem *item) {
    if (item->text() == "..") {
        currentDir.cdUp();
    } else {
        currentDir.cd(item->text());
    }
    getLocalFileList();
}

/**
 * Вывод списка файлов и директорий при навигации по каталогам сервера.
 * 
 * @param item Выбранный каталог.
 */
void MainWindow::openRemotePath(QListWidgetItem* item) {
    if (item->text() == "..") {
        nestingCounter--;
        cdUpRemote();
    } else {
        nestingCounter++;
        remotePath += "/" + item->text();
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
    QString fileName;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        for (int i = 0; i < widget.localFiles->selectedItems().size(); i++) {
            fileName = widget.localFiles->selectedItems().at(i)->text();
            QFileInfo file(currentDir.absolutePath() + QDir::separator() + fileName);
            if (file.isFile()) {
                pi->setPassive(passive);
                if (passive) {
                    pi->sendCommand("PASV");
                } else {
                    pi->sendCommand("PORT");
                }
                pi->setLocalPath(file.absoluteFilePath().toStdString());
                pi->setPath((remotePath + "/" + fileName).toStdString());
                pi->sendCommand("STOR");
            } else {
                // Создаем каталог и переходим в него
                pi->setPath((remotePath + "/" + fileName).toStdString());
                pi->sendCommand("MKD");
                pi->sendCommand("CWD");
                remotePath += "/" + fileName;
                currentDir.cd(fileName);
                storeFolder(); // Отправка содержимого выбранного каталога
                // Возвращение в исходный каталог
                pi->setPath("..");
                pi->sendCommand("CWD");
                cdUpRemote();
            }
        }
        getRemoteFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        for (int i = 0; i < widget.remoteFiles->selectedItems().size(); i++) {
            fileName = widget.remoteFiles->selectedItems().at(i)->text();
            if (widget.remoteFiles->selectedItems().at(i)->type()) { // Файл
                pi->setPassive(passive);
                if (passive) {
                    pi->sendCommand("PASV");
                } else {
                    pi->sendCommand("PORT");
                }
                pi->setLocalPath((currentDir.absolutePath() + QDir::separator() + fileName).toStdString());
                pi->setPath((remotePath + "/" + fileName).toStdString());
                pi->sendCommand("RETR");
            } else { // Каталог
                // Создаем каталог и переходим в него
                currentDir.mkdir(fileName);
                currentDir.cd(fileName);
                // Копирование содержимого выбранного каталога
                remotePath += "/" + fileName;
                pi->setPath(remotePath.toStdString());
                pi->sendCommand("CWD");
                retrieveFolder(remotePath.toStdString());
                pi->setPath("..");
                pi->sendCommand("CWD");
                cdUpRemote();
                currentDir.cdUp(); // Возвращение в исходный каталог
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
        oldName = item->text();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        widget.localFiles->editItem(item);
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        QListWidgetItem *item = *widget.remoteFiles->selectedItems().begin();
        oldName = item->text();
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
    QFile::rename(currentDir.absolutePath() + QDir::separator() + oldName,
            currentDir.absolutePath() + QDir::separator() + item->text()); // Переименование
}

/**
 * Переименован файл или директория на сервере.
 * 
 * @param item Файл или директория.
 */
void MainWindow::renamedRemote(QListWidgetItem *item) {
    pi->setPath((remotePath + "/" + oldName).toStdString());
    pi->setNewPath((remotePath + "/" + item->text()).toStdString());
    if (pi->sendCommand("RNFR")) {
        pi->sendCommand("RNTO");
    }
}

/**
 * Удаление выбранных файлов и директорий.
 */
void MainWindow::deleteFiles() {
    QList<QListWidgetItem*> files;
    QString fileName;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        files = widget.localFiles->selectedItems();
        for (int i = 0; i < files.size(); i++) {
            fileName = files.at(i)->text();
            QFileInfo file(currentDir.absolutePath() + QDir::separator() + fileName);
            if (file.isFile()) {
                if (QFile::remove(file.absoluteFilePath())) {
                    service->printMessage(1, "File '" + file.absoluteFilePath().toStdString() + "' successfully removed.");
                } else {
                    service->printMessage(1, "File '" + file.absoluteFilePath().toStdString() + "' was not removed.");
                }
            } else {
                currentDir.cd(fileName);
                if (deleteLocalFolder()) {
                    service->printMessage(1, "Folder '" + currentDir.absolutePath().toStdString() + "' successfully removed.");
                } else {
                    service->printMessage(1, "Folder '" + currentDir.absolutePath().toStdString() + "' was not removed.");
                }
                currentDir.cdUp();
                currentDir.rmdir(fileName);
            }
        }
        getLocalFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        for (int i = 0; i < widget.remoteFiles->selectedItems().size(); i++) {
            fileName = widget.remoteFiles->selectedItems().at(i)->text();
            if (widget.remoteFiles->selectedItems().at(i)->type()) { // Файл
                pi->setPath((remotePath + "/" + fileName).toStdString());
                if (pi->sendCommand("DELE")) {
                    service->printMessage(1, "File '" + (remotePath + "/" + fileName).toStdString() + "' successfully removed.");
                } else {
                    service->printMessage(1, "File '" + (remotePath + "/" + fileName).toStdString() + "' was not removed.");
                }
            } else { // Директория
                if (deleteRemoteFolder((remotePath + "/" + fileName).toStdString())) {
                    service->printMessage(1, "Folder '" + (remotePath + "/" + fileName).toStdString() + "' successfully removed.");
                } else {
                    service->printMessage(1, "Folder '" + (remotePath + "/" + fileName).toStdString() + "' was not removed.");
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
    QString name;
    bool ok;
    
    if (this->focusWidget() == widget.localFiles) { // Выбран локальный файл или каталог
        name = QInputDialog::getText(this, "Enter directory's name",
                "Name:", QLineEdit::Normal, QDir::home().dirName(), &ok);
        if (!ok || name.isEmpty()) {
            return;
        }
        currentDir.mkdir(name);
        getLocalFileList();
    } else if (this->focusWidget() == widget.remoteFiles) { // Выбран удаленный файл или каталог
        name = QInputDialog::getText(this, "Enter directory's name",
                "Name:", QLineEdit::Normal, QDir::home().dirName(), &ok);
        if (!ok || name.isEmpty()) {
            return;
        }
        pi->setPath((remotePath + "/" + name).toStdString());
        pi->sendCommand("MKD");
        getRemoteFileList();
    } else {
        QMessageBox::information(this, "Information", "You should select a file or directory!");
    }
}

/**
 * Перейти к родительской директории сервера.
 */
void MainWindow::cdUpRemote() {
    int pos = remotePath.lastIndexOf("/");
    remotePath.remove(pos+1, remotePath.length() - pos);
}

/**
 * Вывести список локальных файлов и каталогов в текущей директории.
 */
void MainWindow::getLocalFileList() {
    QStringList files;
    
    widget.localFiles->clear();
    files = currentDir.entryList(QStringList("*"), QDir::Files | QDir::Dirs, QDir::Name);
    for (int i = 0; i != files.size(); i++) {
        if (files.at(i) != ".") {
            if (files.at(i) == "..") {
                widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/up.ico"), files.at(i)));
            } else {
                QFileInfo fi(currentDir.absolutePath() + QDir::separator() + files.at(i));
                if (fi.isFile()) {
                    widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/file.ico"), files.at(i)));
                } else {
                    widget.localFiles->addItem(new QListWidgetItem(QIcon(":/Content/images/folder.ico"), files.at(i)));
                }
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
 */
void MainWindow::storeFolder() {
    QStringList files;
    
    files = currentDir.entryList(QStringList("*"), QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i != files.size(); i++) {
        QFileInfo file(currentDir.absolutePath() + QDir::separator() + files.at(i));
        if (file.isFile()) {
            pi->setPassive(passive);
            if (passive) {
                pi->sendCommand("PASV");
            } else {
                pi->sendCommand("PORT");
            }
            pi->setLocalPath(file.absoluteFilePath().toStdString());
            pi->setPath((remotePath + "/" + files.at(i)).toStdString());
            pi->sendCommand("STOR");
        } else {
            currentDir.cd(files.at(i));
            // Создаем каталог и переходим в него
            pi->setPath(files.at(i).toStdString());
            pi->sendCommand("MKD");
            pi->sendCommand("CWD");
            remotePath += "/" + files.at(i);
            storeFolder(); // Отправка содержимого текущего каталога
            // Возвращение в исходный каталог
            pi->setPath("..");
            pi->sendCommand("CWD");
            cdUpRemote();
            currentDir.cdUp();
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
                    currentDir.mkdir(QString::fromStdString(*iter));
                    currentDir.cd(QString::fromStdString(*iter));
                    // Копирование содержимого выбранного каталога
                    remotePath += "/" + QString::fromStdString(*iter);
                    pi->setPath(remotePath.toStdString());
                    pi->sendCommand("CWD");
                    retrieveFolder(remotePath.toStdString());
                    cdUpRemote();
                    pi->setPath("..");
                    pi->sendCommand("CWD");
                    // Возвращение в исходный каталог
                    currentDir.cdUp();
                } else { // Файл
                    pi->setPassive(passive);
                    if (passive) {
                        pi->sendCommand("PASV");
                    } else {
                        pi->sendCommand("PORT");
                    }
                    pi->setLocalPath((currentDir.absolutePath() + QDir::separator()).toStdString() + *iter);
                    pi->setPath(path + "/" + *iter);
                    pi->sendCommand("RETR");
                }
                fullListIter++;
            }
        }
    }
}

/**
 * Рекурсивно удалить содержимое локальной директории.
 * 
 * @return 0 - не удалена, другое - удалена.
 */
int MainWindow::deleteLocalFolder() {
    QStringList files;
    int success = 1;
    
    files = currentDir.entryList(QStringList("*"), QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
    for (int i = 0; i < files.size(); i++) {
        QFileInfo file(currentDir.absolutePath() + QDir::separator() + files.at(i));
        if (file.isFile()) {
            if (QFile::remove(file.absoluteFilePath())) {
                service->printMessage(1, "File '" + file.absoluteFilePath().toStdString() + "' successfully removed.");
            } else {
                service->printMessage(1, "File '" + file.absoluteFilePath().toStdString() + "' was not removed.");
                success = 0;
            }
        } else {
            currentDir.cd(files.at(i));
            if (deleteLocalFolder()) {
                service->printMessage(1, "Folder '" + currentDir.absoluteFilePath(files.at(i)).toStdString() + "' successfully removed.");
            } else {
                service->printMessage(1, "Folder '" + currentDir.absoluteFilePath(files.at(i)).toStdString() + "' was not removed.");
                success = 0;
            }
            currentDir.cdUp();
            if (!currentDir.rmdir(files.at(i))) {
                success = 0;
            }
        }
    }
    if (success) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * Рекурсивное удаление содержимого директорий на сервере.
 * 
 * @param path Имя директории.
 * 
 * @return 0 -не удалось удалить, другое - успешно удалена.
 */
int MainWindow::deleteRemoteFolder(string path) {
    list<string> files;
    list<string> fullList;
    int success = 1;

    pi->setPath(path);
    pi->sendCommand("CWD");
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
    options.setParameter("paths", "drive", drive.toStdString());
    options.setParameter("paths", "localPath", currentDir.absolutePath().toStdString());
    
    delete pi;
    delete csWindow;
    delete service;
}
