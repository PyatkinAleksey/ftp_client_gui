/*
 * File:   main.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 20:03
 */

#include <QtGui/QApplication>
#include <windows.h>
#include <string.h>
#include <iostream>
#include "ui/MainWindow.h"
#include "ui/ConnectionSettings.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ConnectionSettings *csWindow = new ConnectionSettings();
    MainWindow mainWindow(csWindow);

    mainWindow.show();

    return app.exec();
}
