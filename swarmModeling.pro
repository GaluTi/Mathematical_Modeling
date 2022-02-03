QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += core orbit \

SOURCES += \
    core/cEci.cpp \
    core/cJulian.cpp \
    core/cSite.cpp \
    core/cTLE.cpp \
    core/cVector.cpp \
    core/coord.cpp \
    core/globals.cpp \
    core/stdafx.cpp \
    main.cpp \
    mainwindow.cpp \
    normaldistribwin.cpp \
    orbit/cNoradBase.cpp \
    orbit/cNoradSDP4.cpp \
    orbit/cNoradSGP4.cpp \
    orbit/cOrbit.cpp \
    orbit/cSatellite.cpp \
    orbit/stdafx.cpp \
    qcustomplot.cpp \
    uniformdistribwin.cpp \
    world.cpp \
    worldobject.cpp

HEADERS += \
    core/coreLib.h \
    core/cEci.h \
    core/cJulian.h \
    core/cSite.h \
    core/cTLE.h \
    core/cVector.h \
    core/coord.h \
    core/coreLib.h \
    core/exceptions.h \
    core/globals.h \
    core/stdafx.h \
    mainwindow.h \
    normaldistribwin.h \
    orbit/cNoradBase.h \
    orbit/cNoradSDP4.h \
    orbit/cNoradSGP4.h \
    orbit/cOrbit.h \
    orbit/cSatellite.h \
    orbit/orbitLib.h \
    orbit/stdafx.h \
    qcustomplot.h \
    uniformdistribwin.h \
    world.h \
    worldobject.h

FORMS += \
    mainwindow.ui \
    normaldistribwin.ui \
    uniformdistribwin.ui

win32:RC_ICONS += AppIcon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
