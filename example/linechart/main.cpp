#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qlineseries.h>
#include <qchart.h>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMainWindow window;

//![1]

    QLineSeries* series0 = new QLineSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);

    QLineSeries* series1 = new QLineSeries();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);
//![1]

//![2]
    series0->add(0, 6);
    series0->add(2, 4);
    series0->add(3, 8);
    series0->add(7, 4);
    series0->add(10,5);

    series1->add(1, 1);
    series1->add(3, 3);
    series1->add(7, 6);
    series1->add(8, 3);
    series1->add(10,2);
//![2]
//![3]
    QChartView* chartView =  new QChartView(&window);

    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("Basic line chart example");
    chartView->addSeries(series0);
    chartView->addSeries(series1);
//![3]

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}
