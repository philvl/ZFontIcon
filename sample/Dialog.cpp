#include "Dialog.h"
#include "ui_Dialog.h"

#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa_4.7.h"
#include "ZFontIcon/ZFont_fa_5.13.h"
#include "ZFontIcon/ZFont_mdi_2.2.h"

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
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_FREE_SOLID);      // _995 icons
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_FREE_REGULAR);    // _152 icons
    // FA5 Pro
    if(!USE_PRO_FONT)
        ui->tabWidget->removeTab(1);
    else {
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_SOLID);   // 1850 icons
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_REGULAR); // 1850 icons
        ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_PRO_LIGHT);   // 1850 icons
    }
    // FA5 Brands
    ZFontIcon::addFont(":/fa_5.13.0/" + FA5_OTF_FILE_BRANDS);          // _442 icons

    // Fonts Awesome 4 (legacy)
    ZFontIcon::addFont(":/fa_4.7.0/"  + FA4_OTF_FILE_FREE_REGULAR);    // _675 icons

    // Google Material Design icons
    ZFontIcon::addFont(":/gmd_2.2.0/" + GMD_OTF_FILE_REGULAR);         // _932 icons
//----


    // Show registered fonts (family and styles) in a treeWidget
    QMapIterator<QString, QStringList> iterator(ZFontIcon::registeredFonts());
    while (iterator.hasNext()) {
        iterator.next();
        QTreeWidgetItem *familyItem= new QTreeWidgetItem(ui->treeWidget);
        familyItem->setText(0, iterator.key());
        familyItem->setExpanded(true);
        for(const QString &style : iterator.value()) {
            QTreeWidgetItem *styleItem= new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);
        }
    }


    // Font Awesome 5 FREE
    //----------------------
    // The family of the first loaded font is used by default. In this example, the
    // "Font Awesome 5 Solid" font family is set by default. Solid, Regular, and Light
    // styles share the same family name so specify the family is useless.
    // As different styles from the same font family have been loaded (Solid and Regular),
    // we need to specify which style to use explicitly
    ui->fa5_btn101->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::SOLID,   Fa5::fa_flag,    QColor(195,  65,  65)));
    ui->fa5_btn102->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::SOLID,   Fa5::fa_star,    QColor(214, 197,  64)));
    ui->fa5_btn103->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::SOLID,   Fa5::fa_user,    QColor( 69, 100, 214)));
    ui->fa5_btn104->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::SOLID,   Fa5::fa_map,     QColor(102, 163,  52)));
    ui->fa5_btn105->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::SOLID,   Fa5::fa_comment, QColor(  0,   0,   0)));

    ui->fa5_btn111->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::REGULAR, Fa5::fa_flag,    QColor(195,  65,  65)));
    ui->fa5_btn112->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::REGULAR, Fa5::fa_star,    QColor(214, 197,  64)));
    ui->fa5_btn113->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::REGULAR, Fa5::fa_user,    QColor( 69, 100, 214)));
    ui->fa5_btn114->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::REGULAR, Fa5::fa_map,     QColor(102, 163,  52)));
    ui->fa5_btn115->setIcon(ZFontIcon::icon(Fa5::FAMILY, Fa5::REGULAR, Fa5::fa_comment, QColor(  0,   0,   0)));


    // Font Awesome 5 BRANDS
    //------------------------
    // FA5 Brands is not the first added font, so we must specify the family explicitly
    // FA5 Brands font has only one style so we don't need to specify it
    ui->fa5_btn121->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_github,    QColor(0, 0, 0)));
    ui->fa5_btn122->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_gitlab,    QColor(0, 0, 0)));
    ui->fa5_btn123->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_facebook,  QColor(0, 0, 0)));
    ui->fa5_btn124->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_twitter,   QColor(0, 0, 0)));
    ui->fa5_btn125->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_instagram, QColor(0, 0, 0)));


    // Advanced use exemple with Font Awesome 5 FREE
    //----------------------
    ZFontIconOption fIcon;
    fIcon.fontFamily=    Fa5::FAMILY;
    fIcon.fontStyle=     Fa5::SOLID;
    fIcon.glyph=         Fa5::fa_lock;
    fIcon.glyphOn=       Fa5::fa_unlock;
    fIcon.color=         QColor(195,  65,  65);
    fIcon.colorOn=       QColor(102, 163,  52);
    fIcon.colorActive=   QColor(234,  78,  78);
    fIcon.colorActiveOn= QColor(122, 196,  62);
    fIcon.scaleFactor=   0.85;
    fIcon.scaleFactorOn= 1.00;
    ui->fa5_btn131->setIcon(ZFontIcon::icon(fIcon));
    ui->fa5_btn132->setIcon(ZFontIcon::icon(fIcon));
    ui->fa5_btn133->setIcon(ZFontIcon::icon(fIcon));


    // Font Awesome 5 PRO
    //---------------------
    if(USE_PRO_FONT) {
        ui->fa5pro_btn201->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa5pro_btn202->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_star,    QColor(214, 197,  64)));
        ui->fa5pro_btn203->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa5pro_btn204->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_map,     QColor(102, 163,  52)));
        ui->fa5pro_btn205->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::SOLID,   Fa5pro::fa_comment, QColor(  0,   0,   0)));

        ui->fa5pro_btn211->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa5pro_btn212->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_star,    QColor(214, 197,  64)));
        ui->fa5pro_btn213->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa5pro_btn214->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_map,     QColor(102, 163,  52)));
        ui->fa5pro_btn215->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::REGULAR, Fa5pro::fa_comment, QColor(  0,   0,   0)));

        ui->fa5pro_btn221->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa5pro_btn222->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_star,    QColor(214, 197,  64)));
        ui->fa5pro_btn223->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa5pro_btn224->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_map,     QColor(102, 163,  52)));
        ui->fa5pro_btn225->setIcon(ZFontIcon::icon(Fa5pro::FAMILY, Fa5pro::LIGHT,   Fa5pro::fa_comment, QColor(  0,   0,   0)));
    }


    // Font Awesome 4.7.0
    //---------------------
    ui->fa4_btn101->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_flag,      QColor(195,  65,  65)));
    ui->fa4_btn102->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_star,      QColor(214, 197,  64)));
    ui->fa4_btn103->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_user,      QColor( 69, 100, 214)));
    ui->fa4_btn104->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_map,       QColor(102, 163,  52)));
    ui->fa4_btn105->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_comment,   QColor(  0,   0,   0)));

    ui->fa4_btn111->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_flag_o,    QColor(195,  65,  65)));
    ui->fa4_btn112->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_star_o,    QColor(214, 197,  64)));
    ui->fa4_btn113->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_user_o,    QColor( 69, 100, 214)));
    ui->fa4_btn114->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_map_o,     QColor(102, 163,  52)));
    ui->fa4_btn115->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_comment_o, QColor(  0,   0,   0)));

    ui->fa4_btn121->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_github,    QColor(0, 0, 0)));
    ui->fa4_btn122->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_gitlab,    QColor(0, 0, 0)));
    ui->fa4_btn123->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_facebook,  QColor(0, 0, 0)));
    ui->fa4_btn124->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_twitter,   QColor(0, 0, 0)));
    ui->fa4_btn125->setIcon(ZFontIcon::icon(Fa4::FAMILY, Fa4::fa_instagram, QColor(0, 0, 0)));


    // Google Material Design Icons 2.2.0
    //-------------------------------------
    ui->mdi_btn101->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_flag,        QColor(195,  65,  65)));
    ui->mdi_btn102->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_star,        QColor(214, 197,  64)));
    ui->mdi_btn103->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_person,      QColor( 69, 100, 214)));
    ui->mdi_btn104->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_map,         QColor(102, 163,  52)));
    ui->mdi_btn105->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_chat_bubble, QColor(  0,   0,   0)));

    ui->mdi_btn112->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_star_border,         QColor(214, 197,  64)));
    ui->mdi_btn113->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_person_outline,      QColor( 69, 100, 214)));
    ui->mdi_btn115->setIcon(ZFontIcon::icon(Mdi::FAMILY, Mdi::md_chat_bubble_outline, QColor(  0,   0,   0)));
}

Dialog::~Dialog() {
    delete ui;
}
