#include "chart_p.h"
#include "chartpresenter_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE


Chart::Chart(ChartPresenter *presenter):QObject(presenter),
    m_animator(0),
    m_presenter(presenter)
{
};

void Chart::setAnimator(ChartAnimator* animator)
{
    m_animator=animator;
}

ChartAnimator* Chart::animator() const
{
    return m_animator;
}

ChartPresenter* Chart::presenter() const
{
    return m_presenter;
}

void Chart::handleGeometryChanged(const QRectF& rect)
{
    Q_UNUSED(rect);
    qWarning()<<"Slot not implemented";
}

void Chart::handleDomainChanged(qreal minX,qreal maxX,qreal minY,qreal maxY)
{
    Q_UNUSED(minX);
    Q_UNUSED(maxX);
    Q_UNUSED(minY);
    Q_UNUSED(maxY);
    qWarning()<<"Slot not implemented";
}

void Chart::rangeXChanged(qreal min, qreal max, int tickXCount)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(tickXCount);
    qWarning()<<"Slot not implemented";
}

void Chart::rangeYChanged(qreal min, qreal max, int tickYCount)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(tickYCount);
    qWarning()<<"Slot not implemented";
}

#include "moc_chart_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
