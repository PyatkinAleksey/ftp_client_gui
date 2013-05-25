# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/MinGW-Windows
TARGET = ftp-client
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui
SOURCES += FileSystem.cpp Options.cpp ProtocolInterpreter.cpp Service.cpp UserDTP.cpp main.cpp ui/AboutProgram.cpp ui/ConnectionSettings.cpp ui/MainWindow.cpp
HEADERS += FileSystem.h Options.h ProtocolInterpreter.h Service.h UserDTP.h ui/AboutProgram.h ui/ConnectionSettings.h ui/MainWindow.h
FORMS += ui/AboutProgram.ui ui/ConnectionSettings.ui ui/MainWindow.ui
RESOURCES += Icons.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += . 
LIBS += -lws2_32  
