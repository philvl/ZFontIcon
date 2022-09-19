# ZFontIcon - Icon fonts support for Qt applications
ZFontIcon is released under the MIT License


## Description
ZFontIcon provides a simple way to use any glyph/icon font as QIcon in your Qt5/Qt6 applications.

Some helpers are included to use the following icon fonts with no effort:
- Font Awesome 6.2.0  (Free, Brands and Pro)
- Font Awesome 5.15.4 (Free, Brands and Pro)
- Font Awesome 4.7.0
- Bootstrap Icons 1.9.1
- Google Material Design Icons 4 (v2022-08-01, github master 1c57576)
- Material Design Icons 6.9.96
- Phosphor 1.4

You can use any other icon fonts using Unicode character codes. For convenience, I suggest you create your own font helper: simply create an enumeration listing all the Unicode characters of the font icons. Have a look at the code, it's very easy!


## Qt Compatibility
ZFontIcon requires at least Qt 5.9.
ZFontIcon is tested under Windows, and Linux with:
- Qt 5.9
- Qt 5.12
- Qt 5.15
- Qt 6.0
- Qt 6.2


## Installation
The easiest way to include ZFontIcon in your project is to copy the ZFontIcon folder to your project tree and add the following include() to your Qt project (.pro) file:

    include("ZFontIcon/ZFontIcon.pri")

Now, you are ready!


## Usage
### Basic usage

First of all, you need to load the icon fonts you want to use (typically in the main.cpp):

```c++
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h" // FA6 helpers

// FA6 Free
ZFontIcon::addFont(":/fa6/" + Fa6::FA6_TTF_FILE_FREE_SOLID);
ZFontIcon::addFont(":/fa6/" + Fa6::FA6_TTF_FILE_FREE_REGULAR);

// FA6 Pro (if you have a license)
ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_SOLID);
ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_REGULAR);
ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_LIGHT);
ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_THIN);

// FA6 Pro Sharp (if you have a license)
ZFontIcon::addFont(":/fa6/" + Fa6sharp::FA6_TTF_FILE_SHARP);

// FA6 Brands
ZFontIcon::addFont(":/fa6/" + Fa6brands::FA6_TTF_FILE_BRANDS);
```

Then you can get your favorite icons:

```c++
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"

// FA6 Free (FA6 Free include about 150 regular icon)
ZFontIcon::icon(Fa6::FAMILY,       Fa6::SOLID,      Fa6::fa_flag, QColor(195,  65,  65));
ZFontIcon::icon(Fa6::FAMILY,       Fa6::REGULAR,    Fa6::fa_flag, QColor(195,  65,  65));

// FA6 Pro (only if you have a license)
ZFontIcon::icon(Fa6pro::FAMILY,    Fa6pro::SOLID,   Fa6pro::fa_flag, QColor(195,  65,  65));
ZFontIcon::icon(Fa6pro::FAMILY,    Fa6pro::REGULAR, Fa6pro::fa_flag, QColor(195,  65,  65));
ZFontIcon::icon(Fa6pro::FAMILY,    Fa6pro::LIGHT,   Fa6pro::fa_flag, QColor(195,  65,  65));
ZFontIcon::icon(Fa6pro::FAMILY,    Fa6pro::THIN,    Fa6pro::fa_flag, QColor(195,  65,  65));

// FA6 Sharp (only if you have a license)
//   Use the glyphs defined in fa5pro namespace because they are identical to Fa6sharp glyphs
ZFontIcon::icon(Fa6sharp::FAMILY,  Fa6sharp::SOLID, Fa6pro::fa_flag, QColor(195,  65,  65));

// FA6 Brands (note that FA6 Brands has no font style)
ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_github, QColor(128, 0, 0));
```


### Intermediate usage
Need to set default icon color for the whole project? No problem, use the global definition!

```c++
ZFontIconOption::gColor=         QColor(195,  65,  65); // Default color
ZFontIconOption::gColorDisabled= QColor(122, 196,  62); // Color when icon is disabled
ZFontIconOption::gColorSelected= QColor(122, 196,  62); // Color when icon is selected

// Optional settings: if not set, color value will be used
ZFontIconOption::gColorOn=       QColor(102, 163,  52); // Color when icon state is On
ZFontIconOption::gColorActive=   QColor(234,  78,  78); // Color when icon is hovered
ZFontIconOption::gColorActiveOn= QColor(122, 196,  62); // Color when icon is hovered and state is On
```


### Advanced usage
More customization needed? You can set all aspects of your icon:

- Rotate, flip from top to bottom and flip from left to right icon
- On icon state change [On/Off] you can use different:
  - font styles (eg. switch from Solid to Regular font style);
  - glyphs (eg. change glyph from lock to unlock);
  - colors (override global colors);
  - scale factors (eg. make On state glyph bigger than Off state glyph);
- On mouse hover, you can:
  - set a hover color for Off state;
  - set a hover color for On state,
- For icon mode Selected and Disabled, you can change the default color.

```c++
ZFontIconOption fIcon;

// Minimum required arguments
fIcon.fontFamily=    Fa6::FAMILY;           // Set the font icon family
fIcon.fontStyle=     Fa6::SOLID;            // Set the family style (Required if font families have multiple registered styles)
fIcon.glyph=         Fa6::fa_grin;          // Set the default glyph
fIcon.color=         QColor(195,  65,  65); // Set the default color

// Optional arguments
fIcon.fontStyleOn=   Fa6::REGULAR;          // Font style when icon state is On
fIcon.glyphOn=       Fa6::fa_grin_stars;    // Glyph when icon state is On

fIcon.colorOn=       QColor(102, 163,  52); // Color when icon state is On
fIcon.colorActive=   QColor(234,  78,  78); // Color when icon is hovered
fIcon.colorActiveOn= QColor(122, 196,  62); // Color when icon is hovered and state is On
fIcon.colorDisabled= QColor(122, 196,  62); // Color when icon is disabled
fIcon.colorSelected= QColor(122, 196,  62); // Color when icon is selected

fIcon.scaleFactor=   0.80;                  // Default icon scale factor
fIcon.scaleFactorOn= 1.00;                  // Scale factor when icon state is On

fIcon.rotateAngle=   0.00;                  // Icon clockwise rotation in degree
fIcon.flipLeftRight= false;                 // Icon flip from left to right
fIcon.flipTopBottom= false;                 // Icon flip from top to bottom

ZFontIcon::icon(fIcon);
```


## Tips
With meta-object support for font helper namespaces, you can iterate over the namespace:

```c++
QMetaEnum metaEnum= QMetaEnum::fromType<Fa6::Glyph>();
for(int i= 0; i < metaEnum.keyCount(); ++i) {
    qDebug() << metaEnum.key(i);   // Name of the given index
    qDebug() << metaEnum.value(i); // Value with the given index
}
```


## Example

The following repository contains a commented example based on Font Awesome.
Open ZFontIconSample.pro in QtCreator and run it or read sources for more information.
Check the comments at the beginning of main.cpp to enable FA6 Pro or FA5 Pro.


## Support

I do not provide any specific support, but if you have any question, please feel free to reach me out via email at philvl.dev(at)gmail.com


## Credits
ZFontIcon is inspired/based on: QFontIcon by Sacha Schutz - sacha@labsquare.org | https://github.com/dridk

Special thanks to contributors:
- Ti-R | https://github.com/Ti-R
