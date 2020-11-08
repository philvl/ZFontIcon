QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ZHeaderHelper/main.cpp \
    ZHeaderHelper/MainWindow.cpp \
    ZHeaderHelper/WidgetFaHelper.cpp \
    ZHeaderHelper/WidgetGmdHelper.cpp

HEADERS += \
    ZHeaderHelper/MainWindow.h \
    ZHeaderHelper/WidgetFaHelper.h \
    ZHeaderHelper/WidgetGmdHelper.h

FORMS += \
    ZHeaderHelper/MainWindow.ui \
    ZHeaderHelper/WidgetFaHelper.ui \
    ZHeaderHelper/WidgetGmdHelper.ui

RESOURCES += \
    ZHeaderHelper/res/0_resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
