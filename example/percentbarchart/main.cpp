#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <percentbarchartseries.h>
#include "chartwidget.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    PercentBarChartSeries* series0 = new PercentBarChartSeries();

    // Create some test data to chart
    QList<qreal> data0;
    data0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
    QList<qreal> data1;
    data1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0;
    QList<qreal> data2;
    data2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1;
    QList<qreal> data3;
    data3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5;
    QList<qreal> data4;
    data4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10;

    series0->addData(data0);
    series0->addData(data1);
    series0->addData(data2);
    series0->addData(data3);
    series0->addData(data4);

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

