/********************************************************************************
** Form generated from reading UI file 'ConnectionSettings.ui'
**
** Created: Sat 25. May 20:39:52 2013
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTIONSETTINGS_H
#define UI_CONNECTIONSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_ConnectionSettings
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *connection;
    QLineEdit *address;
    QLabel *labelAddress;
    QLabel *labelUsername;
    QLineEdit *username;
    QLabel *labelPassword;
    QLineEdit *password;
    QGroupBox *modes;
    QLabel *labelType;
    QComboBox *type;
    QLabel *labelMode;
    QComboBox *mode;
    QLabel *labelStructure;
    QComboBox *structure;
    QCheckBox *passive;

    void setupUi(QDialog *ConnectionSettings)
    {
        if (ConnectionSettings->objectName().isEmpty())
            ConnectionSettings->setObjectName(QString::fromUtf8("ConnectionSettings"));
        ConnectionSettings->setWindowModality(Qt::ApplicationModal);
        ConnectionSettings->resize(400, 318);
        ConnectionSettings->setModal(true);
        buttonBox = new QDialogButtonBox(ConnectionSettings);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(50, 280, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        connection = new QGroupBox(ConnectionSettings);
        connection->setObjectName(QString::fromUtf8("connection"));
        connection->setGeometry(QRect(10, 10, 381, 111));
        address = new QLineEdit(connection);
        address->setObjectName(QString::fromUtf8("address"));
        address->setGeometry(QRect(90, 20, 281, 20));
        labelAddress = new QLabel(connection);
        labelAddress->setObjectName(QString::fromUtf8("labelAddress"));
        labelAddress->setGeometry(QRect(20, 20, 46, 13));
        labelUsername = new QLabel(connection);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));
        labelUsername->setGeometry(QRect(20, 50, 61, 16));
        username = new QLineEdit(connection);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(90, 50, 151, 20));
        labelPassword = new QLabel(connection);
        labelPassword->setObjectName(QString::fromUtf8("labelPassword"));
        labelPassword->setGeometry(QRect(20, 80, 51, 16));
        password = new QLineEdit(connection);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(90, 80, 151, 20));
        modes = new QGroupBox(ConnectionSettings);
        modes->setObjectName(QString::fromUtf8("modes"));
        modes->setGeometry(QRect(10, 130, 381, 141));
        labelType = new QLabel(modes);
        labelType->setObjectName(QString::fromUtf8("labelType"));
        labelType->setGeometry(QRect(20, 20, 46, 13));
        type = new QComboBox(modes);
        type->setObjectName(QString::fromUtf8("type"));
        type->setGeometry(QRect(90, 20, 111, 22));
        labelMode = new QLabel(modes);
        labelMode->setObjectName(QString::fromUtf8("labelMode"));
        labelMode->setGeometry(QRect(20, 50, 46, 13));
        mode = new QComboBox(modes);
        mode->setObjectName(QString::fromUtf8("mode"));
        mode->setGeometry(QRect(90, 50, 111, 22));
        labelStructure = new QLabel(modes);
        labelStructure->setObjectName(QString::fromUtf8("labelStructure"));
        labelStructure->setGeometry(QRect(20, 80, 46, 13));
        structure = new QComboBox(modes);
        structure->setObjectName(QString::fromUtf8("structure"));
        structure->setGeometry(QRect(90, 80, 111, 22));
        passive = new QCheckBox(modes);
        passive->setObjectName(QString::fromUtf8("passive"));
        passive->setGeometry(QRect(20, 110, 111, 17));
        passive->setChecked(false);
        passive->setTristate(false);

        retranslateUi(ConnectionSettings);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConnectionSettings, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConnectionSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConnectionSettings);
    } // setupUi

    void retranslateUi(QDialog *ConnectionSettings)
    {
        ConnectionSettings->setWindowTitle(QApplication::translate("ConnectionSettings", "ConnectionSettings", 0, QApplication::UnicodeUTF8));
        connection->setTitle(QApplication::translate("ConnectionSettings", "Connection settings", 0, QApplication::UnicodeUTF8));
        address->setText(QString());
        labelAddress->setText(QApplication::translate("ConnectionSettings", "Address:", 0, QApplication::UnicodeUTF8));
        labelUsername->setText(QApplication::translate("ConnectionSettings", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Username:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        labelPassword->setText(QApplication::translate("ConnectionSettings", "Password:", 0, QApplication::UnicodeUTF8));
        modes->setTitle(QApplication::translate("ConnectionSettings", "Modes", 0, QApplication::UnicodeUTF8));
        labelType->setText(QApplication::translate("ConnectionSettings", "Type:", 0, QApplication::UnicodeUTF8));
        type->clear();
        type->insertItems(0, QStringList()
         << QApplication::translate("ConnectionSettings", "ASCII Non-Print", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConnectionSettings", "Image", 0, QApplication::UnicodeUTF8)
        );
        labelMode->setText(QApplication::translate("ConnectionSettings", "Mode:", 0, QApplication::UnicodeUTF8));
        mode->clear();
        mode->insertItems(0, QStringList()
         << QApplication::translate("ConnectionSettings", "Stream", 0, QApplication::UnicodeUTF8)
        );
        labelStructure->setText(QApplication::translate("ConnectionSettings", "Structure:", 0, QApplication::UnicodeUTF8));
        structure->clear();
        structure->insertItems(0, QStringList()
         << QApplication::translate("ConnectionSettings", "File", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ConnectionSettings", "Record", 0, QApplication::UnicodeUTF8)
        );
        passive->setText(QApplication::translate("ConnectionSettings", "Passive mode", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectionSettings: public Ui_ConnectionSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTIONSETTINGS_H
