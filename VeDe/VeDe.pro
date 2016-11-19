#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T00:18:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VeDe
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    graphics/gobject.cpp \
    graphics/property.cpp \
    graphics/colorproperty.cpp \
    graphics/vertex.cpp \
    graphics/line.cpp \
    graphics/color.cpp \
    graphics/canvas.cpp \
    qtcustompainter.cpp \
    graphics/custompainter.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    graphics/gobject.h \
    graphics/property.h \
    graphics/colorproperty.h \
    graphics/vertex.h \
    graphics/line.h \
    graphics/color.h \
    graphics/canvas.h \
    qtcustompainter.h \
    graphics/custompainter.h

FORMS    += mainwindow.ui
