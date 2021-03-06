#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T01:17:22
#
#-------------------------------------------------

#QT       -= gui

TARGET = VeDe-Graphics
TEMPLATE = lib
CONFIG += staticlib

unix {
    QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter
    QMAKE_CXXFLAGS_WARN_ON += -Wno-sign-compare
    QMAKE_CXXFLAGS_WARN_ON += -Wno-return-local-addr
}

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
    tools/restrictabletool.cpp \
    objects/shape.cpp \
    properties/propertyholder.cpp \
    properties/propertyfactory.cpp \
    tools/shapetool.cpp \
    objects/path.cpp \
    tools/pathtool.cpp \
    converters.cpp \
    helpers.cpp \
    tools/userevent.cpp \
    commands/selectcommand.cpp \
    tools/commonstates.cpp \
    commands/translatecommand.cpp \
    commands/rotatecommand.cpp \
    commands/scalecommand.cpp \
    tools/manipulatetool.cpp \
    objects/controlpoint.cpp \
    canvasmanager.cpp \
    canvasmanagersvg.cpp \
    gobjecttypes.cpp

HEADERS += \
    vertex.h \
    canvas.h \
    color.h \
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
    tools/restrictabletool.h \
    graphics_exceptions.h \
    objects/shape.h \
    properties/propertyholder.h \
    properties/propertyfactory.h \
    properties/propertynames.h \
    tools/shapetool.h \
    objects/path.h \
    tools/pathtool.h \
    converters.h \
    helpers.h \
    event.h \
    common.h \
    tools/userevent.h \
    tools/usereventtype.h \
    commands/selectcommand.h \
    tools/commonstates.h \
    commands/translatecommand.h \
    commands/rotatecommand.h \
    commands/scalecommand.h \
    tools/manipulatetool.h \
    objects/controlpoint.h \
    canvasmanager.h \
    canvasmanagersvg.h \
    gobjecttypes.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
