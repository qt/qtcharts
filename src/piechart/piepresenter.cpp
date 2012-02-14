
#include "piepresenter.h"
#include "pieslice.h"
#include <QDebug>
#include <QTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresenter::PiePresenter(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(changed(const QPieSeries::ChangeSet&)), this, SLOT(handleSeriesChanged(const QPieSeries::ChangeSet&)));
    connect(series, SIGNAL(sizeFactorChanged()), this, SLOT(updateGeometry()));
    connect(series, SIGNAL(positionChanged()), this, SLOT(updateGeometry()));
}

PiePresenter::~PiePresenter()
{
    // slices deleted automatically through QGraphicsItem
}

void PiePresenter::paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *)
{
    // TODO: paint shadows for all components
    // - get paths from items & merge & offset and draw with shadow color?
}

void PiePresenter::handleSeriesChanged(const QPieSeries::ChangeSet& changeSet)
{
    qDebug() << "PiePresenter::handleSeriesChanged()";
    qDebug() << "  added  : " << changeSet.m_added;
    qDebug() << "  changed: " << changeSet.m_changed;
    qDebug() << "  removed: " << changeSet.m_removed;

    // ignore changeset when there are no visual slices
    // changeset might not be valid about the added slices
    if (m_slices.count() == 0) {
        foreach (QPieSliceId id, m_series->m_slices.keys())
            addSlice(id);
        return;
    }

    foreach (QPieSliceId id, changeSet.m_removed)
        deleteSlice(id);

    foreach (QPieSliceId id, changeSet.m_changed)
        updateSlice(id);

    foreach (QPieSliceId id, changeSet.m_added)
        addSlice(id);
}

void PiePresenter::updateGeometry()
{
    prepareGeometryChange();

    m_pieRect = m_rect;

    if (m_pieRect.width() < m_pieRect.height()) {
        m_pieRect.setWidth(m_pieRect.width() * m_series->sizeFactor());
        m_pieRect.setHeight(m_pieRect.width());
        m_pieRect.moveCenter(m_rect.center());
    } else {
        m_pieRect.setHeight(m_pieRect.height() * m_series->sizeFactor());
        m_pieRect.setWidth(m_pieRect.height());
        m_pieRect.moveCenter(m_rect.center());
    }

    switch (m_series->position()) {
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

    // update slice geometry
    const qreal fullPie = 360;
    qreal angle = 0;
    foreach (QPieSliceId id, m_slices.keys()) {
        qreal span = fullPie * m_series->slice(id).percentage();
        m_slices[id]->updateGeometry(m_pieRect, angle, span);
        angle += span;
    }

    //qDebug() << "PiePresenter::updateGeometry" << m_rect << m_pieRect;
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

void PiePresenter::addSlice(QPieSliceId id)
{
    qDebug() << "PiePresenter::addSlice()" << id;

    if (m_slices.contains(id)) {
        qWarning() << "PiePresenter::addSlice(): slice already exists!" << id;
        updateSlice(id);
        return;
    }

    // create slice
    PieSlice *slice = new PieSlice(id, m_series, this);
    m_slices.insert(id, slice);

    updateGeometry();
}

void PiePresenter::updateSlice(QPieSliceId id)
{
    qDebug() << "PiePresenter::updateSlice()" << id;

    // TODO: animation
    if (m_slices.contains(id))
        m_slices.value(id)->updateData();
    else {
        qWarning() << "PiePresenter::updateSlice(): slice does not exist!" << id;
        addSlice(id);
    }

    updateGeometry();
}

void PiePresenter::deleteSlice(QPieSliceId id)
{
    qDebug() << "PiePresenter::deleteSlice()" << id;

    // TODO: animation
    if (m_slices.contains(id))
        delete m_slices.take(id);
    else
        qWarning() << "PiePresenter::deleteSlice(): slice does not exist!" << id;

    updateGeometry();
}

#include "moc_piepresenter.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
