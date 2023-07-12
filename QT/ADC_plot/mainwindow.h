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

private:
    Ui::MainWindow *ui;
    QTimer MyTimer;

};

#endif // MAINWINDOW_H
