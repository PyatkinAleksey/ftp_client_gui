/* 
 * File:   Service.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 09.05.2013, 0:55
 */

#include "Service.h"

// Элемент для вывода сообщений должен быть статическим, поскольку будет создано
// несколько экземпляров этого класса и все они должны будут работать с одним и тем же полем.
QTextBrowser* Service::browser = NULL;

/**
 * Установка элемента для вывода сообщений.
 * 
 * @param browser Элемент.
 */
void Service::setOutputArea(QTextBrowser *browser) {
    this->browser = browser;
}

/**
 * Вывод сообщений на экран.
 * 
 * @param type Тип сообщений (0 - простой вывод, 1 - информационное сообщение,
 *      2 - ошибка, 3 - ввод информации).
 * @param message Сообщение для вывода.
 */
void Service::printMessage(int type, string message) {
    switch (type) {
        case 0:
            browser->append(QString::fromStdString(message));
            break;
        case 1:
            browser->append(QString::fromStdString("Info: " + message + "\n"));
            break;
        case 2:
            browser->append(QString::fromStdString("Error: " + message + "\n"));
            break;
        case 3:
            browser->append(QString::fromStdString("> " + message + "\n" + "> "));
            break;
        default: break;
    }
}