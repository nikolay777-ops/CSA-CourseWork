#ifndef PROCSTATS_H
#define PROCSTATS_H

#include <QDialog>
#include <windows.h>

namespace Ui {
class ProcStats;
}

class ProcStats : public QDialog
{
    Q_OBJECT

public:
    HANDLE handle;
    explicit ProcStats(QWidget *parent = nullptr, HANDLE handle = NULL);
    ~ProcStats();

private slots:
    void TimerSlot();

private:
    Ui::ProcStats *ui;
    double xCpuBegin, xCpuEnd, yCpuBegin, yCpuEnd, X;
    int N;

    QVector<double> x,y;
    QTimer* timer;
    int time;

};

#endif // PROCSTATS_H
