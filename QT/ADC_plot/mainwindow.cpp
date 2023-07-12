#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include "inc/ADCLib.h"
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" Electron ");
    MainWindow::Plot_init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Plot_init()
{
    QMessageBox msgBox;
    if (!Ac97Init())
    {
        msgBox.setText("Could not initialize ADC.");
        msgBox.exec();
    }
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setPen(QPen(Qt::blue));


    ui->customplot->addGraph(); // red line
    ui->customplot->graph(1)->setPen(QPen(Qt::red));
    ui->customplot->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->customplot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);


    ui->customplot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customplot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customplot->xAxis->setAutoTickStep(false);
    ui->customplot->xAxis->setTickStep(1);
    connect(ui->customplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot->yAxis2, SLOT(setRange(QCPRange)));
    connect(&MyTimer, SIGNAL(timeout()), this, SLOT(ADC_plot()));
    MyTimer.start(10);

}

void MainWindow::ADC_plot()
{
    static BYTE adcChannel = 1;
    double samples=1;
    static DWORD data = 0;
    double temp;
    BOOL ret = FALSE;
    static int count=0;


    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        ret = ReadADCChannel(adcChannel, &data, samples);   ///< Read ADC channel
        temp = (MicrovoltsPerLsb(adcChannel)*data) / (1000000.0*samples);

        ui->customplot->graph(0)->addData(key,temp);
        ui->customplot->graph(1)->clearData();
        ui->customplot->graph(1)->addData(key, temp);
        ui->customplot->graph(0)->removeDataBefore(key-10);
        ui->customplot->graph(0)->rescaleValueAxis();
        lastPointKey = key;
    }
    ui->customplot->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->customplot->replot();

    ui->statusBar->showMessage(QString("%1 Voltage, Total Data points: %2").arg(temp,0,'f',3).arg(count), 0);
    count++;
}
