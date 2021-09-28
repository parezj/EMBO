TEMPLATE = app
TARGET = duplicates_test

QT -= gui
QT += network

CONFIG -= app_bundle
CONFIG += debug_and_release warn_off
CONFIG += thread exceptions rtti stl

# without c++11 & AppKit library compiler can't solve address for symbols
CONFIG += c++11
macx: LIBS += -framework AppKit

include($$PWD/../../qBreakpad.pri)
QMAKE_LIBDIR += $$OUT_PWD/../../handler
LIBS += -lqBreakpad

SOURCES += main.cpp

OBJECTS_DIR = _build/obj
MOC_DIR = _build
