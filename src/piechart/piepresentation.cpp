
#include "piepresentation.h"
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresentation::PiePresentation(QGraphicsItem *parent, QPieSeries *series) :
    ChartItem(parent),
    m_pieSeries(series)
{
    Q_ASSERT(parent);
    Q_ASSERT(series);
    m_rect = parentItem()->boundingRect();
    setAcceptHoverEvents(true);
}

PiePresentation::~PiePresentation()
{
    while (m_slices.count())
        delete m_slices.takeLast();
}

void PiePresentation::seriesChanged()
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

    resize();
}

void PiePresentation::setSize(const QSizeF &size)
{
    // TODO: allow user setting the size?
    // TODO: allow user defining the margins?
    m_rect.setSize(size);
    resize();
}

void PiePresentation::setPlotDomain(const PlotDomain& plotDomain)
{
    // TODO
}

void PiePresentation::resize()
{
    m_pieRect = m_rect;

    if (m_pieRect.width() < m_pieRect.height()) {
        m_pieRect.setWidth(m_pieRect.width() * m_pieSeries->m_sizeFactor);
        m_pieRect.setHeight(m_pieRect.width());
        m_pieRect.moveCenter(m_rect.center());
    } else {
        m_pieRect.setHeight(m_pieRect.height() * m_pieSeries->m_sizeFactor);
        m_pieRect.setWidth(m_pieRect.height());
        m_pieRect.moveCenter(m_rect.center());
    }

    switch (m_pieSeries->m_position) {
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
}

void PiePresentation::handleDomainChanged(const Domain& domain)
{
    // TODO
}

void PiePresentation::handleGeometryChanged(const QRectF& rect)
{
    setSize(rect.size());
}

#include "moc_piepresentation.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
