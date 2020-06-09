/*
MIT License

Copyright (c) 2020 Philippe Vianney-Liaud | https://github.com/philvl

ZFontIcon is inspired/based on:
  QFontIcon by Sacha Schutz | https://github.com/dridk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "ZFontIcon.h"

// Qt Gui
#include <QFontDatabase>
#include <QIconEngine>
#include <QPainter>
#include <QPalette>
// Qt Widgets
#include <QApplication>
// Qt Core
#include <QDebug>


// Private IconEngine for internal use only
class ZFontIconEngine : public QIconEngine {
public:
    ZFontIconEngine() : QIconEngine() {}
    ~ZFontIconEngine() {}

    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE {
        QChar glyph= _fIcon.glyph;
        if(state == QIcon::On && _fIcon.glyphOn > 0)
            glyph= _fIcon.glyphOn;

        QColor penColor= _fIcon.color;
        switch(mode) {
        case QIcon::Normal: // When icon is available and the user is not interacting with the icon
            if(state == QIcon::On && _fIcon.colorOn.isValid())
                penColor= _fIcon.colorOn;
            break;
        case QIcon::Active: // When icon is available and the user is interacting with the icon (eg. mouse over it or clicking it)
            if(state == QIcon::Off && _fIcon.colorActive.isValid())
                penColor= _fIcon.colorActive;
            else if(state == QIcon::On && _fIcon.colorActiveOn.isValid())
                penColor= _fIcon.colorActiveOn;
            else if(state == QIcon::On && _fIcon.colorOn.isValid())
                penColor= _fIcon.colorOn;
            break;
        case QIcon::Disabled: // When icon is not available
            penColor= _fIcon.colorDisabled;
            break;
        case QIcon::Selected: // When icon is selected
            penColor= _fIcon.colorSelected;
            break;
        }

        float scalefactor= _fIcon.scaleFactor;
        if(state == QIcon::On && _fIcon.scaleFactorOn > 0)
            scalefactor= _fIcon.scaleFactorOn;

        QFont font(_fIcon.fontFamily);
        if(!_fIcon.fontStyle.isEmpty())
            font.setStyleName(_fIcon.fontStyle);
        int drawSize= qRound(rect.height() * scalefactor);
        font.setPixelSize(drawSize);

        painter->save();
        painter->setPen(penColor);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, glyph);
        painter->restore();
    }
    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE {
        QPixmap pix(size);
        pix.fill(Qt::transparent);

        QPainter painter(&pix);
        paint(&painter, QRect(QPoint(0,0),size), mode, state);
        return pix;
    }

    void setIconOption(const ZFontIconOption &fIcon) {
        _fIcon= fIcon;
    }

    virtual QIconEngine *clone() const Q_DECL_OVERRIDE {
        ZFontIconEngine *engine= new ZFontIconEngine;
        engine->setIconOption(_fIcon);
        return engine;
    }

private:
    ZFontIconOption _fIcon;
};



//=================================================================================================
//-------------------------------------------------------------------------------------------------
//=================================================================================================
ZFontIconOption::ZFontIconOption() {
    fontFamily=    QString();
    fontStyle=     QString();

    // Default icon character value
    glyph=      0;
    glyphOn=    0;

    // Default icon color values
    color=         QApplication::palette().color(QPalette::Normal,   QPalette::ButtonText);
    colorOn=       QColor();
    colorActive=   QColor();
    colorActiveOn= QColor();
    colorDisabled= QApplication::palette().color(QPalette::Disabled, QPalette::ButtonText);
    colorSelected= QApplication::palette().color(QPalette::Active,   QPalette::ButtonText);

    // Default icon scale factor values
    scaleFactor=   0.85;
    scaleFactorOn= 0;
}



//=================================================================================================
//-------------------------------------------------------------------------------------------------
//=================================================================================================
QMap<QString, QStringList> ZFontIcon::_registeredFontList= QMap<QString, QStringList>();


bool ZFontIcon::addFont(const QString &filename) {
    // Load font specified by filename and makes it available to the application
    const int fontId= QFontDatabase::addApplicationFont(filename);
    if(fontId < 0) {
        qWarning() << "ZFontIcon::addFont: Cannot load font file:" << filename;
        return false;
    }

    // Retrieve the family name of the added font and associated styles
    QFontDatabase fontDb;
    const QString fontFamilyName= fontDb.applicationFontFamilies(fontId).first();
    const QStringList fontStyleList= fontDb.styles(fontFamilyName);

    // Compare familyStyleList with knownStyleList to find new added styles
    // On success, we register the font and associated styles
    QStringList knownStyleList= _registeredFontList.value(fontFamilyName);
    for(const QString &style : fontStyleList) {
        if(!knownStyleList.contains(style)) {
            _registeredFontList.insert(fontFamilyName, fontStyleList);
            return true;
        }
    }

    // Otherwise, the added font has already been registered, so we unload it
    qWarning() << "ZFontIcon::addFont: Ignore already registered font:" << filename;
    QFontDatabase::removeApplicationFont(fontId);
    return false;
}

QIcon ZFontIcon::icon(ZFontIconOption fIcon) {
    if(_registeredFontList.isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family added";
        return QIcon();
    }
    int matchIndex;

    // Family matching
    //-- Get all registered families containing the desired font family name
    const QStringList matchFamilies= _registeredFontList.keys().filter(fIcon.fontFamily, Qt::CaseInsensitive);
    if(matchFamilies.isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family match with:" << fIcon.fontFamily;
        return QIcon();
    }
    //-- The first family in the match list is used by default
    QString familyToUse= matchFamilies.first();
    //-- Looking for an exact match for the desired font family name
    if((matchIndex= matchFamilies.indexOf(fIcon.fontFamily, Qt::CaseInsensitive)) > -1)
        familyToUse= matchFamilies.at(matchIndex);
    //-- If the font style is set, try to find a font family name containing the desired style name
    else if(!fIcon.fontStyle.isEmpty() && (matchIndex= matchFamilies.indexOf(fIcon.fontFamily + ' ' + fIcon.fontStyle, Qt::CaseInsensitive)) > -1)
        familyToUse= matchFamilies.at(matchIndex);
    //-- If the font style is set, try to find a font family witch embed the desired style
    else if(!fIcon.fontStyle.isEmpty()) {
        for(const QString &family : matchFamilies) {
            QStringList familyStyleList= _registeredFontList.value(family);
            if(familyStyleList.contains(fIcon.fontStyle, Qt::CaseInsensitive))
                familyToUse= family;
        }
    }
    fIcon.fontFamily= familyToUse;

    // Style matching
    //-- Get all registered styles for the family to use
    const QStringList familyStyleList= _registeredFontList.value(familyToUse);
    //-- The first family style is used by default
    QString styleToUse= familyStyleList.first();
    //-- Looking for an exact match for the desired style name
    if(!fIcon.fontStyle.isEmpty() && (matchIndex= familyStyleList.indexOf(fIcon.fontStyle, Qt::CaseInsensitive)) > -1)
        styleToUse= familyStyleList.at(matchIndex);
    fIcon.fontStyle= styleToUse;

    // Generate icon
    ZFontIconEngine *engine= new ZFontIconEngine;
    engine->setIconOption(fIcon);
    return QIcon(engine);
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QString &fontStyle, const QChar &glyph, const QColor &color) {
    ZFontIconOption fIcon;
    fIcon.fontFamily= fontFamily;
    fIcon.fontStyle=  fontStyle;
    fIcon.glyph= glyph;
    fIcon.color= color;
    return icon(fIcon);
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QChar &glyph, const QColor &color) {
    ZFontIconOption fIcon;
    fIcon.fontFamily= fontFamily;
    fIcon.glyph= glyph;
    fIcon.color= color;
    return icon(fIcon);
}

QMap<QString, QStringList> ZFontIcon::registeredFonts() {
    return _registeredFontList;
}


//---
//- Private methods
//---
ZFontIcon::ZFontIcon(QObject *parent) : QObject(parent) {}
ZFontIcon::~ZFontIcon() {}
