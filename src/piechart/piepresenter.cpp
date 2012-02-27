
#include "piepresenter_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "pieslicelabel_p.h"
#include "qpieseries.h"
#include <qmath.h>
#include <QDebug>
#include <QFontMetrics>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresenter::PiePresenter(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(changed(const QPieSeries::ChangeSet&)), this, SLOT(handleSeriesChanged(const QPieSeries::ChangeSet&)));
    connect(series, SIGNAL(sizeFactorChanged()), this, SLOT(updateGeometry()));
    connect(series, SIGNAL(positionChanged()), this, SLOT(updateGeometry()));

    if (m_series->count()) {
        QPieSeries::ChangeSet changeSet;
        changeSet.appendAdded(m_series->m_slices);
        handleSeriesChanged(changeSet);
    }
}

PiePresenter::~PiePresenter()
{
    // slices deleted automatically through QGraphicsItem
}

void PiePresenter::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
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

    // calculate maximum rectangle for pie
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

    // position the pie rectangle
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

    // calculate how much space we need around the pie rectangle (labels & exploding)
    qreal delta = 0;
    qreal pieRadius = pieRect.height() / 2;
    foreach (QPieSlice* s, m_series->m_slices) {

        // calculate the farthest point in the slice from the pie center
        qreal centerAngle = s->angle() + (s->angleSpan() / 2);
        qreal len = pieRadius + s->labelArmLength() + s->explodeDistance();
        QPointF dp(qSin(centerAngle*(PI/180)) * len, -qCos(centerAngle*(PI/180)) * len);
        QPointF p = pieRect.center() + dp;

        // TODO: consider the label text

        // calculate how much the radius must get smaller to fit that point in the base rectangle
        qreal dt = m_rect.top() - p.y();
        if (dt > delta) delta = dt;
        qreal dl = m_rect.left() - p.x();
        if (dl > delta) delta = dl;
        qreal dr = p.x() - m_rect.right();
        if (dr > delta) delta = dr;
        qreal db = p.y() - m_rect.bottom();
        if (db > delta) delta = db;

        //if (!m_rect.contains(p)) qDebug() << s->label() << dt << dl << dr << db << "delta" << delta;
    }

    // shrink the pie rectangle so that everything outside it fits the base rectangle
    pieRect.adjust(delta, delta, -delta, -delta);

    // update slices
    if (m_pieRect != pieRect) {
        m_pieRect = pieRect;
        //qDebug() << "PiePresenter::updateGeometry()" << m_rect << m_pieRect;
        foreach (PieSlice* s, m_slices.values()) {
            s->setPieRect(m_pieRect);
            s->updateGeometry();
            s->update();
        }
    }
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
    slice->setPieRect(m_pieRect);
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
