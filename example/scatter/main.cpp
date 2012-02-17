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

    // Add scatter series with simple test data
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 5.0)
             << QPointF(1.0, 4.5)
             << QPointF(1.0, 5.5)
             << QPointF(1.5, 5.0)
             << QPointF(2.0, 4.5)
             << QPointF(2.0, 5.5)
             << QPointF(2.5, 5.0);
    chartWidget->addSeries(scatter);

    // Add another scatter series
    // - more data with random component
    QScatterSeries *scatter2 = new QScatterSeries();
    for (qreal i(0.0); i < 20; i += 0.05) {
        (*scatter2) << QPointF(i + (qreal)(rand() % 100) / 100.0,
                               i + (qreal)(rand() % 100) / 100.0);
    }
    chartWidget->addSeries(scatter2);
    // Custom pen and brush (not those defined by the chart theme)
    // - uses opaque color
    QColor color("#2685BF");
    color.setAlpha(80);
    QBrush brush(Qt::SolidPattern);
    brush.setColor(color);
    scatter2->setMarkerBrush(brush);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(2);
    scatter2->setMarkerPen(pen);
    // use a rectangle as the marker shape
    scatter2->setMarkerShape(QScatterSeries::MarkerShapeRectangle);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(640, 480);
    w.setCentralWidget(chartWidget);
    w.show();

    return a.exec();
}
