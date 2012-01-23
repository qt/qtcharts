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

QChart::QChart(QGraphicsObject* parent) : QGraphicsObject(parent),
		m_axisX(new Axis(this)),
		m_axisY(new Axis(this)),
		m_grid(new XYGrid(this)),
		m_plotDataIndex(0),
		m_marginSize(0)
{
    //  setFlags(QGraphicsItem::ItemClipsChildrenToShape);
    // set axis
    m_axisY->rotate(90);
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    return m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    // TODO: we should check the series not already added

    m_series<<series;

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
        m_plotDomainList<<domain;
        m_xyLineChartItems<<item;
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
        connect(this, SIGNAL(sizeChanged(QRectF)),
                scatterSeries, SLOT(chartSizeChanged(QRectF)));
        scatterSeries->d->setParentItem(this);
        return scatterSeries;
    }
    case QChartSeries::SeriesTypePie: {
        // TODO: we now have also a list of y values as a parameter, it is ignored
        // we should use a generic data class instead of list of x and y values
        QPieSeries *pieSeries = new QPieSeries(x, this);
        connect(this, SIGNAL(sizeChanged(QRectF)),
                pieSeries, SLOT(chartSizeChanged(QRectF)));
        return pieSeries;
    }
    default:
        break;
    }

    return 0;
}

void QChart::setSize(const QSizeF& size)
{
    m_rect = QRect(QPoint(0,0),size.toSize());
    m_rect.adjust(margin(),margin(), -margin(), -margin());
    m_grid->setPos(m_rect.topLeft());
    m_grid->setSize(m_rect.size());

    // TODO: TTD for setting scale
    //emit scaleChanged(100, 100);
    // TODO: calculate the origo
    // TODO: not sure if emitting a signal here is the best from performance point of view
    emit sizeChanged(QRectF(0, 0, size.width(), size.height()));

    for (int i(0); i < m_plotDomainList.size(); i++)
        m_plotDomainList[i].m_viewportRect = m_rect;

    // TODO: line chart items are updated separately as they don't support update
    // via sizeChanged signal
    foreach(XYLineChartItem* item ,m_xyLineChartItems)
        item->updateXYPlotDomain(m_plotDomainList.at(m_plotDataIndex));


    if (m_plotDomainList.count())
        m_grid->setXYPlotData(m_plotDomainList.at(m_plotDataIndex));

    update();
}

int QChart::margin() const
{
    return m_marginSize;
}

void QChart::setMargin(int margin)
{
    m_marginSize = margin;
}

#include "moc_qchart.cpp"


QTCOMMERCIALCHART_END_NAMESPACE
