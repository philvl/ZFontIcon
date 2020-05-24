#include "Dialog.h"
#include "ui_Dialog.h"

#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa_4.7.h"
#include "ZFontIcon/ZFont_fa_5.13.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);


    // Enable Font Awesome 5 Pro
    //-- Note: Add the FA5 Pro font to the resource file
    bool USE_PRO_FONT= false;

// The following part of the code should be moved to the main.cpp file
    // Fonts Awesome 5
    //-- FA5 Free   supports  995 Solid icons and 151 Regular icons
    //-- FA5 Pro    supports 1850 Solid, Regular and Light icons
    //-- FA5 Brands supports  442 icons
    //-- Note that: Solid, Regular and Light styles share the same family name,
    //--            Brands icons have a different family name
    // FA5 Free
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_FREE_SOLID);   //  995 icons
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_FREE_REGULAR); //  152 icons
    // FA5 Pro
    if(!USE_PRO_FONT)
        ui->tabWidget->removeTab(1);
    else {
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_SOLID);  // 1850 icons
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_REGULAR);// 1850 icons
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_LIGHT);  // 1850 icons
    }
    // FA5 Brands
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_BRANDS);       //  442 icons

    // Fonts Awesome 4 (legacy)
    ZFontIcon::addFont(":/fa_4.7.0/"  + FA4_OTF_FILE_FREE_REGULAR); //  675 icons
//----


    // Font Awesome 5 FREE
    //----------------------
    // The family of the first loaded font is used by default. In this example, the
    // "Font Awesome 5 Solid" font family is set by default. Solid, Regular, and Light
    // styles share the same family name so specify the family is useless.
    // As different styles from the same font family have been loaded (Solid and Regular),
    // we need to specify which style to use explicitly
    ui->fa5_btn101->setIcon(ZFontIcon::icon(fa5::fa_flag, QColor(0, 0, 0), fa5::SOLID));
    ui->fa5_btn102->setIcon(ZFontIcon::icon(fa5::fa_star, QColor(0, 0, 0), fa5::SOLID));
    ui->fa5_btn103->setIcon(ZFontIcon::icon(fa5::fa_user, QColor(0, 0, 0), fa5::SOLID));
    ui->fa5_btn104->setIcon(ZFontIcon::icon(fa5::fa_map,  QColor(0, 0, 0), fa5::SOLID));

    ui->fa5_btn111->setIcon(ZFontIcon::icon(fa5::fa_flag, QColor(0, 0, 0), fa5::REGULAR));
    ui->fa5_btn112->setIcon(ZFontIcon::icon(fa5::fa_star, QColor(0, 0, 0), fa5::REGULAR));
    ui->fa5_btn113->setIcon(ZFontIcon::icon(fa5::fa_user, QColor(0, 0, 0), fa5::REGULAR));
    ui->fa5_btn114->setIcon(ZFontIcon::icon(fa5::fa_map,  QColor(0, 0, 0), fa5::REGULAR));


    // Font Awesome 5 BRANDS
    //------------------------
    // FA5 Brands is not the first added font, so we must specify the family explicitly
    // FA5 Brands font has only one style so we don't need to specify it
    ui->fa5_btn121->setIcon(ZFontIcon::icon(fa5brands::FAMILY, fa5brands::fa_github,    QColor(0, 0, 0)));
    ui->fa5_btn122->setIcon(ZFontIcon::icon(fa5brands::FAMILY, fa5brands::fa_facebook,  QColor(0, 0, 0)));
    ui->fa5_btn123->setIcon(ZFontIcon::icon(fa5brands::FAMILY, fa5brands::fa_twitter,   QColor(0, 0, 0)));
    ui->fa5_btn124->setIcon(ZFontIcon::icon(fa5brands::FAMILY, fa5brands::fa_instagram, QColor(0, 0, 0)));


    // Font Awesome 5 PRO
    //---------------------
    if(USE_PRO_FONT) {
        ui->fa5pro_btn201->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_flag, QColor(0, 0, 0), fa5pro::SOLID));
        ui->fa5pro_btn202->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_star, QColor(0, 0, 0), fa5pro::SOLID));
        ui->fa5pro_btn203->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_user, QColor(0, 0, 0), fa5pro::SOLID));
        ui->fa5pro_btn204->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_map,  QColor(0, 0, 0), fa5pro::SOLID));

        ui->fa5pro_btn211->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_flag, QColor(0, 0, 0), fa5pro::REGULAR));
        ui->fa5pro_btn212->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_star, QColor(0, 0, 0), fa5pro::REGULAR));
        ui->fa5pro_btn213->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_user, QColor(0, 0, 0), fa5pro::REGULAR));
        ui->fa5pro_btn214->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_map,  QColor(0, 0, 0), fa5pro::REGULAR));

        ui->fa5pro_btn221->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_flag, QColor(0, 0, 0), fa5pro::LIGHT));
        ui->fa5pro_btn222->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_star, QColor(0, 0, 0), fa5pro::LIGHT));
        ui->fa5pro_btn223->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_user, QColor(0, 0, 0), fa5pro::LIGHT));
        ui->fa5pro_btn224->setIcon(ZFontIcon::icon(fa5pro::FAMILY, fa5pro::fa_map,  QColor(0, 0, 0), fa5pro::LIGHT));
    }


    // Font Awesome 4.7.0
    //---------------------
    ui->fa4_btn101->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_flag, QColor(0, 0, 0)));
    ui->fa4_btn102->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_star, QColor(0, 0, 0)));
    ui->fa4_btn103->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_user, QColor(0, 0, 0)));
    ui->fa4_btn104->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_map,  QColor(0, 0, 0)));

    ui->fa4_btn111->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_flag_o, QColor(0, 0, 0)));
    ui->fa4_btn112->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_star_o, QColor(0, 0, 0)));
    ui->fa4_btn113->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_user_o, QColor(0, 0, 0)));
    ui->fa4_btn114->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_map_o,  QColor(0, 0, 0)));

    ui->fa4_btn121->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_github,    QColor(0, 0, 0)));
    ui->fa4_btn122->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_facebook,  QColor(0, 0, 0)));
    ui->fa4_btn123->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_twitter,   QColor(0, 0, 0)));
    ui->fa4_btn124->setIcon(ZFontIcon::icon(fa4::FAMILY, fa4::fa_instagram, QColor(0, 0, 0)));
}

Dialog::~Dialog() {
    delete ui;
}
