#include <QtGui/QApplication>
#include <QMainWindow>
#include <qchartglobal.h>
#include <qchartview.h>
#include <qscatterseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //! [1]
    // Create chart view
    QChartView *chartView = new QChartView();
    chartView->setChartTheme(QChart::ChartThemeIcy);
    // Add scatter series with simple test data
    QScatterSeries *scatter = new QScatterSeries();
    *scatter << QPointF(0.5, 5.0) << QPointF(1.0, 4.5) << QPointF(1.0, 5.5) << QPointF(1.5, 5.0);
    // Chart takes ownership
    chartView->addSeries(scatter);
    //! [1]

    // And more
    //! [3]
    *scatter << QPointF(2.0, 5.5) << QPointF(2.2, 5.4);
    //! [3]

    // Add another scatter series (re-use the previous pointer)
    // - more data with random component
    scatter = new QScatterSeries();
    for (qreal i(0.0); i < 20; i += 0.15) {
        (*scatter) << QPointF(i + (qreal)(rand() % 100) / 100.0,
                               i + (qreal)(rand() % 100) / 100.0);
    }
    //! [4]
    QBrush brush(QColor(255, 0, 0, 100), Qt::SolidPattern);
    scatter->setBrush(brush);
    //! [4]
    //! [5]
    QPen pen(QColor(0, 255, 0, 80), 3);
    scatter->setPen(pen);
    //! [5]
    //! [6]
    scatter->setShape(QScatterSeries::MarkerShapeRectangle);
    //! [6]
    chartView->addSeries(scatter);

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(400, 300);
    w.setCentralWidget(chartView);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
