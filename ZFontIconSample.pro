QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
lessThan(QT_MAJOR_VERSION, 6): DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    sample/WidgetCheatSheet.cpp \
    sample/main.cpp \
    sample/MainWindow.cpp \
    sample/WidgetSample.cpp

HEADERS += \
    sample/MainWindow.h \
    sample/WidgetCheatSheet.h \
    sample/WidgetSample.h

FORMS   += \
    sample/MainWindow.ui \
    sample/WidgetCheatSheet.ui \
    sample/WidgetSample.ui

# Add the following line to your project
include("ZFontIcon/ZFontIcon.pri")
DISTFILES += \
    CHANGELOG.md \
    LICENSE.md \
    README.md

linux {
    # For Ubuntu - Prevent from executable recognizes as shared library
    # The behavior is occurring because newer ubuntu distros set GCC default link flag -pie, which marks
    # e_type as ET_DYN on the binary file. Consequently, the Operating System recognizes as Shared Library.
    QMAKE_LFLAGS += -no-pie
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
