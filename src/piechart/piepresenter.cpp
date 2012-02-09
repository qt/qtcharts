
#include "piepresenter.h"
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresenter::PiePresenter(QGraphicsItem *parent, QPieSeries *series) :
    ChartItem(parent),
    m_pieSeries(series)
{
    Q_ASSERT(parent);
    Q_ASSERT(series);
    m_rect = parentItem()->boundingRect();
    setAcceptHoverEvents(true);
}

PiePresenter::~PiePresenter()
{
    while (m_slices.count())
        delete m_slices.takeLast();
}

void PiePresenter::handleSeriesChanged(const PieChangeSet& changeSet)
{
    const qreal fullPie = 360;
    qreal total = 0;

    // calculate total
    foreach (QPieSlice sliceData, m_pieSeries->slices())
        total += sliceData.m_value;

    // TODO: no need to create new slices in case size changed; we should re-use the existing ones
    while (m_slices.count())
        delete m_slices.takeLast();

    // create slices
    qreal angle = 0;
    for (int i=0; i<m_pieSeries->count(); i++) {
        QPieSlice sliceData = m_pieSeries->slice(i);
        qreal span = sliceData.m_value / total * fullPie;
        PieSlice *slice = new PieSlice(this, i, angle, span);
        m_slices.append(slice);
        angle += span;
    }
}

void PiePresenter::updateGeometry()
{
    prepareGeometryChange();

    m_pieRect = m_rect;

    if (m_pieRect.width() < m_pieRect.height()) {
        m_pieRect.setWidth(m_pieRect.width() * m_pieSeries->sizeFactor());
        m_pieRect.setHeight(m_pieRect.width());
        m_pieRect.moveCenter(m_rect.center());
    } else {
        m_pieRect.setHeight(m_pieRect.height() * m_pieSeries->sizeFactor());
        m_pieRect.setWidth(m_pieRect.height());
        m_pieRect.moveCenter(m_rect.center());
    }

    switch (m_pieSeries->position()) {
        case QPieSeries::PiePositionTopLeft: {
            m_pieRect.setHeight(m_pieRect.height() / 2);
            m_pieRect.setWidth(m_pieRect.height());
            m_pieRect.moveCenter(QPointF(m_rect.center().x() / 2, m_rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionTopRight: {
            m_pieRect.setHeight(m_pieRect.height() / 2);
            m_pieRect.setWidth(m_pieRect.height());
            m_pieRect.moveCenter(QPointF((m_rect.center().x() / 2) * 3, m_rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionBottomLeft: {
            m_pieRect.setHeight(m_pieRect.height() / 2);
            m_pieRect.setWidth(m_pieRect.height());
            m_pieRect.moveCenter(QPointF(m_rect.center().x() / 2, (m_rect.center().y() / 2) * 3));
            break;
        }
        case QPieSeries::PiePositionBottomRight: {
            m_pieRect.setHeight(m_pieRect.height() / 2);
            m_pieRect.setWidth(m_pieRect.height());
            m_pieRect.moveCenter(QPointF((m_rect.center().x() / 2) * 3, (m_rect.center().y() / 2) * 3));
            break;
        }
        default:
            break;
    }

    qDebug() << "presentation rect:" << m_rect;
    qDebug() << "pie rect:" << m_pieRect;
    foreach (PieSlice *slice, m_slices)
        slice->updateGeometry();
}

void PiePresenter::handleDomainChanged(const Domain& domain)
{
    // TODO
}

void PiePresenter::handleGeometryChanged(const QRectF& rect)
{
    m_rect = rect;
    updateGeometry();

}

#include "moc_piepresenter.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
