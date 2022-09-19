#include "MainWindow.h"
#include <QApplication>

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_bi1.h"
#include "ZFontIcon/ZFont_gmi4.h"
#include "ZFontIcon/ZFont_mdi6.h"
#include "ZFontIcon/ZFont_ph1.h"

// Enable Font Awesome 6 Pro and Font Awesome 5 Pro
bool USE_FA6_PRO_FONT= false; // Note: Edit resource file in plain text Editor to add FA6 Pro fonts
bool USE_FA5_PRO_FONT= false; // Note: Edit resource file in plain text Editor to add FA5 Pro fonts


//--------------------
// Fonts Awesome 6.x -
//--------------------
void registerFa6_fonts() {
    // Note that:
    //   Solid, Regular Light and Thin styles share the same family name,
    //   Brands style have a different family name

    // FA6 Free (Solid and Regular styles)
    ZFontIcon::addFont(":/fa6/" + Fa6::FA6_TTF_FILE_FREE_SOLID);
    ZFontIcon::addFont(":/fa6/" + Fa6::FA6_TTF_FILE_FREE_REGULAR); // Support less icons than Solid style (~150)
    // FA6 Brands (Regular style)
    ZFontIcon::addFont(":/fa6/" + Fa6brands::FA6_TTF_FILE_BRANDS);

    // FA6 Pro (Solid, Regular Light and Thin styles)
    if(USE_FA6_PRO_FONT) {
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_SOLID);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_REGULAR);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_LIGHT);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_THIN);
        ZFontIcon::addFont(":/fa6/" + Fa6sharp::FA6_TTF_FILE_SHARP);
    }
}


//-----------------------
// Fonts Awesome 5.15.4 -
//-----------------------
void registerFa5_fonts() {
    // Note that:
    //   Solid, Regular Light and Thin styles share the same family name,
    //   Brands style have a different family name

    // FA5 Free (Solid and Regular styles)
    ZFontIcon::addFont(":/fa5/" + Fa5::FA5_WOFF_FILE_FREE_SOLID);
    ZFontIcon::addFont(":/fa5/" + Fa5::FA5_WOFF_FILE_FREE_REGULAR); // Support less icons than Solid style (~150)
    // FA5 Brands (Regular style)
    ZFontIcon::addFont(":/fa5/" + Fa5brands::FA5_WOFF_FILE_BRANDS);

    // FA5 Pro (Solid, Regular Light and Thin styles)
    if(USE_FA5_PRO_FONT) {
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_WOFF_FILE_PRO_SOLID);
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_WOFF_FILE_PRO_REGULAR);
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_WOFF_FILE_PRO_LIGHT);
    }
}


//-----------------------------
// Fonts Awesome 4.7 (legacy) -
//-----------------------------
void registerFa4_fonts() {
    ZFontIcon::addFont(":/fa4/"  + Fa4::FA4_WOFF_FILE_REGULAR);
}


//----------------------
// BootStrap Icons 1.x -
//----------------------
void registerBi1_fonts() {
    ZFontIcon::addFont(":/bi1/"  + Bi1::BI1_WOFF_FILE_REGULAR);
}


//----------------------------
// Google Material Icons 4.x -
//----------------------------
void registerGmi4_fonts() {
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_OUTLINED);
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_ROUNDED);
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_SHARP);
}


//----------------------------
// Material Design Icons 6.x -
//----------------------------
void registerMdi6_fonts() {
    ZFontIcon::addFont(":/mdi6/" + Mdi6::MDI6_WOFF_FILE_REGULAR);
}


//----------------------------
// Phosphor 1.x -
//----------------------------
void registerPh1_fonts() {
    ZFontIcon::addFont(":/ph1/" + Ph1::PH1_WOFF_FILE_REGULAR);
}





int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Register fonts
    registerFa6_fonts();
    registerFa5_fonts();
    registerFa4_fonts();
    registerBi1_fonts();
    registerGmi4_fonts();
    registerMdi6_fonts();
    registerPh1_fonts();

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
