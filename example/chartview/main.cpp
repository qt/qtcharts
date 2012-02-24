#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qlinechartseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    // Create chart view
    QChartView *chartView = new QChartView();
    chartView->setChartTheme(QChart::ChartThemeIcy);
    //! [1]

    //! [2]
    // Add series to the chart
    QLineChartSeries *series = new QLineChartSeries();
    series->add(0.0, 0.8);
    series->add(1.1, 1.1);
    series->add(1.6, 1.8);
    series->add(2.0, 2.5);
    chartView->addSeries(series);
    //! [2]

    //! [3]
    // Change theme
    chartView->setChartTheme(QChart::ChartThemeScientific);
    //! [3]

    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartView);
    w.show();

    return a.exec();
}
