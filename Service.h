/* 
 * File:    Service.h
 * Author:  Aleksey Pyatkin
 *
 * Created on 09.05.2013, 0:52
 */

#pragma once

#include <string>
#include <QtGui/QTextBrowser>

using namespace std;

/**
 * Сервисный класс. Содержит методы, предназначенные для выполнения общих задач,
 * таких как вывод сообщений на экран в разных форматах и т.п.
 */
class Service {
    
    public:
        void setOutputArea(QTextBrowser *browser);      // Установка элемента, в который будут выводиться сообщения
        void printMessage(int type, string message);    // Вывод сообщений на экран
        
    private:
        static QTextBrowser *browser;   // Элемент для вывода сообщений
    
};