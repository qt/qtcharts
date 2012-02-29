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
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTheme(QChart::ChartThemeScientific);
    // Add scatter series with linear test data with random "noise"
    QScatterSeries *scatter = new QScatterSeries();
    for (qreal i(0.0); i < 20; i += 0.25) {
        qreal x = i + (qreal)(rand() % 100) / 100.0;
        qreal y = i + (qreal)(rand() % 100) / 100.0;
        (*scatter) << QPointF(x, y);
    }
    // Chart takes ownership
    chartView->addSeries(scatter);
    //! [1]

    // And more
    //! [2]
    //*scatter << QPointF(2.0, 5.5) << QPointF(2.2, 5.4);
    //! [2]

    //! [3]
    QBrush brush(QColor(255, 0, 0, 80), Qt::SolidPattern);
    scatter->setBrush(brush);
    QPen pen(QColor(0, 255, 0, 60), 3);
    scatter->setPen(pen);
    scatter->setShape(QScatterSeries::MarkerShapeRectangle);
    scatter->setSize(15.0);
    //! [3]

    // Use the chart widget as the central widget
    QMainWindow w;
    w.resize(400, 300);
    w.setCentralWidget(chartView);
    w.setWindowFlags(Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
