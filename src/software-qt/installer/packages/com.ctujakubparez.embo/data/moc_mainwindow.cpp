/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/__stm32programmer/mainwindow.h"
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
    QByteArrayData data[27];
    char stringdata0[380];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "logView"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "info"
QT_MOC_LITERAL(4, 25, 5), // "level"
QT_MOC_LITERAL(5, 31, 17), // "dataProcessSignal"
QT_MOC_LITERAL(6, 49, 5), // "value"
QT_MOC_LITERAL(7, 55, 5), // "total"
QT_MOC_LITERAL(8, 61, 19), // "taskFininshedSignal"
QT_MOC_LITERAL(9, 81, 19), // "on_tbBrowse_clicked"
QT_MOC_LITERAL(10, 101, 18), // "on_bCancel_clicked"
QT_MOC_LITERAL(11, 120, 17), // "on_bWrite_clicked"
QT_MOC_LITERAL(12, 138, 16), // "on_bRead_clicked"
QT_MOC_LITERAL(13, 155, 18), // "on_bDevice_clicked"
QT_MOC_LITERAL(14, 174, 19), // "on_ClearBtn_clicked"
QT_MOC_LITERAL(15, 194, 18), // "on_SaveBtn_clicked"
QT_MOC_LITERAL(16, 213, 20), // "on_deleteBtn_clicked"
QT_MOC_LITERAL(17, 234, 21), // "on_ConnectBtn_clicked"
QT_MOC_LITERAL(18, 256, 7), // "checked"
QT_MOC_LITERAL(19, 264, 18), // "on_bVerfiy_toggled"
QT_MOC_LITERAL(20, 283, 16), // "on_bSkip_toggled"
QT_MOC_LITERAL(21, 300, 15), // "on_bRun_toggled"
QT_MOC_LITERAL(22, 316, 12), // "userOperator"
QT_MOC_LITERAL(23, 329, 8), // "filename"
QT_MOC_LITERAL(24, 338, 11), // "logInfoSlot"
QT_MOC_LITERAL(25, 350, 15), // "dataProcessSlot"
QT_MOC_LITERAL(26, 366, 13) // "taskFininshed"

    },
    "MainWindow\0logView\0\0info\0level\0"
    "dataProcessSignal\0value\0total\0"
    "taskFininshedSignal\0on_tbBrowse_clicked\0"
    "on_bCancel_clicked\0on_bWrite_clicked\0"
    "on_bRead_clicked\0on_bDevice_clicked\0"
    "on_ClearBtn_clicked\0on_SaveBtn_clicked\0"
    "on_deleteBtn_clicked\0on_ConnectBtn_clicked\0"
    "checked\0on_bVerfiy_toggled\0on_bSkip_toggled\0"
    "on_bRun_toggled\0userOperator\0filename\0"
    "logInfoSlot\0dataProcessSlot\0taskFininshed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    2,  114,    2, 0x06 /* Public */,
       8,    0,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  120,    2, 0x09 /* Protected */,
      10,    0,  121,    2, 0x09 /* Protected */,
      11,    0,  122,    2, 0x09 /* Protected */,
      12,    0,  123,    2, 0x09 /* Protected */,
      13,    0,  124,    2, 0x08 /* Private */,
      14,    0,  125,    2, 0x08 /* Private */,
      15,    0,  126,    2, 0x08 /* Private */,
      16,    0,  127,    2, 0x08 /* Private */,
      17,    1,  128,    2, 0x08 /* Private */,
      19,    1,  131,    2, 0x08 /* Private */,
      20,    1,  134,    2, 0x08 /* Private */,
      21,    1,  137,    2, 0x08 /* Private */,
      22,    1,  140,    2, 0x08 /* Private */,
      24,    2,  143,    2, 0x08 /* Private */,
      25,    2,  148,    2, 0x08 /* Private */,
      26,    0,  153,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->logView((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->dataProcessSignal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->taskFininshedSignal(); break;
        case 3: _t->on_tbBrowse_clicked(); break;
        case 4: _t->on_bCancel_clicked(); break;
        case 5: _t->on_bWrite_clicked(); break;
        case 6: _t->on_bRead_clicked(); break;
        case 7: _t->on_bDevice_clicked(); break;
        case 8: _t->on_ClearBtn_clicked(); break;
        case 9: _t->on_SaveBtn_clicked(); break;
        case 10: _t->on_deleteBtn_clicked(); break;
        case 11: _t->on_ConnectBtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_bVerfiy_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_bSkip_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->on_bRun_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->userOperator((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 16: _t->logInfoSlot((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 17: _t->dataProcessSlot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->taskFininshed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::logView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::dataProcessSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::taskFininshedSignal)) {
                *result = 2;
                return;
            }
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::logView(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::dataProcessSignal(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::taskFininshedSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
