/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Mon 13. May 00:35:20 2013
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
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
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
    QAction *actionCopy;
    QAction *actionRename;
    QAction *actionDelete;
    QAction *actionMakeDirectory;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QComboBox *globalEntities;
    QSplitter *verticalSplitter;
    QSplitter *horizontalSplitter;
    QListWidget *localFiles;
    QListWidget *remoteFiles;
    QTextBrowser *logs;
    QMenuBar *mainMenu;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuHelp;
    QMenu *menuActions;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(782, 663);
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Menu&Toolbar/images/connect.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnect->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Menu&Toolbar/images/exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionConnectionSettings = new QAction(MainWindow);
        actionConnectionSettings->setObjectName(QString::fromUtf8("actionConnectionSettings"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Menu&Toolbar/images/settings.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionConnectionSettings->setIcon(icon2);
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName(QString::fromUtf8("actionManual"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Menu&Toolbar/images/manual.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionManual->setIcon(icon3);
        actionAboutProgram = new QAction(MainWindow);
        actionAboutProgram->setObjectName(QString::fromUtf8("actionAboutProgram"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Menu&Toolbar/images/about_program.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionAboutProgram->setIcon(icon4);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Menu&Toolbar/images/copy.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon5);
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Menu&Toolbar/images/rename.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionRename->setIcon(icon6);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Menu&Toolbar/images/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon7);
        actionMakeDirectory = new QAction(MainWindow);
        actionMakeDirectory->setObjectName(QString::fromUtf8("actionMakeDirectory"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Menu&Toolbar/images/make_directory.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionMakeDirectory->setIcon(icon8);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        globalEntities = new QComboBox(centralwidget);
        globalEntities->setObjectName(QString::fromUtf8("globalEntities"));
        globalEntities->setMinimumSize(QSize(764, 0));

        gridLayout_2->addWidget(globalEntities, 0, 0, 1, 1);

        verticalSplitter = new QSplitter(centralwidget);
        verticalSplitter->setObjectName(QString::fromUtf8("verticalSplitter"));
        verticalSplitter->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(verticalSplitter->sizePolicy().hasHeightForWidth());
        verticalSplitter->setSizePolicy(sizePolicy);
        verticalSplitter->setOrientation(Qt::Vertical);
        horizontalSplitter = new QSplitter(verticalSplitter);
        horizontalSplitter->setObjectName(QString::fromUtf8("horizontalSplitter"));
        horizontalSplitter->setOrientation(Qt::Horizontal);
        localFiles = new QListWidget(horizontalSplitter);
        localFiles->setObjectName(QString::fromUtf8("localFiles"));
        horizontalSplitter->addWidget(localFiles);
        remoteFiles = new QListWidget(horizontalSplitter);
        remoteFiles->setObjectName(QString::fromUtf8("remoteFiles"));
        horizontalSplitter->addWidget(remoteFiles);
        verticalSplitter->addWidget(horizontalSplitter);
        logs = new QTextBrowser(verticalSplitter);
        logs->setObjectName(QString::fromUtf8("logs"));
        verticalSplitter->addWidget(logs);

        gridLayout_2->addWidget(verticalSplitter, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        mainMenu = new QMenuBar(MainWindow);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        mainMenu->setGeometry(QRect(0, 0, 782, 21));
        menuFile = new QMenu(mainMenu);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOptions = new QMenu(mainMenu);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuHelp = new QMenu(mainMenu);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuActions = new QMenu(mainMenu);
        menuActions->setObjectName(QString::fromUtf8("menuActions"));
        MainWindow->setMenuBar(mainMenu);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        mainMenu->addAction(menuFile->menuAction());
        mainMenu->addAction(menuActions->menuAction());
        mainMenu->addAction(menuOptions->menuAction());
        mainMenu->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionConnectionSettings);
        menuHelp->addAction(actionManual);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAboutProgram);
        menuActions->addAction(actionCopy);
        menuActions->addAction(actionRename);
        menuActions->addAction(actionDelete);
        menuActions->addSeparator();
        menuActions->addAction(actionMakeDirectory);
        toolBar->addAction(actionConnect);
        toolBar->addSeparator();
        toolBar->addAction(actionCopy);
        toolBar->addAction(actionRename);
        toolBar->addAction(actionDelete);
        toolBar->addSeparator();
        toolBar->addAction(actionMakeDirectory);

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
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCopy->setToolTip(QApplication::translate("MainWindow", "Copy files (F5)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCopy->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
        actionRename->setText(QApplication::translate("MainWindow", "Rename", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRename->setToolTip(QApplication::translate("MainWindow", "Rename file (F2)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRename->setShortcut(QApplication::translate("MainWindow", "F2", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("MainWindow", "Delete", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindow", "Delete files (Del)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));
        actionMakeDirectory->setText(QApplication::translate("MainWindow", "Make directory", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMakeDirectory->setToolTip(QApplication::translate("MainWindow", "Make directory (F7)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionMakeDirectory->setShortcut(QApplication::translate("MainWindow", "F7", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuActions->setTitle(QApplication::translate("MainWindow", "Actions", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
