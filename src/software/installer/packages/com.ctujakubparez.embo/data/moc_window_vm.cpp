/****************************************************************************
** Meta object code from reading C++ file 'window_vm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/src/windows/window_vm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_vm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WindowVm_t {
    QByteArrayData data[76];
    char stringdata0[1748];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WindowVm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WindowVm_t qt_meta_stringdata_WindowVm = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WindowVm"
QT_MOC_LITERAL(1, 9, 7), // "closing"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "const char*"
QT_MOC_LITERAL(4, 30, 9), // "className"
QT_MOC_LITERAL(5, 40, 10), // "on_msg_err"
QT_MOC_LITERAL(6, 51, 4), // "text"
QT_MOC_LITERAL(7, 56, 10), // "MsgBoxType"
QT_MOC_LITERAL(8, 67, 4), // "type"
QT_MOC_LITERAL(9, 72, 9), // "needClose"
QT_MOC_LITERAL(10, 82, 11), // "on_msg_read"
QT_MOC_LITERAL(11, 94, 3), // "ch1"
QT_MOC_LITERAL(12, 98, 3), // "ch2"
QT_MOC_LITERAL(13, 102, 3), // "ch3"
QT_MOC_LITERAL(14, 106, 3), // "ch4"
QT_MOC_LITERAL(15, 110, 3), // "vcc"
QT_MOC_LITERAL(16, 114, 13), // "on_timer_plot"
QT_MOC_LITERAL(17, 128, 15), // "on_timer_digits"
QT_MOC_LITERAL(18, 144, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(19, 169, 29), // "on_actionViewPoints_triggered"
QT_MOC_LITERAL(20, 199, 7), // "checked"
QT_MOC_LITERAL(21, 207, 28), // "on_actionViewLines_triggered"
QT_MOC_LITERAL(22, 236, 31), // "on_actionInterpLinear_triggered"
QT_MOC_LITERAL(23, 268, 29), // "on_actionInterpSinc_triggered"
QT_MOC_LITERAL(24, 298, 27), // "on_actionShowPlot_triggered"
QT_MOC_LITERAL(25, 326, 30), // "on_actionExportStart_triggered"
QT_MOC_LITERAL(26, 357, 29), // "on_actionExportStop_triggered"
QT_MOC_LITERAL(27, 387, 28), // "on_actionExportPNG_triggered"
QT_MOC_LITERAL(28, 416, 28), // "on_actionExportPDF_triggered"
QT_MOC_LITERAL(29, 445, 31), // "on_actionExportFolder_triggered"
QT_MOC_LITERAL(30, 477, 28), // "on_actionExportCSV_triggered"
QT_MOC_LITERAL(31, 506, 33), // "on_actionExportTXT_Tabs_trigg..."
QT_MOC_LITERAL(32, 540, 38), // "on_actionExportTXT_Semicolon_..."
QT_MOC_LITERAL(33, 579, 28), // "on_actionExportMAT_triggered"
QT_MOC_LITERAL(34, 608, 30), // "on_actionMeasEnabled_triggered"
QT_MOC_LITERAL(35, 639, 28), // "on_actionMeasReset_triggered"
QT_MOC_LITERAL(36, 668, 32), // "on_actionMeasChannel_1_triggered"
QT_MOC_LITERAL(37, 701, 32), // "on_actionMeasChannel_2_triggered"
QT_MOC_LITERAL(38, 734, 32), // "on_actionMeasChannel_3_triggered"
QT_MOC_LITERAL(39, 767, 32), // "on_actionMeasChannel_4_triggered"
QT_MOC_LITERAL(40, 800, 27), // "on_actionMath_1_2_triggered"
QT_MOC_LITERAL(41, 828, 27), // "on_actionMath_3_4_triggered"
QT_MOC_LITERAL(42, 856, 24), // "on_cursorH_valuesChanged"
QT_MOC_LITERAL(43, 881, 3), // "min"
QT_MOC_LITERAL(44, 885, 3), // "max"
QT_MOC_LITERAL(45, 889, 24), // "on_cursorV_valuesChanged"
QT_MOC_LITERAL(46, 914, 33), // "on_pushButton_cursorsHoff_cli..."
QT_MOC_LITERAL(47, 948, 32), // "on_pushButton_cursorsHon_clicked"
QT_MOC_LITERAL(48, 981, 33), // "on_pushButton_cursorsVoff_cli..."
QT_MOC_LITERAL(49, 1015, 32), // "on_pushButton_cursorsVon_clicked"
QT_MOC_LITERAL(50, 1048, 16), // "on_qcpMouseWheel"
QT_MOC_LITERAL(51, 1065, 12), // "QWheelEvent*"
QT_MOC_LITERAL(52, 1078, 16), // "on_qcpMousePress"
QT_MOC_LITERAL(53, 1095, 12), // "QMouseEvent*"
QT_MOC_LITERAL(54, 1108, 30), // "on_pushButton_disable1_clicked"
QT_MOC_LITERAL(55, 1139, 29), // "on_pushButton_enable1_clicked"
QT_MOC_LITERAL(56, 1169, 30), // "on_pushButton_disable2_clicked"
QT_MOC_LITERAL(57, 1200, 29), // "on_pushButton_enable2_clicked"
QT_MOC_LITERAL(58, 1230, 30), // "on_pushButton_disable3_clicked"
QT_MOC_LITERAL(59, 1261, 29), // "on_pushButton_enable3_clicked"
QT_MOC_LITERAL(60, 1291, 30), // "on_pushButton_disable4_clicked"
QT_MOC_LITERAL(61, 1322, 29), // "on_pushButton_enable4_clicked"
QT_MOC_LITERAL(62, 1352, 35), // "on_doubleSpinBox_gain1_valueC..."
QT_MOC_LITERAL(63, 1388, 4), // "arg1"
QT_MOC_LITERAL(64, 1393, 35), // "on_doubleSpinBox_gain2_valueC..."
QT_MOC_LITERAL(65, 1429, 35), // "on_doubleSpinBox_gain3_valueC..."
QT_MOC_LITERAL(66, 1465, 35), // "on_doubleSpinBox_gain4_valueC..."
QT_MOC_LITERAL(67, 1501, 29), // "on_pushButton_disable_clicked"
QT_MOC_LITERAL(68, 1531, 28), // "on_pushButton_enable_clicked"
QT_MOC_LITERAL(69, 1560, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(70, 1588, 31), // "on_pushButton_resetZoom_clicked"
QT_MOC_LITERAL(71, 1620, 31), // "on_spinBox_average_valueChanged"
QT_MOC_LITERAL(72, 1652, 28), // "on_dial_average_valueChanged"
QT_MOC_LITERAL(73, 1681, 5), // "value"
QT_MOC_LITERAL(74, 1687, 31), // "on_spinBox_display_valueChanged"
QT_MOC_LITERAL(75, 1719, 28) // "on_dial_display_valueChanged"

    },
    "WindowVm\0closing\0\0const char*\0className\0"
    "on_msg_err\0text\0MsgBoxType\0type\0"
    "needClose\0on_msg_read\0ch1\0ch2\0ch3\0ch4\0"
    "vcc\0on_timer_plot\0on_timer_digits\0"
    "on_actionAbout_triggered\0"
    "on_actionViewPoints_triggered\0checked\0"
    "on_actionViewLines_triggered\0"
    "on_actionInterpLinear_triggered\0"
    "on_actionInterpSinc_triggered\0"
    "on_actionShowPlot_triggered\0"
    "on_actionExportStart_triggered\0"
    "on_actionExportStop_triggered\0"
    "on_actionExportPNG_triggered\0"
    "on_actionExportPDF_triggered\0"
    "on_actionExportFolder_triggered\0"
    "on_actionExportCSV_triggered\0"
    "on_actionExportTXT_Tabs_triggered\0"
    "on_actionExportTXT_Semicolon_triggered\0"
    "on_actionExportMAT_triggered\0"
    "on_actionMeasEnabled_triggered\0"
    "on_actionMeasReset_triggered\0"
    "on_actionMeasChannel_1_triggered\0"
    "on_actionMeasChannel_2_triggered\0"
    "on_actionMeasChannel_3_triggered\0"
    "on_actionMeasChannel_4_triggered\0"
    "on_actionMath_1_2_triggered\0"
    "on_actionMath_3_4_triggered\0"
    "on_cursorH_valuesChanged\0min\0max\0"
    "on_cursorV_valuesChanged\0"
    "on_pushButton_cursorsHoff_clicked\0"
    "on_pushButton_cursorsHon_clicked\0"
    "on_pushButton_cursorsVoff_clicked\0"
    "on_pushButton_cursorsVon_clicked\0"
    "on_qcpMouseWheel\0QWheelEvent*\0"
    "on_qcpMousePress\0QMouseEvent*\0"
    "on_pushButton_disable1_clicked\0"
    "on_pushButton_enable1_clicked\0"
    "on_pushButton_disable2_clicked\0"
    "on_pushButton_enable2_clicked\0"
    "on_pushButton_disable3_clicked\0"
    "on_pushButton_enable3_clicked\0"
    "on_pushButton_disable4_clicked\0"
    "on_pushButton_enable4_clicked\0"
    "on_doubleSpinBox_gain1_valueChanged\0"
    "arg1\0on_doubleSpinBox_gain2_valueChanged\0"
    "on_doubleSpinBox_gain3_valueChanged\0"
    "on_doubleSpinBox_gain4_valueChanged\0"
    "on_pushButton_disable_clicked\0"
    "on_pushButton_enable_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_resetZoom_clicked\0"
    "on_spinBox_average_valueChanged\0"
    "on_dial_average_valueChanged\0value\0"
    "on_spinBox_display_valueChanged\0"
    "on_dial_display_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowVm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      56,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  294,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    3,  297,    2, 0x08 /* Private */,
      10,    5,  304,    2, 0x08 /* Private */,
      16,    0,  315,    2, 0x08 /* Private */,
      17,    0,  316,    2, 0x08 /* Private */,
      18,    0,  317,    2, 0x08 /* Private */,
      19,    1,  318,    2, 0x08 /* Private */,
      21,    1,  321,    2, 0x08 /* Private */,
      22,    1,  324,    2, 0x08 /* Private */,
      23,    1,  327,    2, 0x08 /* Private */,
      24,    1,  330,    2, 0x08 /* Private */,
      25,    0,  333,    2, 0x08 /* Private */,
      26,    0,  334,    2, 0x08 /* Private */,
      27,    0,  335,    2, 0x08 /* Private */,
      28,    0,  336,    2, 0x08 /* Private */,
      29,    0,  337,    2, 0x08 /* Private */,
      30,    1,  338,    2, 0x08 /* Private */,
      31,    1,  341,    2, 0x08 /* Private */,
      32,    1,  344,    2, 0x08 /* Private */,
      33,    1,  347,    2, 0x08 /* Private */,
      34,    1,  350,    2, 0x08 /* Private */,
      35,    0,  353,    2, 0x08 /* Private */,
      36,    1,  354,    2, 0x08 /* Private */,
      37,    1,  357,    2, 0x08 /* Private */,
      38,    1,  360,    2, 0x08 /* Private */,
      39,    1,  363,    2, 0x08 /* Private */,
      40,    1,  366,    2, 0x08 /* Private */,
      41,    1,  369,    2, 0x08 /* Private */,
      42,    2,  372,    2, 0x08 /* Private */,
      45,    2,  377,    2, 0x08 /* Private */,
      46,    0,  382,    2, 0x08 /* Private */,
      47,    0,  383,    2, 0x08 /* Private */,
      48,    0,  384,    2, 0x08 /* Private */,
      49,    0,  385,    2, 0x08 /* Private */,
      50,    1,  386,    2, 0x08 /* Private */,
      52,    1,  389,    2, 0x08 /* Private */,
      54,    0,  392,    2, 0x08 /* Private */,
      55,    0,  393,    2, 0x08 /* Private */,
      56,    0,  394,    2, 0x08 /* Private */,
      57,    0,  395,    2, 0x08 /* Private */,
      58,    0,  396,    2, 0x08 /* Private */,
      59,    0,  397,    2, 0x08 /* Private */,
      60,    0,  398,    2, 0x08 /* Private */,
      61,    0,  399,    2, 0x08 /* Private */,
      62,    1,  400,    2, 0x08 /* Private */,
      64,    1,  403,    2, 0x08 /* Private */,
      65,    1,  406,    2, 0x08 /* Private */,
      66,    1,  409,    2, 0x08 /* Private */,
      67,    0,  412,    2, 0x08 /* Private */,
      68,    0,  413,    2, 0x08 /* Private */,
      69,    0,  414,    2, 0x08 /* Private */,
      70,    0,  415,    2, 0x08 /* Private */,
      71,    1,  416,    2, 0x08 /* Private */,
      72,    1,  419,    2, 0x08 /* Private */,
      74,    1,  422,    2, 0x08 /* Private */,
      75,    1,  425,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, 0x80000000 | 7, QMetaType::Bool,    6,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   43,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 51,    2,
    QMetaType::Void, 0x80000000 | 53,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   63,
    QMetaType::Void, QMetaType::Double,   63,
    QMetaType::Void, QMetaType::Double,   63,
    QMetaType::Void, QMetaType::Double,   63,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   63,
    QMetaType::Void, QMetaType::Int,   73,
    QMetaType::Void, QMetaType::Int,   63,
    QMetaType::Void, QMetaType::Int,   73,

       0        // eod
};

