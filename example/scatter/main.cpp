#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qscatterseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create chart widget
    QChartView *chartView = new QChartView();

    //! [1]
    // Add scatter series with simple test data
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 5.0)
             << QPointF(1.0, 4.5)
             << QPointF(1.0, 5.5)
             << QPointF(1.5, 5.0)
             << QPointF(2.0, 4.5)
             << QPointF(2.0, 5.5)
             << QPointF(2.5, 5.0);
    // Chart takes ownership
    chartView->addSeries(scatter);
    //! [1]

    // Add another scatter series
    // - more data with random component
    QScatterSeries *scatter2 = new QScatterSeries();
    for (qreal i(0.0); i < 20; i += 0.15) {
        (*scatter2) << QPointF(i + (qreal)(rand() % 100) / 100.0,
                               i + (qreal)(rand() % 100) / 100.0);
    }
    QBrush brush(QColor(255, 0, 0, 100), Qt::SolidPattern);
    scatter2->setMarkerBrush(brush);
    QPen pen(QColor(0, 255, 0, 80), 3);
    scatter2->setMarkerPen(pen);
    scatter2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    chartView->addSeries(scatter2);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartView);
    w.show();

    return a.exec();
}
