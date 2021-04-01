#include "MainWindow.h"
#include "Dialog.h"
#include "DialogSheetCheat.h"
#include <QApplication>

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_gmi4.h"

// Enable Font Awesome 6 Preview and Font Awesome 5 Pro
bool USE_FA6_FREE_PREVIEW= false; // Note: Edit resource file in plain text Editor to add FA6 Free fonts
bool USE_FA6_PRO_PREVIEW=  false; // Note: Edit resource file in plain text Editor to add FA6 Pro fonts
bool USE_FA5_PRO_FONT=     false; // Note: Edit resource file in plain text Editor to add FA5 Pro fonts


//------------------------------
// Fonts Awesome 6.x (Preview) -
//------------------------------
void registerFA6_fonts() {
    // Note that:
    //   Solid, Regular Light and Thin styles share the same family name,
    //   Brands style have a different family name

    if(USE_FA6_FREE_PREVIEW) {
        // FA6 Free (Solid and Regular styles)
        ZFontIcon::addFont(":/fa6/" + Fa6::FA6_OTF_FILE_FREE_SOLID);
        ZFontIcon::addFont(":/fa6/" + Fa6::FA6_OTF_FILE_FREE_REGULAR); // Support less icons than Solid style (~150)
        // FA6 Brands (Regular style)
        ZFontIcon::addFont(":/fa6/" + Fa6brands::FA6_OTF_FILE_BRANDS);
    }

    // FA6 Pro (Solid, Regular Light and Thin styles)
    if(USE_FA6_PRO_PREVIEW) {
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_OTF_FILE_PRO_SOLID);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_OTF_FILE_PRO_REGULAR);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_OTF_FILE_PRO_LIGHT);
        ZFontIcon::addFont(":/fa6/" + Fa6pro::FA6_OTF_FILE_PRO_THIN);
    }
}


//-----------------------
// Fonts Awesome 5.15.3 -
//-----------------------
void registerFa5_fonts() {
    // Note that:
    //   Solid, Regular Light and Thin styles share the same family name,
    //   Brands style have a different family name

    // FA5 Free (Solid and Regular styles)
    ZFontIcon::addFont(":/fa5/" + Fa5::FA5_OTF_FILE_FREE_SOLID);
    ZFontIcon::addFont(":/fa5/" + Fa5::FA5_OTF_FILE_FREE_REGULAR); // Support less icons than Solid style (~150)
    // FA5 Brands (Regular style)
    ZFontIcon::addFont(":/fa5/" + Fa5brands::FA5_OTF_FILE_BRANDS);

    // FA5 Pro (Solid, Regular Light and Thin styles)
    if(USE_FA5_PRO_FONT) {
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_SOLID);
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_REGULAR);
        ZFontIcon::addFont(":/fa5/" + Fa5pro::FA5_OTF_FILE_PRO_LIGHT);
    }
}


//-----------------------------
// Fonts Awesome 4.7 (legacy) -
//-----------------------------
void registerFa4_fonts() {
    ZFontIcon::addFont(":/fa4/"  + Fa4::FA4_OTF_FILE_FREE_REGULAR);
}


//----------------------------
// Google Material Icons 4.x -
//----------------------------
void registerGmi4_fonts() {
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_OUTLINED);
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_ROUNDED);
    ZFontIcon::addFont(":/gmi4/" + Gmi4::GMD_OTF_FILE_SHARP);
}





int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Register fonts
    registerFA6_fonts();
    registerFa5_fonts();
    registerFa4_fonts();
    registerGmi4_fonts();

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
