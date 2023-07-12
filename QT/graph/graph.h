#ifndef GRAPH_H
#define GRAPH_H

#include <QtGui/QMainWindow>
#include "ui_graph.h"

class graph : public QMainWindow
{
	Q_OBJECT

public:
	graph(QWidget *parent = 0, Qt::WFlags flags = 0);
	~graph();

private:
	Ui::graphClass ui;
};

#endif // GRAPH_H
