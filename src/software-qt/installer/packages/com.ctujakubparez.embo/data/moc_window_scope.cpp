/****************************************************************************
** Meta object code from reading C++ file 'window_scope.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/window_scope.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_scope.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowScope_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowScope_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowScope_t qt_meta_stringdata_WindowScope = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WindowScope"
QT_MOC_LITERAL(1, 12, 7), // "closing"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "const char*"
QT_MOC_LITERAL(4, 33, 9), // "className"
QT_MOC_LITERAL(5, 43, 10), // "on_msg_err"
QT_MOC_LITERAL(6, 54, 4), // "text"
QT_MOC_LITERAL(7, 59, 10), // "MsgBoxType"
QT_MOC_LITERAL(8, 70, 4), // "type"
QT_MOC_LITERAL(9, 75, 9), // "needClose"
QT_MOC_LITERAL(10, 85, 24) // "on_actionAbout_triggered"

    },
    "WindowScope\0closing\0\0const char*\0"
    "className\0on_msg_err\0text\0MsgBoxType\0"
    "type\0needClose\0on_actionAbout_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowScope[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,   32,    2, 0x08 /* Private */,
      10,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,
    QMetaType::Void,

       0        // eod
};

void WindowScope::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowScope *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closing((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 1: _t->on_msg_err((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->on_actionAbout_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowScope::*)(const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowScope::closing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowScope::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WindowScope.data,
    qt_meta_data_WindowScope,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowScope::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowScope::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowScope.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IEmboInstrument"))
        return static_cast< IEmboInstrument*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WindowScope::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WindowScope::closing(const char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
