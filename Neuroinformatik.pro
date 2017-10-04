#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T16:06:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Neuroinformatik
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tools.cpp \
    array.cpp \
    learning.cpp \
    vector_list.cpp \
    qcustomplot/qcustomplot.cpp \
    csv_file.cpp \
    learningstochastic.cpp

HEADERS  += mainwindow.h \
    tools.h \
    array.h \
    learning.h \
    vector_list.h \
    qcustomplot/qcustomplot.h \
    csv_file.h \
    learningstochastic.h

FORMS    += mainwindow.ui
