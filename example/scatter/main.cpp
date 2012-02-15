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

    // Create widget and scatter series
    QChartView *chartWidget = new QChartView();
    QScatterSeries *scatter =
            qobject_cast<QScatterSeries *>(chartWidget->createSeries(QChartSeries::SeriesTypeScatter));
    Q_ASSERT(scatter);

    // Add test data to the series
    for (qreal i(0.0); i < 20; i += 0.5)
        scatter->addData(QPointF(i + ((qreal)(rand() % 100)) / 100,
                                 i + ((qreal)(rand() % 100)) / 100 ));

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartWidget);
    w.show();

    return a.exec();
}
