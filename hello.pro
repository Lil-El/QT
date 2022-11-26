QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    currencymodel.cpp \
    dnd.cpp \
    main.cpp \
    mainwindow.cpp \
    mdialog.cpp \
    mywindow.cpp \
    paint.cpp \
    track.cpp \
    trackdelegate.cpp

HEADERS += \
    currencymodel.h \
    dnd.h \
    mainwindow.h \
    mdialog.h \
    mywindow.h \
    paint.h \
    track.h \
    trackdelegate.h

FORMS += \
    dnd.ui \
    mainwindow.ui \
    mdialog.ui \
    mywindow.ui \
    paint.ui

TRANSLATIONS += \
    hello_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Readme.md \
    img.png
