/*
 * File:   MainWindow.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#include "MainWindow.h"

MainWindow::MainWindow(ConnectionSettings *csw) {
    list<string> globalEntities;
    int i;

    pi = new ProtocolInterpreter();
    service = new Service();
    globalEntity = options.getParameter("paths", "globalEntity", "A:");
    localPath = options.getParameter("paths", "localPath", globalEntity);
    widget.setupUi(this);
    service->setOutputArea(widget.logs);
    csWindow = csw;
    csWindow->setModal(true);
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
    connect(widget.actionConnect, SIGNAL(triggered()), this, SLOT(ftpConnect()));
}

void MainWindow::openPath(QString item) {
    list<string> files;
    
    widget.localFiles->clear();
    files = fs.getFileNames(item.toStdString());
    files.sort();
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        widget.localFiles->addItem(QString::fromStdString(*iter));
    }
    globalEntity = item.toStdString();
    localPath = globalEntity;
}

void MainWindow::openPath(QListWidgetItem *item) {
    list<string> files;
    string dir = item->text().toStdString();
    int pos;

    localPath += "/" + dir;
    widget.localFiles->clear();
    files = fs.getFileNames(localPath);
    files.sort();
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        widget.localFiles->addItem(QString::fromStdString(*iter));
    }
    if (dir == "..") {
        localPath.erase(localPath.find("/..", 0), 3);
        pos = localPath.find_last_of("/", localPath.length());
        localPath.erase(pos, localPath.length() - pos);
    }
}

void MainWindow::ftpConnect() {
    bool ok;
    string password;
    int passive;
    
    pi->setAddress(options.getParameter("connection", "address", "127.0.0.1"));
    pi->openControlConnection();
    pi->setUser(options.getParameter("connection", "user", "anonymous"));
    if (pi->sendCommand("USER") == 1) { // Требуется пароль
        if (options.getParameter("connection", "password", "") == "") { // В конфиге пароль не установлен
            password = QInputDialog::getText(this, "Enter your password",
                    "Password:", QLineEdit::Normal, QDir::home().dirName(), &ok).toStdString();
            if (!ok || password.empty()) {
                return;
            } else {
                widget.logs->setText("YES");
            }
        } else {
            password = options.getParameter("connection", "password", "");
        }
        pi->setPassword(password);
        pi->sendCommand("PASS");
    }
    passive = options.getParameter("modes", "passive", 1);
    pi->setPassive(passive);
    if (passive) {
        pi->sendCommand("PASV");
    } else {
        pi->sendCommand("PORT");
    }
    pi->setPath("#");
    if (pi->sendCommand("NLST")) {
        for (list<string>::iterator iterator = pi->fileList.begin();
                iterator != pi->fileList.end(); ++iterator) {
            widget.remoteFiles->addItem(QString::fromStdString(*iterator));
        }
        widget.actionConnect->setDisabled(true); // Деактивируем кнопку
    } else {
        widget.remoteFiles->addItem("Directory is empty.");
    }
}

MainWindow::~MainWindow() {
    options.setParameter("paths", "globalEntity", globalEntity);
    options.setParameter("paths", "localPath", localPath);
    
    delete pi;
    delete csWindow;
    delete service;
}
