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
        Q_UNUSED(state);

        QColor penColor;
        switch(mode) {
        case QIcon::Normal: // When icon is available and the user is not interacting with the icon
        case QIcon::Active: // When icon is available and the user is interacting with the icon (eg. mouse over it or clicking it)
            penColor= _iconColor;
            if(!_iconColor.isValid())
                penColor= QApplication::palette().color(QPalette::Normal, QPalette::ButtonText);
            break;
        case QIcon::Disabled: // When icon is not available
            penColor= QApplication::palette().color(QPalette::Disabled, QPalette::ButtonText);
            break;
        case QIcon::Selected: // When icon is selected
            penColor= QApplication::palette().color(QPalette::Active, QPalette::ButtonText);
            break;
        }

        QFont font(_fontFamily);
        if(!_iconStyle.isEmpty())
            font.setStyleName(_iconStyle);
        int drawSize= qRound(rect.height() * 0.85);
        font.setPixelSize(drawSize);

        painter->save();
        painter->setPen(penColor);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, _iconCode);
        painter->restore();
    }
    virtual QPixmap pixmap(const QSize &size, QIcon::Mode mode, QIcon::State state) Q_DECL_OVERRIDE {
        QPixmap pix(size);
        pix.fill(Qt::transparent);

        QPainter painter(&pix);
        paint(&painter, QRect(QPoint(0,0),size), mode, state);
        return pix;
    }

    void setFontFamily(const QString &family) {
        _fontFamily= family;
    }
    void setIconCode(const QChar &code){
        _iconCode= code;
    }
    void setIconColor(const QColor &color) {
        _iconColor= color;
    }
    void setIconStyle(const QString &style) {
        _iconStyle= style;
    }

    virtual QIconEngine *clone() const Q_DECL_OVERRIDE {
        ZFontIconEngine * engine= new ZFontIconEngine;
        engine->setFontFamily(_fontFamily);
        engine->setIconCode(_iconCode);
        engine->setIconColor(_iconColor);
        engine->setIconStyle(_iconStyle);
        return engine;
    }

private:
    QString _fontFamily;
    QChar   _iconCode;
    QColor  _iconColor;
    QString _iconStyle;
};



//=================================================================================================
//-------------------------------------------------------------------------------------------------
//=================================================================================================
QMap<QString, QStringList> ZFontIcon::_registeredFontList= QMap<QString, QStringList>();


bool ZFontIcon::addFont(const QString &filename) {
    // Register the given font file
    const int fontId= QFontDatabase::addApplicationFont(filename);
    if(fontId < 0) {
        qWarning() << "ZFontIcon::addFont: Cannot load font file:" << filename;
        return false;
    }

    // Gets the family and styles of the added font
    QFontDatabase fontDb;
    QString     fontFamilyName=  fontDb.applicationFontFamilies(fontId).first();
    QStringList familyStyleList= fontDb.styles(fontFamilyName);

    // Retrieve the styles already known from the added font family
    QStringList knownStyleList= _registeredFontList.value(fontFamilyName);

    // Remove already known styles from the style list of the added font
    for(const QString &knownStyle : knownStyleList) {
        if(familyStyleList.contains(knownStyle))
            familyStyleList.removeOne(knownStyle);
    }

    // If the new font style list is empty, the added font has
    // already been registered, so we need to unregister it
    if(familyStyleList.isEmpty()) {
        qWarning() << "ZFontIcon::addFont: Ignore already registered font:" << filename;
        QFontDatabase::removeApplicationFont(fontId);
        return false;
    }

    // Update registered font info
    knownStyleList.append(familyStyleList);
    _registeredFontList.insert(fontFamilyName, knownStyleList);
    return true;
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QString &iconStyle, const QChar &iconCode,  const QColor &iconColor) {
    if(_registeredFontList.isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family added";
        return QIcon();
    }
    int matchIndex;

    // Family matching
    //-- Get all registered families containing the desired font family name
    QStringList matchFamilies= _registeredFontList.keys().filter(fontFamily, Qt::CaseInsensitive);
    if(matchFamilies.isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family match with:" << fontFamily;
        return QIcon();
    }

    //-- The first family in the match list is used by default
    QString familyToUse= matchFamilies.first();
    //-- Looking for an exact match for the desired font family name
    if((matchIndex= matchFamilies.indexOf(fontFamily, Qt::CaseInsensitive)) > -1) {
        //qDebug() << "ZFontIcon::icon: Match with family name";
        familyToUse= matchFamilies.at(matchIndex);
    }
    //-- If the font style is set, try to find a font family name containing the desired style name
    else if(!iconStyle.isEmpty() && (matchIndex= matchFamilies.indexOf(fontFamily + ' ' + iconStyle, Qt::CaseInsensitive)) > -1) {
        //qDebug() << "ZFontIcon::icon: Match with family+style name";
        familyToUse= matchFamilies.at(matchIndex);
    }
    //-- If the font style is set, try to find a font family witch embed the desired style
    else if(!iconStyle.isEmpty()) {
        QStringList familyStyleList;
        for(const QString &family : matchFamilies) {
            familyStyleList= _registeredFontList.value(family);
            if(familyStyleList.contains(iconStyle, Qt::CaseInsensitive)) {
                //qDebug() << "ZFontIcon::icon: Match with family embedded style name";
                familyToUse= family;
            }
        }
    }

    // Style matching
    //-- Get all registered styles for the family to use
    QStringList familyStyleList= _registeredFontList.value(familyToUse);
    //-- The first family style is used by default
    QString styleToUse = familyStyleList.first();
    //-- Looking for an exact match for the desired style name
    if(!iconStyle.isEmpty() && (matchIndex= familyStyleList.indexOf(iconStyle, Qt::CaseInsensitive)) > -1) {
        styleToUse= familyStyleList.at(matchIndex);
    }

    // Generate icon
    ZFontIconEngine *engine= new ZFontIconEngine;
    engine->setFontFamily(familyToUse);
    engine->setIconCode(iconCode);
    engine->setIconStyle(styleToUse);
    engine->setIconColor(iconColor);
    return QIcon(engine);
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QChar &iconCode, const QColor &iconColor) {
    return icon(fontFamily, QString(), iconCode, iconColor);
}

QMap<QString, QStringList> ZFontIcon::registeredFonts() {
    return _registeredFontList;
}


//---
//- Private methods
//---
ZFontIcon::ZFontIcon(QObject *parent) : QObject(parent) {}
ZFontIcon::~ZFontIcon() {}
