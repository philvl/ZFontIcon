#ifndef DIALOGSHEETCHEAT_H
#define DIALOGSHEETCHEAT_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DialogSheetCheat; }
QT_END_NAMESPACE

class DialogSheetCheat : public QDialog {
    Q_OBJECT

// METHODS
public:
    explicit DialogSheetCheat(QWidget *parent = nullptr);
    ~DialogSheetCheat();

private slots:
    void on_listWidgetFontFamilies_currentTextChanged(const QString &fontFamily);
    void on_comboBoxFontStyles_currentIndexChanged(int index);
    void on_pushButtonGenerate_clicked();

private:
    void updateSheetCheat();

// VARIABLES
private:
    Ui::DialogSheetCheat *ui;
};

#endif // DIALOGSHEETCHEAT_H
