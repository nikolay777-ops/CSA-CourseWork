#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QSessionManager>
#include <QLabel>
#include <QFormLayout>

#include "Processor.h"
#include "Battery.h"
#include "BIOS.h"
#include "MotherBoard.h"
#include "NetworkAdapter.h"
#include "RAM.h"
#include "VideoAdapter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:

       void on_actionOpen_Process_triggered();

       void on_actionClose_triggered();

       void on_pushButton_clicked();

       void on_tableWidget_cellDoubleClicked(int row, int column);

       void on_procButton_clicked();

       void UpdateLoad();

       void on_vaButton_clicked();

       void on_hardChoose_activated(int index);

       void on_ramButton_clicked();

       void on_naButton_clicked();

       void on_biosButton_clicked();

       void on_batteryButton_clicked();

       void on_mothButton_clicked();

       void on_actionInfo_triggered();

private:
    Ui::MainWindow* ui;
    QTimer* timer;
    int time;
    Processor* proc;
    Battery* battery;
    BIOS* bios;
    vector<CacheLevel*> cache;
    MotherBoard* board;
    vector<NetworkAdapter*> nt_adap;
    vector<RAM*> ram;
    vector<VideoAdapter*> vid_adapter;
    QFormLayout* form_layout;


    void initializeIcons();
    void ClearHard();
    QLabel* CreateLabel(const QString name, QWidget* widget);
    QFormLayout* CreateLayout(unordered_map<string, string> map);
    void updateProcesses(Ui::MainWindow* ui);
    void clearWidget();
};
#endif // MAINWINDOW_H
