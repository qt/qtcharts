#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qlineseries.h>
#include <qscatterseries.h>
#include <qbarseries.h>
#include <qbarset.h>
#include <qpieseries.h>
#include <QStringList>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    // Create chart view
    QChartView *chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("Simple Line Chart");
    // Add series to the chart
    QLineSeries *line = new QLineSeries();
    line->add(0.0, 0.8);
    line->add(1.1, 1.1);
    line->add(2.0, 2.5);
    chartView->addSeries(line);
    //! [1]

    chartView->setChartTitle("\'Scietific\' theme");
    //! [2]
    // Change theme
    chartView->setChartTheme(QChart::ChartThemeScientific);
    //! [2]

    chartView->setChartTitle("Simple Pie Chart");
    //! [3]
    // Add pie series
    // ...
    QPieSeries *pie = new QPieSeries();
    pie->add(3.4, "slice1");
    pie->add(6.7, "slice2");
    chartView->addSeries(pie);
    //! [3]

    chartView->setChartTitle("Simple Scatter Chart");
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

    chartView->setChartTitle("Simple Bar Chart");
    //! [5]
    // ...
    // Add bar series
    QStringList barCategory;
    barCategory << "Jan"
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
    w.resize(400, 300);
    w.setCentralWidget(chartView);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
