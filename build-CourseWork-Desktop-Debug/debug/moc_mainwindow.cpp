/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Lox1/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 31), // "on_actionOpen_Process_triggered"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 24), // "on_actionClose_triggered"
QT_MOC_LITERAL(4, 69, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(5, 91, 32), // "on_tableWidget_cellDoubleClicked"
QT_MOC_LITERAL(6, 124, 3), // "row"
QT_MOC_LITERAL(7, 128, 6), // "column"
QT_MOC_LITERAL(8, 135, 21), // "on_procButton_clicked"
QT_MOC_LITERAL(9, 157, 10), // "UpdateLoad"
QT_MOC_LITERAL(10, 168, 19), // "on_vaButton_clicked"
QT_MOC_LITERAL(11, 188, 23), // "on_hardChoose_activated"
QT_MOC_LITERAL(12, 212, 5), // "index"
QT_MOC_LITERAL(13, 218, 20), // "on_ramButton_clicked"
QT_MOC_LITERAL(14, 239, 19), // "on_naButton_clicked"
QT_MOC_LITERAL(15, 259, 21), // "on_biosButton_clicked"
QT_MOC_LITERAL(16, 281, 24), // "on_batteryButton_clicked"
QT_MOC_LITERAL(17, 306, 21), // "on_mothButton_clicked"
QT_MOC_LITERAL(18, 328, 23) // "on_actionInfo_triggered"

    },
    "MainWindow\0on_actionOpen_Process_triggered\0"
    "\0on_actionClose_triggered\0"
    "on_pushButton_clicked\0"
    "on_tableWidget_cellDoubleClicked\0row\0"
    "column\0on_procButton_clicked\0UpdateLoad\0"
    "on_vaButton_clicked\0on_hardChoose_activated\0"
    "index\0on_ramButton_clicked\0"
    "on_naButton_clicked\0on_biosButton_clicked\0"
    "on_batteryButton_clicked\0on_mothButton_clicked\0"
    "on_actionInfo_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    2,   87,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    1,   95,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,
      15,    0,  100,    2, 0x08 /* Private */,
      16,    0,  101,    2, 0x08 /* Private */,
      17,    0,  102,    2, 0x08 /* Private */,
      18,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionOpen_Process_triggered(); break;
        case 1: _t->on_actionClose_triggered(); break;
        case 2: _t->on_pushButton_clicked(); break;
        case 3: _t->on_tableWidget_cellDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_procButton_clicked(); break;
        case 5: _t->UpdateLoad(); break;
        case 6: _t->on_vaButton_clicked(); break;
        case 7: _t->on_hardChoose_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_ramButton_clicked(); break;
        case 9: _t->on_naButton_clicked(); break;
        case 10: _t->on_biosButton_clicked(); break;
        case 11: _t->on_batteryButton_clicked(); break;
        case 12: _t->on_mothButton_clicked(); break;
        case 13: _t->on_actionInfo_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
