QT       += core gui network serialport help

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

VERSION = 0.1.5
MIN_FW = 0.2.3

DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += MIN_FW_VER=\\\"$$MIN_FW\\\"

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

include(__updater/QSimpleUpdater.pri)

LINUX_LIB_DIR = ubuntu_18
MACOS_LIB_DIR = mac_10.15

win32 {

    include(__crashhandler/qBreakpad.pri)

    contains(TARGET_ARCH, x86_64) {

        ARCHITECTURE = win64
        QMAKE_LIBDIR += $$PWD/lib/win64
        LIBS += $$PWD/lib/win64/libfftw3-3.dll
        LIBS += $$PWD/lib/win64/libqBreakpad.a

        CONFIG(release, debug|release): DESTDIR = $$PWD/build-win64/release
        CONFIG(debug, debug|release): DESTDIR = $$PWD/build-win64/debug

        inst.files += $$PWD/lib/win64/libfftw3-3.dll
        inst.path += $${DESTDIR}
        INSTALLS += inst

    } else {

        ARCHITECTURE = win32
        QMAKE_LIBDIR += $$PWD/lib/win32
        LIBS += $$PWD/lib/win32/libfftw3-3.dll
        LIBS += $$PWD/lib/win32/libqBreakpad.a

        CONFIG(release, debug|release): DESTDIR = $$PWD/build-win32/release
        CONFIG(debug, debug|release): DESTDIR = $$PWD/build-win32/debug

        inst.files += $$PWD/lib/win32/libfftw3-3.dll
        inst.path += $${DESTDIR}
        INSTALLS += inst
    }
}

linux {

    #include(__crashhandler/qBreakpad.pri)

    ARCHITECTURE = linux
    QMAKE_LIBDIR += $$PWD/lib/$$LINUX_LIB_DIR
    LIBS += $$PWD/lib/$$LINUX_LIB_DIR/libfftw3.a
    #LIBS += $$PWD/lib/$$LINUX_LIB_DIR/libqBreakpad.a

    CONFIG(release, debug|release): DESTDIR = $$PWD/build/linux/release
    CONFIG(debug, debug|release): DESTDIR = $$PWD/build/linux/debug
}

macx {

    include(__crashhandler/qBreakpad.pri)

    ARCHITECTURE = mac
    QMAKE_LIBDIR += $$PWD/lib/$$MACOS_LIB_DIR
    LIBS += -framework AppKit
    LIBS += $$PWD/lib/$$MACOS_LIB_DIR/libfftw3.a
    LIBS += $$PWD/lib/$$MACOS_LIB_DIR/libqBreakpad.a

    CONFIG(release, debug|release): DESTDIR = $$PWD/build/macx/release
    CONFIG(debug, debug|release): DESTDIR = $$PWD/build/macx/debug
}

#LIBS += -lOpenGL32
#DEFINES += QCUSTOMPLOT_USE_OPENGL

help.files += "$${PWD}/doc/EMBO.chm" \
              "$${PWD}/doc/EMBO.pdf"
help.path += $${DESTDIR}/doc
INSTALLS += help

QMAKE_TARGET_COMPANY = CTU Jakub Parez
QMAKE_TARGET_PRODUCT = EMBO
QMAKE_TARGET_DESCRIPTION = EMBedded Oscilloscope
QMAKE_TARGET_COPYRIGHT = CTU Jakub Parez

QMAKE_CXXFLAGS += -Wno-deprecated -Wno-deprecated-declarations
QMAKE_POST_LINK=$(MAKE) install

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src/
INCLUDEPATH += src/windows/

SOURCES += \
    lib/qdial2.cpp \
    src/core.cpp \
    lib/ctkrangeslider.cpp \
    lib/qcustomplot.cpp \
    src/main.cpp \
    src/messages.cpp \
    src/msg.cpp \
    src/qcpcursors.cpp \
    src/recorder.cpp \
    src/settings.cpp \
    src/utils.cpp \
    src/windows/window__main.cpp \
    src/windows/window_cntr.cpp \
    src/windows/window_la.cpp \
    src/windows/window_pwm.cpp \
    src/windows/window_scope.cpp \
    src/windows/window_sgen.cpp \
    src/windows/window_vm.cpp

HEADERS += \
    lib/qdial2.h \
    src/containers.h \
    src/core.h \
    src/css.h \
    src/interfaces.h \
    lib/ctkrangeslider.h \
    lib/fftw3.h \
    lib/qcustomplot.h \
    src/messages.h \
    src/movemean.h \
    src/msg.h \
    src/qcpcursors.h \
    src/recorder.h \
    src/settings.h \
    src/utils.h \
    src/windows/window__main.h \
    src/windows/window_cntr.h \
    src/windows/window_la.h \
    src/windows/window_pwm.h \
    src/windows/window_scope.h \
    src/windows/window_sgen.h \
    src/windows/window_vm.h

FORMS += \
    src/windows/window__main.ui \
    src/windows/window_cntr.ui \
    src/windows/window_la.ui \
    src/windows/window_pwm.ui \
    src/windows/window_scope.ui \
    src/windows/window_sgen.ui \
    src/windows/window_vm.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources/resources.qrc

DISTFILES += \
    icon.icns \
    icon.ico
