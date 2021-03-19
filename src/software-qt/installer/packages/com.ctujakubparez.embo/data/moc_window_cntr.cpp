/****************************************************************************
** Meta object code from reading C++ file 'window_cntr.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/window_cntr.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_cntr.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowCntr_t {
    QByteArrayData data[25];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowCntr_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowCntr_t qt_meta_stringdata_WindowCntr = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WindowCntr"
QT_MOC_LITERAL(1, 11, 7), // "closing"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "const char*"
QT_MOC_LITERAL(4, 32, 9), // "className"
QT_MOC_LITERAL(5, 42, 9), // "on_msg_ok"
QT_MOC_LITERAL(6, 52, 4), // "val1"
QT_MOC_LITERAL(7, 57, 4), // "val2"
QT_MOC_LITERAL(8, 62, 10), // "on_msg_err"
QT_MOC_LITERAL(9, 73, 4), // "text"
QT_MOC_LITERAL(10, 78, 10), // "MsgBoxType"
QT_MOC_LITERAL(11, 89, 4), // "type"
QT_MOC_LITERAL(12, 94, 9), // "needClose"
QT_MOC_LITERAL(13, 104, 13), // "on_msg_enable"
QT_MOC_LITERAL(14, 118, 7), // "enabled"
QT_MOC_LITERAL(15, 126, 8), // "fastMode"
QT_MOC_LITERAL(16, 135, 11), // "on_msg_read"
QT_MOC_LITERAL(17, 147, 4), // "freq"
QT_MOC_LITERAL(18, 152, 6), // "period"
QT_MOC_LITERAL(19, 159, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(20, 184, 29), // "on_pushButton_disable_clicked"
QT_MOC_LITERAL(21, 214, 28), // "on_pushButton_enable_clicked"
QT_MOC_LITERAL(22, 243, 30), // "on_radioButton_precise_clicked"
QT_MOC_LITERAL(23, 274, 27), // "on_radioButton_fast_clicked"
QT_MOC_LITERAL(24, 302, 15) // "on_timer_render"

    },
    "WindowCntr\0closing\0\0const char*\0"
    "className\0on_msg_ok\0val1\0val2\0on_msg_err\0"
    "text\0MsgBoxType\0type\0needClose\0"
    "on_msg_enable\0enabled\0fastMode\0"
    "on_msg_read\0freq\0period\0"
    "on_actionAbout_triggered\0"
    "on_pushButton_disable_clicked\0"
    "on_pushButton_enable_clicked\0"
    "on_radioButton_precise_clicked\0"
    "on_radioButton_fast_clicked\0on_timer_render"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowCntr[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   72,    2, 0x08 /* Private */,
       8,    3,   77,    2, 0x08 /* Private */,
      13,    2,   84,    2, 0x08 /* Private */,
      16,    2,   89,    2, 0x08 /* Private */,
      19,    0,   94,    2, 0x08 /* Private */,
      20,    0,   95,    2, 0x08 /* Private */,
      21,    0,   96,    2, 0x08 /* Private */,
      22,    0,   97,    2, 0x08 /* Private */,
      23,    0,   98,    2, 0x08 /* Private */,
      24,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10, QMetaType::Bool,    9,   11,   12,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   14,   15,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   17,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WindowCntr::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowCntr *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closing((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 1: _t->on_msg_ok((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->on_msg_err((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->on_msg_enable((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->on_msg_read((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->on_actionAbout_triggered(); break;
        case 6: _t->on_pushButton_disable_clicked(); break;
        case 7: _t->on_pushButton_enable_clicked(); break;
        case 8: _t->on_radioButton_precise_clicked(); break;
        case 9: _t->on_radioButton_fast_clicked(); break;
        case 10: _t->on_timer_render(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowCntr::*)(const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowCntr::closing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowCntr::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WindowCntr.data,
    qt_meta_data_WindowCntr,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowCntr::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowCntr::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowCntr.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IEmboInstrument"))
        return static_cast< IEmboInstrument*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WindowCntr::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void WindowCntr::closing(const char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
