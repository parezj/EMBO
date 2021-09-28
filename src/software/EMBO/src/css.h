/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CSS_H
#define CSS_H

/* groups */


#define CSS_INSTR_GROUP_SCOPE "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(190,220,240,0.5), stop:0.32 rgba(190,220,240,0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_LA    "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(240,190,190,0.5), stop:0.32 rgba(240,190,190,0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_VM    "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(240,230,190, 0.5), stop:0.32 rgba(240,230,190, 0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_CNTR  "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(200,220,200,0.5), stop:0.32 rgba(200,220,200,0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_PWM   "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(220,200,180,0.5), stop:0.32 rgba(220,200,180,0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_SGEN  "QGroupBox {background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0  rgba(200,200,220,0.5), stop:0.32 rgba(200,200,220,0.5), stop:1  black); \
                                          border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
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

#define CSS_BUTTON_SCAN       " QPushButton { text-align:left; padding-left:7px  }"
#define CSS_BUTTON_CONNECT    " QPushButton { text-align:left; padding-left:18px }"
#define CSS_BUTTON_DISCONNECT " QPushButton { text-align:left; padding-left:8px  }"

#define CSS_BUTTON_SCOPE      " QPushButton { text-align:left; padding-left:20px }"
#define CSS_BUTTON_LA         " QPushButton { text-align:left; padding-left:15px }"
#define CSS_BUTTON_VM         " QPushButton { text-align:left; padding-left:31px }"
#define CSS_BUTTON_CNTR       " QPushButton { text-align:left; padding-left:41px }"
#define CSS_BUTTON_PWM        " QPushButton { text-align:left; padding-left:10px }"
#define CSS_BUTTON_SGEN       " QPushButton { text-align:left; padding-left:8px  }"

#define CSS_BUTTON_CNTR_ON    " QPushButton { text-align:left; padding-left:13px }"
#define CSS_BUTTON_PWM_ON     " QPushButton { text-align:left; padding-left:15px }"
#define CSS_BUTTON_SGEN_ON    " QPushButton { text-align:left; padding-left:15px }"
#define CSS_BUTTON_VM_ON      " QPushButton { text-align:left; padding-left:13px }"
#define CSS_BUTTON_VM_MAIN    " QPushButton { text-align:left; padding-left:22px }"
#define CSS_BUTTON_VM_RESET   " QPushButton { text-align:left; padding-left:5px }"
#define CSS_BUTTON_VM_RESETZ  " QPushButton { text-align:left; padding-left:4px  }"

#define CSS_BUTTON_CH         " QPushButton { text-align:left; padding-left:13px }"
#define CSS_BUTTON_FORC       " QPushButton { text-align:left; padding-left:13px }"
#define CSS_BUTTON_FFT        " QPushButton { text-align:left; padding-left:11px }"
#define CSS_BUTTON_BIT        " QPushButton { text-align:left; padding-left:8px }"
#define CSS_BUTTON_AVG        " QPushButton { text-align:left; padding-left:11px }"


#define CSS_BUTTON_ON         "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #AAAAAA); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_OFF        "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #69D769); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #ACFAAC); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_ON_NODIS   "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #AAAAAA); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }  \
                               QPushButton:disabled { color: black; }"

#define CSS_BUTTON_OFF_NODIS  "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #69D769); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #ACFAAC); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }  \
                               QPushButton:disabled { color: black; }"

#define CSS_INSTR_BUTTON_OFF  "QPushButton {padding: 0.2em 0.2em 0.3em 0.2em; color: gray; border: 1px solid gray; border-radius: 5px;}"

/* channel buttons */

#define CSS_BUTTON_CH1        "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #0072BD); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #63BFFC); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_CH2        "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #D95319); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #FDA47D); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_CH3        "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #77AC30); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #C3F384); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_CH4        "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #7E2F8E); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #CC70DE); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; } \
                               QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \
                                                      background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"

#define CSS_BUTTON_CH1_NODIS  "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #0072BD); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #63BFFC); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }"

#define CSS_BUTTON_CH2_NODIS  "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #D95319); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #FDA47D); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }"

#define CSS_BUTTON_CH3_NODIS   "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #77AC30); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #C3F384); } \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }"

