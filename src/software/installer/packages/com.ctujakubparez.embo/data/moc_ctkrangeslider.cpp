/****************************************************************************
** Meta object code from reading C++ file 'ctkrangeslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/lib/ctkrangeslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctkrangeslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ctkRangeSlider_t {
    QByteArrayData data[22];
    char stringdata0[301];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ctkRangeSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ctkRangeSlider_t qt_meta_stringdata_ctkRangeSlider = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ctkRangeSlider"
QT_MOC_LITERAL(1, 15, 19), // "minimumValueChanged"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "min"
QT_MOC_LITERAL(4, 40, 19), // "maximumValueChanged"
QT_MOC_LITERAL(5, 60, 3), // "max"
QT_MOC_LITERAL(6, 64, 13), // "valuesChanged"
QT_MOC_LITERAL(7, 78, 22), // "minimumPositionChanged"
QT_MOC_LITERAL(8, 101, 22), // "maximumPositionChanged"
QT_MOC_LITERAL(9, 124, 16), // "positionsChanged"
QT_MOC_LITERAL(10, 141, 15), // "setMinimumValue"
QT_MOC_LITERAL(11, 157, 15), // "setMaximumValue"
QT_MOC_LITERAL(12, 173, 9), // "setValues"
QT_MOC_LITERAL(13, 183, 14), // "onRangeChanged"
QT_MOC_LITERAL(14, 198, 7), // "minimum"
QT_MOC_LITERAL(15, 206, 7), // "maximum"
QT_MOC_LITERAL(16, 214, 12), // "minimumValue"
QT_MOC_LITERAL(17, 227, 12), // "maximumValue"
QT_MOC_LITERAL(18, 240, 15), // "minimumPosition"
QT_MOC_LITERAL(19, 256, 15), // "maximumPosition"
QT_MOC_LITERAL(20, 272, 14), // "symmetricMoves"
QT_MOC_LITERAL(21, 287, 13) // "handleToolTip"

    },
    "ctkRangeSlider\0minimumValueChanged\0\0"
    "min\0maximumValueChanged\0max\0valuesChanged\0"
    "minimumPositionChanged\0maximumPositionChanged\0"
    "positionsChanged\0setMinimumValue\0"
    "setMaximumValue\0setValues\0onRangeChanged\0"
    "minimum\0maximum\0minimumValue\0maximumValue\0"
    "minimumPosition\0maximumPosition\0"
    "symmetricMoves\0handleToolTip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ctkRangeSlider[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       6,  102, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    2,   70,    2, 0x06 /* Public */,
       7,    1,   75,    2, 0x06 /* Public */,
       8,    1,   78,    2, 0x06 /* Public */,
       9,    2,   81,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   86,    2, 0x0a /* Public */,
      11,    1,   89,    2, 0x0a /* Public */,
      12,    2,   92,    2, 0x0a /* Public */,
      13,    2,   97,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

 // properties: name, type, flags
      16, QMetaType::Int, 0x00095103,
      17, QMetaType::Int, 0x00095103,
      18, QMetaType::Int, 0x00095103,
      19, QMetaType::Int, 0x00095103,
      20, QMetaType::Bool, 0x00095103,
      21, QMetaType::QString, 0x00095103,

       0        // eod
};

void ctkRangeSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ctkRangeSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->minimumValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->maximumValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->valuesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->minimumPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->maximumPositionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->positionsChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->setMinimumValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setMaximumValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setValues((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->onRangeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ctkRangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::minimumValueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ctkRangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::maximumValueChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ctkRangeSlider::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::valuesChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ctkRangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::minimumPositionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ctkRangeSlider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::maximumPositionChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ctkRangeSlider::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ctkRangeSlider::positionsChanged)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ctkRangeSlider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->minimumValue(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->maximumValue(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->minimumPosition(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->maximumPosition(); break;
        case 4: *reinterpret_cast< bool*>(_v) = _t->symmetricMoves(); break;
        case 5: *reinterpret_cast< QString*>(_v) = _t->handleToolTip(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ctkRangeSlider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinimumValue(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMaximumValue(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setMinimumPosition(*reinterpret_cast< int*>(_v)); break;
        case 3: _t->setMaximumPosition(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setSymmetricMoves(*reinterpret_cast< bool*>(_v)); break;
        case 5: _t->setHandleToolTip(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ctkRangeSlider::staticMetaObject = { {
    QMetaObject::SuperData::link<QSlider::staticMetaObject>(),
    qt_meta_stringdata_ctkRangeSlider.data,
    qt_meta_data_ctkRangeSlider,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ctkRangeSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ctkRangeSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ctkRangeSlider.stringdata0))
        return static_cast<void*>(this);
    return QSlider::qt_metacast(_clname);
}

int ctkRangeSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 6;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 6;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ctkRangeSlider::minimumValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ctkRangeSlider::maximumValueChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ctkRangeSlider::valuesChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ctkRangeSlider::minimumPositionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ctkRangeSlider::maximumPositionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ctkRangeSlider::positionsChanged(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
