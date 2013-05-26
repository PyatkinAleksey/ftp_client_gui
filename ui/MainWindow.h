/* 
 * File:   MainWindow.h
 * Author: Aleksey Pyatkin
 *
 * Created on 11.05.2013, 23:22
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <list>
#include <QtGui/QInputDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include "../Service.h"
#include "../Options.h"
#include "../ProtocolInterpreter.h"
#include "ConnectionSettings.h"
#include "AboutProgram.h"
#include "ui_MainWindow.h"

/**
 * Класс, описывающий главное окно приложения.
 */
class MainWindow : public QMainWindow {
    
    Q_OBJECT
    
    public:
        MainWindow(ConnectionSettings *csw);    // Инициализация приложения
        virtual ~MainWindow();                  // Сохранение параметров и освобождение памяти
        
    private slots:
        void openPath(QString item);                // Вывод списка файлов и каталогов при выборе диска
        void openPath(QListWidgetItem *item);       // Вывод списка файлов и директорий при навигации по каталогам
        void openRemotePath(QListWidgetItem *item); // Вывод списка файлов и директорий при навигации по каталогам сервера
        void ftpConnect();                          // Осуществление соединения и получения списка файлов и директорий корневого каталога
        void copy();                                // Копирование файлов и директорий
        void rename();                              // Переименование файла или директории
        void renamedLocal(QListWidgetItem *item);   // Переименован локальный файл или директория
        void renamedRemote(QListWidgetItem *item);  // Переименован файл или директория на сервере
        void deleteFiles();                         // Удаление файлов и директорий
        void makeDir();                             // Создание директорий
        
    private:
        Ui::MainWindow widget;          // Виджет главного окна
        Service *service;               // Указатель на объект сервисного класса
        Options options;                // Объект класса для получения свойств из конфига
        ProtocolInterpreter *pi;        // Указатель на объект интерпретатора протокола
        ConnectionSettings *csWindow;   // Указатель на окно свойств соединения
        AboutProgram *apWindow;         // Указатель на окно "О программе"
        QString drive;                  // Глобальная сущность
        QDir currentDir;                // Текущая директория
        QString remotePath;             // Путь на сервере
        int passive;                    // Пассивный режим
        int nestingCounter;             // Счетчик вложенности каталогов для определения корневой директории сервера
        QString oldName;                // Старое имя файла для операции переименования

        void cdUpRemote();                      // Подняться по дереву каталогов сервера
        void getLocalFileList();                // Вывести список локальных файлов и каталогов в текущей директории
        void getRemoteFileList();               // Вывести список файлов и каталогов сервера в текущей директории
        void storeFolder();                     // Отправить каталог на сервер
        void retrieveFolder(string path);       // Скопировать каталог с сервера
        int deleteLocalFolder();                // Рекурсивно удалить директорию
        int deleteRemoteFolder(string path);    // Рекурсивно удалить директорию на сервере
        
};

#endif	/* _MAINWINDOW_H */
