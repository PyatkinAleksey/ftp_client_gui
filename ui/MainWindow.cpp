/*
 * File:   MainWindow.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#include "MainWindow.h"

MainWindow::MainWindow(ConnectionSettings *csw) {
    widget.setupUi(this);
    csWindow = csw;
    csWindow->setModal(true);
    connect(widget.actionConnectionSettings, SIGNAL(triggered()), csWindow, SLOT(show()));
}

MainWindow::~MainWindow() {
}
