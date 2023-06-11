INCLUDEPATH += $$PWD

equals(QT_MAJOR_VERSION, 5):lessThan(QT_MINOR_VERSION, 15) {
   error(ZFontIcon requires at least Qt 5.15 or newer but Qt $$[QT_VERSION] was detected.)
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
    $$PWD/ZFont_mdi7.h \
    $$PWD/ZFont_ph1.h \
    $$PWD/ZFont_ph2.h

RESOURCES += \
    $$PWD/Fonts.qrc
