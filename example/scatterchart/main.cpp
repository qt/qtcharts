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
    QScatterSeries *scatter = new QScatterSeries();

    QBrush brush(Qt::red);
    QPen pen(Qt::black);
    pen.setWidth(2);

    scatter->setPen(pen);
    scatter->setBrush(brush);
    scatter->setShape(QScatterSeries::MarkerShapeCircle);
    scatter->setSize(15.0);
//! [1]

//! [2]
    for (qreal i(0.0); i < 20; i += 0.5) {
        qreal x = i + (qreal) (rand() % 100) / 100.0;
        qreal y = i + (qreal) (rand() % 100) / 100.0;
        scatter->add(x, y);
    }
    *scatter << QPointF(2.0, 5.5) << QPointF(2.2, 5.4);
//! [2]

//! [3]
    QMainWindow window;
    QChartView *chartView = new QChartView(&window);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setChartTitle("Basic scatter chart example");
    chartView->addSeries(scatter);
//! [3]

//! [4]
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//! [4]
    return a.exec();
}
