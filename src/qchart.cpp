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
    QList<XYPlotDomain> m_plotDomainList;
    QList<XYLineChartItem*> m_xyLineChartItems;
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

        QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);

        XYPlotDomain domain;
        //TODO "nice numbers algorithm"
        domain.m_ticksX=4;
        domain.m_ticksY=4;

        for (int i = 0 ; i < xyseries->count() ; i++)
        {
            qreal x = xyseries->x(i);
            qreal y = xyseries->y(i);
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
        }

        XYLineChartItem* item = new XYLineChartItem(xyseries,this);
        item->updateXYPlotDomain(domain);
        d->m_plotDomainList<<domain;
        d->m_xyLineChartItems<<item;
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
    d->m_rect = QRect(QPoint(0,0),size.toSize());
    d->m_rect.adjust(margin(),margin(),-margin(),-margin());
    d->m_grid->setPos(d->m_rect.topLeft());
    d->m_grid->setSize(d->m_rect.size());
    // TODO: line chart items would need to be updated separately as they don't support update
    // via paint method
    for (int i =0; i< d->m_plotDomainList.size();i++)
    {
        d->m_plotDomainList[i].m_viewportRect = d->m_rect;

    }

    foreach(XYLineChartItem* item , d->m_xyLineChartItems)
        item->updateXYPlotDomain(d->m_plotDomainList.at(d->m_plotDataIndex));

    d->m_grid->setXYPlotData(d->m_plotDomainList.at(d->m_plotDataIndex));
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
