#include <QtGui/QApplication>
#include <QMainWindow>
#include <cmath>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qpieseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create widget and scatter series
    QChartView *chartWidget = new QChartView();
    QPieSeries *series = qobject_cast<QPieSeries *>(chartWidget->createSeries(QChartSeries::SeriesTypePie));
    Q_ASSERT(series);

    // Add test data to the series
    QList<qreal> x;
    for (qreal i(0.0); i < 20; i += 0.5) {
        // Linear data with random component
        x.append(i + ((qreal)(rand() % 100)) / 100 );
    }
    series->setData(x);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartWidget);
    w.show();

    return a.exec();
}
