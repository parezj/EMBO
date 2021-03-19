/****************************************************************************
** Meta object code from reading C++ file 'Updater.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/__updater/src/Updater.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Updater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Updater_t {
    QByteArrayData data[34];
    char stringdata0[435];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Updater_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Updater_t qt_meta_stringdata_Updater = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Updater"
QT_MOC_LITERAL(1, 8, 16), // "checkingFinished"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "url"
QT_MOC_LITERAL(4, 30, 16), // "downloadFinished"
QT_MOC_LITERAL(5, 47, 8), // "filepath"
QT_MOC_LITERAL(6, 56, 17), // "appcastDownloaded"
QT_MOC_LITERAL(7, 74, 4), // "data"
QT_MOC_LITERAL(8, 79, 15), // "checkForUpdates"
QT_MOC_LITERAL(9, 95, 6), // "setUrl"
QT_MOC_LITERAL(10, 102, 13), // "setModuleName"
QT_MOC_LITERAL(11, 116, 4), // "name"
QT_MOC_LITERAL(12, 121, 17), // "setNotifyOnUpdate"
QT_MOC_LITERAL(13, 139, 6), // "notify"
QT_MOC_LITERAL(14, 146, 17), // "setNotifyOnFinish"
QT_MOC_LITERAL(15, 164, 18), // "setUserAgentString"
QT_MOC_LITERAL(16, 183, 5), // "agent"
QT_MOC_LITERAL(17, 189, 16), // "setModuleVersion"
QT_MOC_LITERAL(18, 206, 7), // "version"
QT_MOC_LITERAL(19, 214, 20), // "setDownloaderEnabled"
QT_MOC_LITERAL(20, 235, 7), // "enabled"
QT_MOC_LITERAL(21, 243, 14), // "setPlatformKey"
QT_MOC_LITERAL(22, 258, 11), // "platformKey"
QT_MOC_LITERAL(23, 270, 19), // "setUseCustomAppcast"
QT_MOC_LITERAL(24, 290, 13), // "customAppcast"
QT_MOC_LITERAL(25, 304, 29), // "setUseCustomInstallProcedures"
QT_MOC_LITERAL(26, 334, 6), // "custom"
QT_MOC_LITERAL(27, 341, 18), // "setMandatoryUpdate"
QT_MOC_LITERAL(28, 360, 16), // "mandatory_update"
QT_MOC_LITERAL(29, 377, 7), // "onReply"
QT_MOC_LITERAL(30, 385, 14), // "QNetworkReply*"
QT_MOC_LITERAL(31, 400, 5), // "reply"
QT_MOC_LITERAL(32, 406, 18), // "setUpdateAvailable"
QT_MOC_LITERAL(33, 425, 9) // "available"

    },
    "Updater\0checkingFinished\0\0url\0"
    "downloadFinished\0filepath\0appcastDownloaded\0"
    "data\0checkForUpdates\0setUrl\0setModuleName\0"
    "name\0setNotifyOnUpdate\0notify\0"
    "setNotifyOnFinish\0setUserAgentString\0"
    "agent\0setModuleVersion\0version\0"
    "setDownloaderEnabled\0enabled\0"
    "setPlatformKey\0platformKey\0"
    "setUseCustomAppcast\0customAppcast\0"
    "setUseCustomInstallProcedures\0custom\0"
    "setMandatoryUpdate\0mandatory_update\0"
    "onReply\0QNetworkReply*\0reply\0"
    "setUpdateAvailable\0available"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Updater[] = {

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
       4,    2,  102,    2, 0x06 /* Public */,
       6,    2,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,  112,    2, 0x0a /* Public */,
       9,    1,  113,    2, 0x0a /* Public */,
      10,    1,  116,    2, 0x0a /* Public */,
      12,    1,  119,    2, 0x0a /* Public */,
      14,    1,  122,    2, 0x0a /* Public */,
      15,    1,  125,    2, 0x0a /* Public */,
      17,    1,  128,    2, 0x0a /* Public */,
      19,    1,  131,    2, 0x0a /* Public */,
      21,    1,  134,    2, 0x0a /* Public */,
      23,    1,  137,    2, 0x0a /* Public */,
      25,    1,  140,    2, 0x0a /* Public */,
      27,    1,  143,    2, 0x0a /* Public */,
      29,    1,  146,    2, 0x08 /* Private */,
      32,    1,  149,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    3,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Bool,   24,
    QMetaType::Void, QMetaType::Bool,   26,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, QMetaType::Bool,   33,

       0        // eod
};

void Updater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Updater *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->checkingFinished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->downloadFinished((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->appcastDownloaded((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 3: _t->checkForUpdates(); break;
        case 4: _t->setUrl((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setModuleName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setNotifyOnUpdate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: _t->setNotifyOnFinish((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 8: _t->setUserAgentString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->setModuleVersion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->setDownloaderEnabled((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 11: _t->setPlatformKey((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->setUseCustomAppcast((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 13: _t->setUseCustomInstallProcedures((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 14: _t->setMandatoryUpdate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 15: _t->onReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 16: _t->setUpdateAvailable((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Updater::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::checkingFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Updater::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::downloadFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Updater::*)(const QString & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Updater::appcastDownloaded)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Updater::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Updater.data,
    qt_meta_data_Updater,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Updater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Updater::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Updater.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Updater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Updater::checkingFinished(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Updater::downloadFinished(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Updater::appcastDownloaded(const QString & _t1, const QByteArray & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
