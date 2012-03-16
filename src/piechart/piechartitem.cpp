#include "piechartitem_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include <QDebug>
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieChartItem::PieChartItem(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(changed()), this, SLOT(handleSeriesChanged()));

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

void PieChartItem::handleSeriesChanged()
{
    QVector<PieSliceLayout> layout = calculateLayout();
    applyLayout(layout);
    update();
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));

    //qDebug() << "PieChartItem::handleSliceChanged" << slice->label();

    // TODO: Optimize. No need to calculate everything.
    QVector<PieSliceLayout> layout = calculateLayout();
    foreach (PieSliceLayout sl, layout) {
        if (sl.m_data == slice)
            updateLayout(sl);
    }
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
    QVector<PieSliceLayout> sliceLayout = calculateLayout();
    applyLayout(sliceLayout);
    update();
}


QVector<PieSliceLayout> PieChartItem::calculateLayout()
{
    // find pie center coordinates
    QPointF center;
    center.setX(m_rect.left() + (m_rect.width() * m_series->pieHorizontalPosition()));
    center.setY(m_rect.top() + (m_rect.height() * m_series->pieVerticalPosition()));

    // find maximum radius for pie
    qreal radius = m_rect.height() / 2;
    if (m_rect.width() < m_rect.height())
        radius = m_rect.width() / 2;

    // apply size factor
    radius *= m_series->pieSize();

    QVector<PieSliceLayout> layout;
    foreach (QPieSlice* s, m_series->slices()) {
        PieSliceLayout sliceLayout;
        sliceLayout.m_data = s;
        sliceLayout.m_center = PieSlice::sliceCenter(center, radius, s);
        sliceLayout.m_radius = radius;
        sliceLayout.m_startAngle = s->startAngle();
        sliceLayout.m_angleSpan = s->m_angleSpan;
        layout << sliceLayout;
    }

    return layout;
}

void PieChartItem::applyLayout(QVector<PieSliceLayout> &layout)
{
    if (m_animator)
        m_animator->applyLayout(this, layout);
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

        // find slice
        PieSlice *slice = m_slices.value(l.m_data);
        if (!slice) {
            // add a new slice
            slice = new PieSlice(this);
            m_slices.insert(l.m_data, slice);

            // connect signals
            connect(l.m_data, SIGNAL(changed()), this, SLOT(handleSliceChanged()));
            connect(slice, SIGNAL(clicked()), l.m_data, SIGNAL(clicked()));
            connect(slice, SIGNAL(hoverEnter()), l.m_data, SIGNAL(hoverEnter()));
            connect(slice, SIGNAL(hoverLeave()), l.m_data, SIGNAL(hoverLeave()));
        }

        // update
        slice->setLayout(l);
        slice->updateGeometry();
        slice->update();
    }

    // delete slices
    foreach (QPieSlice *s, m_slices.keys()) {

        bool found = false;
        foreach (PieSliceLayout l, layout) {
            if (l.m_data == s)
                found = true;
        }

        if (!found)
            destroySlice(s);
    }
}

void PieChartItem::setLayout(PieSliceLayout &layout)
{
    // find slice
    PieSlice *slice = m_slices.value(layout.m_data);
    if (!slice) {
        slice = new PieSlice(this);
        m_slices.insert(layout.m_data, slice);
        connect(layout.m_data, SIGNAL(changed()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(clicked()), layout.m_data, SIGNAL(clicked()));
        connect(slice, SIGNAL(hoverEnter()), layout.m_data, SIGNAL(hoverEnter()));
        connect(slice, SIGNAL(hoverLeave()), layout.m_data, SIGNAL(hoverLeave()));
    }
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
