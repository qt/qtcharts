#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qxychartseries.h"
#include "xylinechartitem_p.h"
#include "xyplotdomain_p.h"
#include "axis_p.h"
#include "xygrid_p.h"
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartPrivate
{
public:

    QChartPrivate(QChart* parent):
    m_axisX(new Axis(parent)),
    m_axisY(new Axis(parent)),
    m_grid(new XYGrid(parent)),
    m_plotDataIndex(0),
    m_marginSize(0){}

    Axis* m_axisX;
    Axis* m_axisY;
    XYGrid* m_grid;
    QRect m_rect;
    QList<const QChartSeries*> m_series;
    QList<XYPlotDomain> m_plotDataList;
    QList<QGraphicsItem*> m_items;
    int m_plotDataIndex;
    int m_marginSize;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChart::QChart(QGraphicsItem* parent):QGraphicsItem(parent),
d_ptr(new QChartPrivate(this))
{
    //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    // set axis
    Q_D(QChart);
    d->m_axisY->rotate(90);

    //TODO hardcoded values , to removed soon
    XYPlotDomain data;
    data.m_minX = 0.0;
    data.m_maxX = 100.0;
    data.m_minY = 0.0;
    data.m_maxY = 100.0;
    data.m_ticksX=4;
    data.m_ticksY=4;

    d->m_plotDataList.clear();
    d->m_plotDataList << data;

    d->m_grid->setZValue(10);
    d->m_grid->setXYPlotData(d->m_plotDataList.at(0));
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    Q_D(const QChart);
    return d->m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    Q_D(QChart);

    d->m_series<<series;

    switch(series->type())
    {
    case QChartSeries::SeriesTypeLine: {
        XYLineChartItem* item = new XYLineChartItem(static_cast<QXYChartSeries*>(series),this);
        item->updateXYPlotData(d->m_plotDataList.at(0));
        d->m_items<<item;
        break;
    }
    case QChartSeries::SeriesTypeScatter: {
        break;
    }
    }
}

QChartSeries* QChart::createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type)
{
    Q_D(QChart);

    // TODO: support also other types
    Q_ASSERT(type == QChartSeries::SeriesTypeScatter);
    QChartSeries *series = 0;

    switch (type) {
    case QChartSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = new QScatterSeries(x, y, this);
        d->m_items.append(scatterSeries->d);
        scene()->addItem(scatterSeries->d);
        //series = qobject_cast<QChartSeries *>(scatterSeries);
        break;
    }
    default:
        break;
    }

    return series;
}
void QChart::setSize(const QSizeF& size)
{
    Q_D(QChart);
    //TODO refactor to setGeometry
    d->m_rect = QRect(QPoint(0,0),size.toSize());
    d->m_rect.adjust(margin(),margin(),-margin(),-margin());
    d->m_grid->setPos(d->m_rect.topLeft());
    d->m_grid->setSize(d->m_rect.size());
    d->m_plotDataList[0].m_viewportRect = d->m_rect;
    // TODO: line chart items would need to be updated separately as they don't support update
    // via paint method
    foreach(QGraphicsItem* item , d->m_items)
        reinterpret_cast<XYLineChartItem*>(item)->updateXYPlotData(d->m_plotDataList.at(0));
    update();
}

int QChart::margin() const
{
    Q_D(const QChart);
    return d->m_marginSize;
}

void QChart::setMargin(int margin)
{
    Q_D(QChart);
    d->m_marginSize = margin;
}

QTCOMMERCIALCHART_END_NAMESPACE
