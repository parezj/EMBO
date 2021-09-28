/****************************************************************************
** Meta object code from reading C++ file 'window_scope.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../EMBO/src/windows/window_scope.h"
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
    QByteArrayData data[143];
    char stringdata0[3387];
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
QT_MOC_LITERAL(5, 43, 10), // "on_msg_set"
QT_MOC_LITERAL(6, 54, 7), // "DaqBits"
QT_MOC_LITERAL(7, 62, 4), // "bits"
QT_MOC_LITERAL(8, 67, 3), // "mem"
QT_MOC_LITERAL(9, 71, 2), // "fs"
QT_MOC_LITERAL(10, 74, 3), // "ch1"
QT_MOC_LITERAL(11, 78, 3), // "ch2"
QT_MOC_LITERAL(12, 82, 3), // "ch3"
QT_MOC_LITERAL(13, 86, 3), // "ch4"
QT_MOC_LITERAL(14, 90, 7), // "trig_ch"
QT_MOC_LITERAL(15, 98, 8), // "trig_val"
QT_MOC_LITERAL(16, 107, 11), // "DaqTrigEdge"
QT_MOC_LITERAL(17, 119, 9), // "trig_edge"
QT_MOC_LITERAL(18, 129, 11), // "DaqTrigMode"
QT_MOC_LITERAL(19, 141, 9), // "trig_mode"
QT_MOC_LITERAL(20, 151, 8), // "trig_pre"
QT_MOC_LITERAL(21, 160, 4), // "maxZ"
QT_MOC_LITERAL(22, 165, 9), // "smpl_time"
QT_MOC_LITERAL(23, 175, 9), // "fs_real_n"
QT_MOC_LITERAL(24, 185, 7), // "fs_real"
QT_MOC_LITERAL(25, 193, 11), // "on_msg_read"
QT_MOC_LITERAL(26, 205, 4), // "data"
QT_MOC_LITERAL(27, 210, 10), // "on_msg_err"
QT_MOC_LITERAL(28, 221, 4), // "text"
QT_MOC_LITERAL(29, 226, 10), // "MsgBoxType"
QT_MOC_LITERAL(30, 237, 4), // "type"
QT_MOC_LITERAL(31, 242, 9), // "needClose"
QT_MOC_LITERAL(32, 252, 13), // "on_msg_ok_set"
QT_MOC_LITERAL(33, 266, 19), // "on_msg_ok_forceTrig"
QT_MOC_LITERAL(34, 286, 15), // "on_msg_daqReady"
QT_MOC_LITERAL(35, 302, 5), // "Ready"
QT_MOC_LITERAL(36, 308, 5), // "ready"
QT_MOC_LITERAL(37, 314, 8), // "firstPos"
QT_MOC_LITERAL(38, 323, 13), // "on_timer_plot"
QT_MOC_LITERAL(39, 337, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(40, 362, 29), // "on_actionViewPoints_triggered"
QT_MOC_LITERAL(41, 392, 7), // "checked"
QT_MOC_LITERAL(42, 400, 28), // "on_actionViewLines_triggered"
QT_MOC_LITERAL(43, 429, 31), // "on_actionInterpLinear_triggered"
QT_MOC_LITERAL(44, 461, 29), // "on_actionInterpSinc_triggered"
QT_MOC_LITERAL(45, 491, 29), // "on_actionExportSave_triggered"
QT_MOC_LITERAL(46, 521, 28), // "on_actionExportPNG_triggered"
QT_MOC_LITERAL(47, 550, 28), // "on_actionExportPDF_triggered"
QT_MOC_LITERAL(48, 579, 31), // "on_actionExportFolder_triggered"
QT_MOC_LITERAL(49, 611, 28), // "on_actionExportCSV_triggered"
QT_MOC_LITERAL(50, 640, 33), // "on_actionExportTXT_Tabs_trigg..."
QT_MOC_LITERAL(51, 674, 38), // "on_actionExportTXT_Semicolon_..."
QT_MOC_LITERAL(52, 713, 28), // "on_actionExportMAT_triggered"
QT_MOC_LITERAL(53, 742, 30), // "on_actionMeasEnabled_triggered"
QT_MOC_LITERAL(54, 773, 28), // "on_actionMeasReset_triggered"
QT_MOC_LITERAL(55, 802, 32), // "on_actionMeasChannel_1_triggered"
QT_MOC_LITERAL(56, 835, 32), // "on_actionMeasChannel_2_triggered"
QT_MOC_LITERAL(57, 868, 32), // "on_actionMeasChannel_3_triggered"
QT_MOC_LITERAL(58, 901, 32), // "on_actionMeasChannel_4_triggered"
QT_MOC_LITERAL(59, 934, 27), // "on_actionMath_1_2_triggered"
QT_MOC_LITERAL(60, 962, 27), // "on_actionMath_3_4_triggered"
QT_MOC_LITERAL(61, 990, 34), // "on_actionMath_XY_X_1_Y_2_trig..."
QT_MOC_LITERAL(62, 1025, 34), // "on_actionMath_XY_X_3_Y_4_trig..."
QT_MOC_LITERAL(63, 1060, 31), // "on_actionFFTChannel_1_triggered"
QT_MOC_LITERAL(64, 1092, 31), // "on_actionFFTChannel_2_triggered"
QT_MOC_LITERAL(65, 1124, 31), // "on_actionFFTChannel_3_triggered"
QT_MOC_LITERAL(66, 1156, 31), // "on_actionFFTChannel_4_triggered"
QT_MOC_LITERAL(67, 1188, 34), // "on_actionFFTSplit_Screen_trig..."
QT_MOC_LITERAL(68, 1223, 24), // "on_cursorH_valuesChanged"
QT_MOC_LITERAL(69, 1248, 3), // "min"
QT_MOC_LITERAL(70, 1252, 3), // "max"
QT_MOC_LITERAL(71, 1256, 24), // "on_cursorV_valuesChanged"
QT_MOC_LITERAL(72, 1281, 33), // "on_pushButton_cursorsHoff_cli..."
QT_MOC_LITERAL(73, 1315, 32), // "on_pushButton_cursorsHon_clicked"
QT_MOC_LITERAL(74, 1348, 33), // "on_pushButton_cursorsVoff_cli..."
QT_MOC_LITERAL(75, 1382, 32), // "on_pushButton_cursorsVon_clicked"
QT_MOC_LITERAL(76, 1415, 16), // "on_qcpMouseWheel"
QT_MOC_LITERAL(77, 1432, 12), // "QWheelEvent*"
QT_MOC_LITERAL(78, 1445, 16), // "on_qcpMousePress"
QT_MOC_LITERAL(79, 1462, 12), // "QMouseEvent*"
QT_MOC_LITERAL(80, 1475, 28), // "on_radioButton_zoomH_clicked"
QT_MOC_LITERAL(81, 1504, 28), // "on_radioButton_zoomV_clicked"
QT_MOC_LITERAL(82, 1533, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(83, 1561, 31), // "on_pushButton_resetZoom_clicked"
QT_MOC_LITERAL(84, 1593, 32), // "on_pushButton_single_off_clicked"
QT_MOC_LITERAL(85, 1626, 31), // "on_pushButton_single_on_clicked"
QT_MOC_LITERAL(86, 1658, 29), // "on_pushButton_run_off_clicked"
QT_MOC_LITERAL(87, 1688, 25), // "on_pushButton_run_clicked"
QT_MOC_LITERAL(88, 1714, 26), // "on_pushButton_stop_clicked"
QT_MOC_LITERAL(89, 1741, 36), // "on_radioButton_trigMode_Auto_..."
QT_MOC_LITERAL(90, 1778, 38), // "on_radioButton_trigMode_Norma..."
QT_MOC_LITERAL(91, 1817, 40), // "on_radioButton_trigMode_Disab..."
QT_MOC_LITERAL(92, 1858, 39), // "on_radioButton_trigSlope_Risi..."
QT_MOC_LITERAL(93, 1898, 40), // "on_radioButton_trigSlope_Fall..."
QT_MOC_LITERAL(94, 1939, 31), // "on_radioButton_trigCh_1_clicked"
QT_MOC_LITERAL(95, 1971, 31), // "on_radioButton_trigCh_2_clicked"
QT_MOC_LITERAL(96, 2003, 31), // "on_radioButton_trigCh_3_clicked"
QT_MOC_LITERAL(97, 2035, 31), // "on_radioButton_trigCh_4_clicked"
QT_MOC_LITERAL(98, 2067, 31), // "on_spinBox_trigVal_valueChanged"
QT_MOC_LITERAL(99, 2099, 4), // "arg1"
QT_MOC_LITERAL(100, 2104, 28), // "on_dial_trigVal_valueChanged"
QT_MOC_LITERAL(101, 2133, 5), // "value"
QT_MOC_LITERAL(102, 2139, 31), // "on_spinBox_trigPre_valueChanged"
QT_MOC_LITERAL(103, 2171, 28), // "on_dial_trigPre_valueChanged"
QT_MOC_LITERAL(104, 2200, 30), // "on_pushButton_trigForc_clicked"
QT_MOC_LITERAL(105, 2231, 18), // "on_hideTrigSliders"
QT_MOC_LITERAL(106, 2250, 29), // "on_dial_trigVal_sliderPressed"
QT_MOC_LITERAL(107, 2280, 29), // "on_dial_trigPre_sliderPressed"
QT_MOC_LITERAL(108, 2310, 30), // "on_dial_trigVal_sliderReleased"
QT_MOC_LITERAL(109, 2341, 30), // "on_dial_trigPre_sliderReleased"
QT_MOC_LITERAL(110, 2372, 28), // "on_radioButton_fsMem_clicked"
QT_MOC_LITERAL(111, 2401, 26), // "on_radioButton_div_clicked"
QT_MOC_LITERAL(112, 2428, 27), // "on_spinBox_mem_valueChanged"
QT_MOC_LITERAL(113, 2456, 24), // "on_dial_mem_valueChanged"
QT_MOC_LITERAL(114, 2481, 26), // "on_spinBox_fs_valueChanged"
QT_MOC_LITERAL(115, 2508, 23), // "on_dial_fs_valueChanged"
QT_MOC_LITERAL(116, 2532, 27), // "on_spinBox_div_valueChanged"
QT_MOC_LITERAL(117, 2560, 24), // "on_dial_div_valueChanged"
QT_MOC_LITERAL(118, 2585, 30), // "on_pushButton_disable1_clicked"
QT_MOC_LITERAL(119, 2616, 30), // "on_pushButton_disable2_clicked"
QT_MOC_LITERAL(120, 2647, 30), // "on_pushButton_disable3_clicked"
QT_MOC_LITERAL(121, 2678, 30), // "on_pushButton_disable4_clicked"
QT_MOC_LITERAL(122, 2709, 29), // "on_pushButton_enable1_clicked"
QT_MOC_LITERAL(123, 2739, 29), // "on_pushButton_enable2_clicked"
QT_MOC_LITERAL(124, 2769, 29), // "on_pushButton_enable3_clicked"
QT_MOC_LITERAL(125, 2799, 29), // "on_pushButton_enable4_clicked"
QT_MOC_LITERAL(126, 2829, 38), // "on_doubleSpinBox_gain_ch1_val..."
QT_MOC_LITERAL(127, 2868, 38), // "on_doubleSpinBox_gain_ch2_val..."
QT_MOC_LITERAL(128, 2907, 38), // "on_doubleSpinBox_gain_ch3_val..."
QT_MOC_LITERAL(129, 2946, 38), // "on_doubleSpinBox_gain_ch4_val..."
QT_MOC_LITERAL(130, 2985, 29), // "on_dial_Vpos_ch1_valueChanged"
QT_MOC_LITERAL(131, 3015, 29), // "on_dial_Vpos_ch2_valueChanged"
QT_MOC_LITERAL(132, 3045, 29), // "on_dial_Vpos_ch3_valueChanged"
QT_MOC_LITERAL(133, 3075, 29), // "on_dial_Vpos_ch4_valueChanged"
QT_MOC_LITERAL(134, 3105, 33), // "on_pushButton_average_off_cli..."
QT_MOC_LITERAL(135, 3139, 32), // "on_pushButton_average_on_clicked"
QT_MOC_LITERAL(136, 3172, 31), // "on_spinBox_average_valueChanged"
QT_MOC_LITERAL(137, 3204, 30), // "on_pushButton_bit8_off_clicked"
QT_MOC_LITERAL(138, 3235, 29), // "on_pushButton_bit8_on_clicked"
QT_MOC_LITERAL(139, 3265, 31), // "on_pushButton_bit12_off_clicked"
QT_MOC_LITERAL(140, 3297, 30), // "on_pushButton_bit12_on_clicked"
QT_MOC_LITERAL(141, 3328, 29), // "on_pushButton_fft_off_clicked"
QT_MOC_LITERAL(142, 3358, 28) // "on_pushButton_fft_on_clicked"

    },
    "WindowScope\0closing\0\0const char*\0"
    "className\0on_msg_set\0DaqBits\0bits\0mem\0"
    "fs\0ch1\0ch2\0ch3\0ch4\0trig_ch\0trig_val\0"
    "DaqTrigEdge\0trig_edge\0DaqTrigMode\0"
    "trig_mode\0trig_pre\0maxZ\0smpl_time\0"
    "fs_real_n\0fs_real\0on_msg_read\0data\0"
    "on_msg_err\0text\0MsgBoxType\0type\0"
    "needClose\0on_msg_ok_set\0on_msg_ok_forceTrig\0"
    "on_msg_daqReady\0Ready\0ready\0firstPos\0"
    "on_timer_plot\0on_actionAbout_triggered\0"
    "on_actionViewPoints_triggered\0checked\0"
    "on_actionViewLines_triggered\0"
    "on_actionInterpLinear_triggered\0"
    "on_actionInterpSinc_triggered\0"
    "on_actionExportSave_triggered\0"
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
    "on_actionMath_XY_X_1_Y_2_triggered\0"
    "on_actionMath_XY_X_3_Y_4_triggered\0"
    "on_actionFFTChannel_1_triggered\0"
    "on_actionFFTChannel_2_triggered\0"
    "on_actionFFTChannel_3_triggered\0"
    "on_actionFFTChannel_4_triggered\0"
    "on_actionFFTSplit_Screen_triggered\0"
    "on_cursorH_valuesChanged\0min\0max\0"
    "on_cursorV_valuesChanged\0"
    "on_pushButton_cursorsHoff_clicked\0"
    "on_pushButton_cursorsHon_clicked\0"
    "on_pushButton_cursorsVoff_clicked\0"
    "on_pushButton_cursorsVon_clicked\0"
    "on_qcpMouseWheel\0QWheelEvent*\0"
    "on_qcpMousePress\0QMouseEvent*\0"
    "on_radioButton_zoomH_clicked\0"
    "on_radioButton_zoomV_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_resetZoom_clicked\0"
    "on_pushButton_single_off_clicked\0"
    "on_pushButton_single_on_clicked\0"
    "on_pushButton_run_off_clicked\0"
    "on_pushButton_run_clicked\0"
    "on_pushButton_stop_clicked\0"
    "on_radioButton_trigMode_Auto_clicked\0"
    "on_radioButton_trigMode_Normal_clicked\0"
    "on_radioButton_trigMode_Disabled_clicked\0"
    "on_radioButton_trigSlope_Rising_clicked\0"
    "on_radioButton_trigSlope_Falling_clicked\0"
    "on_radioButton_trigCh_1_clicked\0"
    "on_radioButton_trigCh_2_clicked\0"
    "on_radioButton_trigCh_3_clicked\0"
    "on_radioButton_trigCh_4_clicked\0"
    "on_spinBox_trigVal_valueChanged\0arg1\0"
    "on_dial_trigVal_valueChanged\0value\0"
    "on_spinBox_trigPre_valueChanged\0"
    "on_dial_trigPre_valueChanged\0"
    "on_pushButton_trigForc_clicked\0"
    "on_hideTrigSliders\0on_dial_trigVal_sliderPressed\0"
    "on_dial_trigPre_sliderPressed\0"
    "on_dial_trigVal_sliderReleased\0"
    "on_dial_trigPre_sliderReleased\0"
    "on_radioButton_fsMem_clicked\0"
    "on_radioButton_div_clicked\0"
    "on_spinBox_mem_valueChanged\0"
    "on_dial_mem_valueChanged\0"
    "on_spinBox_fs_valueChanged\0"
    "on_dial_fs_valueChanged\0"
    "on_spinBox_div_valueChanged\0"
    "on_dial_div_valueChanged\0"
    "on_pushButton_disable1_clicked\0"
    "on_pushButton_disable2_clicked\0"
    "on_pushButton_disable3_clicked\0"
    "on_pushButton_disable4_clicked\0"
    "on_pushButton_enable1_clicked\0"
    "on_pushButton_enable2_clicked\0"
    "on_pushButton_enable3_clicked\0"
    "on_pushButton_enable4_clicked\0"
    "on_doubleSpinBox_gain_ch1_valueChanged\0"
    "on_doubleSpinBox_gain_ch2_valueChanged\0"
    "on_doubleSpinBox_gain_ch3_valueChanged\0"
    "on_doubleSpinBox_gain_ch4_valueChanged\0"
    "on_dial_Vpos_ch1_valueChanged\0"
    "on_dial_Vpos_ch2_valueChanged\0"
    "on_dial_Vpos_ch3_valueChanged\0"
    "on_dial_Vpos_ch4_valueChanged\0"
    "on_pushButton_average_off_clicked\0"
    "on_pushButton_average_on_clicked\0"
    "on_spinBox_average_valueChanged\0"
    "on_pushButton_bit8_off_clicked\0"
    "on_pushButton_bit8_on_clicked\0"
    "on_pushButton_bit12_off_clicked\0"
    "on_pushButton_bit12_on_clicked\0"
    "on_pushButton_fft_off_clicked\0"
    "on_pushButton_fft_on_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WindowScope[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     105,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  539,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,   16,  542,    2, 0x08 /* Private */,
      25,    1,  575,    2, 0x08 /* Private */,
      27,    3,  578,    2, 0x08 /* Private */,
      32,    4,  585,    2, 0x08 /* Private */,
      33,    2,  594,    2, 0x08 /* Private */,
      34,    2,  599,    2, 0x08 /* Private */,
      38,    0,  604,    2, 0x08 /* Private */,
      39,    0,  605,    2, 0x08 /* Private */,
      40,    1,  606,    2, 0x08 /* Private */,
      42,    1,  609,    2, 0x08 /* Private */,
      43,    1,  612,    2, 0x08 /* Private */,
      44,    1,  615,    2, 0x08 /* Private */,
      45,    0,  618,    2, 0x08 /* Private */,
      46,    0,  619,    2, 0x08 /* Private */,
      47,    0,  620,    2, 0x08 /* Private */,
      48,    0,  621,    2, 0x08 /* Private */,
      49,    1,  622,    2, 0x08 /* Private */,
      50,    1,  625,    2, 0x08 /* Private */,
      51,    1,  628,    2, 0x08 /* Private */,
      52,    1,  631,    2, 0x08 /* Private */,
      53,    1,  634,    2, 0x08 /* Private */,
      54,    0,  637,    2, 0x08 /* Private */,
      55,    1,  638,    2, 0x08 /* Private */,
      56,    1,  641,    2, 0x08 /* Private */,
      57,    1,  644,    2, 0x08 /* Private */,
      58,    1,  647,    2, 0x08 /* Private */,
      59,    1,  650,    2, 0x08 /* Private */,
      60,    1,  653,    2, 0x08 /* Private */,
      61,    1,  656,    2, 0x08 /* Private */,
      62,    1,  659,    2, 0x08 /* Private */,
      63,    1,  662,    2, 0x08 /* Private */,
      64,    1,  665,    2, 0x08 /* Private */,
      65,    1,  668,    2, 0x08 /* Private */,
      66,    1,  671,    2, 0x08 /* Private */,
      67,    1,  674,    2, 0x08 /* Private */,
      68,    2,  677,    2, 0x08 /* Private */,
      71,    2,  682,    2, 0x08 /* Private */,
      72,    0,  687,    2, 0x08 /* Private */,
      73,    0,  688,    2, 0x08 /* Private */,
      74,    0,  689,    2, 0x08 /* Private */,
      75,    0,  690,    2, 0x08 /* Private */,
      76,    1,  691,    2, 0x08 /* Private */,
      78,    1,  694,    2, 0x08 /* Private */,
      80,    1,  697,    2, 0x08 /* Private */,
      81,    1,  700,    2, 0x08 /* Private */,
      82,    0,  703,    2, 0x08 /* Private */,
      83,    0,  704,    2, 0x08 /* Private */,
      84,    0,  705,    2, 0x08 /* Private */,
      85,    0,  706,    2, 0x08 /* Private */,
      86,    0,  707,    2, 0x08 /* Private */,
      87,    0,  708,    2, 0x08 /* Private */,
      88,    0,  709,    2, 0x08 /* Private */,
      89,    1,  710,    2, 0x08 /* Private */,
      90,    1,  713,    2, 0x08 /* Private */,
      91,    1,  716,    2, 0x08 /* Private */,
      92,    1,  719,    2, 0x08 /* Private */,
      93,    1,  722,    2, 0x08 /* Private */,
      94,    1,  725,    2, 0x08 /* Private */,
      95,    1,  728,    2, 0x08 /* Private */,
      96,    1,  731,    2, 0x08 /* Private */,
      97,    1,  734,    2, 0x08 /* Private */,
      98,    1,  737,    2, 0x08 /* Private */,
     100,    1,  740,    2, 0x08 /* Private */,
     102,    1,  743,    2, 0x08 /* Private */,
     103,    1,  746,    2, 0x08 /* Private */,
     104,    0,  749,    2, 0x08 /* Private */,
     105,    0,  750,    2, 0x08 /* Private */,
     106,    0,  751,    2, 0x08 /* Private */,
     107,    0,  752,    2, 0x08 /* Private */,
     108,    0,  753,    2, 0x08 /* Private */,
     109,    0,  754,    2, 0x08 /* Private */,
     110,    1,  755,    2, 0x08 /* Private */,
     111,    1,  758,    2, 0x08 /* Private */,
     112,    1,  761,    2, 0x08 /* Private */,
     113,    1,  764,    2, 0x08 /* Private */,
     114,    1,  767,    2, 0x08 /* Private */,
     115,    1,  770,    2, 0x08 /* Private */,
     116,    1,  773,    2, 0x08 /* Private */,
     117,    1,  776,    2, 0x08 /* Private */,
     118,    0,  779,    2, 0x08 /* Private */,
     119,    0,  780,    2, 0x08 /* Private */,
     120,    0,  781,    2, 0x08 /* Private */,
     121,    0,  782,    2, 0x08 /* Private */,
     122,    0,  783,    2, 0x08 /* Private */,
     123,    0,  784,    2, 0x08 /* Private */,
     124,    0,  785,    2, 0x08 /* Private */,
     125,    0,  786,    2, 0x08 /* Private */,
     126,    1,  787,    2, 0x08 /* Private */,
     127,    1,  790,    2, 0x08 /* Private */,
     128,    1,  793,    2, 0x08 /* Private */,
     129,    1,  796,    2, 0x08 /* Private */,
     130,    1,  799,    2, 0x08 /* Private */,
     131,    1,  802,    2, 0x08 /* Private */,
     132,    1,  805,    2, 0x08 /* Private */,
     133,    1,  808,    2, 0x08 /* Private */,
     134,    0,  811,    2, 0x08 /* Private */,
     135,    0,  812,    2, 0x08 /* Private */,
     136,    1,  813,    2, 0x08 /* Private */,
     137,    0,  816,    2, 0x08 /* Private */,
     138,    0,  817,    2, 0x08 /* Private */,
     139,    0,  818,    2, 0x08 /* Private */,
     140,    0,  819,    2, 0x08 /* Private */,
     141,    0,  820,    2, 0x08 /* Private */,
     142,    0,  821,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Int, QMetaType::Int, 0x80000000 | 16, 0x80000000 | 18, QMetaType::Int, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,    7,    8,    9,   10,   11,   12,   13,   14,   15,   17,   19,   20,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::QByteArray,   26,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 29, QMetaType::Bool,   28,   30,   31,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::QString,   21,   22,   23,   24,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, 0x80000000 | 35, QMetaType::Int,   36,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   69,   70,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   69,   70,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 77,    2,
    QMetaType::Void, 0x80000000 | 79,    2,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   99,
    QMetaType::Void, QMetaType::Double,   99,
    QMetaType::Void, QMetaType::Double,   99,
    QMetaType::Void, QMetaType::Double,   99,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   99,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 1: _t->on_msg_set((*reinterpret_cast< DaqBits(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])),(*reinterpret_cast< int(*)>(_a[9])),(*reinterpret_cast< DaqTrigEdge(*)>(_a[10])),(*reinterpret_cast< DaqTrigMode(*)>(_a[11])),(*reinterpret_cast< int(*)>(_a[12])),(*reinterpret_cast< double(*)>(_a[13])),(*reinterpret_cast< double(*)>(_a[14])),(*reinterpret_cast< double(*)>(_a[15])),(*reinterpret_cast< const QString(*)>(_a[16]))); break;
        case 2: _t->on_msg_read((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->on_msg_err((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< MsgBoxType(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->on_msg_ok_set((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 5: _t->on_msg_ok_forceTrig((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->on_msg_daqReady((*reinterpret_cast< Ready(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_timer_plot(); break;
        case 8: _t->on_actionAbout_triggered(); break;
        case 9: _t->on_actionViewPoints_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_actionViewLines_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_actionInterpLinear_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->on_actionInterpSinc_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_actionExportSave_triggered(); break;
        case 14: _t->on_actionExportPNG_triggered(); break;
        case 15: _t->on_actionExportPDF_triggered(); break;
        case 16: _t->on_actionExportFolder_triggered(); break;
        case 17: _t->on_actionExportCSV_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->on_actionExportTXT_Tabs_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->on_actionExportTXT_Semicolon_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_actionExportMAT_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_actionMeasEnabled_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->on_actionMeasReset_triggered(); break;
        case 23: _t->on_actionMeasChannel_1_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->on_actionMeasChannel_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: _t->on_actionMeasChannel_3_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_actionMeasChannel_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_actionMath_1_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->on_actionMath_3_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->on_actionMath_XY_X_1_Y_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->on_actionMath_XY_X_3_Y_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->on_actionFFTChannel_1_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 32: _t->on_actionFFTChannel_2_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 33: _t->on_actionFFTChannel_3_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->on_actionFFTChannel_4_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 35: _t->on_actionFFTSplit_Screen_triggered((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 36: _t->on_cursorH_valuesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 37: _t->on_cursorV_valuesChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->on_pushButton_cursorsHoff_clicked(); break;
        case 39: _t->on_pushButton_cursorsHon_clicked(); break;
        case 40: _t->on_pushButton_cursorsVoff_clicked(); break;
        case 41: _t->on_pushButton_cursorsVon_clicked(); break;
        case 42: _t->on_qcpMouseWheel((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 43: _t->on_qcpMousePress((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 44: _t->on_radioButton_zoomH_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->on_radioButton_zoomV_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->on_pushButton_reset_clicked(); break;
        case 47: _t->on_pushButton_resetZoom_clicked(); break;
        case 48: _t->on_pushButton_single_off_clicked(); break;
        case 49: _t->on_pushButton_single_on_clicked(); break;
        case 50: _t->on_pushButton_run_off_clicked(); break;
        case 51: _t->on_pushButton_run_clicked(); break;
        case 52: _t->on_pushButton_stop_clicked(); break;
        case 53: _t->on_radioButton_trigMode_Auto_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->on_radioButton_trigMode_Normal_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->on_radioButton_trigMode_Disabled_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->on_radioButton_trigSlope_Rising_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: _t->on_radioButton_trigSlope_Falling_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->on_radioButton_trigCh_1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: _t->on_radioButton_trigCh_2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->on_radioButton_trigCh_3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->on_radioButton_trigCh_4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->on_spinBox_trigVal_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->on_dial_trigVal_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->on_spinBox_trigPre_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 65: _t->on_dial_trigPre_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->on_pushButton_trigForc_clicked(); break;
        case 67: _t->on_hideTrigSliders(); break;
        case 68: _t->on_dial_trigVal_sliderPressed(); break;
        case 69: _t->on_dial_trigPre_sliderPressed(); break;
        case 70: _t->on_dial_trigVal_sliderReleased(); break;
        case 71: _t->on_dial_trigPre_sliderReleased(); break;
        case 72: _t->on_radioButton_fsMem_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 73: _t->on_radioButton_div_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 74: _t->on_spinBox_mem_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 75: _t->on_dial_mem_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->on_spinBox_fs_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->on_dial_fs_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->on_spinBox_div_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->on_dial_div_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 80: _t->on_pushButton_disable1_clicked(); break;
        case 81: _t->on_pushButton_disable2_clicked(); break;
        case 82: _t->on_pushButton_disable3_clicked(); break;
        case 83: _t->on_pushButton_disable4_clicked(); break;
        case 84: _t->on_pushButton_enable1_clicked(); break;
        case 85: _t->on_pushButton_enable2_clicked(); break;
        case 86: _t->on_pushButton_enable3_clicked(); break;
        case 87: _t->on_pushButton_enable4_clicked(); break;
        case 88: _t->on_doubleSpinBox_gain_ch1_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 89: _t->on_doubleSpinBox_gain_ch2_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 90: _t->on_doubleSpinBox_gain_ch3_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 91: _t->on_doubleSpinBox_gain_ch4_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 92: _t->on_dial_Vpos_ch1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 93: _t->on_dial_Vpos_ch2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 94: _t->on_dial_Vpos_ch3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 95: _t->on_dial_Vpos_ch4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 96: _t->on_pushButton_average_off_clicked(); break;
        case 97: _t->on_pushButton_average_on_clicked(); break;
        case 98: _t->on_spinBox_average_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 99: _t->on_pushButton_bit8_off_clicked(); break;
        case 100: _t->on_pushButton_bit8_on_clicked(); break;
        case 101: _t->on_pushButton_bit12_off_clicked(); break;
        case 102: _t->on_pushButton_bit12_on_clicked(); break;
        case 103: _t->on_pushButton_fft_off_clicked(); break;
        case 104: _t->on_pushButton_fft_on_clicked(); break;
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
        if (_id < 105)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 105;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 105)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 105;
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
