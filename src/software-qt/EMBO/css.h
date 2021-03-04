/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CSS_H
#define CSS_H

/* groups */


#define CSS_INSTR_GROUP_SCOPE "QGroupBox {background-color: rgba(190,220,240,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_LA    "QGroupBox {background-color: rgba(240,190,190,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_VM    "QGroupBox {background-color: rgba(240,230,190,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_CNTR  "QGroupBox {background-color: rgba(200,220,200,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_PWM   "QGroupBox {background-color: rgba(220,200,180,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_SGEN  "QGroupBox {background-color: rgba(200,200,220,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

/* MATLAB colors

#define CSS_INSTR_GROUP_SCOPE "QGroupBox {background-color: rgba(0,114,189,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_LA    "QGroupBox {background-color: rgba(217,83,25,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_VM    "QGroupBox {background-color: rgba(237,177,32,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_CNTR  "QGroupBox {background-color: rgba(119,172,48,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_PWM   "QGroupBox {background-color: rgba(77,190,238,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_SGEN  "QGroupBox {background-color: rgba(162,20,47,0.2);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

*/

#define CSS_INSTR_GROUP_OFF   "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_GROUP2            "QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

/* buttons */

#define CSS_BUTTON_ON         "QPushButton { \
                                   padding: 0.2em 0.2em 0.3em 0.2em; \
                                   border: 1px solid rgb(100, 100, 100); \
                                   border-radius: 5px; \
                                   background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B); \
                                   color: black; \
                               } \
                               QPushButton:hover:!pressed \
                               { \
                                   border: 1px solid black; \
                                   border-radius: 5px; \
                                   background: #FFFFFF; \
                                   color:#2f836a; \
                               } \
                               QPushButton:pressed \
                               { \
                                   border: 1px solid black; \
                                   border-radius: 5px; \
                                   background: #AAAAAA; \
                                   color:white; \
                               } \
                               QPushButton:disabled { \
                                   border: 1px solid rgb(180, 180, 180); \
                                   background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); \
                                   color: gray; \
                               }"

#define CSS_INSTR_BUTTON_OFF   "QPushButton {padding: 0.2em 0.2em 0.3em 0.2em; border: 0px; color: gray;}"

/* radio buttons */

#define CSS_RADIOBUTTON        "QRadioButton:checked { background-color: rgba(245,245,245, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:hover { background-color: rgba(230,230,230, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:checked:hover { background-color: rgba(245,245,245, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton::indicator { width: 20px; height: 20px; } \
                                QRadioButton::indicator:unchecked { image: url(:/main/resources/img/radio_off1.png); } \
                                QRadioButton::indicator:unchecked:hover { image: url(:/main/resources/img/radio_off2.png); } \
                                QRadioButton::indicator:checked { image: url(:/main/resources/img/radio_on2.png); }"

/* input controls */

#define CSS_TEXTBOX            "QTextBrowser { background-color: white; border: 1px solid gray; border-radius:10px; \
                                               text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QTextBrowser:disabled { background-color: rgba(240,240,240, 1.0); \
                                                        border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px; \
                                                        text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }"

#define CSS_SPINBOX            "QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px; \
                                           text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up4.png); } \
                                QSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down4.png); } \
                                QSpinBox::up-button:hover { image: url(:/main/resources/img/arrow_up4b.png); } \
                                QSpinBox::down-button:hover { image: url(:/main/resources/img/arrow_down4b.png); } \
                                QSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:10px; \
                                                    border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px; \
                                                    text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up3.png); } \
                                QSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down3.png); }"

#endif // CSS_H
