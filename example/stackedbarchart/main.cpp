#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qstackedbarseries.h>
#include <qbarset.h>
#include <qchartaxis.h>
#include <QStringList>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    //! [1]
    // Define categories
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    //! [1]

    //! [2]
    // Create some test sets for chat
    QBarSet *set0 = new QBarSet("Bub");
    QBarSet *set1 = new QBarSet("Bob");
    QBarSet *set2 = new QBarSet("Guybrush");
    QBarSet *set3 = new QBarSet("Larry");
    QBarSet *set4 = new QBarSet("Zak");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2;
    //! [2]

    //! [3]
    // Create series and add sets to it
    QStackedBarSeries* series = new QStackedBarSeries(categories);

    series->addBarSet(set0);
    series->addBarSet(set1);
    series->addBarSet(set2);
    series->addBarSet(set3);
    series->addBarSet(set4);
    //! [3]

    //! [4]
    // Enable features
    series->setToolTipEnabled();
    series->setFloatingValuesEnabled();
    //! [4]

    //! [5]
    // Create view for chart and add series to it. Apply theme.

    QChartView* chartView =  new QChartView(&window);
    chartView->addSeries(series);
    chartView->setChartTitle("simple stacked barchart");
    chartView->setChartTheme(QChart::ChartThemeIcy);
    //! [5]

    //! [6]
    chartView->axisX()->setAxisVisible(false);
    chartView->axisX()->setGridVisible(false);
    chartView->axisX()->setLabelsVisible(false);
    //! [6]

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

