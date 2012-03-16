#include "piechartitem_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieChartItem::PieChartItem(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleSlicesAdded(QList<QPieSlice*>)));
    connect(series, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleSlicesRemoved(QList<QPieSlice*>)));
    connect(series, SIGNAL(piePositionChanged()), this, SLOT(handlePieLayoutChanged()));
    connect(series, SIGNAL(pieSizeChanged()), this, SLOT(handlePieLayoutChanged()));

    QTimer::singleShot(0, this, SLOT(initialize()));

    // Note: the following does not affect as long as the item does not have anything to paint
    setZValue(ChartPresenter::PieSeriesZValue);
}

PieChartItem::~PieChartItem()
{
    // slices deleted automatically through QGraphicsItem
}

void PieChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_UNUSED(painter)
    // TODO: paint shadows for all components
    // - get paths from items & merge & offset and draw with shadow color?
    //painter->setBrush(QBrush(Qt::red));
    //painter->drawRect(m_debugRect);
}

void PieChartItem::initialize()
{
    handleSlicesAdded(m_series->m_slices);
}

void PieChartItem::handleSlicesAdded(QList<QPieSlice*> slices)
{
    foreach (QPieSlice *s, slices) {
        PieSlice* slice = new PieSlice(this);
        m_slices.insert(s, slice);
        connect(s, SIGNAL(changed()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(clicked()), s, SIGNAL(clicked()));
        connect(slice, SIGNAL(hoverEnter()), s, SIGNAL(hoverEnter()));
        connect(slice, SIGNAL(hoverLeave()), s, SIGNAL(hoverLeave()));

        PieSliceLayout layout = calculateSliceLayout(s);

        if (m_animator)
            m_animator->addAnimation(this, s, layout);
        else
            setLayout(layout);
    }
}

void PieChartItem::handleSlicesRemoved(QList<QPieSlice*> slices)
{
    foreach (QPieSlice *s, slices) {
        if (m_animator)
            m_animator->removeAnimation(this, s);
        else
            destroySlice(s);
    }
}

void PieChartItem::handlePieLayoutChanged()
{
    QVector<PieSliceLayout> layout = calculateLayout();
    applyLayout(layout);
    update();
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    PieSliceLayout layout = calculateSliceLayout(slice);
    updateLayout(layout);
    update();
}

void PieChartItem::handleDomainChanged(qreal, qreal, qreal, qreal)
{
    // TODO
}

void PieChartItem::handleGeometryChanged(const QRectF& rect)
{
    prepareGeometryChange();
    m_rect = rect;
    handlePieLayoutChanged();
}

void PieChartItem::calculatePieLayout()
{
    // find pie center coordinates
    m_pieCenter.setX(m_rect.left() + (m_rect.width() * m_series->pieHorizontalPosition()));
    m_pieCenter.setY(m_rect.top() + (m_rect.height() * m_series->pieVerticalPosition()));

    // find maximum radius for pie
    m_pieRadius = m_rect.height() / 2;
    if (m_rect.width() < m_rect.height())
        m_pieRadius = m_rect.width() / 2;

    // apply size factor
    m_pieRadius *= m_series->pieSize();
}

PieSliceLayout PieChartItem::calculateSliceLayout(QPieSlice *slice)
{
    PieSliceLayout sliceLayout;
    sliceLayout.m_data = slice;
    sliceLayout.m_center = PieSlice::sliceCenter(m_pieCenter, m_pieRadius, slice);
    sliceLayout.m_radius = m_pieRadius;
    sliceLayout.m_startAngle = slice->startAngle();
    sliceLayout.m_angleSpan = slice->m_angleSpan;
    return sliceLayout;
}

QVector<PieSliceLayout> PieChartItem::calculateLayout()
{
    calculatePieLayout();
    QVector<PieSliceLayout> layout;
    foreach (QPieSlice* s, m_series->slices()) {
        if (m_slices.contains(s)) // calculate layout only for those slices that are already visible
            layout << calculateSliceLayout(s);
    }
    return layout;
}

void PieChartItem::applyLayout(QVector<PieSliceLayout> &layout)
{
    if (m_animator)
        m_animator->updateLayout(this, layout);
    else
        setLayout(layout);
}

void PieChartItem::updateLayout(PieSliceLayout &layout)
{
    if (m_animator)
        m_animator->updateLayout(this, layout);
    else
        setLayout(layout);
}

void PieChartItem::setLayout(QVector<PieSliceLayout> &layout)
{
    foreach (PieSliceLayout l, layout) {
        PieSlice *slice = m_slices.value(l.m_data);
        Q_ASSERT(slice);
        slice->setLayout(l);
        slice->updateData(l.m_data);
        slice->updateGeometry();
        slice->update();
    }
}

void PieChartItem::setLayout(PieSliceLayout &layout)
{
    // find slice
    PieSlice *slice = m_slices.value(layout.m_data);
    Q_ASSERT(slice);
    slice->setLayout(layout);
    if (m_series->m_slices.contains(layout.m_data)) // Slice has been deleted if not found. Animations ongoing...
        slice->updateData(layout.m_data);
    slice->updateGeometry();
    slice->update();
}

void PieChartItem::destroySlice(QPieSlice *slice)
{
    delete m_slices.take(slice);
}

#include "moc_piechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
