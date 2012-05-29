#include "chartview.h"
#include <QScatterSeries>

ChartView::ChartView(QWidget *parent) :
    QChartView(new QChart(), parent)
{
    //![1]
    QScatterSeries *series0 = new QScatterSeries();
    series0->setName("scatter1");
    series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series0->setMarkerSize(15.0);

    QScatterSeries *series1 = new QScatterSeries();
    series1->setName("scatter2");
    series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series1->setMarkerSize(20.0);
    //![1]

    //![2]
    series0->append(0, 6);
    series0->append(2, 4);
    series0->append(3, 8);
    series0->append(7, 4);
    series0->append(10, 5);

    *series1 << QPointF(1, 1) << QPointF(3, 3) << QPointF(7, 6) << QPointF(8, 3) << QPointF(10, 2);
    //![2]

    //![3]
    setRenderHint(QPainter::Antialiasing);
    chart()->addSeries(series0);
    chart()->addSeries(series1);
    chart()->setTitle("Simple scatterchart example");
    chart()->setBackgroundDropShadowEnabled(false);
    //![3]
}
