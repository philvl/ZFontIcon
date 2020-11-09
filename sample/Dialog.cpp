#include "Dialog.h"
#include "ui_Dialog.h"

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_gmi4.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

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

    //--------------------------------
    // Font Awesome 6 FREE (Preview) -
    //--------------------------------
    if(ZFontIcon::registeredFonts().contains(Fa6::FAMILY) && ZFontIcon::registeredFonts().contains(Fa6brands::FAMILY)) {
        // The family of the first loaded font is used by default. In this example, the
        // "Font Awesome 6 Solid" font family is set by default. Solid, Regular, Light
        // and Thin styles share the same family name so specify the family is useless.
        // As different styles from the same font family have been loaded (Solid and Regular),
        // we need to specify which style to use explicitly
        ui->fa6_btn101->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::SOLID,   Fa6::fa_flag,    QColor(195,  65,  65)));
        ui->fa6_btn102->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::SOLID,   Fa6::fa_star,    QColor(214, 197,  64)));
        ui->fa6_btn103->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::SOLID,   Fa6::fa_user,    QColor( 69, 100, 214)));
        ui->fa6_btn104->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::SOLID,   Fa6::fa_map,     QColor(102, 163,  52)));
        ui->fa6_btn105->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::SOLID,   Fa6::fa_comment, QColor(  0,   0,   0)));

        ui->fa6_btn111->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::REGULAR, Fa6::fa_flag,    QColor(195,  65,  65)));
        ui->fa6_btn112->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::REGULAR, Fa6::fa_star,    QColor(214, 197,  64)));
        ui->fa6_btn113->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::REGULAR, Fa6::fa_user,    QColor( 69, 100, 214)));
        ui->fa6_btn114->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::REGULAR, Fa6::fa_map,     QColor(102, 163,  52)));
        ui->fa6_btn115->setIcon(ZFontIcon::icon(Fa6::FAMILY, Fa6::REGULAR, Fa6::fa_comment, QColor(  0,   0,   0)));

        // Advanced use exemple with Font Awesome 6 FREE
        ZFontIconOption fIconFa6;
        fIconFa6.fontFamily=    Fa6::FAMILY;
        fIconFa6.fontStyle=     Fa6::SOLID;
        fIconFa6.fontStyleOn=   Fa6::REGULAR;
        fIconFa6.glyph=         Fa6::fa_face_grin;
        fIconFa6.glyphOn=       Fa6::fa_face_grin_stars;
        fIconFa6.color=         QColor(195,  65,  65);
        fIconFa6.colorOn=       QColor(102, 163,  52);
        fIconFa6.colorActive=   QColor(234,  78,  78);
        fIconFa6.colorActiveOn= QColor(122, 196,  62);
        fIconFa6.scaleFactor=   0.85;
        fIconFa6.scaleFactorOn= 1.00;
        ui->fa6_btn121->setIcon(ZFontIcon::icon(fIconFa6));
        ui->fa6_btn122->setIcon(ZFontIcon::icon(fIconFa6));
        ui->fa6_btn123->setIcon(ZFontIcon::icon(fIconFa6));


        //----------------------------------
        // Font Awesome 6 BRANDS (Preview) -
        //----------------------------------
        // FA6 Brands is not the first added font, so we must specify the family explicitly
        // FA6 Brands font has only one style so we don't need to specify it
        ui->fa6_btn131->setIcon(ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_github    ));
        ui->fa6_btn132->setIcon(ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_gitlab    ));
        ui->fa6_btn133->setIcon(ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_facebook  ));
        ui->fa6_btn134->setIcon(ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_twitter   ));
        ui->fa6_btn135->setIcon(ZFontIcon::icon(Fa6brands::FAMILY, Fa6brands::fa_instagram ));
    }
    else {
        // Remove FA6 Free tab
        QWidget *fa6_tab= ui->tabWidget->findChild<QWidget*>("fa6_tab");
        int tabIndex= ui->tabWidget->indexOf(fa6_tab);
        ui->tabWidget->removeTab(tabIndex);
    }


    //-------------------------------
    // Font Awesome 6 PRO (Preview) -
    //-------------------------------
    if(ZFontIcon::registeredFonts().contains(Fa6pro::FAMILY)) {
        ui->fa6pro_btn201->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::SOLID,   Fa6pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa6pro_btn202->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::SOLID,   Fa6pro::fa_star,    QColor(214, 197,  64)));
        ui->fa6pro_btn203->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::SOLID,   Fa6pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa6pro_btn204->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::SOLID,   Fa6pro::fa_map,     QColor(102, 163,  52)));
        ui->fa6pro_btn205->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::SOLID,   Fa6pro::fa_comment, QColor(  0,   0,   0)));

        ui->fa6pro_btn211->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::REGULAR, Fa6pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa6pro_btn212->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::REGULAR, Fa6pro::fa_star,    QColor(214, 197,  64)));
        ui->fa6pro_btn213->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::REGULAR, Fa6pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa6pro_btn214->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::REGULAR, Fa6pro::fa_map,     QColor(102, 163,  52)));
        ui->fa6pro_btn215->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::REGULAR, Fa6pro::fa_comment, QColor(  0,   0,   0)));

        ui->fa6pro_btn221->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::LIGHT,   Fa6pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa6pro_btn222->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::LIGHT,   Fa6pro::fa_star,    QColor(214, 197,  64)));
        ui->fa6pro_btn223->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::LIGHT,   Fa6pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa6pro_btn224->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::LIGHT,   Fa6pro::fa_map,     QColor(102, 163,  52)));
        ui->fa6pro_btn225->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::LIGHT,   Fa6pro::fa_comment, QColor(  0,   0,   0)));

        ui->fa6pro_btn231->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::THIN,    Fa6pro::fa_flag,    QColor(195,  65,  65)));
        ui->fa6pro_btn232->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::THIN,    Fa6pro::fa_star,    QColor(214, 197,  64)));
        ui->fa6pro_btn233->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::THIN,    Fa6pro::fa_user,    QColor( 69, 100, 214)));
        ui->fa6pro_btn234->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::THIN,    Fa6pro::fa_map,     QColor(102, 163,  52)));
        ui->fa6pro_btn235->setIcon(ZFontIcon::icon(Fa6pro::FAMILY, Fa6pro::THIN,    Fa6pro::fa_comment, QColor(  0,   0,   0)));
    }
    else {
        // Remove FA6 Pro tab
        QWidget *fa6pro_tab= ui->tabWidget->findChild<QWidget*>("fa6pro_tab");
        int tabIndex= ui->tabWidget->indexOf(fa6pro_tab);
        ui->tabWidget->removeTab(tabIndex);
    }


    //----------------------
    // Font Awesome 5 FREE -
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

    // Advanced use exemple with Font Awesome 5 FREE
    ZFontIconOption fIconFa5;
    fIconFa5.fontFamily=    Fa5::FAMILY;
    fIconFa5.fontStyle=     Fa5::SOLID;
    fIconFa5.fontStyleOn=   Fa5::REGULAR;
    fIconFa5.glyph=         Fa5::fa_grin;
    fIconFa5.glyphOn=       Fa5::fa_grin_stars;
    fIconFa5.color=         QColor(195,  65,  65);
    fIconFa5.colorOn=       QColor(102, 163,  52);
    fIconFa5.colorActive=   QColor(234,  78,  78);
    fIconFa5.colorActiveOn= QColor(122, 196,  62);
    fIconFa5.scaleFactor=   0.85;
    fIconFa5.scaleFactorOn= 1.00;
    ui->fa5_btn121->setIcon(ZFontIcon::icon(fIconFa5));
    ui->fa5_btn122->setIcon(ZFontIcon::icon(fIconFa5));
    ui->fa5_btn123->setIcon(ZFontIcon::icon(fIconFa5));


    //------------------------
    // Font Awesome 5 BRANDS -
    //------------------------
    // FA5 Brands is not the first added font, so we must specify the family explicitly
    // FA5 Brands font has only one style so we don't need to specify it
    ui->fa5_btn131->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_github    ));
    ui->fa5_btn132->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_gitlab    ));
    ui->fa5_btn133->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_facebook  ));
    ui->fa5_btn134->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_twitter   ));
    ui->fa5_btn135->setIcon(ZFontIcon::icon(Fa5brands::FAMILY, Fa5brands::fa_instagram ));


    //---------------------
    // Font Awesome 5 PRO -
    //---------------------
    if(ZFontIcon::registeredFonts().contains(Fa5pro::FAMILY)) {
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
    else {
        // Remove FA5 Pro tab
        QWidget *fa5pro_tab= ui->tabWidget->findChild<QWidget*>("fa5pro_tab");
        int tabIndex= ui->tabWidget->indexOf(fa5pro_tab);
        ui->tabWidget->removeTab(tabIndex);
    }


    //-----------------------------------
    // Font Awesome 4.7.0 FREE (Legacy) -
    //-----------------------------------
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


    //---------------------------------------------
    // Google Material Design Icons 4.x | 96206ad -
    //---------------------------------------------
    ui->gmi_btn101->setIcon(ZFontIcon::icon(Gmi4::FAMILY_OUTLINED, Gmi4::gmi_tour,        QColor(195,  65,  65)));
    ui->gmi_btn102->setIcon(ZFontIcon::icon(Gmi4::FAMILY_OUTLINED, Gmi4::gmi_star_rate,   QColor(214, 197,  64)));
    ui->gmi_btn103->setIcon(ZFontIcon::icon(Gmi4::FAMILY_OUTLINED, Gmi4::gmi_account_box, QColor( 69, 100, 214)));
    ui->gmi_btn104->setIcon(ZFontIcon::icon(Gmi4::FAMILY_OUTLINED, Gmi4::gmi_map,         QColor(102, 163,  52)));
    ui->gmi_btn105->setIcon(ZFontIcon::icon(Gmi4::FAMILY_OUTLINED, Gmi4::gmi_comment,     QColor(  0,   0,   0)));

    ui->gmi_btn111->setIcon(ZFontIcon::icon(Gmi4::FAMILY_ROUND,    Gmi4::gmi_tour,        QColor(195,  65,  65)));
    ui->gmi_btn112->setIcon(ZFontIcon::icon(Gmi4::FAMILY_ROUND,    Gmi4::gmi_star_rate,   QColor(214, 197,  64)));
    ui->gmi_btn113->setIcon(ZFontIcon::icon(Gmi4::FAMILY_ROUND,    Gmi4::gmi_account_box, QColor( 69, 100, 214)));
    ui->gmi_btn114->setIcon(ZFontIcon::icon(Gmi4::FAMILY_ROUND,    Gmi4::gmi_map,         QColor(102, 163,  52)));
    ui->gmi_btn115->setIcon(ZFontIcon::icon(Gmi4::FAMILY_ROUND,    Gmi4::gmi_comment,     QColor(  0,   0,   0)));

    ui->gmi_btn121->setIcon(ZFontIcon::icon(Gmi4::FAMILY_SHARP,    Gmi4::gmi_tour,        QColor(195,  65,  65)));
    ui->gmi_btn122->setIcon(ZFontIcon::icon(Gmi4::FAMILY_SHARP,    Gmi4::gmi_star_rate,   QColor(214, 197,  64)));
    ui->gmi_btn123->setIcon(ZFontIcon::icon(Gmi4::FAMILY_SHARP,    Gmi4::gmi_account_box, QColor( 69, 100, 214)));
    ui->gmi_btn124->setIcon(ZFontIcon::icon(Gmi4::FAMILY_SHARP,    Gmi4::gmi_map,         QColor(102, 163,  52)));
    ui->gmi_btn125->setIcon(ZFontIcon::icon(Gmi4::FAMILY_SHARP,    Gmi4::gmi_comment,     QColor(  0,   0,   0)));
}

Dialog::~Dialog() {
    delete ui;
}
