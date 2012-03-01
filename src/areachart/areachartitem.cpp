#include "areachartitem_p.h"
#include "qareaseries.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

AreaChartItem::AreaChartItem(ChartPresenter* presenter, QAreaSeries* areaSeries,QGraphicsItem *parent):ChartItem(parent),
m_presenter(presenter),
m_series(areaSeries),
m_upper(0),
m_lower(0)
{
    //m_items.setZValue(ChartPresenter::LineChartZValue);
    m_upper = new AreaBoundItem(this,presenter,m_series->upperSeries());
    if(m_series->lowerSeries()){
    m_lower = new AreaBoundItem(this,presenter,m_series->lowerSeries());
    }
    setZValue(ChartPresenter::LineChartZValue);

    QObject::connect(presenter,SIGNAL(geometryChanged(const QRectF&)),this,SLOT(handleGeometryChanged(const QRectF&)));
    QObject::connect(areaSeries,SIGNAL(updated()),this,SLOT(handleUpdated()));

    handleUpdated();
}

AreaChartItem::~AreaChartItem()
{
    delete m_upper;
    delete m_lower;
};

QRectF AreaChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath AreaChartItem::shape() const
{
    return m_path;
}

void AreaChartItem::setPen(const QPen& pen)
{
    m_pen = pen;
}

void AreaChartItem::setBrush(const QBrush& brush)
{
    m_brush = brush;
}

void AreaChartItem::updatePath()
{
    QPainterPath path;

    path.connectPath(m_upper->shape());
    if(m_lower){
    path.connectPath(m_lower->shape().toReversed());
    }
    else{
        QPointF first = path.pointAtPercent(0);
        QPointF last =  path.pointAtPercent(1);
        path.lineTo(last.x(),m_clipRect.bottom());
        path.lineTo(first.x(),m_clipRect.bottom());
    }
    path.closeSubpath();
    prepareGeometryChange();
    m_path=path;
    m_rect=path.boundingRect();
    update();
}

void AreaChartItem::handleUpdated()
{
    setPen(m_series->pen());
    setBrush(m_series->brush());
    update();
}

void AreaChartItem::handleDomainChanged(const Domain& domain)
{
    m_upper->handleDomainChanged(domain);
    if(m_lower)
    m_lower->handleDomainChanged(domain);
}

void AreaChartItem::handleGeometryChanged(const QRectF& rect)
{
    m_clipRect=rect.translated(-rect.topLeft());
    setPos(rect.topLeft());
    m_upper->handleGeometryChanged(rect);
    if(m_lower)
    m_lower->handleGeometryChanged(rect);
}
//painter

void AreaChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->setClipRect(m_clipRect);
    painter->drawPath(m_path);
    painter->restore();
}

#include "moc_areachartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
