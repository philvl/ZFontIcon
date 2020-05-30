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
// Qt Gui
#include <QColor>


class ZFontIcon : public QObject {
    Q_OBJECT
public:
    static ZFontIcon *instance();

    // Add Font. The first one is used by default
    static bool addFont(const QString &filename);
    // Main methods. Return icons from code
    static QIcon icon(const QString &fontFamily, const QChar &iconCode, const QColor &iconColor= QColor(), const QString &iconStyle= QString());
    static QIcon icon(const QChar &iconCode, const QColor &iconColor= QColor(), const QString &iconStyle= QString());
    // Return added families
    const QStringList &families() const;

protected:
    void addFontFamily(const QString &family);

private:
    explicit ZFontIcon(QObject *parent = 0);
    ~ZFontIcon();

    static ZFontIcon *_instance;
    QStringList _fontFamilies;
};

#endif // ZFONTICON_H
