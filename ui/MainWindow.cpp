/*
 * File:   MainWindow.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#include "MainWindow.h"

MainWindow::MainWindow(ConnectionSettings *csw) {
    list<string> globalEntities;
    string globalEntity;
    int i;
    
    widget.setupUi(this);
    csWindow = csw;
    csWindow->setModal(true);
    connect(widget.actionConnectionSettings, SIGNAL(triggered()), csWindow, SLOT(show()));
    globalEntity = options.getParameter("paths", "globalEntity", "A:");
    globalEntities = fs.getGlobalEntities();
    i = 0;
    for (list<string>::iterator iter = globalEntities.begin(); iter != globalEntities.end(); iter++) {
        widget.globalEntities->addItem(QString::fromStdString(*iter));
        if (*iter == globalEntity) {
            widget.globalEntities->setCurrentIndex(i);
        }
        i++;
    }
    connect(widget.globalEntities, SIGNAL(currentIndexChanged(QString)), this, SLOT(openPath(QString)));
    openPath(QString::fromStdString(globalEntity));
}

void MainWindow::openPath(QString item) {
    list<string> files;
    
    widget.localFiles->clear();
    files = fs.getFileNames(item.toStdString());
    files.sort();
    for (list<string>::iterator iter = files.begin(); iter != files.end(); iter++) {
        widget.localFiles->addItem(QString::fromStdString(*iter));
    }
}

MainWindow::~MainWindow() {
    options.setParameter("paths", "globalEntity",
            widget.globalEntities->itemText(widget.globalEntities->currentIndex()).toStdString());
}
