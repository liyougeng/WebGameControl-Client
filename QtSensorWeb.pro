#-------------------------------------------------
#
# Project created by QtCreator 2010-09-16T11:47:32
#
#-------------------------------------------------



CONFIG += mobility
CONFIG += debug
MOBILITY += sensors

QT       += core gui
 QT += network
TARGET = QtCompass
TEMPLATE = app

RESOURCES     = Qtcompass.qrc

SOURCES += main.cpp\
 compass.cpp\
 mainwindow.cpp \
    webclient.cpp

HEADERS  += compass.h \
mainwindow.h \
    webclient.h


symbian {
    TARGET.UID3 = 0xe1a822a5
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
    #ICON = ./images/Compass.svg
}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/QtCompass/bin
    INSTALLS += target
}
