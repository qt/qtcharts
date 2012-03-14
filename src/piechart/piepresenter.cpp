#include "piepresenter_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include "chartpresenter_p.h"
#include <QDebug>
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresenter::PiePresenter(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(changed()), this, SLOT(handleSeriesChanged()));

    // Note: the following does not affect as long as the item does not have anything to paint
    setZValue(ChartPresenter::PieSeriesZValue);
}

PiePresenter::~PiePresenter()
{
    // slices deleted automatically through QGraphicsItem
}

void PiePresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: paint shadows for all components
    // - get paths from items & merge & offset and draw with shadow color?
    //painter->setBrush(QBrush(Qt::red));
    //painter->drawRect(m_debugRect);
}

void PiePresenter::handleSeriesChanged()
{
    QVector<PieSliceLayout> sliceLayout = calculateLayout();
    applyLayout(sliceLayout);
    update();
}

void PiePresenter::handleSliceChanged()
{
    // TODO: optimize don't need to handle all slices
    QVector<PieSliceLayout> sliceLayout = calculateLayout();
    applyLayout(sliceLayout);
    update();
}

void PiePresenter::handleDomainChanged(qreal, qreal, qreal, qreal)
{
    // TODO
}

void PiePresenter::handleGeometryChanged(const QRectF& rect)
{
    prepareGeometryChange();
    m_rect = rect;
    QVector<PieSliceLayout> sliceLayout = calculateLayout();
    applyLayout(sliceLayout);
    update();
}


QVector<PieSliceLayout> PiePresenter::calculateLayout()
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

void PiePresenter::applyLayout(const QVector<PieSliceLayout> &layout)
{
    //if(m_animator)
    //        m_animator->applyLayout(this,points);
    //else
    setLayout(layout);
}

void PiePresenter::setLayout(const QVector<PieSliceLayout> &layout)
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
            delete m_slices.take(s);
    }
}

#include "moc_piepresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
