#include "DialogSheetCheat.h"
#include "ui_DialogSheetCheat.h"

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_gmi4.h"

#include <QGridLayout>
#include <QMetaEnum>
#include <QDebug>
#include <QLabel>
#include <QIcon>

DialogSheetCheat::DialogSheetCheat(QWidget *parent) : QDialog(parent), ui(new Ui::DialogSheetCheat) {
    ui->setupUi(this);

    // Set combobox Font families
    QMapIterator<QString, QStringList> iterator(ZFontIcon::registeredFonts());
    while(iterator.hasNext()) {
        iterator.next();
        ui->listWidgetFontFamilies->addItem(iterator.key());
    }
    ui->listWidgetFontFamilies->setCurrentRow(0);

    // Set combobox Icon Size
    ui->comboBoxIconSize->addItem("16x16",  16); // Index 0
    ui->comboBoxIconSize->addItem("24x24",  24); // Index 1
    ui->comboBoxIconSize->addItem("32x32",  32); // Index 2
    ui->comboBoxIconSize->addItem("48x48",  48); // Index 3
    ui->comboBoxIconSize->addItem("56x56",  56); // Index 4
    ui->comboBoxIconSize->addItem("64x64",  64); // Index 5
    ui->comboBoxIconSize->addItem("96x96",  96); // Index 6
    ui->comboBoxIconSize->setCurrentIndex(4);
}

DialogSheetCheat::~DialogSheetCheat() {
    delete ui;
}


void DialogSheetCheat::on_listWidgetFontFamilies_currentTextChanged(const QString &fontFamily) {
    // Set combobox Font styles
    ui->comboBoxFontStyles->clear();
    ui->comboBoxFontStyles->setEnabled(false);
    QMap<QString, QStringList> registeredFonts= ZFontIcon::registeredFonts();
    for(const QString &style : registeredFonts.value(fontFamily))
        ui->comboBoxFontStyles->addItem(style);
    if(ui->comboBoxFontStyles->count() > 1)
        ui->comboBoxFontStyles->setEnabled(true);
}

void DialogSheetCheat::on_comboBoxFontStyles_currentIndexChanged(int index) {
    Q_UNUSED(index)
    if(!ui->comboBoxFontStyles->count())
        return;
    //updateSheetCheat();
}

void DialogSheetCheat::on_pushButtonGenerate_clicked() {
    updateSheetCheat();
}

void DialogSheetCheat::updateSheetCheat() {
    QString fontFamily= ui->listWidgetFontFamilies->currentItem()->text();
    QString fontStyle=  ui->comboBoxFontStyles->currentText();

    int iconSize= ui->comboBoxIconSize->currentData().toInt();
    if(fontFamily.isEmpty() || fontStyle.isEmpty())
        return;

    // Delete current scrollWidget content
    if(ui->scrollArea->widget())
        delete ui->scrollArea->widget();

    // Create fresh scrollWidget
    QWidget *scrollWidget= new QWidget();
    ui->scrollArea->setWidget(scrollWidget);

    // Create a gridLayout
    QGridLayout *gLayout= new QGridLayout();
    gLayout->setContentsMargins(32, 32, 32, 32);
    gLayout->setSpacing(iconSize/2);
    scrollWidget->setLayout(gLayout);


    const int MAX_COLUMN= 8;
    int row=     0;
    int column=  0;

    QMetaEnum metaEnum;
    // Font Awesome 6
    if(fontFamily == Fa6::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa6::Glyph>();
    else if(fontFamily == Fa6pro::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa6pro::Glyph>();
    else if(fontFamily == Fa6brands::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa6brands::Glyph>();
    // Font Awesome 5
    else if(fontFamily == Fa5::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa5::Glyph>();
    else if(fontFamily == Fa5pro::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa5pro::Glyph>();
    else if(fontFamily == Fa5brands::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa5brands::Glyph>();
    // Font Awesome 4
    else if(fontFamily == Fa4::FAMILY)
        metaEnum= QMetaEnum::fromType<Fa4::Glyph>();
    // Google Material Icons
    else if(fontFamily == Gmi4::FAMILY_OUTLINED || fontFamily == Gmi4::FAMILY_ROUND || fontFamily == Gmi4::FAMILY_SHARP)
        metaEnum= QMetaEnum::fromType<Gmi4::Glyph>();
    else
        return;


    // Generate SheetCheat
    for(int i= 0; i < metaEnum.keyCount(); ++i) {
        QString glyphName=    metaEnum.key(i);
        ushort  glyphUnicode= metaEnum.value(i);
        //qDebug() << glyphUnicode << glyphName;

        // Create QIcon
        QIcon   icon= ZFontIcon::icon(fontFamily, fontStyle, glyphUnicode, QColor(), 0.8);
        QPixmap pixmap= icon.pixmap(iconSize, iconSize);
        // Show in QLabel
        QLabel *label= new QLabel(scrollWidget);
        label->setAlignment(Qt::AlignCenter);
        label->setPixmap(pixmap);
        label->setToolTip(glyphName);
        // Add QLabel inside gridLayout
        if(column >= MAX_COLUMN) {
            row++;
            column= 0;
        }
        gLayout->addWidget(label, row, column++);
    }

    //
    //QSpacerItem(int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Minimum, QSizePolicy::Policy vPolicy = QSizePolicy::Minimum)
    gLayout->addItem(new QSpacerItem(0, 10, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed), 0, MAX_COLUMN); // horizontalSpacer
    gLayout->addItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::MinimumExpanding), ++row, 0); // verticalSpacer
}
