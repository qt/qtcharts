#include <QApplication>
#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10,2);
//![2]
//![3]
    QMainWindow window;
    QChartView* chartView =  new QChartView(&window);

    chartView->setChartTitle("Basic line chart example");
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->addSeries(series0);
    chartView->addSeries(series1);
//![3]
//![4]
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![4]

    return a.exec();
}
