/****************************************************************************
** Meta object code from reading C++ file 'cpumonitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Lox1/cpumonitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cpumonitor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CpuMonitor_t {
    QByteArrayData data[7];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CpuMonitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CpuMonitor_t qt_meta_stringdata_CpuMonitor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CpuMonitor"
QT_MOC_LITERAL(1, 11, 11), // "getCpuUsage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "getCores"
QT_MOC_LITERAL(4, 33, 11), // "getCoreName"
QT_MOC_LITERAL(5, 45, 1), // "i"
QT_MOC_LITERAL(6, 47, 12) // "getCoreUsage"

    },
    "CpuMonitor\0getCpuUsage\0\0getCores\0"
    "getCoreName\0i\0getCoreUsage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CpuMonitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x02 /* Public */,
       3,    0,   35,    2, 0x02 /* Public */,
       4,    1,   36,    2, 0x02 /* Public */,
       6,    1,   39,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,    5,
    QMetaType::Double, QMetaType::Int,    5,

       0        // eod
};

void CpuMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CpuMonitor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getCpuUsage(); break;
        case 1: { int _r = _t->getCores();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { QString _r = _t->getCoreName((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 3: { double _r = _t->getCoreUsage((*reinterpret_cast< const int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CpuMonitor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CpuMonitor.data,
    qt_meta_data_CpuMonitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CpuMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CpuMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CpuMonitor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CpuMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
