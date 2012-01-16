#include "qchartview.h"
#include "qbarchart.h"
#include <qevent.h>

QChartView::QChartView(QGraphicsScene *scene, QWidget *parent ) :
    QGraphicsView(scene,parent)
{
    mChart = new QBarChart();
    mChart->setSize(640,480);
    scene->addItem(mChart);

    QList<int> data;
    data << 1;
    data << 1;
    data << 2;
    data << 3;
    data << 5;
    data << 8;
    data << 13;
    data << 21;
    data << 42;
    mChart->addSeries(data);

}


void QChartView::resizeEvent(QResizeEvent *event)
{
    mChart->setSize(event->size().height(), event->size().width());
}
