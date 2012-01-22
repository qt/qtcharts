#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qpieseries.h"
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

QChart::QChart(QGraphicsObject* parent) : QGraphicsObject(parent),
d(new QChartPrivate(this))
{
    //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    // set axis
    d->m_axisY->rotate(90);
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    return d->m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    // TODO: we should check the series not already added

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
        // TODO: Not tested:
//    case QChartSeries::SeriesTypeScatter: {
//        QScatterSeries *scatter = qobject_cast<QScatterSeries *>(series);
//        if (scatter) {
//            scatter->d->setParentItem(this);
//            scene()->addItem(scatter->d);
//        }
//        break;
//    }
    }
}

QChartSeries* QChart::createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type)
{
    // TODO: support also other types; not only scatter and pie
    Q_ASSERT(type == QChartSeries::SeriesTypeScatter
             || type == QChartSeries::SeriesTypePie);

    switch (type) {
    case QChartSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = new QScatterSeries(x, y, this);
        connect(this, SIGNAL(sizeChanged(QRectF, qreal, qreal)),
                scatterSeries, SLOT(chartSizeChanged(QRectF, qreal, qreal)));
        scatterSeries->d->setParentItem(this);
        return scatterSeries;
    }
    case QChartSeries::SeriesTypePie: {
        // TODO: we now have also a list of y values as a parameter, it is ignored
        // we should use a generic data class instead of list of x and y values
        QPieSeries *pieSeries = new QPieSeries(x, this);
        connect(this, SIGNAL(sizeChanged(QRectF, qreal, qreal)),
                pieSeries, SLOT(chartSizeChanged(QRectF, qreal, qreal)));
        return pieSeries;
    }
    default:
        break;
    }

    return 0;
}

void QChart::setSize(const QSizeF& size)
{
    d->m_rect = QRect(QPoint(0,0),size.toSize());
    d->m_rect.adjust(margin(),margin(), -margin(), -margin());
    d->m_grid->setPos(d->m_rect.topLeft());
    d->m_grid->setSize(d->m_rect.size());

    // TODO: calculate the scale
    // TODO: calculate the origo
    // TODO: not sure if emitting a signal here is the best from performance point of view
    const qreal xscale = size.width() / 100;
    const qreal yscale = size.height() / 100;
    emit sizeChanged(QRectF(0, 0, size.width(), size.height()), xscale, yscale);

    for (int i(0); i < d->m_plotDomainList.size(); i++)
        d->m_plotDomainList[i].m_viewportRect = d->m_rect;

    // TODO: line chart items are updated separately as they don't support update
    // via sizeChanged signal
    foreach(XYLineChartItem* item , d->m_xyLineChartItems)
        item->updateXYPlotDomain(d->m_plotDomainList.at(d->m_plotDataIndex));

    if (d->m_plotDomainList.count())
        d->m_grid->setXYPlotData(d->m_plotDomainList.at(d->m_plotDataIndex));
    update();
}

int QChart::margin() const
{
    return d->m_marginSize;
}

void QChart::setMargin(int margin)
{
    d->m_marginSize = margin;
}

#include "moc_qchart.cpp"


QTCOMMERCIALCHART_END_NAMESPACE
