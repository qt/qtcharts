#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qareaseries.h>
#include <qchart.h>
#include <qchartaxis.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]

    QLineSeries* series0 = new QLineSeries();
    QLineSeries* series1 = new QLineSeries();

//![1]

//![2]
    *series0 << QPointF(1, 5) << QPointF(3, 7) << QPointF(7, 6) << QPointF(9, 7) << QPointF(12,6)<<QPointF(16,7)<<QPointF(18,5);
    *series1 << QPointF(1, 3) << QPointF(3, 4) << QPointF(7, 3) << QPointF(8, 2) << QPointF(12,3)<<QPointF(16,4)<<QPointF(18,3);
//![2]
//![3]

    QAreaSeries* series = new QAreaSeries(series0,series1);
    QPen pen(0x059605);
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setColorAt(0.0,0x3cc63c);
    gradient.setColorAt(1.0, 0x26f626);
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    series->setBrush(gradient);

//![3]
//![4]
    QMainWindow window;
    QChartView* chartView =  new QChartView(&window);

    chartView->setChartTitle("Basic area chart example");
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->addSeries(series);
    chartView->axisX()->setRange(0,20);
    chartView->axisY()->setRange(0,10);
//![4]
//![5]
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![5]

    return a.exec();
}
