#ifndef WIDGET_SAMPLE_H
#define WIDGET_SAMPLE_H

// Qt Widgets
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetSample; }
QT_END_NAMESPACE

class WidgetSample : public QWidget {
    Q_OBJECT

// METHODS
public:
    explicit WidgetSample(QWidget *parent = nullptr);
    ~WidgetSample();

// VARIABLE
private:
    Ui::WidgetSample *ui;
};

#endif // WIDGET_SAMPLE_H
