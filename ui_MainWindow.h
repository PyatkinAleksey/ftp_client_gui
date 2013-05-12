/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Sun 12. May 12:11:23 2013
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionExit;
    QAction *actionConnectionSettings;
    QAction *actionManual;
    QAction *actionAboutProgram;
    QWidget *centralwidget;
    QMenuBar *mainMenu;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionConnectionSettings = new QAction(MainWindow);
        actionConnectionSettings->setObjectName(QString::fromUtf8("actionConnectionSettings"));
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName(QString::fromUtf8("actionManual"));
        actionAboutProgram = new QAction(MainWindow);
        actionAboutProgram->setObjectName(QString::fromUtf8("actionAboutProgram"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        mainMenu = new QMenuBar(MainWindow);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        mainMenu->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(mainMenu);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOptions = new QMenu(mainMenu);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(mainMenu);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(mainMenu);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        mainMenu->addAction(menuFile->menuAction());
        mainMenu->addAction(menuOptions->menuAction());
        mainMenu->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionConnectionSettings);
        menuHelp->addAction(actionManual);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAboutProgram);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "FTP-client", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionConnectionSettings->setText(QApplication::translate("MainWindow", "Connection settings", 0, QApplication::UnicodeUTF8));
        actionManual->setText(QApplication::translate("MainWindow", "Manual", 0, QApplication::UnicodeUTF8));
        actionAboutProgram->setText(QApplication::translate("MainWindow", "About program", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
