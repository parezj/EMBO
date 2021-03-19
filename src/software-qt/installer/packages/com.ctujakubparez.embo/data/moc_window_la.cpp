/****************************************************************************
** Meta object code from reading C++ file 'window_la.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/window_la.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_la.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowLa_t {
    QByteArrayData data[20];
    char stringdata0[183];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowLa_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowLa_t qt_meta_stringdata_WindowLa = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WindowLa"
QT_MOC_LITERAL(1, 9, 7), // "closing"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "const char*"
QT_MOC_LITERAL(4, 30, 9), // "className"
QT_MOC_LITERAL(5, 40, 9), // "on_msg_ok"
QT_MOC_LITERAL(6, 50, 4), // "val1"
QT_MOC_LITERAL(7, 55, 4), // "val2"
QT_MOC_LITERAL(8, 60, 10), // "on_msg_err"
QT_MOC_LITERAL(9, 71, 4), // "text"
QT_MOC_LITERAL(10, 76, 10), // "MsgBoxType"
QT_MOC_LITERAL(11, 87, 4), // "type"
QT_MOC_LITERAL(12, 92, 9), // "needClose"
QT_MOC_LITERAL(13, 102, 10), // "on_msg_set"
QT_MOC_LITERAL(14, 113, 11), // "on_msg_read"
QT_MOC_LITERAL(15, 125, 4), // "data"
QT_MOC_LITERAL(16, 130, 15), // "on_msg_daqReady"
QT_MOC_LITERAL(17, 146, 5), // "Ready"
QT_MOC_LITERAL(18, 152, 5), // "ready"
QT_MOC_LITERAL(19, 158, 24) // "on_actionAbout_triggered"

    },
    "WindowLa\0closing\0\0const char*\0className\0"
    "on_msg_ok\0val1\0val2\0on_msg_err\0text\0"
    "MsgBoxType\0type\0needClose\0on_msg_set\0"
    "on_msg_read\0data\0on_msg_daqReady\0Ready\0"
    "ready\0on_actionAbout_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowLa[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   52,    2, 0x08 /* Private */,
       8,    3,   57,    2, 0x08 /* Private */,
      13,    0,   64,    2, 0x08 /* Private */,
      14,    1,   65,    2, 0x08 /* Private */,
      16,    1,   68,    2, 0x08 /* Private */,
      19,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10, QMetaType::Bool,    9,   11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,

       0        // eod
};

void WindowLa::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowLa *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closing((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 1: _t->on_msg_ok((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->on_msg_err((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->on_msg_set(); break;
        case 4: _t->on_msg_read((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_msg_daqReady((*reinterpret_cast< Ready(*)>(_a[1]))); break;
        case 6: _t->on_actionAbout_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowLa::*)(const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowLa::closing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowLa::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WindowLa.data,
    qt_meta_data_WindowLa,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowLa::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowLa::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowLa.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IEmboInstrument"))
        return static_cast< IEmboInstrument*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WindowLa::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WindowLa::closing(const char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
