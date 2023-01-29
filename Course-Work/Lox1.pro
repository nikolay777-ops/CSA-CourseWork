QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BIOS.cpp \
    BaseLibs.cpp \
    Battery.cpp \
    CacheLevel.cpp \
    MotherBoard.cpp \
    NetworkAdapter.cpp \
    Processor.cpp \
    RandomAccessMemory.cpp \
    VideoAdapter.cpp \
    cpumonitor.cpp \
    main.cpp \
    mainwindow.cpp \
    process-monitor.cpp \
    processorwidget.cpp \
    procstats.cpp \
    qcustomplot.cpp

HEADERS += \
    BIOS.h \
    BaseLibs.h \
    Battery.h \
    CacheLevel.h \
    MotherBoard.h \
    NetworkAdapter.h \
    Processor.h \
    RAM.h \
    VideoAdapter.h \
    cpumonitor.h \
    hardware.h \
    mainwindow.h \
    process-monitor.h \
    processorwidget.h \
    procstats.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    procstats.ui

LIBS += -lPsapi \
        -lole32 \
        -loleaut32 \
        -lws2_32 \
        -lwbemuuid

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
