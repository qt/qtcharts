#include <QApplication>
#include <QMainWindow>
#include <qchartview.h>
#include <qstackedbarchartseries.h>
#include <qbarset.h>
#include <qbarcategory.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;

    //! [1]
    // Create category
    QBarCategory *category = new QBarCategory;
    *category << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "June" << "Jul" << "Aug" << "Sep" << "Oct" << "Nov" << "Dec";
    //! [1]

    //! [2]
    // Create some test sets for chat
    QBarSet *set0 = new QBarSet("Bub");
    QBarSet *set1 = new QBarSet("Bob");
    QBarSet *set2 = new QBarSet("Guybrush");
    QBarSet *set3 = new QBarSet("Larry");
    QBarSet *set4 = new QBarSet("Zak");

    *set0 << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10 << 11 << 12;
    *set1 << 5 << 0 << 0 << 4 << 0 << 7 << 8 << 9 << 9 << 0 << 4 << 2;
    *set2 << 3 << 5 << 8 << 13 << 8 << 5 << 3 << 2 << 1 << 1 << 3 << 5;
    *set3 << 5 << 6 << 7 << 3 << 4 << 5 << 8 << 9 << 10 << 5 << 2 << 7;
    *set4 << 9 << 7 << 5 << 3 << 1 << 2 << 4 << 6 << 8 << 10 << 1 << 6;
    //! [2]

    //! [3]
    // Create series and add sets to it
    QStackedBarChartSeries* series = new QStackedBarChartSeries(category);

    series->addBarSet(set0);
    series->addBarSet(set1);
    series->addBarSet(set2);
    series->addBarSet(set3);
    series->addBarSet(set4);
    //! [3]

    //! [4]
    // Enable features
    series->enableToolTip();
    series->enableFloatingValues();
    //! [4]

    //! [5]
    // Create view for chart and add series to it. Apply theme.

    QChartView* chartView =  new QChartView(&window);
    chartView->addSeries(series);
    chartView->setChartTitle("simple stacked barchart");
    chartView->setChartTheme(QChart::ChartThemeIcy);
    //! [5]

    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return a.exec();
}

