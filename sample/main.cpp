#include "MainWindow.h"
#include <QApplication>

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_bi1.h"
#include "ZFontIcon/ZFont_gmi4.h"
#include "ZFontIcon/ZFont_mdi7.h"
#include "ZFontIcon/ZFont_ph2.h"

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

    // FA6 Free (Solid style)
    ZFontIcon::addFont(":/fa6/" + Fa6::FA6_TTF_FILE_FREE_SOLID);

    // FA6 Brands (Regular style)
    ZFontIcon::addFont(":/fa6/" + Fa6brands::FA6_TTF_FILE_BRANDS);

    // FA6 Pro (Solid, Regular Light and Thin styles)
    if(USE_FA6_PRO_FONT) {
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_SOLID);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_REGULAR);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_LIGHT);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_TTF_FILE_PRO_THIN);
        // Sharp
        ZFontIcon::addFont(":/fa6/" + Fa6sharp::FA6_TTF_FILE_SHARP_SOLID);
        ZFontIcon::addFont(":/fa6/" + Fa6sharp::FA6_TTF_FILE_SHARP_REGULAR);
        ZFontIcon::addFont(":/fa6/" + Fa6sharp::FA6_TTF_FILE_SHARP_LIGHT);
    }
}


//-----------------------
// Fonts Awesome 5.15.4 -
//-----------------------
void registerFa5_fonts() {
    // Note that:
    //   Solid, Regular Light and Thin styles share the same family name,
    //   Brands style have a different family name

    // FA5 Free (Solid style)
    ZFontIcon::addFont(":/fa5/" + Fa5::FA5_OTF_FILE_FREE_SOLID);

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
    ZFontIcon::addFont(":/fa4/"  + Fa4::FA4_TTF_FILE_REGULAR);
}


//----------------------
// BootStrap Icons 1.x -
//----------------------
void registerBi1_fonts() {
    ZFontIcon::addFont(":/bi1/"  + Bi1::BI1_TTF_FILE_REGULAR);
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
// Material Design Icons 7.x -
//----------------------------
void registerMdi7_fonts() {
    ZFontIcon::addFont(":/mdi7/" + Mdi6::MDI6_TTF_FILE_REGULAR);
}


//----------------------------
// Phosphor 2.x -
//----------------------------
void registerPh2_fonts() {
    ZFontIcon::addFont(":/ph2/" + Ph2::PH2_TTF_FILE_BOLD);
    ZFontIcon::addFont(":/ph2/" + Ph2::PH2_TTF_FILE_FILL);
    ZFontIcon::addFont(":/ph2/" + Ph2::PH2_TTF_FILE_REGULAR);
    ZFontIcon::addFont(":/ph2/" + Ph2::PH2_TTF_FILE_LIGHT);
    ZFontIcon::addFont(":/ph2/" + Ph2::PH2_TTF_FILE_THIN);
}





int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Register fonts
    registerFa6_fonts();
    registerFa5_fonts();
    registerFa4_fonts();
    registerBi1_fonts();
    registerGmi4_fonts();
    registerMdi7_fonts();
    registerPh2_fonts();

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
