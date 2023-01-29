#include "processorwidget.h"
#include "ui_processorwidget.h"

ProcessorWidget::ProcessorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProcessorWidget)
{
    ui->setupUi(this);
}

ProcessorWidget::~ProcessorWidget()
{
    delete ui;
}
