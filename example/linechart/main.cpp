#include <QApplication>
#include <QMainWindow>
#include <qchartwidget.h>
#include <qchart.h>
#include "chartview.h"
#include <cmath>

QCHART_USE_NAMESPACE

#define PI 3.14159265358979

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QXYSeries* series0 = new QXYSeries();
    series0->setColor(Qt::blue);
    QXYSeries* series1 = new QXYSeries();
    series1->setColor(Qt::red);
    QXYSeries* series2 = new QXYSeries();
    series2->setColor(Qt::gray);
    QXYSeries* series3 = new QXYSeries();
    series3->setColor(Qt::green);

    int numPoints = 100;

    for (int x = 0; x < numPoints; ++x) {
    	  series0->add(x,0);
    	  series1->add(x, uint(sin(PI/25*x)*100) % 100);
    	  series2->add(x, uint(cos(PI/25*x)*100) % 100);
    	  series3->add(x,100);
     }

    QList<QXYSeries*> dataset;

    qDebug()<<"Series 1:" << *series1;
    qDebug()<<"Series 2:" << *series2;

    dataset << series0;
    dataset << series1;
    dataset << series2;
    dataset << series3;

    QChart* chart = QChart::createXYLineChart(dataset);
    chart->setMargin(50);
    QChartWidget* chartWidget =  new QChartWidget();
    chartWidget->addChart(chart);

    ChartView* view = new ChartView(chartWidget,&window);
    window.setCentralWidget(view);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
