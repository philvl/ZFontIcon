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
    ZFontIconEngine(const ZFontIconOption &fIcon) : _fIcon(fIcon) {}
    ~ZFontIconEngine() {}

    virtual void paint(QPainter *painter, const QRect &rect, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE {
        QString fontFamily= _fIcon.fontFamily;
        QString fontStyle=  _fIcon.fontStyle;
        if(state == QIcon::On && !_fIcon.fontFamilyOn.isEmpty()) {
            fontFamily= _fIcon.fontFamilyOn;
            fontStyle=  _fIcon.fontStyleOn;
        }

        QString glyph= QString::fromUcs4(&_fIcon.glyph, 1);
        if(state == QIcon::On && _fIcon.glyphOn > 0)
            glyph= QString::fromUcs4(&_fIcon.glyphOn, 1);

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

        qreal scaleFactor= _fIcon.scaleFactor;
        if(state == QIcon::On && _fIcon.scaleFactorOn > 0)
            scaleFactor= _fIcon.scaleFactorOn;
        int fontHeight= qRound(rect.height()*scaleFactor);


        QFont font(fontFamily);
        if(!fontStyle.isEmpty())
            font.setStyleName(fontStyle);
        font.setPixelSize(fontHeight);

        painter->save();
        // Apply icon transformations
        painter->translate(rect.center()+QPoint(1,1));
        if(_fIcon.rotateAngle)
            painter->rotate(_fIcon.rotateAngle);
        if(_fIcon.flipLeftRight)
            painter->scale(-1.0, 1.0);
        if(_fIcon.flipTopBottom)
            painter->scale(1.0, -1.0);
        painter->translate(-rect.center()-QPoint(1,1));
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

    virtual QIconEngine *clone() const Q_DECL_OVERRIDE {
        return new ZFontIconEngine(_fIcon);
    }

private:
    ZFontIconOption _fIcon;
};



//=================================================================================================
//-------------------------------------------------------------------------------------------------
//=================================================================================================
ZFontIconOption::ZFontIconOption() {
    fontFamily=   fontStyle=   QString();
    fontFamilyOn= fontStyleOn= QString();

    // Default icon character value
    glyph= glyphOn= 0;

    // Default icon color values
    color=         QApplication::palette().color(QPalette::Normal,   QPalette::ButtonText);
    colorOn=       QColor();
    colorActive=   QColor();
    colorActiveOn= QColor();
    colorDisabled= QApplication::palette().color(QPalette::Disabled, QPalette::ButtonText);
    colorSelected= QApplication::palette().color(QPalette::Active,   QPalette::ButtonText);

    // Default icon scale factor values
    scaleFactor=   0.80;
    scaleFactorOn= 0.00;

    // More fun options
    rotateAngle=   0.00;
    flipLeftRight= false;
    flipTopBottom= false;
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
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    const QString fontFamily= QFontDatabase::applicationFontFamilies(fontId).first();
    const QStringList fontStyleList= QFontDatabase::styles(fontFamily);
#else
    QFontDatabase fontDb;
    const QString fontFamily= fontDb.applicationFontFamilies(fontId).first();
    const QStringList fontStyleList= fontDb.styles(fontFamily);
#endif

    if(fontStyleList.isEmpty()) {
        qWarning() << "ZFontIcon::addFont: Family with no styles is not supported";
        QFontDatabase::removeApplicationFont(fontId);
        return false;
    }

    // Compare familyStyleList with knownStyleList to find new added styles
    // On success, we register the font and associated styles
    const QStringList knownStyleList= _registeredFontList.value(fontFamily);
    for(const QString &style : fontStyleList) {
        if(!knownStyleList.contains(style)) {
            _registeredFontList.insert(fontFamily, fontStyleList);
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
    if(fIcon.fontFamily.isEmpty() || fIcon.glyph <= 0) {
        qWarning() << "ZFontIcon::icon: minimum requirements not set";
        return QIcon();
    }

    if(fIcon.fontFamilyOn.isEmpty() && !fIcon.fontStyleOn.isEmpty())
        fIcon.fontFamilyOn= fIcon.fontFamily;
    if(!fIcon.fontFamilyOn.isEmpty()) {
        const QString familyOnToUse= familyMatching(fIcon.fontFamilyOn, fIcon.fontStyleOn);
        if(familyOnToUse.isEmpty()) {
            qWarning() << "ZFontIcon::icon: No font family match with:" << fIcon.fontFamilyOn;
            return QIcon();
        }
        fIcon.fontFamilyOn= familyOnToUse;
        fIcon.fontStyleOn=  styleMatching(familyOnToUse, fIcon.fontStyleOn);
    }

    const QString familyToUse= familyMatching(fIcon.fontFamily, fIcon.fontStyle);
    if(familyToUse.isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family match with:" << fIcon.fontFamily;
        return QIcon();
    }
    fIcon.fontFamily= familyToUse;
    fIcon.fontStyle=  styleMatching(familyToUse, fIcon.fontStyle);

    // Generate icon
    return QIcon(new ZFontIconEngine(fIcon));
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QString &fontStyle, const char32_t glyph, const QColor &color, const qreal scaleFactor) {
    ZFontIconOption fIcon;
    fIcon.fontFamily= fontFamily;
    fIcon.fontStyle=  fontStyle;
    fIcon.glyph= glyph;
    if(color.isValid())
        fIcon.color= color;
    if(scaleFactor > 0)
        fIcon.scaleFactor= scaleFactor;
    return icon(fIcon);
}

QIcon ZFontIcon::icon(const QString &fontFamily, const char32_t glyph, const QColor &color, const qreal scaleFactor) {
    return icon(fontFamily, QString(), glyph, color, scaleFactor);
}

QMap<QString, QStringList> ZFontIcon::registeredFonts() {
    return _registeredFontList;
}

bool ZFontIcon::isRegistered(const QString &fontFamily) {
    // Get all registered families containing the desired font family name
    QStringList families= _registeredFontList.keys();
    if(families.filter(fontFamily, Qt::CaseInsensitive).isEmpty())
        return false;
    return true;
}


//---
//- Private methods
//---
QString ZFontIcon::familyMatching(const QString &fontFamily, const QString &fontStyle) {
    int matchIndex;
    // Get all registered families containing the desired font family name
    QStringList matchFamilies= _registeredFontList.keys();
    matchFamilies= matchFamilies.filter(fontFamily, Qt::CaseInsensitive);
    if(matchFamilies.isEmpty())
        return QString();
    // The first family in the match list is used by default
    QString familyToUse= matchFamilies.first();
    // Looking for an exact match for the desired font family name
    if((matchIndex= matchFamilies.indexOf(fontFamily, Qt::CaseInsensitive)) > -1)
        familyToUse= matchFamilies.at(matchIndex);
    // If the font style is set, try to find a font family name containing the desired style name
    else if(!fontStyle.isEmpty() && (matchIndex= matchFamilies.indexOf(fontFamily + ' ' + fontStyle, Qt::CaseInsensitive)) > -1)
        familyToUse= matchFamilies.at(matchIndex);
    // If the font style is set, try to find a font family witch embed the desired style
    else if(!fontStyle.isEmpty()) {
        for(const QString &family : qAsConst(matchFamilies)) {
            QStringList familyStyleList= _registeredFontList.value(family);
            if(familyStyleList.contains(fontStyle, Qt::CaseInsensitive))
                familyToUse= family;
        }
    }
    return familyToUse;
}

QString ZFontIcon::styleMatching(const QString &familyToUse, const QString &fontStyle) {
    int matchIndex;
    // Get all registered styles for the family to use
    const QStringList familyStyleList= _registeredFontList.value(familyToUse);
    if(familyStyleList.isEmpty())
        return QString();
    // The first family style is used by default
    QString styleToUse= familyStyleList.first();
    // Looking for an exact match for the desired style name
    if(!fontStyle.isEmpty() && (matchIndex= familyStyleList.indexOf(fontStyle, Qt::CaseInsensitive)) > -1)
        styleToUse= familyStyleList.at(matchIndex);
    return styleToUse;
}
