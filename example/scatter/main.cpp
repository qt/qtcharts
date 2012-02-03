#include <QtGui/QApplication>
#include <QMainWindow>
#include <cmath>
#include <qchartglobal.h>
#include <qchartwidget.h>
#include <qscatterseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create widget and scatter series
    QChartWidget chartWidget;
    QScatterSeries *scatter =
            qobject_cast<QScatterSeries *>(chartWidget.createSeries(QChartSeries::SeriesTypeScatter));
    Q_ASSERT(scatter);

    // Add test data to the series
    QList<qreal> x;
    QList<qreal> y;
    for (qreal i(0.0); i < 20; i += 0.5) {
        // Linear data with random component
        x.append(i + ((qreal)(rand() % 100)) / 100 );
        y.append(i + ((qreal)(rand() % 100)) / 100 );
    }
    scatter->setData(x, y);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(&chartWidget);
    w.show();

    return a.exec();
}
