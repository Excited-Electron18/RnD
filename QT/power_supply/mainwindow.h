#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void Plot_init();
    BOOL PortOpen(HANDLE *port, DWORD baudRate);
    BOOL PortClose(HANDLE *port);
    void Serial_port();
 private slots:
     void ADC_plot();
     void data_send();

private:
    Ui::MainWindow *ui;
    QTimer MyTimer1;
    QTimer MyTimer2;
};

#endif // MAINWINDOW_H
