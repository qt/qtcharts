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
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QXYChartSeries* series1 = QXYChartSeries::create();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);

    int numPoints = 100;

    for (int x = 0; x <= numPoints; ++x) {
    	  series0->add(x, abs(sin(PI/50*x)*100));
    	  series1->add(x, abs(cos(PI/50*x)*100));
    }

    QChartView* chartView =  new QChartView(&window);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setTitle("Custom color line chart example");
    chartView->addSeries(series0);
    chartView->addSeries(series1);
    chartView->setBackground(Qt::blue,Qt::yellow,QChart::HorizonatlGradientOrientation);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
