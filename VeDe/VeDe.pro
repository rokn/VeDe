#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T00:18:38
#
#-------------------------------------------------

#include(../VeDe-Graphics/VeDe-Graphics.pro)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VeDe
TEMPLATE = app

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    qtcustompainter.cpp \
    toolaction.cpp \
    workspace.cpp \
    properywidgetfactory.cpp \
    propertyconverter.cpp \
    canvasimpl.cpp

HEADERS  += mainwindow.h \
    canvaswidget.h \
    qtcustompainter.h \
    toolaction.h \
    workspace.h \
    properywidgetfactory.h \
    propertyconverter.h \
    canvasimpl.h

FORMS    +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-vede-graphics-debug/release/ -lVeDe-Graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-vede-graphics-debug/debug/ -lVeDe-Graphics
else:unix: LIBS += -L$$PWD/../build-vede-graphics-debug/ -lVeDe-Graphics

INCLUDEPATH += $$PWD/../VeDe-Graphics
INCLUDEPATH += $$PWD/../VeDe-Graphics/objects
INCLUDEPATH += $$PWD/../VeDe-Graphics/commands
INCLUDEPATH += $$PWD/../VeDe-Graphics/tools
DEPENDPATH += $$PWD/../VeDe-Graphics

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-vede-graphics-debug/release/libVeDe-Graphics.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-vede-graphics-debug/debug/libVeDe-Graphics.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-vede-graphics-debug/release/VeDe-Graphics.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-vede-graphics-debug/debug/VeDe-Graphics.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-vede-graphics-debug/libVeDe-Graphics.a

RESOURCES += \
    images.qrc
