#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qchart.h>
#include <cmath>
#include "wavegenerator.h"
#include <QGLWidget>

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

    WaveGenerator generator(series0,series1);

    QChartView* chartView =  new QChartView(&window);

    chartView->setViewport( new QGLWidget() );
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("This is wave generator buahha.");
    chartView->addSeries(series0);
    chartView->addSeries(series1);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
