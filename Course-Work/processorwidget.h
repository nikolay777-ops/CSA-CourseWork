#ifndef PROCESSORWIDGET_H
#define PROCESSORWIDGET_H

#include <QWidget>

namespace Ui {
class ProcessorWidget;
}

class ProcessorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProcessorWidget(QWidget *parent = nullptr);
    ~ProcessorWidget();

private:
    Ui::ProcessorWidget *ui;
};

#endif // PROCESSORWIDGET_H
