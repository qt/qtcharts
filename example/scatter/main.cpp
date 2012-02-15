#include <QtGui/QApplication>
#include <QMainWindow>
#include <cmath>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qscatterseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create chart widget
    QChartView *chartWidget = new QChartView();

    // Create scatter series with simple test data
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 2.0)
             << QPointF(1.0, 2.5)
             << QPointF(1.5, 2.0)
             << QPointF(2.0, 2.5);
    chartWidget->addSeries(scatter);

    // Add another scatter series with more complex data with random component
    QScatterSeries *scatter2 = new QScatterSeries();
    for (qreal i(0.0); i < 20; i += 0.5)
        (*scatter2) << QPointF(i + (qreal)(rand() % 100) / 100.0,
                           i + (qreal)(rand() % 100) / 100.0);
    chartWidget->addSeries(scatter2);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartWidget);
    w.show();

    return a.exec();
}
