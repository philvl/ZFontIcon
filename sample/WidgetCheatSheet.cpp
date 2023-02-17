#include "WidgetCheatSheet.h"
#include "ui_WidgetCheatSheet.h"

// Qt Core
#include <QMetaEnum>
#include <QDebug>

// Qt Gui
#include <QIcon>

// Qt Widgets
#include <QGridLayout>
#include <QLabel>

// Font icons
#include "ZFontIcon/ZFontIcon.h"
#include "ZFontIcon/ZFont_fa6.h"
#include "ZFontIcon/ZFont_fa5.h"
#include "ZFontIcon/ZFont_fa4.h"
#include "ZFontIcon/ZFont_bi1.h"
#include "ZFontIcon/ZFont_gmi4.h"
#include "ZFontIcon/ZFont_mdi7.h"
#include "ZFontIcon/ZFont_ph1.h"

WidgetCheatSheet::WidgetCheatSheet(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetCheatSheet) {
    ui->setupUi(this);

    // Set combobox Icon Size
    ui->comboBoxIconSize->addItem("16x16",  16); // Index 0
    ui->comboBoxIconSize->addItem("24x24",  24); // Index 1
    ui->comboBoxIconSize->addItem("32x32",  32); // Index 2
    ui->comboBoxIconSize->addItem("48x48",  48); // Index 3
    ui->comboBoxIconSize->addItem("56x56",  56); // Index 4
    ui->comboBoxIconSize->addItem("64x64",  64); // Index 5
    ui->comboBoxIconSize->addItem("96x96",  96); // Index 6
    ui->comboBoxIconSize->setCurrentIndex(4);

    // Set combobox Font families
    QStringList familiesList= ZFontIcon::registeredFonts().keys();
    for(const QString &family : familiesList)
        ui->listWidgetFontFamilies->addItem(family);
    ui->listWidgetFontFamilies->setCurrentRow(0);
}

WidgetCheatSheet::~WidgetCheatSheet() {
    delete ui;
}

void WidgetCheatSheet::on_listWidgetFontFamilies_currentTextChanged(const QString &fontFamily) {
    // Set combobox Font styles
    ui->comboBoxFontStyles->clear();
    ui->comboBoxFontStyles->setEnabled(false);
    QMap<QString, QStringList> registeredFonts= ZFontIcon::registeredFonts();
    for(const QString &style : registeredFonts.value(fontFamily))
        ui->comboBoxFontStyles->addItem(style);
    if(ui->comboBoxFontStyles->count() > 1)
        ui->comboBoxFontStyles->setEnabled(true);
}

void WidgetCheatSheet::on_comboBoxFontStyles_currentIndexChanged(int index) {
    Q_UNUSED(index)
    updateCheatSheet();
}

void WidgetCheatSheet::on_comboBoxIconSize_currentIndexChanged(int index) {
    Q_UNUSED(index)
    updateCheatSheet();
}

void WidgetCheatSheet::on_spinBoxScaleFactor_valueChanged(double value) {
    Q_UNUSED(value)
    updateCheatSheet();
}

void WidgetCheatSheet::on_lineEditSearch_textChanged(const QString &newSearch) {
    Q_UNUSED(newSearch)
    static QString prevSearch;
    if(newSearch.trimmed().size() >= 3 || prevSearch.size() >= 3)
        updateCheatSheet();
    prevSearch= newSearch.trimmed();
}

void WidgetCheatSheet::updateCheatSheet() {
    if(!ui->listWidgetFontFamilies->currentItem())
        return;
    QString fontFamily=    ui->listWidgetFontFamilies->currentItem()->text();
    QString fontStyle=     ui->comboBoxFontStyles->currentText();
    int     iconSize=      ui->comboBoxIconSize->currentData().toInt();
    double  scaleFactor=   ui->spinBoxScaleFactor->value();
    QString currentSearch= ui->lineEditSearch->text();
    if(fontFamily.isEmpty() || fontStyle.isEmpty() || !iconSize || !scaleFactor)
        return;

    // Delete current scrollWidget content
    if(ui->scrollArea->widget())
        delete ui->scrollArea->widget();

    // Create fresh scrollWidget
    QWidget *scrollWidget= new QWidget();
    ui->scrollArea->setWidget(scrollWidget);

    // Create a gridLayout
    QGridLayout *gLayout= new QGridLayout();
    gLayout->setSizeConstraint(QLayout::SetFixedSize);
    gLayout->setContentsMargins(32, 32, 32, 32);
    gLayout->setSpacing(iconSize/2);
    scrollWidget->setLayout(gLayout);

    QMetaEnum metaEnum;
    // Font Awesome 6
    if(fontFamily.startsWith(Fa6::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa6::Glyph>();
    else if(fontFamily.startsWith(Fa6pro::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa6pro::Glyph>();
    else if(fontFamily.startsWith(Fa6sharp::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa6pro::Glyph>();
    else if(fontFamily.startsWith(Fa6brands::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa6brands::Glyph>();
    // Font Awesome 5
    else if(fontFamily.startsWith(Fa5::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa5::Glyph>();
    else if(fontFamily.startsWith(Fa5pro::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa5pro::Glyph>();
    else if(fontFamily.startsWith(Fa5brands::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa5brands::Glyph>();
    // Font Awesome 4
    else if(fontFamily.startsWith(Fa4::FAMILY))
        metaEnum= QMetaEnum::fromType<Fa4::Glyph>();
    // Bootstrap Icons
    else if(fontFamily.startsWith(Bi1::FAMILY))
        metaEnum= QMetaEnum::fromType<Bi1::Glyph>();
    // Google Material Icons
    else if(fontFamily.startsWith(Gmi4::FAMILY_OUTLINED) || fontFamily.startsWith(Gmi4::FAMILY_ROUND) || fontFamily.startsWith(Gmi4::FAMILY_SHARP))
        metaEnum= QMetaEnum::fromType<Gmi4::Glyph>();
    // Material Design Icons
    else if(fontFamily.startsWith(Mdi6::FAMILY))
        metaEnum= QMetaEnum::fromType<Mdi6::Glyph>();
    // Phosphor Icons
    else if(fontFamily.startsWith(Ph1::FAMILY))
        metaEnum= QMetaEnum::fromType<Ph1::Glyph>();
    else {
        qDebug() << "WidgetCheatSheet::updateCheatSheet() -> Enum not found";
        return;
    }

    const int MAX_COLUMN= 8;
    int row=     0;
    int column=  0;

    // Generate SheetCheat
    for(int i= 0; i < metaEnum.keyCount(); ++i) {
        QString  glyphName= metaEnum.key(i);
        char32_t glyphUcs4= metaEnum.value(i);

        // Filter only if search field contains at least 3 characters
        if(currentSearch.trimmed().size() >= 3 && !glyphName.contains(currentSearch))
            continue;

        // Create QIcon
        QIcon   icon= ZFontIcon::icon(fontFamily, fontStyle, glyphUcs4, QColor(), scaleFactor);
        QPixmap pixmap= icon.pixmap(iconSize, iconSize);
        // Show in QLabel
        QLabel *label= new QLabel(scrollWidget);
        label->setAlignment(Qt::AlignCenter);
        label->setPixmap(pixmap);
        label->setToolTip("0x" + QString::number(glyphUcs4, 16).toUpper() + '\n' + glyphName);
        // Add QLabel inside gridLayout
        if(column >= MAX_COLUMN) {
            row++;
            column= 0;
        }
        gLayout->addWidget(label, row, column++);
    }
}
