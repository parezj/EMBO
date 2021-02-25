QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RC_ICONS = icon.ico

VERSION = 0.0.2.0
QMAKE_TARGET_COMPANY = CTU/Jakub Parez
QMAKE_TARGET_PRODUCT = EMBO
QMAKE_TARGET_DESCRIPTION = EMBedded Oscilloscope
QMAKE_TARGET_COPYRIGHT = Jakub Parez

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    lib/qcustomplot.cpp \
    main.cpp \
    msg.cpp \
    utils.cpp \
    window_main.cpp

HEADERS += \
    core.h \
    lib/qcustomplot.h \
    msg.h \
    utils.h \
    window_main.h

FORMS += \
    window_main.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    css/style.css \
    icon.ico