#define CSS_BUTTON_CH4_NODIS  "QPushButton { padding: 0.2em 0.2em 0.3em 0.2em; border: 1px solid rgb(150, 150, 150); border-radius: 5px; color: black; \
                                             background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #7E2F8E); } \
                               QPushButton:hover:!pressed { border: 1px solid rgb(150, 150, 150); border-radius: 5px; color:#256552; \
                                                            background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1 #CC70DE);} \
                               QPushButton:pressed { border: 2px solid rgb(150, 150, 150); border-radius: 5px; background: #FFFFFF; color:#2f836a; }"

/* radio buttons */

#define CSS_RADIOBUTTON        "QRadioButton:checked { background-color: rgba(245,245,245, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:hover { background-color: rgba(230,230,230, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:checked:hover { background-color: rgba(245,245,245, 0.8); border: 0px; border-radius:5px; } \
                                QRadioButton::indicator { width: 20px; height: 20px; } \
                                QRadioButton::indicator:unchecked { image: url(:/main/img/radio_off1.png); } \
                                QRadioButton::indicator:unchecked:hover { image: url(:/main/img/radio_off1.png); } \
                                QRadioButton::indicator:checked { image: url(:/main/img/radio_on2.png); } \
                                QRadioButton::indicator::disabled { image: url(:/main/img/radio_off_dis.png); } \
                                QRadioButton::disabled { color:gray; }"

#define CSS_RADIOBUTTON_NODIS  "QRadioButton:checked { background-color: rgba(245,245,245, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:hover { background-color: rgba(230,230,230, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:checked:hover { background-color: rgba(245,245,245, 0.8); border: 0px; border-radius:5px; } \
                                QRadioButton::indicator { width: 20px; height: 20px; } \
                                QRadioButton::indicator:unchecked { image: url(:/main/img/radio_off1.png); } \
                                QRadioButton::indicator:unchecked:hover { image: url(:/main/img/radio_off1.png); } \
                                QRadioButton::indicator:checked { image: url(:/main/img/radio_on2.png); }"

/* input controls */

#define CSS_TEXTBOX            "QTextBrowser { background-color: rgba(245,245,245, 1.0); border: 1px solid gray; border-radius:10px; \
                                               text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QTextBrowser:disabled { background-color: transparent; border: 1px solid gray; border-radius:10px; \
                                                        text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }"

#define CSS_TEXTBOX_NODIS      "QTextBrowser { background-color: rgba(245,245,245, 1.0); border: 1px solid gray; border-radius:10px; \
                                               text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }"

#define CSS_SPINBOX            "QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px; \
                                           text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up4.png); } \
                                QSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down4.png); } \
                                QSpinBox::up-button:hover { image: url(:/main/img/arrow_up4b.png); } \
                                QSpinBox::down-button:hover { image: url(:/main/img/arrow_down4b.png); } \
                                QSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:10px; \
                                                    border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px; \
                                                    text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up3.png); } \
                                QSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down3.png); }"

#define CSS_SPINBOX_NODIS      "QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px; \
                                           text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up4.png); } \
                                QSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down4.png); } \
                                QSpinBox::up-button:hover { image: url(:/main/img/arrow_up4b.png); } \
                                QSpinBox::down-button:hover { image: url(:/main/img/arrow_down4b.png); } \
                                QSpinBox:disabled { color: black; }"

// special style
#define CSS_DSPINBOX           "QDoubleSpinBox { background-color: white;border: 1px solid gray; border-radius:10px; color:black; \
                                                 text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  } \
                                QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up4.png); } \
                                QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down4.png); } \
                                QDoubleSpinBox::up-button:hover { image: url(:/main/img/arrow_up4b.png); } \
                                QDoubleSpinBox::down-button:hover { image: url(:/main/img/arrow_down4b.png); } \
                                QDoubleSpinBox:disabled { background-color: rgba(220,220,220, 1.0); border: 1px transparent; border-radius:10px; \
                                                          border: 1px solid gray; border-radius:10px; \
                                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up3.png); } \
                                QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down3.png); }"

#define CSS_DSPINBOX_NODIS     "QDoubleSpinBox { background-color: white;border: 1px solid gray; border-radius:10px; color:black; \
                                                 text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  } \
                                QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up4.png); } \
                                QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down4.png); } \
                                QDoubleSpinBox::up-button:hover { image: url(:/main/img/arrow_up4b.png); } \
                                QDoubleSpinBox::down-button:hover { image: url(:/main/img/arrow_down4b.png); }"

// like spinbox
#define CSS_DSPINBOX2          "QDoubleSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px; \
                                text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  } \
                                QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up4.png); } \
                                QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down4.png); } \
                                QDoubleSpinBox::up-button:hover { image: url(:/main/img/arrow_up4b.png); } \
                                QDoubleSpinBox::down-button:hover { image: url(:/main/img/arrow_down4b.png); } \
                                QDoubleSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:10px; \
                                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px; \
                                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_up3.png); } \
                                QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/img/arrow_down3.png); }"

/* trigger sliders */

