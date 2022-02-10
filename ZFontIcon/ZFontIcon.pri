INCLUDEPATH += $$PWD

equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 8) {
   error(ZFontIcon requires at least Qt 5.8 or newer but Qt $$[QT_VERSION] was detected.)
}

SOURCES += \
    $$PWD/ZFontIcon.cpp

HEADERS += \
    $$PWD/ZFontIcon.h \
    $$PWD/ZFont_bi1.h \
    $$PWD/ZFont_fa4.h \
    $$PWD/ZFont_fa5.h \
    $$PWD/ZFont_fa6.h \
    $$PWD/ZFont_gmi4.h \
    $$PWD/ZFont_mdi6.h \
    $$PWD/ZFont_ph1.h

RESOURCES += \
    $$PWD/Fonts.qrc
