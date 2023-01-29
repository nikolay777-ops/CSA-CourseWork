#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "procstats.h"
#include "BaseLibs.h"
#include "process-monitor.h"

#include <QtWidgets>
#include <QMessageBox>
#include <QDir>


void MainWindow::ClearHard(){
    if(this->proc != NULL){
        delete this->proc; this->proc = NULL;
    }
    delete this->battery; this->battery = NULL;
    delete this->bios; this->bios = NULL;
    this->cache.clear();
    delete this->board; this->board = NULL;
    this->nt_adap.clear();
    this->ram.clear();
    this->vid_adapter.clear();
}

QIcon returnPixmap(const char* path){
    return QIcon(QPixmap(path));
}

void MainWindow::initializeIcons()
{
    QPixmap pixmap("C:/Users/nikoz/Desktop/img.jpg");
    QIcon ButtonIcon(pixmap);
    ui->procButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/processor.png"));
    ui->procButton->setIconSize(QSize(16,16));

    ui->vaButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/video-adapter.png"));
    ui->vaButton->setIconSize(QSize(16,16));

    ui->ramButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/ram.png"));
    ui->ramButton->setIconSize(QSize(16,16));

    ui->naButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/network-adapter.png"));
    ui->naButton->setIconSize(QSize(16,16));

    ui->biosButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/bios.png"));
    ui->biosButton->setIconSize(QSize(16,16));

    ui->mothButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/motherboard.png"));
    ui->mothButton->setIconSize(QSize(16,16));

    ui->batteryButton->setIcon(returnPixmap("C:/Users/nikoz/Desktop/Kursach/pics/battery.png"));
    ui->batteryButton->setIconSize(QSize(16,16));
}

MainWindow::MainWindow(QWidget* parent)
    :QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    proc = NULL;
    battery = NULL;
    bios = NULL;
    board = NULL;
    form_layout = new QFormLayout();


    ui->setupUi(this);
    initializeIcons();
    ui->hardChoose->hide();
    updateProcesses(ui);

    ui->tableWidget->setStyleSheet("QTableWidget{"
                                   "background-color: #C0C0C0;"
                                   "alternate-background-color: #606060;"
                                   "selection-background-color: #282828;"
                                   "}");

    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setTextElideMode(Qt::ElideRight);
}

void MainWindow::updateProcesses(Ui::MainWindow *ui){
    QList<Process*> list = GetProcessList();
    ui->tableWidget->setRowCount(list.size());
    int i = ui->tableWidget->rowCount() - 1;
    for (QList<Process*>::iterator it = list.begin(); it != list.end(); ++it){
        QTableWidgetItem* item;

        for(int j = 0; j < ui->tableWidget->columnCount(); j++){
            item = new QTableWidgetItem;
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            if(j == 0){
                item->setText((*it)->name);
                ui->tableWidget->setItem(i, j, item);
            }
            else if (j == 1){
                item->setText(QString::number((*it)->proc_id));
                ui->tableWidget->setItem(i, j, item);
            }
            else if (j == 2){
                item->setText((*it)->th_count);
                ui->tableWidget->setItem(i, j, item);
            }
            else if (j == 3){
                item->setText((*it)->prior_base);
                ui->tableWidget->setItem(i, j, item);
            }
        }
    i -= 1;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearWidget(){

    while(this->form_layout->rowCount() > 0){

        this->form_layout->removeRow(0);
    }
}

void MainWindow::on_actionOpen_Process_triggered()
{
    QString filter = "Exe file (*.exe)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open a process", QDir::homePath(), filter);

    QDesktopServices::openUrl(QUrl("file:///"+file_name, QUrl::TolerantMode));
    updateProcesses(ui);
}

void MainWindow::on_actionInfo_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Task Manager");
    msgBox.setText("This app was builded by Vashkevich Nikolai as course work for 5th term of studying.");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_pushButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
    QMessageBox msgBox;
    if(items.size() == 4){
        QTableWidgetItem* item = items.takeAt(1);
        QString text = item->text();
        unsigned int result = text.toUInt();
        killProcessByID(result);
        msgBox.setWindowTitle("Terminate Result");
        msgBox.setText("Process has terminated");
        msgBox.exec();
        updateProcesses(ui);
    }
    else{
        msgBox.setText("You haven't choose any process.");
        msgBox.exec();
    }
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    ProcStats window;
    QList<Process*> list = GetProcessList();

    window.setWindowTitle("RAM Usage");
    window.setModal(true);
    window.exec();
}

void MainWindow::on_procButton_clicked()
{
    clearWidget();
    ClearHard();
    ui->hardChoose->clear();
    ui->hardChoose->hide();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->proc = Processor::GetProcessorInfo(&hres, pLoc, pSvc);

    this->timer = new QTimer(this);
    delete ui->infoWidget->layout();
    this->form_layout = CreateLayout(this->proc->ToMap());

    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateLoad()));
    disconnect(timer, SIGNAL(timeout()), this, SLOT(UpdateLoad()));
    ui->infoWidget->show();
    timer->start(20);
}

