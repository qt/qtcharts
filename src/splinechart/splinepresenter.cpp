#include "splinepresenter_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

SplinePresenter::SplinePresenter(QSplineSeries* series, QGraphicsObject *parent) :
    ChartItem(parent),m_series(series),m_boundingRect()
{
    if (parent)
        m_boundingRect = parent->boundingRect();
    else
        m_boundingRect = QRectF(10,50, 250, 250);
}

void SplinePresenter::handleGeometryChanged(const QRectF&)
{
    update();
}

void SplinePresenter::handleDomainChanged(const Domain& domain)
{
    //
}

void SplinePresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->save();

    painter->setPen(Qt::SolidLine);

    QPainterPath splinePath;
    splinePath.moveTo(m_series->at(0));
    for (int i = 0; i < m_series->count() - 1; i++)
    {
        painter->setPen(Qt::red);
        splinePath.cubicTo(m_series->controlPoint(2 * i), m_series->controlPoint(2 * i + 1), m_series->at(i + 1));
        painter->drawEllipse(m_series->at(i), 4, 4);

        painter->setPen(Qt::blue);
        painter->drawLine(m_series->at(i), m_series->controlPoint(2 * i));
        painter->drawLine(m_series->at(i + 1), m_series->controlPoint(2 * i + 1));
        painter->drawEllipse(m_series->controlPoint(2 * i), 4, 4);
        painter->drawEllipse(m_series->controlPoint(2 * i + 1), 4, 4);
    }
    painter->setPen(Qt::red);
    painter->drawPath(splinePath);
    painter->restore();
}

#include "moc_splinepresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
