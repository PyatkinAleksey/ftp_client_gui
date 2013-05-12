/*
 * File:   main.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 20:03
 */

#include <QtGui/QApplication>
#include <QtCore/QTextCodec>
#include <windows.h>
#include <string.h>
#include <iostream>
#include "ui/MainWindow.h"
#include "ui/ConnectionSettings.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ConnectionSettings *csWindow = new ConnectionSettings();
    MainWindow mainWindow(csWindow);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1251"));
    mainWindow.showMaximized();

    return app.exec();
}
