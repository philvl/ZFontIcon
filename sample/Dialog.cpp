#include "Dialog.h"
#include "ui_Dialog.h"

#include "ZFontIcon/ZFontIcon.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(2);


    // Font Awesome 4.7.0
    QFontIcon::addFont(":/fa_4.7.0/FontAwesome_v4.7.0_Free.otf"); //  675 icons

    ui->fa4_btn101->setIcon(QFontIcon::icon(0xf024, QColor(0, 0, 0)));
    ui->fa4_btn102->setIcon(QFontIcon::icon(0xf005, QColor(0, 0, 0)));
    ui->fa4_btn103->setIcon(QFontIcon::icon(0xf007, QColor(0, 0, 0)));
    ui->fa4_btn104->setIcon(QFontIcon::icon(0xf279, QColor(0, 0, 0)));

    ui->fa4_btn111->setIcon(QFontIcon::icon(0xf11d, QColor(0, 0, 0)));
    ui->fa4_btn112->setIcon(QFontIcon::icon(0xf006, QColor(0, 0, 0)));
    ui->fa4_btn113->setIcon(QFontIcon::icon(0xf2c0, QColor(0, 0, 0)));
    ui->fa4_btn114->setIcon(QFontIcon::icon(0xf278, QColor(0, 0, 0)));

    ui->fa4_btn121->setIcon(QFontIcon::icon(0xf09b, QColor(0, 0, 0)));
    ui->fa4_btn122->setIcon(QFontIcon::icon(0xf09a, QColor(0, 0, 0)));
    ui->fa4_btn123->setIcon(QFontIcon::icon(0xf099, QColor(0, 0, 0)));
    ui->fa4_btn124->setIcon(QFontIcon::icon(0xf16d, QColor(0, 0, 0)));
}

Dialog::~Dialog() {
    delete ui;
}
