#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <stackedbarchartseries.h>
#include "chartwidget.h"
#include <qbarset.h>
#include <qbarcategory.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    QBarCategory category;
    category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    StackedBarChartSeries* series0 = new StackedBarChartSeries(category);

    QBarSet barSet0;
    QBarSet barSet1;
    QBarSet barSet2;
    QBarSet barSet3;
    QBarSet barSet4;

    // Create some test data to chart
    barSet0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
    barSet1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0 << 4 << 2;
    barSet2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1 << 3 << 5;
    barSet3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5 << 2 << 7;
    barSet4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10 << 1 << 6;

    series0->addBarSet(barSet0);
    series0->addBarSet(barSet1);
    series0->addBarSet(barSet2);
    series0->addBarSet(barSet3);
    series0->addBarSet(barSet4);

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

