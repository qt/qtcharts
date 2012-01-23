#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qxychartseries.h>
#include <qchart.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QXYChartSeries* series0 = QXYChartSeries::create();
    series0->setColor(Qt::blue);
    QXYChartSeries* series1 = QXYChartSeries::create();
    series1->setColor(Qt::red);
    QXYChartSeries* series2 = QXYChartSeries::create();
    series2->setColor(Qt::gray);
    QXYChartSeries* series3 = QXYChartSeries::create();
    series3->setColor(Qt::green);

    int numPoints = 100;

    for (int x = 0; x < numPoints; ++x) {
    	  series0->add(x,0);
    	  series1->add(x, abs(sin(PI/50*x)*100));
    	  series2->add(x, abs(cos(PI/50*x)*100));
    	  series3->add(x,100);
     }

    QList<QXYChartSeries*> dataset;

    //qDebug()<<"Series 1:" << *series1;
    //qDebug()<<"Series 2:" << *series2;

    dataset << series0;
    dataset << series1;
    dataset << series2;
    dataset << series3;

    QChartView* chartView =  new QChartView(&window);
    chartView->addSeries(series1);
    chartView->addSeries(series2);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
