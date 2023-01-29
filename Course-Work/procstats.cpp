#include "procstats.h"
#include "ui_procstats.h"
#include "process-monitor.h"

ProcStats::ProcStats(QWidget *parent, HANDLE handle) :
    QDialog(parent),
    ui(new Ui::ProcStats)
{
    this->handle = handle;
    ui->setupUi(this);

    ui->widget->xAxis->setRange(0, 3000);
    ui->widget->yAxis->setRange(0, 8000);

    timer = new QTimer(this);
    xCpuEnd = 3000;
    xCpuBegin = 0;
    time = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerSlot()));
    ui->widget->clearGraphs();
    timer->start(20);
    X = this->xCpuBegin;
    x.clear();
    y.clear();
}

void ProcStats::TimerSlot(){
    if(time < 3000){
        if(X <= xCpuEnd){
            x.push_back(X);
            y.push_back(getRamValue(this->handle));
            X += 20;
        }
        time += 20;
    }
    else{
        time = 0;
        timer->stop();
    }

    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}

ProcStats::~ProcStats()
{
    delete ui;
}
