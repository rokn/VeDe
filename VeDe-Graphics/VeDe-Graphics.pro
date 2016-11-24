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
    objects/gobject.cpp \
    objects/line.cpp \
    property.cpp \
    tools/tool.cpp \
    tools/linetool.cpp \
    layer.cpp \
    commands/canvascommand.cpp \
    commands/addgobjectcommand.cpp \
    objects/ellipse.cpp \
    tools/ellipsetool.cpp

HEADERS += \
    vertex.h \
    canvas.h \
    color.h \
#    colorproperty.h \
    custompainter.h \
    objects/gobject.h \
    objects/line.h \
    property.h \
    tools/tool.h \
    tools/linetool.h \
    layer.h \
    commands/command.h \
    commands/canvascommand.h \
    commands/addgobjectcommand.h \
    objects/ellipse.h \
    tools/ellipsetool.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
