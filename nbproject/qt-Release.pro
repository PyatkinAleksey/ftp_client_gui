# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW-Windows
TARGET = ftp-client
VERSION = 0.5
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui
SOURCES += Options.cpp ProtocolInterpreter.cpp Service.cpp UserDTP.cpp main.cpp ui/ConnectionSettings.cpp ui/MainWindow.cpp
HEADERS += Options.h ProtocolInterpreter.h Service.h UserDTP.h ui/ConnectionSettings.h ui/MainWindow.h
FORMS += ui/ConnectionSettings.ui ui/MainWindow.ui
RESOURCES += Icons.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /C/Qt/4.6.0/include /C/MinGW/include 
LIBS += -lws2_32  
