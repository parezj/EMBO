/****************************************************************************
** Meta object code from reading C++ file 'Downloader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/__updater/src/Downloader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Downloader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Downloader_t {
    QByteArrayData data[25];
    char stringdata0[308];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Downloader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Downloader_t qt_meta_stringdata_Downloader = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Downloader"
QT_MOC_LITERAL(1, 11, 16), // "downloadFinished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "url"
QT_MOC_LITERAL(4, 33, 8), // "filepath"
QT_MOC_LITERAL(5, 42, 8), // "setUrlId"
QT_MOC_LITERAL(6, 51, 13), // "startDownload"
QT_MOC_LITERAL(7, 65, 11), // "setFileName"
QT_MOC_LITERAL(8, 77, 4), // "file"
QT_MOC_LITERAL(9, 82, 18), // "setUserAgentString"
QT_MOC_LITERAL(10, 101, 5), // "agent"
QT_MOC_LITERAL(11, 107, 29), // "setUseCustomInstallProcedures"
QT_MOC_LITERAL(12, 137, 6), // "custom"
QT_MOC_LITERAL(13, 144, 18), // "setMandatoryUpdate"
QT_MOC_LITERAL(14, 163, 16), // "mandatory_update"
QT_MOC_LITERAL(15, 180, 8), // "finished"
QT_MOC_LITERAL(16, 189, 12), // "openDownload"
QT_MOC_LITERAL(17, 202, 13), // "installUpdate"
QT_MOC_LITERAL(18, 216, 14), // "cancelDownload"
QT_MOC_LITERAL(19, 231, 8), // "saveFile"
QT_MOC_LITERAL(20, 240, 8), // "received"
QT_MOC_LITERAL(21, 249, 5), // "total"
QT_MOC_LITERAL(22, 255, 14), // "calculateSizes"
QT_MOC_LITERAL(23, 270, 14), // "updateProgress"
QT_MOC_LITERAL(24, 285, 22) // "calculateTimeRemaining"

    },
    "Downloader\0downloadFinished\0\0url\0"
    "filepath\0setUrlId\0startDownload\0"
    "setFileName\0file\0setUserAgentString\0"
    "agent\0setUseCustomInstallProcedures\0"
    "custom\0setMandatoryUpdate\0mandatory_update\0"
    "finished\0openDownload\0installUpdate\0"
    "cancelDownload\0saveFile\0received\0total\0"
    "calculateSizes\0updateProgress\0"
    "calculateTimeRemaining"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Downloader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   94,    2, 0x0a /* Public */,
       6,    1,   97,    2, 0x0a /* Public */,
       7,    1,  100,    2, 0x0a /* Public */,
       9,    1,  103,    2, 0x0a /* Public */,
      11,    1,  106,    2, 0x0a /* Public */,
      13,    1,  109,    2, 0x0a /* Public */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,
      19,    2,  116,    2, 0x08 /* Private */,
      22,    2,  121,    2, 0x08 /* Private */,
      23,    2,  126,    2, 0x08 /* Private */,
      24,    2,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QUrl,    3,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   20,   21,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   20,   21,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   20,   21,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   20,   21,

       0        // eod
};

void Downloader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Downloader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadFinished((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->setUrlId((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->startDownload((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 3: _t->setFileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setUserAgentString((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setUseCustomInstallProcedures((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: _t->setMandatoryUpdate((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 7: _t->finished(); break;
        case 8: _t->openDownload(); break;
        case 9: _t->installUpdate(); break;
        case 10: _t->cancelDownload(); break;
        case 11: _t->saveFile((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 12: _t->calculateSizes((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 13: _t->updateProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 14: _t->calculateTimeRemaining((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Downloader::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Downloader::downloadFinished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Downloader::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Downloader.data,
    qt_meta_data_Downloader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Downloader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Downloader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Downloader.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Downloader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void Downloader::downloadFinished(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
