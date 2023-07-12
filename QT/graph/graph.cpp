#include <QApplication>
#include <QtGui/QMainWindow>
#include "graph.h"

graph::graph(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
}

graph::~graph()
{

}

