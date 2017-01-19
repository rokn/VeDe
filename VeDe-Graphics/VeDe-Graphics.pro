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
    properties/property.cpp \
    tools/tool.cpp \
    tools/linetool.cpp \
    layer.cpp \
    commands/canvascommand.cpp \
    commands/addgobjectcommand.cpp \
    objects/ellipse.cpp \
    tools/ellipsetool.cpp \
    objects/rectangle.cpp \
    tools/rectangletool.cpp \
    tools/transition.cpp \
    tools/restrictabletool.cpp \
    graphics_exceptions.cpp \
    objects/shape.cpp \
    properties/propertyholder.cpp \
    properties/propertyfactory.cpp \
    tools/shapetool.cpp \
    objects/path.cpp \
    tools/pathtool.cpp

HEADERS += \
    vertex.h \
    canvas.h \
    color.h \
#    colorproperty.h \
    custompainter.h \
    objects/gobject.h \
    objects/line.h \
    properties/property.h \
    tools/tool.h \
    tools/linetool.h \
    layer.h \
    commands/command.h \
    commands/canvascommand.h \
    commands/addgobjectcommand.h \
    objects/ellipse.h \
    tools/ellipsetool.h \
    objects/rectangle.h \
    tools/rectangletool.h \
    tools/transition.h \
    tools/restrictabletool.h \
    graphics_exceptions.h \
    objects/shape.h \
    properties/propertyholder.h \
    properties/propertyfactory.h \
    properties/propertynames.h \
    tools/shapetool.h \
    tools/transitiontype.h \
    objects/path.h \
    tools/pathtool.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
