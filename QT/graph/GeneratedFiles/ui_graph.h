/********************************************************************************
** Form generated from reading UI file 'graph.ui'
**
** Created: Wed Jul 29 12:22:10 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_graphClass
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QCustomPlot *customPlot;
    QMenuBar *menuBar;
    QMenu *menu_File;

    void setupUi(QMainWindow *graphClass)
    {
        if (graphClass->objectName().isEmpty())
            graphClass->setObjectName(QString::fromUtf8("graphClass"));
        graphClass->resize(600, 400);
        actionExit = new QAction(graphClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(graphClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
		
        horizontalLayout->addWidget(customPlot);

        graphClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(graphClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        graphClass->setMenuBar(menuBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(actionExit);

        retranslateUi(graphClass);
        QObject::connect(actionExit, SIGNAL(triggered()), graphClass, SLOT(close()));

        QMetaObject::connectSlotsByName(graphClass);
    } // setupUi

    void retranslateUi(QMainWindow *graphClass)
    {
        graphClass->setWindowTitle(QApplication::translate("graphClass", "graph", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("graphClass", "E&xit", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("graphClass", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
	class graphClass: public Ui_graphClass{};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H
