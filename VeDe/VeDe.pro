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


SOURCES += main.cpp\
        mainwindow.cpp \
    canvaswidget.cpp \
    qtcustompainter.cpp \

HEADERS  += mainwindow.h \
    canvaswidget.h \
    qtcustompainter.h \

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/release/ -lVeDe-Graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/debug/ -lVeDe-Graphics
else:unix: LIBS += -L$$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/ -lVeDe-Graphics

INCLUDEPATH += $$PWD/../VeDe-Graphics
DEPENDPATH += $$PWD/../VeDe-Graphics

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/release/libVeDe-Graphics.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/debug/libVeDe-Graphics.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/release/VeDe-Graphics.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/debug/VeDe-Graphics.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-VeDe-Graphics-Desktop_Qt_5_7_0_GCC_64bit-Debug/libVeDe-Graphics.a
