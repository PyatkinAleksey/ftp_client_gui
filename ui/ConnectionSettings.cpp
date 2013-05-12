/*
 * File:   ConnectionSettings.cpp
 * Author: Aleksey Pyatkin
 *
 * Created on 12.05.2013, 0:17
 */

#include "ConnectionSettings.h"

ConnectionSettings::ConnectionSettings() {
    widget.setupUi(this);
    getValues();
}

void ConnectionSettings::getValues() {
    string parameter;
    
    widget.address->setText(QString::fromStdString(options.getParameter("connection", "address", "127.0.0.1")));
    widget.username->setText(QString::fromStdString(options.getParameter("connection", "user", "anonymous")));
    widget.password->setText(QString::fromStdString(options.getParameter("connection", "password", "")));
    parameter = options.getParameter("modes", "type", "A N");
    if (parameter == "A N") {
        widget.type->setCurrentIndex(0);
    } else {
        widget.type->setCurrentIndex(0); // По-умолчанию - тип ASCII Non-Print
    }
    parameter = options.getParameter("modes", "mode", "S");
    if (parameter == "S") {
        widget.mode->setCurrentIndex(0);
    } else {
        widget.mode->setCurrentIndex(0); // По-умолчанию - поточный режим
    }
    parameter = options.getParameter("modes", "structure", "F");
    if (parameter == "F") {
        widget.structure->setCurrentIndex(0);
    } else if (parameter == "R") {
        widget.structure->setCurrentIndex(1);
    } else {
        widget.structure->setCurrentIndex(0); // По-умолчанию - структура File
    }
    if (options.getParameter("modes", "passive", 1)) {
        widget.passive->setChecked(true);
    } else {
        widget.passive->setChecked(false);
    }
}

void ConnectionSettings::accept() {
    options.setParameter("connection", "address", widget.address->text().toStdString());
    options.setParameter("connection", "user", widget.username->text().toStdString());
    options.setParameter("connection", "password", widget.password->text().toStdString());
    switch (widget.type->currentIndex()) {
        case 0:
            options.setParameter("modes", "type", "A N");
            break;
        default:
            options.setParameter("modes", "type", "A N");
            break;
    }
    switch (widget.mode->currentIndex()) {
        case 0:
            options.setParameter("modes", "mode", "S");
            break;
        default:
            options.setParameter("modes", "mode", "S");
            break;
    }
    switch (widget.structure->currentIndex()) {
        case 0:
            options.setParameter("modes", "structure", "F");
            break;
        case 1:
            options.setParameter("modes", "structure", "R");
            break;
        default:
            options.setParameter("modes", "structure", "F");
            break;
    }
    if (widget.passive->checkState() == Qt::Checked) {
        options.setParameter("modes", "passive", 1);
    } else {
        options.setParameter("modes", "passive", 0);
    }
    this->close();
}

ConnectionSettings::~ConnectionSettings() {
}
