#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog {
    Q_OBJECT

// METHODS
public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

// VARIABLES
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
