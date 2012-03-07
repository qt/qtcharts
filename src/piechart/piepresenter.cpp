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
    connect(series, SIGNAL(changed(const QPieSeries::ChangeSet&)), this, SLOT(handleSeriesChanged(const QPieSeries::ChangeSet&)));
    connect(series, SIGNAL(piePositionChanged()), this, SLOT(updateGeometry()));
    connect(series, SIGNAL(pieSizeChanged()), this, SLOT(updateGeometry()));

    if (m_series->count()) {
        QPieSeries::ChangeSet changeSet;
        changeSet.appendAdded(m_series->m_slices);
        handleSeriesChanged(changeSet);
    }

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

void PiePresenter::handleSeriesChanged(const QPieSeries::ChangeSet& changeSet)
{
    //qDebug() << "PiePresenter::handleSeriesChanged()";
    //qDebug() << "  added  : " << changeSet.added();
    //qDebug() << "  changed: " << changeSet.changed();
    //qDebug() << "  removed: " << changeSet.removed();

    foreach (QPieSlice* s, changeSet.added())
        addSlice(s);

    foreach (QPieSlice* s, changeSet.changed())
        updateSlice(s);

    foreach (QPieSlice* s, changeSet.removed())
        deleteSlice(s);

    // every change possibly changes the actual pie size
    updateGeometry();
}

void PiePresenter::handleDomainChanged(const Domain& domain)
{
    // TODO
}

void PiePresenter::handleGeometryChanged(const QRectF& rect)
{
    m_rect = rect;
    prepareGeometryChange();
    updateGeometry();
}

void PiePresenter::updateGeometry()
{
    if (!m_rect.isValid() || m_rect.isEmpty())
        return;

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

    // update slices
    if (m_pieCenter != center || m_pieRadius != radius) {
        m_pieCenter = center;
        m_pieRadius = radius;
        //qDebug() << "PiePresenter::updateGeometry()" << m_rect << m_pieCenter << m_pieRadius;
        foreach (PieSlice* s, m_slices.values()) {
            s->setPieCenterAndRadius(center, radius);
            s->updateGeometry();
            s->update();
        }
    }

    update();
}

void PiePresenter::addSlice(QPieSlice* sliceData)
{
    //qDebug() << "PiePresenter::addSlice()" << sliceData;

    if (m_slices.keys().contains(sliceData)) {
        Q_ASSERT(0); // TODO: how to handle this nicely?
        return;
    }

    // create slice
    PieSlice *slice = new PieSlice(this);
    slice->setPieCenterAndRadius(m_pieCenter, m_pieRadius);
    slice->updateData(sliceData);
    slice->updateGeometry();
    slice->update();
    m_slices.insert(sliceData, slice);

    // connect signals
    connect(slice, SIGNAL(clicked()), sliceData, SIGNAL(clicked()));
    connect(slice, SIGNAL(hoverEnter()), sliceData, SIGNAL(hoverEnter()));
    connect(slice, SIGNAL(hoverLeave()), sliceData, SIGNAL(hoverLeave()));
}

void PiePresenter::updateSlice(QPieSlice* sliceData)
{
    //qDebug() << "PiePresenter::updateSlice()" << sliceData;

    if (!m_slices.contains(sliceData)) {
        Q_ASSERT(0); // TODO: how to handle this nicely?
        return;
    }

    m_slices[sliceData]->updateData(sliceData);
}

void PiePresenter::deleteSlice(QPieSlice* sliceData)
{
    //qDebug() << "PiePresenter::deleteSlice()" << sliceData;

    if (!m_slices.contains(sliceData)) {
        Q_ASSERT(0); // TODO: how to handle this nicely?
        return;
    }

    delete m_slices.take(sliceData);
}

#include "moc_piepresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
