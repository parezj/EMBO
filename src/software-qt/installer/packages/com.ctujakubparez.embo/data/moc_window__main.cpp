/****************************************************************************
** Meta object code from reading C++ file 'window__main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/window__main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window__main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowMain_t {
    QByteArrayData data[30];
    char stringdata0[464];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowMain_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowMain_t qt_meta_stringdata_WindowMain = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WindowMain"
QT_MOC_LITERAL(1, 11, 8), // "openComm"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "port"
QT_MOC_LITERAL(4, 26, 9), // "closeComm"
QT_MOC_LITERAL(5, 36, 5), // "force"
QT_MOC_LITERAL(6, 42, 11), // "disposeCore"
QT_MOC_LITERAL(7, 54, 10), // "closeEvent"
QT_MOC_LITERAL(8, 65, 12), // "QCloseEvent*"
QT_MOC_LITERAL(9, 78, 5), // "event"
QT_MOC_LITERAL(10, 84, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(11, 109, 26), // "on_pushButton_scan_clicked"
QT_MOC_LITERAL(12, 136, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(13, 166, 32), // "on_pushButton_disconnect_clicked"
QT_MOC_LITERAL(14, 199, 20), // "on_coreState_changed"
QT_MOC_LITERAL(15, 220, 5), // "State"
QT_MOC_LITERAL(16, 226, 8), // "newState"
QT_MOC_LITERAL(17, 235, 13), // "on_msgDisplay"
QT_MOC_LITERAL(18, 249, 4), // "text"
QT_MOC_LITERAL(19, 254, 10), // "MsgBoxType"
QT_MOC_LITERAL(20, 265, 4), // "type"
QT_MOC_LITERAL(21, 270, 13), // "on_instrClose"
QT_MOC_LITERAL(22, 284, 11), // "const char*"
QT_MOC_LITERAL(23, 296, 9), // "className"
QT_MOC_LITERAL(24, 306, 27), // "on_pushButton_scope_clicked"
QT_MOC_LITERAL(25, 334, 24), // "on_pushButton_la_clicked"
QT_MOC_LITERAL(26, 359, 24), // "on_pushButton_vm_clicked"
QT_MOC_LITERAL(27, 384, 26), // "on_pushButton_cntr_clicked"
QT_MOC_LITERAL(28, 411, 25), // "on_pushButton_pwm_clicked"
QT_MOC_LITERAL(29, 437, 26) // "on_pushButton_sgen_clicked"

    },
    "WindowMain\0openComm\0\0port\0closeComm\0"
    "force\0disposeCore\0closeEvent\0QCloseEvent*\0"
    "event\0on_actionAbout_triggered\0"
    "on_pushButton_scan_clicked\0"
    "on_pushButton_connect_clicked\0"
    "on_pushButton_disconnect_clicked\0"
    "on_coreState_changed\0State\0newState\0"
    "on_msgDisplay\0text\0MsgBoxType\0type\0"
    "on_instrClose\0const char*\0className\0"
    "on_pushButton_scope_clicked\0"
    "on_pushButton_la_clicked\0"
    "on_pushButton_vm_clicked\0"
    "on_pushButton_cntr_clicked\0"
    "on_pushButton_pwm_clicked\0"
    "on_pushButton_sgen_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowMain[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    1,  102,    2, 0x06 /* Public */,
       6,    0,  105,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,  106,    2, 0x08 /* Private */,
      10,    0,  109,    2, 0x08 /* Private */,
      11,    0,  110,    2, 0x08 /* Private */,
      12,    0,  111,    2, 0x08 /* Private */,
      13,    0,  112,    2, 0x08 /* Private */,
      14,    1,  113,    2, 0x08 /* Private */,
      17,    2,  116,    2, 0x08 /* Private */,
      21,    1,  121,    2, 0x08 /* Private */,
      24,    0,  124,    2, 0x08 /* Private */,
      25,    0,  125,    2, 0x08 /* Private */,
      26,    0,  126,    2, 0x08 /* Private */,
      27,    0,  127,    2, 0x08 /* Private */,
      28,    0,  128,    2, 0x08 /* Private */,
      29,    0,  129,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 19,   18,   20,
    QMetaType::Void, 0x80000000 | 22,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WindowMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowMain *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openComm((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->closeComm((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->disposeCore(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->on_actionAbout_triggered(); break;
        case 5: _t->on_pushButton_scan_clicked(); break;
        case 6: _t->on_pushButton_connect_clicked(); break;
        case 7: _t->on_pushButton_disconnect_clicked(); break;
        case 8: _t->on_coreState_changed((*reinterpret_cast< const State(*)>(_a[1]))); break;
        case 9: _t->on_msgDisplay((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2]))); break;
        case 10: _t->on_instrClose((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_scope_clicked(); break;
        case 12: _t->on_pushButton_la_clicked(); break;
        case 13: _t->on_pushButton_vm_clicked(); break;
        case 14: _t->on_pushButton_cntr_clicked(); break;
        case 15: _t->on_pushButton_pwm_clicked(); break;
        case 16: _t->on_pushButton_sgen_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowMain::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowMain::openComm)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WindowMain::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowMain::closeComm)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WindowMain::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowMain::disposeCore)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowMain::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WindowMain.data,
    qt_meta_data_WindowMain,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowMain::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowMain.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WindowMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void WindowMain::openComm(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WindowMain::closeComm(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WindowMain::disposeCore()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
