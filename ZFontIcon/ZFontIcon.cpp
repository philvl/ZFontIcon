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
ZFontIcon* ZFontIcon::_instance= Q_NULLPTR;

ZFontIcon *ZFontIcon::instance() {
    if (!_instance)
        _instance= new ZFontIcon;
    return _instance;
}


bool ZFontIcon::addFont(const QString &filename) {
    int fontId= QFontDatabase::addApplicationFont(filename);
    if(fontId < 0) {
        qWarning()<< "ZFontIcon::addFont: Cannot load font";
        return false;
    }
    QString mainFontFamily= QFontDatabase::applicationFontFamilies(fontId).first();
    instance()->addFontFamily(mainFontFamily);
    return true;
}

QIcon ZFontIcon::icon(const QString &fontFamily, const QChar &iconCode, const QColor &iconColor, const QString &iconStyle) {
    if(instance()->families().isEmpty()) {
        qWarning() << "ZFontIcon::icon: No font family installed";
        return QIcon();
    }

    // Check font family
    QString familyToUse= fontFamily;
    if(familyToUse.isEmpty())
        familyToUse= instance()->families().first();
    else if(!instance()->families().contains(familyToUse, Qt::CaseInsensitive)) {
        qWarning() << "ZFontIcon::icon: Font Family" << familyToUse << "is not loaded";
        return QIcon();
    }

    // Check font style
    QFontDatabase fontDatabase;
    QStringList availableFontStyles= fontDatabase.styles(familyToUse);
    QString styleToUse= iconStyle;
    if(!styleToUse.isEmpty() && !availableFontStyles.contains(iconStyle)) {
        qWarning() << "ZFontIcon::icon: Font Style" << iconStyle << "does not exist for" << familyToUse << ", use prefered style inplace";
        styleToUse.clear();
    }

    // Generate icon
    ZFontIconEngine *engine= new ZFontIconEngine;
    engine->setFontFamily(familyToUse);
    engine->setIconCode(iconCode);
    engine->setIconStyle(styleToUse);
    engine->setIconColor(iconColor);
    return QIcon(engine);
}

QIcon ZFontIcon::icon(const QChar &iconCode, const QColor &iconColor, const QString &iconStyle) {
    return icon(QString(), iconCode, iconColor, iconStyle);
}

const QStringList &ZFontIcon::families() const {
    return _fontFamilies;
}


//---
//- Protected methods
//---
void ZFontIcon::addFontFamily(const QString &family) {
    if(_fontFamilies.contains(family, Qt::CaseInsensitive))
        return;
    _fontFamilies.append(family);
}


//---
//- Private methods
//---
ZFontIcon::ZFontIcon(QObject *parent) : QObject(parent) {}
ZFontIcon::~ZFontIcon() {}
