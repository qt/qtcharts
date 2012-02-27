#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qlinechartseries.h>
#include <qscatterseries.h>
#include <qbarseries.h>
#include <qbarset.h>
#include <qbarcategory.h>
#include <qpieseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    // Create chart view
    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    // Add series to the chart
    QLineChartSeries *line = new QLineChartSeries();
    line->add(0.0, 0.8);
    line->add(1.1, 1.1);
    line->add(2.0, 2.5);
    chartView->addSeries(line);
    //! [1]

    //! [2]
    // Change theme
    chartView->setChartTheme(QChart::ChartThemeScientific);
    //! [2]

    //! [3]
    // Add pie series
    // ...
    QPieSeries *pie = new QPieSeries();
    pie->add(3.4, "slice1");
    pie->add(6.7, "slice2");
    chartView->addSeries(pie);
    //! [3]

    //! [4]
    // Add scatter series
    // ...
    QScatterSeries *scatter = new QScatterSeries();
    for (qreal x(0); x < 100; x += 0.5) {
        qreal y = rand() % 100;
        *(scatter) << QPointF(x, y);
    }
    chartView->addSeries(scatter);
    //! [4]

    //! [5]
    // ...
    // Add bar series
    QBarCategory *barCategory = new QBarCategory();
    *barCategory << "Jan"
                 << "Feb"
                 << "Mar";
    QBarSeries *bar = new QBarSeries(barCategory);
    QBarSet *barSet = new QBarSet("Sales");
    *barSet << 123.2
            << 301.3
            << 285.8;
    bar->addBarSet(barSet);
    chartView->addSeries(bar);
    //! [5]

    QMainWindow w;
    w.resize(380, 250);
    w.setCentralWidget(chartView);
    w.show();

    return a.exec();
}
