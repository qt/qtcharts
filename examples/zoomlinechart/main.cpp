#include "chartwidget.h"
#include <QApplication>
#include <QMainWindow>
#include <QLineSeries>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QLineSeries* series0 = new QLineSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QLineSeries* series1 = new QLineSeries();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);

    int numPoints = 100;

    for (int x = 0; x <= numPoints; ++x) {
    	  series0->add(x, fabs(sin(PI/50*x)*100));
    	  series1->add(x, fabs(cos(PI/50*x)*100));
     }

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->setRenderHint(QPainter::Antialiasing);
    chartWidget->setChartTitle("Zoom in/out line chart example");
    chartWidget->setAnimationOptions(QChart::AllAnimations);
    chartWidget->addSeries(series0);
    chartWidget->addSeries(series1);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