QFormLayout* MainWindow::CreateLayout(unordered_map<string, string> map){
    QFormLayout* layout = new QFormLayout(ui->infoWidget);

    for(auto x : map){
        layout->addRow(CreateLabel(QString::fromStdString(x.first), ui->infoWidget),
                       CreateLabel(QString::fromStdString(x.second), ui->infoWidget));
    }

    return layout;
}

QLabel* MainWindow::CreateLabel(const QString name, QWidget* widget){
    QLabel* lab = new QLabel(name, widget);
    lab->setAlignment(Qt::AlignCenter);

    return lab;
}

void MainWindow::UpdateLoad(){
    Sleep(500);
    this->proc->UpdateProcStats();
    delete ui->infoWidget->layout();
    this->form_layout = CreateLayout(this->proc->ToMap());
    ui->infoWidget->show();
}

void MainWindow::on_vaButton_clicked()
{   
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);
    if (ui->hardChoose->count() > 0){
        ui->hardChoose->clear();
    }
    this->vid_adapter = VideoAdapter::VideoAdapterInfo(&hres, pLoc, pSvc);
    for(int i = 0; i < this->vid_adapter.size(); i++){
        ui->hardChoose->addItem(QString::fromStdString(this->vid_adapter[i]->name));
    }
    ui->hardChoose->setCurrentIndex(0);
    ui->hardChoose->show();

    for(int i = 0; i < this->form_layout->rowCount(); i++){
        this->form_layout->removeRow(0);
    }

    delete ui->infoWidget->layout();
    this->form_layout = CreateLayout(this->vid_adapter[0]->ToMap());

}

void MainWindow::on_hardChoose_activated(int index)
{
    clearWidget();
    delete ui->infoWidget->layout();

    if(nt_adap.size() == 0 && ram.size() == 0){
        this->form_layout = CreateLayout(this->vid_adapter.at(index)->ToMap());
    }
    else if(vid_adapter.size() == 0 && ram.size() == 0){
        this->form_layout = CreateLayout(this->nt_adap.at(index)->ToMap());
    }
    else{
        this->form_layout = CreateLayout(this->ram.at(index)->ToMap());
    }
}

void MainWindow::on_ramButton_clicked()
{
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->ram = RAM::GetRamInfo(&hres, pLoc, pSvc);
    for(int i = 0; i < this->form_layout->rowCount(); i++){
        this->form_layout->removeRow(0);
    }
    delete ui->infoWidget->layout();
    ui->hardChoose->clear();

    for(int i = 0; i < this->ram.size(); i++){
        ui->hardChoose->addItem(QString::fromStdString(this->ram[i]->manufacturer));
    }
    ui->hardChoose->setCurrentIndex(0);
    ui->hardChoose->show();
    this->form_layout = CreateLayout(this->ram[0]->ToMap());
}

void MainWindow::on_naButton_clicked()
{
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->nt_adap = NetworkAdapter::GetNetworkAdapterInfo(&hres, pLoc, pSvc);
    ui->infoWidget->clearMask();

    for(int i = 0; i < this->form_layout->rowCount(); i++){
        this->form_layout->removeRow(0);
    }

    delete ui->infoWidget->layout();
    ui->hardChoose->clear();

    for(int i = 0; i < this->nt_adap.size(); i++){
        ui->hardChoose->addItem(QString::fromStdString(this->nt_adap[i]->caption));
    }
    ui->hardChoose->setCurrentIndex(0);
    ui->hardChoose->show();
    this->form_layout = CreateLayout(this->nt_adap[0]->ToMap());
}

void MainWindow::on_biosButton_clicked()
{
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->bios = BIOS::GetBiosInfo(&hres, pLoc, pSvc);

    for(int i = 0; i < this->form_layout->rowCount(); i++){
        this->form_layout->removeRow(0);
    }

    delete ui->infoWidget->layout();
    if(!ui->hardChoose->isHidden())
    {
        ui->hardChoose->hide();
    }
    this->form_layout = CreateLayout(this->bios->ToMap());
}

void MainWindow::on_batteryButton_clicked()
{
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->battery = Battery::GetBatteryInfo(&hres, pLoc, pSvc);

    clearWidget();

    delete ui->infoWidget->layout();
    if(!ui->hardChoose->isHidden())
    {
        ui->hardChoose->hide();
    }
    this->form_layout = CreateLayout(this->battery->ToMap());
}

void MainWindow::on_mothButton_clicked()
{
    clearWidget();
    ClearHard();
    HRESULT hres;
    IWbemLocator *pLoc = NULL;
    IWbemServices *pSvc = NULL;

    wmi_initialize(&hres, &pLoc, &pSvc);

    this->board = MotherBoard::GetMotherBoardInfo(&hres, pLoc, pSvc);
    for(int i = 0; i < this->form_layout->rowCount(); i++){
        this->form_layout->removeRow(0);
    }
    delete ui->infoWidget->layout();
    if(!ui->hardChoose->isHidden())
    {
        ui->hardChoose->hide();
    }
    this->form_layout = CreateLayout(this->board->ToMap());
}

