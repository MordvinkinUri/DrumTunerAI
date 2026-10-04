QT += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += release

win32 {
    CONFIG += x86_64
    QMAKE_TARGET.arch = x86_64
}

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    frequencydetector.cpp

HEADERS += \
    mainwindow.h \
    frequencydetector.h

FORMS += \
    mainwindow.ui

win32: {
    CONFIG += console
}
