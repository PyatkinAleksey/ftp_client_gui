/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Sat 25. May 18:59:21 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ui/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   12,   11,   11, 0x08,
      35,   12,   11,   11, 0x08,
      62,   12,   11,   11, 0x08,
      95,   11,   11,   11, 0x08,
     108,   11,   11,   11, 0x08,
     115,   11,   11,   11, 0x08,
     124,   12,   11,   11, 0x08,
     155,   12,   11,   11, 0x08,
     187,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0item\0openPath(QString)\0"
    "openPath(QListWidgetItem*)\0"
    "openRemotePath(QListWidgetItem*)\0"
    "ftpConnect()\0copy()\0rename()\0"
    "renamedLocal(QListWidgetItem*)\0"
    "renamedRemote(QListWidgetItem*)\0"
    "deleteFiles()\0makeDir()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openPath((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: openPath((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: openRemotePath((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: ftpConnect(); break;
        case 4: copy(); break;
        case 5: rename(); break;
        case 6: renamedLocal((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: renamedRemote((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: deleteFiles(); break;
        case 9: makeDir(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
