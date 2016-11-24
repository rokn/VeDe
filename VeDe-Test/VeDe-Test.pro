#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T00:58:52
#
#-------------------------------------------------

QT       -= gui

TARGET = vede-test
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter

TEMPLATE = app


SOURCES += gobjecttest.cpp \
    main.cpp \
    tooltest.cpp \
    linetooltest.cpp
HEADERS += catch.hpp \
    fakeit.hpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../tt/build-vede-graphics-debug/release/ -lVeDe-Graphics
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../tt/build-vede-graphics-debug/debug/ -lVeDe-Graphics
else:unix: LIBS += -L$$PWD/../../../../tt/build-vede-graphics-debug/ -lVeDe-Graphics

INCLUDEPATH += $$PWD/../../../../tt/VeDe-Graphics
DEPENDPATH += $$PWD/../../../../tt/VeDe-Graphics

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../tt/build-vede-graphics-debug/release/libVeDe-Graphics.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../tt/build-vede-graphics-debug/debug/libVeDe-Graphics.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../tt/build-vede-graphics-debug/release/VeDe-Graphics.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../tt/build-vede-graphics-debug/debug/VeDe-Graphics.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../tt/build-vede-graphics-debug/libVeDe-Graphics.a
