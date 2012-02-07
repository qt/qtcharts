#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qxychartseries.h>
#include <qchart.h>
#include <cmath>
#include "wavegenerator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

    QXYChartSeries* series0 = QXYChartSeries::create();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QXYChartSeries* series1 = QXYChartSeries::create();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);

    WaveGenerator generator(series0,series1);

    QChartView* chartView =  new QChartView(&window);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setTitle("This is wave generator buahha.");
    chartView->addSeries(series0);
    chartView->addSeries(series1);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
