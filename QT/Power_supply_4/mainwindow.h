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

 private slots:
     void ADC_plot();

     void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer MyTimer1;
};

#endif // MAINWINDOW_H
