#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T01:17:22
#
#-------------------------------------------------

QT       -= gui

TARGET = VeDe-Graphics
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    vertex.cpp \
    canvas.cpp \
    color.cpp \
#    colorproperty.cpp \
    custompainter.cpp \
    gobject.cpp \
    line.cpp \
    property.cpp

HEADERS += \
    vertex.h \
    canvas.h \
    color.h \
#    colorproperty.h \
    custompainter.h \
    gobject.h \
    line.h \
    property.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
