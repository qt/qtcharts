#include "chartwidget.h"
#include <QApplication>
#include <QMainWindow>
#include <qxychartseries.h>
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

    int numPoints = 100;

    for (int x = 0; x <= numPoints; ++x) {
    	  series0->add(x, abs(sin(PI/50*x)*100));
    	  series1->add(x, abs(cos(PI/50*x)*100));
     }

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);
    chartWidget->addSeries(series1);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
