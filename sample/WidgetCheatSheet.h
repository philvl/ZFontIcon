#ifndef WIDGET_CHEATSHEET_H
#define WIDGET_CHEATSHEET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetCheatSheet; }
QT_END_NAMESPACE

class WidgetCheatSheet : public QWidget {
    Q_OBJECT

// METHODS
public:
    explicit WidgetCheatSheet(QWidget *parent = nullptr);
    ~WidgetCheatSheet();

private slots:
    void on_listWidgetFontFamilies_currentTextChanged(const QString &fontFamily);
    void on_comboBoxFontStyles_currentIndexChanged(int index);
    void updateCheatSheet();

// VARIABLES
    void on_comboBoxIconSize_currentIndexChanged(int index);
    void on_spinBoxScaleFactor_valueChanged(double value);
    void on_lineEditSearch_textChanged(const QString &newSearch);

private:
    Ui::WidgetCheatSheet *ui;
};

#endif // WIDGET_CHEATSHEET_H
