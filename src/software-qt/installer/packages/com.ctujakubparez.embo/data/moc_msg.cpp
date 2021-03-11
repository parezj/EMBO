/****************************************************************************
** Meta object code from reading C++ file 'msg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/msg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'msg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Msg_t {
    QByteArrayData data[12];
    char stringdata0[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Msg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Msg_t qt_meta_stringdata_Msg = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Msg"
QT_MOC_LITERAL(1, 4, 2), // "rx"
QT_MOC_LITERAL(2, 7, 0), // ""
QT_MOC_LITERAL(3, 8, 2), // "ok"
QT_MOC_LITERAL(4, 11, 4), // "val1"
QT_MOC_LITERAL(5, 16, 4), // "val2"
QT_MOC_LITERAL(6, 21, 3), // "err"
QT_MOC_LITERAL(7, 25, 4), // "text"
QT_MOC_LITERAL(8, 30, 10), // "MsgBoxType"
QT_MOC_LITERAL(9, 41, 4), // "type"
QT_MOC_LITERAL(10, 46, 9), // "needClose"
QT_MOC_LITERAL(11, 56, 9) // "on_dataRx"

    },
    "Msg\0rx\0\0ok\0val1\0val2\0err\0text\0MsgBoxType\0"
    "type\0needClose\0on_dataRx"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Msg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    2,   45,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x26 /* Public | MethodCloned */,
       3,    0,   53,    2, 0x26 /* Public | MethodCloned */,
       6,    3,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   61,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 8, QMetaType::Bool,    7,    9,   10,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Msg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Msg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rx(); break;
        case 1: _t->ok((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->ok((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ok(); break;
        case 4: _t->err((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 5: _t->on_dataRx(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Msg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg::rx)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Msg::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg::ok)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Msg::*)(QString , MsgBoxType , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Msg::err)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Msg::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Msg.data,
    qt_meta_data_Msg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Msg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Msg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Msg.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Msg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Msg::rx()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Msg::ok(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 4
void Msg::err(QString _t1, MsgBoxType _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
