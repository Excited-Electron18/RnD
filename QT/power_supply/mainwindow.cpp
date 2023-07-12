#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include <QMainWindow>
#include <QSpinBox>
#include <windows.h>
#include <stdlib.h>
#include "inc\CoprocLib.h"
#include "inc/ADCLib.h"

#define BUFFER_SIZE 256
HANDLE portHandle = NULL;
char transmitBuffer[BUFFER_SIZE] = {0};
BOOL retVal = FALSE;
DWORD bytesTransmitted = 0;
double temp = 0;
unsigned int value=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" Electron ");
    Plot_init();
    Serial_port();
    connect(&MyTimer2, SIGNAL(timeout()), this, SLOT(data_send()));
    MyTimer2.start(200);
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
    connect(&MyTimer1, SIGNAL(timeout()), this, SLOT(ADC_plot()));
    MyTimer1.start(20);

}

void MainWindow::ADC_plot()
{
    static BYTE adcChannel = 1;
    double samples=1;
    static DWORD data = 0;
    double temp;
    BOOL ret = FALSE;


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
        //ui->customplot->graph(0)->rescaleValueAxis();
        lastPointKey = key;
    }
    ui->customplot->xAxis->setRange(key+0.25, 10, Qt::AlignRight);
    ui->customplot->replot();

    //ui->statusBar->showMessage(QString("%1 Volt").arg(temp,0,'f',3), 0);
}


BOOL MainWindow::PortOpen(HANDLE *port, DWORD baudRate)
{
    DCB portDCB;                                              ///< COM port configuration structure
    BOOL returnValue = FALSE;
    COMMTIMEOUTS comTimeOut;
    /// Opens interface to reader.
    *port = CreateFile(TEXT("COM2:"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL);
    if (*port == INVALID_HANDLE_VALUE)
    {
        ui->statusBar->showMessage(QString("Error Opening COM Port."));
        return FALSE;
    }

    /// COM Port Configuration.
    portDCB.DCBlength = sizeof (DCB);                         ///< Initializes the DCBlength member.
    GetCommState (*port, &portDCB);                           ///< Gets the default port setting information.
    /// Changes the DCB structure settings.
    portDCB.BaudRate = baudRate;                              ///< Current baud.
    portDCB.fBinary = TRUE;                                   ///< Binary mode; no EOF check.
    portDCB.fParity = FALSE;                                  ///< Disable parity checking.
    portDCB.fOutxCtsFlow = FALSE;                             ///< No CTS output flow control.
    portDCB.fOutxDsrFlow = FALSE;                             ///< No DSR output flow control.
    portDCB.fDtrControl = DTR_CONTROL_DISABLE;                ///< Disable DTR flow control type.
    portDCB.fDsrSensitivity = FALSE;                          ///< DSR sensitivity.
    portDCB.fTXContinueOnXoff = TRUE;                         ///< XOFF continues Tx.
    portDCB.fOutX = FALSE;                                    ///< No XON/XOFF out flow control.
    portDCB.fInX = FALSE;                                     ///< No XON/XOFF in flow control.
    portDCB.fErrorChar = FALSE;                               ///< Disable error replacement.
    portDCB.fNull = FALSE;                                    ///< Disable null stripping.
    portDCB.fRtsControl = RTS_CONTROL_DISABLE;                ///< Disable RTS flow control.
    portDCB.fAbortOnError = FALSE;                            ///< Do not abort reads/writes on error.
    portDCB.ByteSize = 8;                                     ///< Number of bits/byte, 4-8
    portDCB.Parity = NOPARITY;                                ///< 0-4 = no, odd, even, mark, space.
    portDCB.StopBits = ONESTOPBIT;                            ///< 0, 1, 2 = 1, 1.5, 2


    /// Configures the port according to the specifications of the DCB structure.
    if (!SetCommState (*port, &portDCB))
    {
      ui->statusBar->showMessage(QString("Error Configuring COM Port."));
      return FALSE;
    }

    /// Gets communication time out values.
    returnValue = GetCommTimeouts(*port, &comTimeOut);
    comTimeOut.ReadIntervalTimeout = 10;
    comTimeOut.ReadTotalTimeoutMultiplier = 1;
    comTimeOut.ReadTotalTimeoutConstant = 1;
    /// Set communication time out values
    returnValue = SetCommTimeouts(*port, &comTimeOut);

    /// Specifies the events to be monitored for a communication device.
    returnValue = SetCommMask(*port, EV_RXCHAR);

    return TRUE;
}


BOOL MainWindow::PortClose(HANDLE *port)
{
    if (*port == NULL)
    {
        return FALSE;
    }
    CloseHandle(*port);
    *port = NULL;
    return TRUE;
}



void MainWindow::Serial_port()
{
    retVal = PortOpen(&portHandle, 9600);

    if (!retVal)
    {
         ui->statusBar->showMessage(QString("Could not open COM port."));
    }
    else
    {
        ui->statusBar->showMessage(QString("COM port opened successfully."));
    }
}



void MainWindow::data_send()
{
    memset(transmitBuffer, NULL, BUFFER_SIZE);
    fflush(stdin);
    temp=ui->doubleSpinBox->value();
    value=(unsigned int)(temp*1024)/3.3;

    if(0<=value && value<=9)
    {
        sprintf(transmitBuffer,"000%d\r",value);
        ui->statusBar->showMessage(QString("000%1").arg(value));
    }
    else if(10<=value && value<=99)
    {
        sprintf(transmitBuffer,"00%d\r",value);
        ui->statusBar->showMessage(QString("00%1").arg(value));
    }
    else if(100<=value && value<=999)
    {
        sprintf(transmitBuffer,"0%d\r",value);
        ui->statusBar->showMessage(QString("0%1").arg(value));
    }
    else if(1000<=value)
    {
        sprintf(transmitBuffer,"%d\r",value);
        ui->statusBar->showMessage(QString("%1").arg(value));
    }
    retVal = WriteFile(portHandle, transmitBuffer, strlen(transmitBuffer), &bytesTransmitted, NULL);
        if (retVal == TRUE)
                {
                   //ui->statusBar->showMessage(QString("Data send: %1").arg(value));
                }
                else
                {
                   ui->statusBar->showMessage(QString("Data send failure."));
                }
}
