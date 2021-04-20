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
#define CSS_BUTTON_VM_RESET   " QPushButton { text-align:left; padding-left:28px }"
#define CSS_BUTTON_VM_RESETZ  " QPushButton { text-align:left; padding-left:4px  }"


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

/* radio buttons */

#define CSS_RADIOBUTTON        "QRadioButton:checked { background-color: rgba(245,245,245, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:hover { background-color: rgba(230,230,230, 1.0); border: 0px; border-radius:5px; } \
                                QRadioButton:checked:hover { background-color: rgba(245,245,245, 0.8); border: 0px; border-radius:5px; } \
                                QRadioButton::indicator { width: 20px; height: 20px; } \
                                QRadioButton::indicator:unchecked { image: url(:/main/resources/img/radio_off1.png); } \
                                QRadioButton::indicator:unchecked:hover { image: url(:/main/resources/img/radio_off1.png); } \
                                QRadioButton::indicator:checked { image: url(:/main/resources/img/radio_on2.png); }"

/* input controls */

#define CSS_TEXTBOX            "QTextBrowser { background-color: rgba(245,245,245, 1.0); border: 1px solid gray; border-radius:10px; \
                                               text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QTextBrowser:disabled { background-color: transparent; border: 1px solid gray; border-radius:10px; \
                                                        text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }"

#define CSS_TEXTBOX_NODIS      "QTextBrowser { background-color: rgba(245,245,245, 1.0); border: 1px solid gray; border-radius:10px; \
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

#define CSS_SPINBOX_NODIS      "QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px; \
                                           text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; } \
                                QSpinBox::up-button { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up4.png); } \
                                QSpinBox::down-button { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down4.png); } \
                                QSpinBox::up-button:hover { image: url(:/main/resources/img/arrow_up4b.png); } \
                                QSpinBox::down-button:hover { image: url(:/main/resources/img/arrow_down4b.png); } \
                                QSpinBox:disabled { color: black; }"


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
