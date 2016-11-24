#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T01:17:22
#
#-------------------------------------------------

QT       -= gui

TARGET = VeDe-Graphics
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

SOURCES += \
    vertex.cpp \
    canvas.cpp \
    color.cpp \
#    colorproperty.cpp \
    custompainter.cpp \
    gobject.cpp \
    line.cpp \
    property.cpp \
    tool.cpp \
    linetool.cpp \
    layer.cpp \
    commands/canvascommand.cpp \
    commands/addlinecommand.cpp

HEADERS += \
    vertex.h \
    canvas.h \
    color.h \
#    colorproperty.h \
    custompainter.h \
    gobject.h \
    line.h \
    property.h \
    tool.h \
    linetool.h \
    layer.h \
    commands/command.h \
    commands/canvascommand.h \
    commands/addlinecommand.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
