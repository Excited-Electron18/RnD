#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QSpinBox>
#include <QAction>
#include "inc/ADCLib.h"

double temp = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" Electron ");
    Plot_init();
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
    //----------------------------------------------------------
    ui->customplot1->addGraph();
    ui->customplot1->graph(0)->setPen(QPen(Qt::blue));

    ui->customplot1->addGraph(); // red line
    ui->customplot1->graph(1)->setPen(QPen(Qt::red));

    ui->customplot1->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customplot1->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customplot1->xAxis->setAutoTickStep(false);
    ui->customplot1->xAxis->setTickStep(2);

    connect(ui->customplot1->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot1->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customplot1->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot1->yAxis2, SLOT(setRange(QCPRange)));

     //----------------------------------------------------------
    ui->customplot4->addGraph();
    ui->customplot4->graph(0)->setPen(QPen(Qt::green));

    ui->customplot4->addGraph(); // red line
    ui->customplot4->graph(1)->setPen(QPen(Qt::red));

    ui->customplot4->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customplot4->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customplot4->xAxis->setAutoTickStep(false);
    ui->customplot4->xAxis->setTickStep(8);

    // set some pens, brushes and backgrounds:
    ui->customplot4->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot4->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot4->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot4->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot4->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot4->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot4->xAxis->setTickLabelColor(Qt::white);
    ui->customplot4->yAxis->setTickLabelColor(Qt::white);
    ui->customplot4->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot4->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot4->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot4->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot4->xAxis->grid()->setSubGridVisible(true);
    ui->customplot4->yAxis->grid()->setSubGridVisible(true);
    ui->customplot4->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot4->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot4->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customplot4->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    ui->customplot4->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    ui->customplot4->axisRect()->setBackground(axisRectGradient);

    connect(ui->customplot4->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot4->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customplot4->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customplot4->yAxis2, SLOT(setRange(QCPRange)));

    connect(&MyTimer1, SIGNAL(timeout()), this, SLOT(ADC_plot()));
    MyTimer1.start(0);
}

void MainWindow::ADC_plot()
{
    double samples=1;
    static DWORD data = 0;
    double temp1,temp2;
    BOOL ret = FALSE;


    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        ret = ReadADCChannel(1, &data, samples);   ///< Read ADC channel 1
        temp1 = (MicrovoltsPerLsb(1)*data) / (1000000.0*samples);

        ret = ReadADCChannel(2, &data, samples);   ///< Read ADC channel 1
        temp2 = (MicrovoltsPerLsb(1)*data) / (1000000.0*samples);

        ui->customplot1->graph(0)->addData(key,temp1);
        ui->customplot1->graph(1)->addData(key, temp1+0.5);
        ui->customplot1->graph(0)->removeDataBefore(key-10);
        ui->lcdNumber1->display(temp1);
        ui->lcdNumber2->display(temp1+0.5);


        ui->customplot4->graph(0)->addData(key,temp2);
        ui->customplot4->graph(1)->addData(key, temp2+0.5);
        ui->customplot4->graph(0)->removeDataBefore(key-10);
        ui->lcdNumber3->display(temp2);
        ui->lcdNumber4->display(temp2+0.5);

        lastPointKey = key;
    }
    ui->customplot1->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->customplot1->replot();

    ui->customplot4->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->customplot4->replot();
}

void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}
