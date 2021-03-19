/****************************************************************************
** Meta object code from reading C++ file 'QBreakpadHttpUploader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/__crashhandler/handler/QBreakpadHttpUploader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QBreakpadHttpUploader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QBreakpadHttpUploader_t {
    QByteArrayData data[13];
    char stringdata0[149];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QBreakpadHttpUploader_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QBreakpadHttpUploader_t qt_meta_stringdata_QBreakpadHttpUploader = {
    {
QT_MOC_LITERAL(0, 0, 21), // "QBreakpadHttpUploader"
QT_MOC_LITERAL(1, 22, 8), // "finished"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "answer"
QT_MOC_LITERAL(4, 39, 10), // "uploadDump"
QT_MOC_LITERAL(5, 50, 13), // "abs_file_path"
QT_MOC_LITERAL(6, 64, 16), // "onUploadProgress"
QT_MOC_LITERAL(7, 81, 4), // "sent"
QT_MOC_LITERAL(8, 86, 5), // "total"
QT_MOC_LITERAL(9, 92, 7), // "onError"
QT_MOC_LITERAL(10, 100, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(11, 128, 3), // "err"
QT_MOC_LITERAL(12, 132, 16) // "onUploadFinished"

    },
    "QBreakpadHttpUploader\0finished\0\0answer\0"
    "uploadDump\0abs_file_path\0onUploadProgress\0"
    "sent\0total\0onError\0QNetworkReply::NetworkError\0"
    "err\0onUploadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QBreakpadHttpUploader[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x0a /* Public */,
       6,    2,   45,    2, 0x08 /* Private */,
       9,    1,   50,    2, 0x08 /* Private */,
      12,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void QBreakpadHttpUploader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QBreakpadHttpUploader *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->uploadDump((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onUploadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->onError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 4: _t->onUploadFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QBreakpadHttpUploader::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QBreakpadHttpUploader::finished)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QBreakpadHttpUploader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_QBreakpadHttpUploader.data,
    qt_meta_data_QBreakpadHttpUploader,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QBreakpadHttpUploader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QBreakpadHttpUploader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QBreakpadHttpUploader.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QBreakpadHttpUploader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void QBreakpadHttpUploader::finished(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