#define CSS_SCOPE_TRIG_PRE      "QSlider { min-height: 10px; max-height: 10px; margin-left: 28px; margin-right:0px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } \
                                 QSlider::handle:horizontal { width: 36px; image: url(:/main/img/range_up_sm.png); } \
                                 QSlider::handle:horizontal:hover { width: 36px; image: url(:/main/img/range_up2_sm.png); }"

#define CSS_SCOPE_TRIG_VAL      "QSlider { min-width: 10px; max-width: 10px; margin-bottom: 14px; margin-top: 0px; } \
                                 QSlider::groove:vertical { background-color: transparent; } \
                                 QSlider::handle:vertical { height: 36px; image: url(:/main/img/range_right_sm.png); } \
                                 QSlider::handle:vertical:hover { height:36px; image: url(:/main/img/range_right2_sm.png); }"

#define CSS_LA_TRIG_PRE         "QSlider { min-height: 10px; max-height: 10px; margin-left: 8px; margin-right:0px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } \
                                 QSlider::handle:horizontal { width: 36px; image: url(:/main/img/range_up_sm.png); } \
                                 QSlider::handle:horizontal:hover { width: 36px; image: url(:/main/img/range_up2_sm.png); }"

#define CSS_SCOPE_TRIG_PRE_OFF  "QSlider { min-height: 10px; max-height: 10px; margin-left: 8px; margin-right:0px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } QSlider::handle:horizontal { width: 36px; }"
#define CSS_SCOPE_TRIG_VAL_OFF  "QSlider { min-width: 10px; max-width: 10px; margin-bottom: 14px; margin-top: 0px; } \
                                 QSlider::groove:vertical { background-color: transparent; } QSlider::handle:vertical { height: 36px; }"
#define CSS_LA_TRIG_PRE_OFF     "QSlider { min-height: 10px; max-height: 10px; margin-left: 8px; margin-right:0px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } QSlider::handle:horizontal { width: 36px; }"

 /* trigger led */

#define CSS_TRIG_LED1           "QRadioButton::indicator { width: 25px; height: 25px; } \
                                 QRadioButton::indicator::unchecked { image: url(:/main/img/led_gray.png); } \
                                 QRadioButton::indicator::checked   { image: url(:/main/img/led_green.png); }"

#define CSS_TRIG_LED2           "QRadioButton::indicator { width: 25px; height: 25px; } \
                                 QRadioButton::indicator::unchecked { image: url(:/main/img/led_gray.png); } \
                                 QRadioButton::indicator::checked   { image: url(:/main/img/led_green4.png); }"

/* cursors */
#define CSS_CURSOR_H            "ctkRangeSlider { min-height: 25px; max-height: 25px; margin-left: 20px; margin-right:2px; } \
                                 ctkRangeSlider::groove:horizontal { background-color: transparent; } \
                                 ctkRangeSlider::handle:horizontal { width: 25px; image: url(:/main/img/range_down.png); } \
                                 ctkRangeSlider::handle:horizontal:hover { width: 25px; image: url(:/main/img/range_down2.png); } \
                                 QSlider { min-height: 25px; max-height: 25px; margin-left: 20px; margin-right:2px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } \
                                 QSlider::handle:horizontal { width: 25px; image: url(:/main/img/range_down.png); } \
                                 QSlider::handle:horizontal:hover { width: 25px; image: url(:/main/img/range_down2.png); }"

#define CSS_CURSOR_H2           "ctkRangeSlider { min-height: 25px; max-height: 25px; margin-left: 30px; margin-right:2px; } \
                                 ctkRangeSlider::groove:horizontal { background-color: transparent; } \
                                 ctkRangeSlider::handle:horizontal { width: 25px; image: url(:/main/img/range_down.png); } \
                                 ctkRangeSlider::handle:horizontal:hover { width: 25px; image: url(:/main/img/range_down2.png); } \
                                 QSlider { min-height: 25px; max-height: 25px; margin-left: 30px; margin-right:2px; } \
                                 QSlider::groove:horizontal { background-color: transparent; } \
                                 QSlider::handle:horizontal { width: 25px; image: url(:/main/img/range_down.png); } \
                                 QSlider::handle:horizontal:hover { width: 25px; image: url(:/main/img/range_down2.png); }"

/* plot colors  */

#define COLOR1      "#0072BD"
#define COLOR2      "#D95319"
#define COLOR3      "#EDB120"
#define COLOR4      "#7E2F8E"
#define COLOR5      "#77AC30"
#define COLOR6      "#4DBEEE"
#define COLOR7      "#A2142F"

#define COLOR9      "#256552"

#endif // CSS_H