void WindowVm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WindowVm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closing((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 1: _t->on_msg_err((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->on_msg_read((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 3: _t->on_timer_plot(); break;
        case 4: _t->on_timer_digits(); break;
        case 5: _t->on_actionAbout_triggered(); break;
        case 6: _t->on_actionViewPoints_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_actionViewLines_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_actionInterpLinear_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_actionInterpSinc_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_actionShowPlot_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_actionExportStart_triggered(); break;
        case 12: _t->on_actionExportStop_triggered(); break;
        case 13: _t->on_actionExportPNG_triggered(); break;
        case 14: _t->on_actionExportPDF_triggered(); break;
        case 15: _t->on_actionExportFolder_triggered(); break;
        case 16: _t->on_actionExportCSV_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->on_actionExportTXT_Tabs_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_actionExportTXT_Semicolon_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->on_actionExportMAT_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_actionMeasEnabled_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_actionMeasReset_triggered(); break;
        case 22: _t->on_actionMeasChannel_1_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->on_actionMeasChannel_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_actionMeasChannel_3_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_actionMeasChannel_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_actionMath_1_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_actionMath_3_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_cursorH_valuesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 29: _t->on_cursorV_valuesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 30: _t->on_pushButton_cursorsHoff_clicked(); break;
        case 31: _t->on_pushButton_cursorsHon_clicked(); break;
        case 32: _t->on_pushButton_cursorsVoff_clicked(); break;
        case 33: _t->on_pushButton_cursorsVon_clicked(); break;
        case 34: _t->on_qcpMouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 35: _t->on_qcpMousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 36: _t->on_pushButton_disable1_clicked(); break;
        case 37: _t->on_pushButton_enable1_clicked(); break;
        case 38: _t->on_pushButton_disable2_clicked(); break;
        case 39: _t->on_pushButton_enable2_clicked(); break;
        case 40: _t->on_pushButton_disable3_clicked(); break;
        case 41: _t->on_pushButton_enable3_clicked(); break;
        case 42: _t->on_pushButton_disable4_clicked(); break;
        case 43: _t->on_pushButton_enable4_clicked(); break;
        case 44: _t->on_doubleSpinBox_gain1_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 45: _t->on_doubleSpinBox_gain2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 46: _t->on_doubleSpinBox_gain3_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 47: _t->on_doubleSpinBox_gain4_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 48: _t->on_pushButton_disable_clicked(); break;
        case 49: _t->on_pushButton_enable_clicked(); break;
        case 50: _t->on_pushButton_reset_clicked(); break;
        case 51: _t->on_pushButton_resetZoom_clicked(); break;
        case 52: _t->on_spinBox_average_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->on_dial_average_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->on_spinBox_display_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->on_dial_display_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WindowVm::*)(const char * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WindowVm::closing)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WindowVm::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_WindowVm.data,
    qt_meta_data_WindowVm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WindowVm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WindowVm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WindowVm.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "IEmboInstrument"))
        return static_cast< IEmboInstrument*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int WindowVm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 56)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 56;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 56)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 56;
    }
    return _id;
}

// SIGNAL 0
void WindowVm::closing(const char * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
