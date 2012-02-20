#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <qpercentbarchartseries.h>
#include "chartwidget.h"
#include <qbarcategory.h>
#include <qbarset.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    QBarCategory *category = new QBarCategory;
    *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QPercentBarChartSeries* series0 = new QPercentBarChartSeries(category);

    QBarSet *set0 = new QBarSet;
    QBarSet *set1 = new QBarSet;
    QBarSet *set2 = new QBarSet;
    QBarSet *set3 = new QBarSet;
    QBarSet *set4 = new QBarSet;

    // Create some test data to chart
    *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0 << 4 << 2;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1 << 3 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5 << 2 << 7;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10 << 1 << 6;

    series0->addBarSet(set0);
    series0->addBarSet(set1);
    series0->addBarSet(set2);
    series0->addBarSet(set3);
    series0->addBarSet(set4);

    ChartWidget* chartWidget =  new ChartWidget(&window);
    chartWidget->addSeries(series0);

    window.setCentralWidget(chartWidget);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

