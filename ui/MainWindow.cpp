/*
 * File:   MainWindow.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#include "MainWindow.h"

MainWindow::MainWindow(ConnectionSettings *csw) {
    list<string> globalEntities;
    
    widget.setupUi(this);
    csWindow = csw;
    csWindow->setModal(true);
    connect(widget.actionConnectionSettings, SIGNAL(triggered()), csWindow, SLOT(show()));
    globalEntities = fs.getGlobalEntities();
    for (list<string>::iterator iter = globalEntities.begin(); iter != globalEntities.end(); iter++) {
        widget.globalEntities->addItem(QString::fromStdString(*iter));
    }
}

MainWindow::~MainWindow() {
}
