/********************************************************************************
** Form generated from reading UI file 'AboutProgram.ui'
**
** Created: Sat 25. May 20:28:35 2013
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTPROGRAM_H
#define UI_ABOUTPROGRAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutProgram
{
public:
    QDialogButtonBox *buttonBox;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutProgram)
    {
        if (AboutProgram->objectName().isEmpty())
            AboutProgram->setObjectName(QString::fromUtf8("AboutProgram"));
        AboutProgram->resize(342, 162);
        buttonBox = new QDialogButtonBox(AboutProgram);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 130, 321, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        textBrowser = new QTextBrowser(AboutProgram);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 321, 121));

        retranslateUi(AboutProgram);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutProgram, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutProgram);
    } // setupUi

    void retranslateUi(QDialog *AboutProgram)
    {
        AboutProgram->setWindowTitle(QApplication::translate("AboutProgram", "About program", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("AboutProgram", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">FTP-client v.1.0 rev.13</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Author:</span><span style=\" font-size:8pt;\"> Aleksey Pyatkin</span></p>\n"
"<p style=\" margin-top:0px; margin-b"
                        "ottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">E-Mail:</span><span style=\" font-size:8pt;\"> VitalAleksey@gmail.com</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:600;\">Repository:</span><span style=\" font-size:8pt;\"> </span><a href=\"https://github.com/PyatkinAleksey/ftp_client_gui\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">https://github.com/PyatkinAleksey/ftp_client_gui</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p align=\"right\" style=\" margin"
                        "-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\302\251 2013</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AboutProgram: public Ui_AboutProgram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTPROGRAM_H
