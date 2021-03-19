/****************************************************************************
** Meta object code from reading C++ file 'core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DevInfo_t {
    QByteArrayData data[1];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DevInfo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DevInfo_t qt_meta_stringdata_DevInfo = {
    {
QT_MOC_LITERAL(0, 0, 7) // "DevInfo"

    },
    "DevInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DevInfo[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void DevInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject DevInfo::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DevInfo.data,
    qt_meta_data_DevInfo,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DevInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DevInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DevInfo.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DevInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Core_t {
    QByteArrayData data[30];
    char stringdata0[327];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Core_t qt_meta_stringdata_Core = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Core"
QT_MOC_LITERAL(1, 5, 8), // "daqReady"
QT_MOC_LITERAL(2, 14, 0), // ""
QT_MOC_LITERAL(3, 15, 5), // "Ready"
QT_MOC_LITERAL(4, 21, 5), // "ready"
QT_MOC_LITERAL(5, 27, 12), // "stateChanged"
QT_MOC_LITERAL(6, 40, 5), // "State"
QT_MOC_LITERAL(7, 46, 5), // "state"
QT_MOC_LITERAL(8, 52, 10), // "msgDisplay"
QT_MOC_LITERAL(9, 63, 4), // "name"
QT_MOC_LITERAL(10, 68, 10), // "MsgBoxType"
QT_MOC_LITERAL(11, 79, 4), // "type"
QT_MOC_LITERAL(12, 84, 16), // "latencyAndUptime"
QT_MOC_LITERAL(13, 101, 7), // "latency"
QT_MOC_LITERAL(14, 109, 11), // "commTimeout"
QT_MOC_LITERAL(15, 121, 6), // "uptime"
QT_MOC_LITERAL(16, 128, 8), // "finished"
QT_MOC_LITERAL(17, 137, 14), // "on_startThread"
QT_MOC_LITERAL(18, 152, 11), // "on_openComm"
QT_MOC_LITERAL(19, 164, 4), // "port"
QT_MOC_LITERAL(20, 169, 12), // "on_closeComm"
QT_MOC_LITERAL(21, 182, 5), // "force"
QT_MOC_LITERAL(22, 188, 10), // "on_dispose"
QT_MOC_LITERAL(23, 199, 23), // "on_serial_errorOccurred"
QT_MOC_LITERAL(24, 223, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(25, 252, 5), // "error"
QT_MOC_LITERAL(26, 258, 19), // "on_serial_readyRead"
QT_MOC_LITERAL(27, 278, 18), // "on_timer_rxTimeout"
QT_MOC_LITERAL(28, 297, 13), // "on_timer_comm"
QT_MOC_LITERAL(29, 311, 15) // "on_timer_render"

    },
    "Core\0daqReady\0\0Ready\0ready\0stateChanged\0"
    "State\0state\0msgDisplay\0name\0MsgBoxType\0"
    "type\0latencyAndUptime\0latency\0commTimeout\0"
    "uptime\0finished\0on_startThread\0"
    "on_openComm\0port\0on_closeComm\0force\0"
    "on_dispose\0on_serial_errorOccurred\0"
    "QSerialPort::SerialPortError\0error\0"
    "on_serial_readyRead\0on_timer_rxTimeout\0"
    "on_timer_comm\0on_timer_render"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Core[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       5,    1,   87,    2, 0x06 /* Public */,
       8,    2,   90,    2, 0x06 /* Public */,
      12,    3,   95,    2, 0x06 /* Public */,
      16,    0,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  103,    2, 0x0a /* Public */,
      18,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,
      22,    0,  110,    2, 0x0a /* Public */,
      23,    1,  111,    2, 0x08 /* Private */,
      26,    0,  114,    2, 0x08 /* Private */,
      27,    0,  115,    2, 0x08 /* Private */,
      28,    0,  116,    2, 0x08 /* Private */,
      29,    0,  117,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   13,   14,   15,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   19,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Core *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->daqReady((*reinterpret_cast< Ready(*)>(_a[1]))); break;
        case 1: _t->stateChanged((*reinterpret_cast< const State(*)>(_a[1]))); break;
        case 2: _t->msgDisplay((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2]))); break;
        case 3: _t->latencyAndUptime((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->finished(); break;
        case 5: _t->on_startThread(); break;
        case 6: _t->on_openComm((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_closeComm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_dispose(); break;
        case 9: _t->on_serial_errorOccurred((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 10: _t->on_serial_readyRead(); break;
        case 11: _t->on_timer_rxTimeout(); break;
        case 12: _t->on_timer_comm(); break;
        case 13: _t->on_timer_render(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Core::*)(Ready );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::daqReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Core::*)(const State );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::stateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Core::*)(const QString , MsgBoxType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::msgDisplay)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Core::*)(int , int , const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::latencyAndUptime)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Core::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Core::finished)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Core::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Core.data,
    qt_meta_data_Core,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Core::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Core.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Core::daqReady(Ready _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Core::stateChanged(const State _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Core::msgDisplay(const QString _t1, MsgBoxType _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Core::latencyAndUptime(int _t1, int _t2, const QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Core::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
