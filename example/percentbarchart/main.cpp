#include <QApplication>
#include <QMainWindow>
#include <QStandardItemModel>
#include <qpercentbarchartseries.h>
#include <qbarcategory.h>
#include <qchartview.h>

#include "custombarset.h"

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    QBarCategory *category = new QBarCategory;
    *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";

    QPercentBarChartSeries* series = new QPercentBarChartSeries(category);

    // We use custom set, which connects some signals. Could use QBarSet here if we don't need signals
    CustomBarSet *set0 = new CustomBarSet("Bub");
    CustomBarSet *set1 = new CustomBarSet("Bob");
    CustomBarSet *set2 = new CustomBarSet("Guybrush");
    CustomBarSet *set3 = new CustomBarSet("Larry");
    CustomBarSet *set4 = new CustomBarSet("Zak");

    // Create some test data to chart
    *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0 << 4 << 2;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1 << 3 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5 << 2 << 7;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10 << 1 << 6;

    series->addBarSet(set0);
    series->addBarSet(set1);
    series->addBarSet(set2);
    series->addBarSet(set3);
    series->addBarSet(set4);

    QChartView* chartView =  new QChartView(&window);
    chartView->addSeries(series);
    chartView->setChartTitle("simple percent barchart");
    chartView->setChartTheme(QChart::ChartThemeIcy);

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

