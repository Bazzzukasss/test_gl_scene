QT       += core gui opengl printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gl_scene_test
TEMPLATE = app
DESTDIR = ../bin

SOURCES += \
        src/main.cpp \
        src/data.cpp \
        src/main_window.cpp

HEADERS += \
        inc/main_window.h \
        inc/data.h

FORMS   += forms/main_window.ui

INCLUDEPATH += \
            inc \
            $$PWD/../gl_scene/inc

LIBS *= -L$$OUT_PWD/$$DESTDIR -lgl_scene

unix:LIBS += -lGL
win32:LIBS += -lopengl32 -lglu32
