#include "piepresenter_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include <QDebug>
#include <QPainter>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

PiePresenter::PiePresenter(QGraphicsItem *parent, QPieSeries *series)
    :ChartItem(parent),
    m_series(series)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(changed(const QPieSeries::ChangeSet&)), this, SLOT(handleSeriesChanged(const QPieSeries::ChangeSet&)));
    connect(series, SIGNAL(sizeFactorChanged()), this, SLOT(updateGeometry()));
    connect(series, SIGNAL(positionChanged()), this, SLOT(updateGeometry()));
    connect(series, SIGNAL(sizePolicyChanged()), this, SLOT(updateGeometry()));

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

    // calculate maximum rectangle for pie
    QRectF pieRect = m_rect;
    if (pieRect.width() < pieRect.height()) {
        pieRect.setHeight(pieRect.width());
    } else {
        pieRect.setWidth(pieRect.height());
    }

    // position the pie rectangle
    QPointF center = m_rect.center(); // default position is center
    qreal dx = pieRect.width() / 2;
    qreal dy = pieRect.height() / 2;
    if (m_series->position() & QPieSeries::PiePositionLeft)
        center.setX(m_rect.left() + dx);
    if (m_series->position() & QPieSeries::PiePositionRight)
        center.setX(m_rect.right() - dx);
    if (m_series->position() & QPieSeries::PiePositionHCenter)
        center.setX(m_rect.center().x());
    if (m_series->position() & QPieSeries::PiePositionTop)
        center.setY(m_rect.top() + dy);
    if (m_series->position() & QPieSeries::PiePositionBottom)
        center.setY(m_rect.bottom() - dy);
    if (m_series->position() & QPieSeries::PiePositionVCenter)
        center.setY(m_rect.center().y());
    pieRect.moveCenter(center);

    // calculate how much space we need around the pie rectangle (labels & exploding)
    qreal delta = 0;
    qreal pieRadius = pieRect.height() / 2;
    foreach (QPieSlice* s, m_series->m_slices) {

        bool exploded = s->isExploded();
        if (m_series->sizePolicy() & QPieSeries::PieSizePolicyReserveSpaceForExploding)
            exploded = true;

        bool labelVisible = s->isLabelVisible();
        if (m_series->sizePolicy() & QPieSeries::PieSizePolicyReserveSpaceForLabels)
            labelVisible = true;

        qreal centerAngle;
        QPointF armStart;
        QRectF sliceRect = PieSlice::slicePath(center, pieRadius, s->m_startAngle, s->m_angleSpan, exploded, s->explodeDistance(), &centerAngle, &armStart).boundingRect();

        if (labelVisible) {
            QRectF textRect = PieSlice::labelTextRect(s->labelFont(), s->label());
            QPointF textStart;
            QRectF armRect = PieSlice::labelArmPath(armStart, centerAngle, s->labelArmLength(), textRect.width(), &textStart).boundingRect();
            textRect.moveBottomLeft(textStart);
            sliceRect = sliceRect.united(armRect);
            sliceRect = sliceRect.united(textRect);
        }


        qreal dt = m_rect.top() - sliceRect.top();
        if (dt > delta)
            delta = dt;
        qreal dl = m_rect.left() - sliceRect.left();
        if (dl > delta)
            delta = dl;
        qreal dr = sliceRect.right() - m_rect.right();
        if (dr > delta)
            delta = dr;
        qreal db = sliceRect.bottom() - m_rect.bottom();
        if (db > delta)
            delta = db;

        /*
        if (s->label() == "Slice 5") {
            m_debugRect = sliceRect;
            qDebug() << "dt:" << dt << ", dl:" << dl << ", dr:" << dr << ", db:" << db << ", delta:" << delta;
        }
        */
    }

    // shrink the pie rectangle so that everything outside it fits the base rectangle
    pieRect.adjust(delta, delta, -delta, -delta);

    /*
    // apply size factor (range 0.0 ... 1.0)
    pieRect.setWidth(pieRect.width() * m_series->sizeFactor());
    pieRect.setHeight(pieRect.height() * m_series->sizeFactor());

    // position the pie rectangle (again)
    center = m_rect.center(); // default position is center
    dx = pieRect.width() / 2;
    dy = pieRect.height() / 2;
    if (m_series->position() & QPieSeries::PiePositionLeft)
        center.setX(m_rect.left() + dx);
    if (m_series->position() & QPieSeries::PiePositionRight)
        center.setX(m_rect.right() - dx);
    if (m_series->position() & QPieSeries::PiePositionHCenter)
        center.setX(m_rect.center().x());
    if (m_series->position() & QPieSeries::PiePositionTop)
        center.setY(m_rect.top() + dy);
    if (m_series->position() & QPieSeries::PiePositionBottom)
        center.setY(m_rect.bottom() - dy);
    if (m_series->position() & QPieSeries::PiePositionVCenter)
        center.setY(m_rect.center().y());
    pieRect.moveCenter(center);
    */

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
