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

    globalEntity = options.getParameter("paths", "globalEntity", "A:");
    localPath = options.getParameter("paths", "localPath", globalEntity);
    widget.setupUi(this);
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
    
    localPath += "\\" + item->text().toStdString();
    widget.localFiles->clear();
    files = fs.getFileNames(localPath);
    files.sort();
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        widget.localFiles->addItem(QString::fromStdString(*iter));
    }
}

MainWindow::~MainWindow() {
    options.setParameter("paths", "globalEntity", globalEntity);
    options.setParameter("paths", "localPath", localPath);
}
