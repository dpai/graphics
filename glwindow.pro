#-------------------------------------------------
#
# Project created by QtCreator 2014-07-20T14:57:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl

TARGET = glwindow
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    shader.cpp

HEADERS  += widget.h \
    shader.h

LIBS += -lglew32

OTHER_FILES += \
    shader.frag \
    shader.vert
