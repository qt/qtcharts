
#include "piepresenter.h"
#include "pieslice.h"
#include "qpieslice.h"
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
    //qDebug() << "PiePresenter::handleSeriesChanged()";
    //qDebug() << "  added  : " << changeSet.added();
    //qDebug() << "  changed: " << changeSet.changed();
    //qDebug() << "  removed: " << changeSet.removed();

    // ignore changeset when there are no visual slices
    // changeset might not be valid about the added slices
    if (m_slices.count() == 0) {
        foreach (QPieSlice* s, m_series->m_slices)
            addSlice(s);
        return;
    }

    foreach (QPieSlice* s, changeSet.removed())
        deleteSlice(s);

    foreach (QPieSlice* s, changeSet.added())
        addSlice(s);
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

void PiePresenter::updateGeometry()
{
    prepareGeometryChange();

    QRectF pieRect = m_rect;

    if (pieRect.width() < pieRect.height()) {
        pieRect.setWidth(pieRect.width() * m_series->sizeFactor());
        pieRect.setHeight(pieRect.width());
        pieRect.moveCenter(m_rect.center());
    } else {
        pieRect.setHeight(pieRect.height() * m_series->sizeFactor());
        pieRect.setWidth(pieRect.height());
        pieRect.moveCenter(m_rect.center());
    }

    switch (m_series->position()) {
        case QPieSeries::PiePositionTopLeft: {
            pieRect.setHeight(pieRect.height() / 2);
            pieRect.setWidth(pieRect.height());
            pieRect.moveCenter(QPointF(m_rect.center().x() / 2, m_rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionTopRight: {
            pieRect.setHeight(pieRect.height() / 2);
            pieRect.setWidth(pieRect.height());
            pieRect.moveCenter(QPointF((m_rect.center().x() / 2) * 3, m_rect.center().y() / 2));
            break;
        }
        case QPieSeries::PiePositionBottomLeft: {
            pieRect.setHeight(pieRect.height() / 2);
            pieRect.setWidth(pieRect.height());
            pieRect.moveCenter(QPointF(m_rect.center().x() / 2, (m_rect.center().y() / 2) * 3));
            break;
        }
        case QPieSeries::PiePositionBottomRight: {
            pieRect.setHeight(pieRect.height() / 2);
            pieRect.setWidth(pieRect.height());
            pieRect.moveCenter(QPointF((m_rect.center().x() / 2) * 3, (m_rect.center().y() / 2) * 3));
            break;
        }
        default:
            break;
    }

    if (m_pieRect != pieRect) {
        m_pieRect = pieRect;
        //qDebug() << "PiePresenter::updateGeometry()" << m_pieRect;
        foreach (PieSlice* s, m_slices.values()) {
            s->setPieRect(m_pieRect);
            s->updateGeometry();
        }
    }
}

void PiePresenter::addSlice(QPieSlice* sliceData)
{
    //qDebug() << "PiePresenter::addSlice()" << sliceData;

    if (m_slices.keys().contains(sliceData)) {
        //qWarning() << "PiePresenter::addSlice(): slice already exists!" << sliceData;
        Q_ASSERT(0);
        return;
    }

    // create slice
    PieSlice *slice = new PieSlice(this);
    slice->updateData(sliceData);
    m_slices.insert(sliceData, slice);

    // connect signals
    connect(sliceData, SIGNAL(changed()), slice, SLOT(handleSliceDataChanged()));
    connect(slice, SIGNAL(clicked()), sliceData, SIGNAL(clicked()));
    connect(slice, SIGNAL(hoverEnter()), sliceData, SIGNAL(hoverEnter()));
    connect(slice, SIGNAL(hoverLeave()), sliceData, SIGNAL(hoverLeave()));
}

void PiePresenter::deleteSlice(QPieSlice* sliceData)
{
    //qDebug() << "PiePresenter::deleteSlice()" << sliceData;

    if (m_slices.contains(sliceData))
        delete m_slices.take(sliceData);
    else {
        // nothing to remove
        Q_ASSERT(0); // TODO: remove before release
    }
}

#include "moc_piepresenter.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
