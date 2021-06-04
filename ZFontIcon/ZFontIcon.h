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

#ifndef ZFONTICON_H
#define ZFONTICON_H

// Qt Core
#include <QObject>
#include <QString>
#include <QStringList>
#include <QMap>
// Qt Gui
#include <QColor>


class ZFontIconOption {
public:
    ZFontIconOption();
    //--
    QString fontFamily;
    QString fontStyle;
    //--
    QString fontFamilyOn; // Optional: if null, fontFamily value will be used
    QString fontStyleOn;  // Optional: if null, fontStyle value will be used
    //--
    char32_t glyph;
    char32_t glyphOn;       // Optional: if null, glyph value will be used
    //--
    QColor color;
    QColor colorOn;       // Optional: if not set, color value will be used
    QColor colorActive;   // Optional: if not set, color value will be used
    QColor colorActiveOn; // Optional: if not set, color value will be used
    QColor colorDisabled;
    QColor colorSelected;
    //--
    qreal  scaleFactor;
    qreal  scaleFactorOn; // Optional: if null, scaleFactor value will be used
};


class ZFontIcon : public QObject {
    Q_OBJECT
// METHODS
private:
    explicit ZFontIcon(QObject *parent = 0) : QObject(parent) {}
    ~ZFontIcon() {}

public:
    // Add Font
    static bool addFont(const QString &filename);

    // Return icon
    //-- This methods should be used with font families having multiple registered styles (eg, Solid, Regular, Light, etc.)
    static QIcon icon(ZFontIconOption fIcon);
    static QIcon icon(const QString &fontFamily, const QString &fontStyle, const char32_t glyph, const QColor &color= QColor(), const qreal scalefactor= 0);
    //-- This method can be used with font families having only one style
    static QIcon icon(const QString &fontFamily, const char32_t glyph, const QColor &color= QColor(), const qreal scalefactor= 0);

    // Return registered font list (family and styles)
    static QMap<QString, QStringList> registeredFonts();

    // Return bool if given font family is registered
    static bool isRegistered(const QString &fontFamily);

private:
    static QString familyMatching(const QString &fontFamily, const QString &fontStyle);
    static QString styleMatching(const QString &familyToUse, const QString &fontStyle);

// VARIABLES
private:
    static QMap<QString, QStringList> _registeredFontList;
};

#endif // ZFONTICON_H
