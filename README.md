# ZFontIcon - Icon fonts support for Qt applications
ZFontIcon is released under the MIT License


## Description
ZFontIcon provide a simple way to use any glyph/icon fonts as QIcon in your Qt5/Qt6 applications.

Some helpers are included to use the following icon fonts without effort:
- Font Awesome 6.0.0-alpha1 Brands, Free, and Pro (requires a FA pro licence to get alpha fonts)
- Font Awesome 5.15.1 Brands
- Font Awesome 5.15.1 Free
- Font Awesome 5.15.1 Pro (requires a FA pro licence)
- Font Awesome 4.7.0
- Google Material Design Icons 4.x - from github master 96206ad - 2020-08-31

You can use any other icon fonts using Unicode character codes. For convenience, I suggest you create your own font helper: simply create an enumeration listing all the Unicode characters of the font icons. Take a look at the code, it's very easy!


## Qt Compatibility
ZFontIcon requires at least Qt 5.8.
ZFontIcon is tested under Windows, Linux and MacOs with:
- Qt 5.9.9       / c++11
- Qt 5.12.9      / c++11
- Qt 5.15.1      / c++11, c++14, c++17
- Qt 6.0.0-beta3 / c++11, c++14, c++17


## Installation
The easiest way to include ZFontIcon in your project is to copy the ZFontIcon folder to your project tree and add the following include() to your Qt project (.pro) file:

    include(ZFontIcon/ZFontIcon.pri)

Now, you are ready!


## Usage
### Basic usage

First of all, you need to load the icon fonts you want to use (typically in the main.cpp):

```c++
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa5.h" // FA5 helpers

// FA5 Free
ZFontIcon::addFont(":/fa5/" + Fa5::FA5_OTF_FILE_FREE_SOLID);
ZFontIcon::addFont(":/fa5/" + Fa5::FA5_OTF_FILE_FREE_REGULAR);
// FA5 Pro (if you have a license)
ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_SOLID);
ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_REGULAR);
ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_LIGHT);
// FA5 Brands
ZFontIcon::addFont(":/fa5/" + Fa5brands::FA5_OTF_FILE_BRANDS);
```

Then you can get your favorite icons:

```c++
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa5.h"

// FA5 Free (FA5 Free include about 150 regular icon)
ZFontIcon::icon(Fa5::FAMILY,    Fa5::SOLID,      Fa5::fa_flag,    QColor(128, 0, 0));
ZFontIcon::icon(Fa5::FAMILY,    Fa5::REGULAR,    Fa5::fa_flag,    QColor(0, 128, 0));
// FA5 Pro (only if you have a license)
ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_flag, QColor(128, 0, 0));
ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_flag, QColor(0, 128, 0));
ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_flag, QColor(0, 0, 128));
// FA5 Brands (note that FA5 Brands has no font style)
ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_github, QColor(128, 0, 0));
```


### Advanced usage
More customization is needed ? You can set every aspect of your icon:

- On icon state change [On/Off] you can use a different:
  - font style (eg. switch from Solid to Regular font style);
  - glyph (eg. change glyph from lock to unlock);
  - color;
  - scale factor  (eg. make On state glyph bigger than Off state glyph),
- On mouse hover, you can:
  - set a hover color for Off state;
  - set a hover color for On state,
- For icon mode Selected and Disabled, you can change the default color.

```c++
ZFontIconOption fIcon;

// Required arguments
fIcon.fontFamily=    Fa5::FAMILY;           // Set font icon family
fIcon.fontStyle=     Fa5::SOLID;            // Set family style (Required if font families have multiple registered styles)
fIcon.glyph=         Fa5::fa_grin;          // Set default glyph
fIcon.color=         QColor(195,  65,  65); // Set default color

// Optional arguments
fIcon.fontStyleOn=   Fa5::REGULAR;          // Font style when icon state is On
fIcon.glyphOn=       Fa5::fa_grin_stars;    // Glyph when icon state is On

fIcon.colorOn=       QColor(102, 163,  52); // Color when icon state is On
fIcon.colorActive=   QColor(234,  78,  78); // Color when icon is hovered
fIcon.colorActiveOn= QColor(122, 196,  62); // Color when icon is hovered and state is on
fIcon.colorDisabled= QColor(122, 196,  62); // Color when icon is disabled
fIcon.colorSelected= QColor(122, 196,  62); // Color when icon is selected

fIcon.scaleFactor=   0.80;                  // Default icon scale factor
fIcon.scaleFactorOn= 1.00;                  // Scale factor when icon state is On

ZFontIcon::icon(fIcon);
```


## Tips
With meta-object support for fonts helpers namespaces, you can iterate over the namespace:

```c++
QMetaEnum metaEnum= QMetaEnum::fromType<Fa5::Glyph>();
for(int i= 0; i < metaEnum.keyCount(); ++i) {
    qDebug() << metaEnum.key(i);   // Name of the given index
    qDebug() << metaEnum.value(i); // Value with the given index
}
```


## Exemple

The following repository contains a commented example based on Font Awesome.
Open ZFontIconSample.pro in QtCreator and run it or read sources for more information.
Look comments at the beginning of main.cpp to enable FA5 Pro or FA6 preview.


## Credits
ZFontIcon is inspired/based on: QFontIcon by Sacha Schutz - sacha@labsquare.org | https://github.com/dridk
