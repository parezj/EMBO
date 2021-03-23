QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

win32:RC_ICONS = icon.ico
macx: ICON = icon.icns


greaterThan(QT_MAJOR_VERSION, 4){
    TARGET_ARCH=$${QT_ARCH}
}else{
    TARGET_ARCH=$${QMAKE_HOST.arch}
}

include(__crashhandler/qBreakpad.pri)
include(__updater/QSimpleUpdater.pri)

contains(TARGET_ARCH, x86_64){
    ARCHITECTURE = x64
    QMAKE_LIBDIR += $$PWD/lib/x64
}else{
    QMAKE_LIBDIR += $$PWD/lib/x86
    ARCHITECTURE = x86
}

macx: LIBS += -framework AppKit
LIBS += -lqBreakpad


VERSION = 0.0.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QMAKE_TARGET_COMPANY = CTU Jakub Parez
QMAKE_TARGET_PRODUCT = EMBO
QMAKE_TARGET_DESCRIPTION = EMBedded Oscilloscope
QMAKE_TARGET_COPYRIGHT = CTU Jakub Parez


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    core.cpp \
    lib/ctkrangeslider.cpp \
    lib/qcustomplot.cpp \
    main.cpp \
    messages.cpp \
    msg.cpp \
    qcpcursors.cpp \
    settings.cpp \
    utils.cpp \
    window__main.cpp \
    window_cntr.cpp \
    window_la.cpp \
    window_pwm.cpp \
    window_scope.cpp \
    window_sgen.cpp \
    window_vm.cpp

HEADERS += \
    core.h \
    css.h \
    interfaces.h \
    lib/ctkrangeslider.h \
    lib/qcustomplot.h \
    messages.h \
    movemean.h \
    msg.h \
    qcpcursors.h \
    settings.h \
    utils.h \
    window__main.h \
    window_cntr.h \
    window_la.h \
    window_pwm.h \
    window_scope.h \
    window_sgen.h \
    window_vm.h

FORMS += \
    window__main.ui \
    window_cntr.ui \
    window_la.ui \
    window_pwm.ui \
    window_scope.ui \
    window_sgen.ui \
    window_vm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    icon.icns \
    icon.ico
