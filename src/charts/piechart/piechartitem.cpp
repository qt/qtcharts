// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include <QtCharts/qpieslice.h>
#include <QtCharts/qpieseries.h>
#include <QtWidgets/qgraphicssceneevent.h>

#include <private/piechartitem_p.h>
#include <private/piesliceitem_p.h>
#include <private/qpieslice_p.h>
#include <private/qpieseries_p.h>
#include <private/chartpresenter_p.h>
#include <private/chartdataset_p.h>
#include <private/pieanimation_p.h>

QT_BEGIN_NAMESPACE

PieChartItem::PieChartItem(QPieSeries *series, QGraphicsItem* item)
    : ChartItem(series->d_func(),item),
      m_series(series),
      m_animation(0)
{
    Q_ASSERT(series);

    QPieSeriesPrivate *p = QPieSeriesPrivate::fromSeries(series);
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleSeriesVisibleChanged()));
    connect(series, SIGNAL(opacityChanged()), this, SLOT(handleOpacityChanged()));
    connect(series, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleSlicesAdded(QList<QPieSlice*>)));
    connect(series, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleSlicesRemoved(QList<QPieSlice*>)));
    connect(p, SIGNAL(horizontalPositionChanged()), this, SLOT(updateLayout()));
    connect(p, SIGNAL(verticalPositionChanged()), this, SLOT(updateLayout()));
    connect(p, SIGNAL(pieSizeChanged()), this, SLOT(updateLayout()));
    connect(p, SIGNAL(calculatedDataChanged()), this, SLOT(updateLayout()));

    // Note: the following does not affect as long as the item does not have anything to paint
    setZValue(ChartPresenter::PieSeriesZValue);

    // Note: will not create slice items until we have a proper rectangle to draw on.

    setFlag(QGraphicsItem::ItemIsSelectable);
}

PieChartItem::~PieChartItem()
{
    cleanup();
}

void PieChartItem::setAnimation(PieAnimation *animation)
{
    m_animation = animation;
}

ChartAnimation *PieChartItem::animation() const
{
    return m_animation;
}

void PieChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
}

void PieChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
}

void PieChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void PieChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void PieChartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void PieChartItem::cleanup()
{
    ChartItem::cleanup();

    // slice items deleted automatically through QGraphicsItem
    if (m_series) {
        m_series->disconnect(this);
        QPieSeriesPrivate::fromSeries(m_series)->disconnect(this);
        m_series = 0;
    }
    foreach (QPieSlice *slice, m_sliceItems.keys()) {
        slice->disconnect(this);
        QPieSlicePrivate::fromSlice(slice)->disconnect(this);
    }
    m_sliceItems.clear();
}

void PieChartItem::handleDomainUpdated()
{
    QRectF rect(QPointF(0,0),domain()->size());
    if(m_rect!=rect){
        prepareGeometryChange();
        m_rect = rect;
        updateLayout();

        if (m_sliceItems.isEmpty())
              handleSlicesAdded(m_series->slices());
    }
}

void PieChartItem::updateLayout()
{
    // find pie center coordinates
    m_pieCenter.setX(m_rect.left() + (m_rect.width() * m_series->horizontalPosition()));
    m_pieCenter.setY(m_rect.top() + (m_rect.height() * m_series->verticalPosition()));

    // find maximum radius for pie
    m_pieRadius = m_rect.height() / 2;
    if (m_rect.width() < m_rect.height())
        m_pieRadius = m_rect.width() / 2;

    m_holeSize = m_pieRadius;
    // apply size factor
    m_pieRadius *= m_series->pieSize();
    m_holeSize *= m_series->holeSize();

    // set layouts for existing slice items
    const auto slices = m_series->slices();
    for (QPieSlice *slice : slices) {
        PieSliceItem *sliceItem = m_sliceItems.value(slice);
        if (sliceItem) {
            const PieSliceData sliceData = updateSliceGeometry(slice);
            if (m_animation)
                presenter()->startAnimation(m_animation->updateValue(sliceItem, sliceData));
            else
                sliceItem->setLayout(sliceData);
        }
    }

    update();
}

void PieChartItem::handleSlicesAdded(const QList<QPieSlice *> &slices)
{
    // delay creating slice items until there is a proper rectangle
    if (!m_rect.isValid() && m_sliceItems.isEmpty())
        return;

    themeManager()->updateSeries(m_series);

    bool startupAnimation = m_sliceItems.isEmpty();

    for (auto *slice : slices) {
        PieSliceItem *sliceItem = new PieSliceItem(this);
        m_sliceItems.insert(slice, sliceItem);

        // Note: no need to connect to slice valueChanged() etc.
        // This is handled through calculatedDataChanged signal.
        connect(slice, SIGNAL(labelChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(labelVisibleChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(penChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(brushChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(labelBrushChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(labelFontChanged()), this, SLOT(handleSliceChanged()));

        QPieSlicePrivate *p = QPieSlicePrivate::fromSlice(slice);
        connect(p, SIGNAL(labelPositionChanged()), this, SLOT(handleSliceChanged()));
        connect(p, SIGNAL(explodedChanged()), this, SLOT(handleSliceChanged()));
        connect(p, SIGNAL(labelArmLengthFactorChanged()), this, SLOT(handleSliceChanged()));
        connect(p, SIGNAL(explodeDistanceFactorChanged()), this, SLOT(handleSliceChanged()));

        connect(sliceItem, SIGNAL(clicked(Qt::MouseButtons)), slice, SIGNAL(clicked()));
        connect(sliceItem, SIGNAL(hovered(bool)), slice, SIGNAL(hovered(bool)));
        connect(sliceItem, SIGNAL(pressed(Qt::MouseButtons)), slice, SIGNAL(pressed()));
        connect(sliceItem, SIGNAL(released(Qt::MouseButtons)), slice, SIGNAL(released()));
        connect(sliceItem, SIGNAL(doubleClicked(Qt::MouseButtons)), slice, SIGNAL(doubleClicked()));

        PieSliceData sliceData = updateSliceGeometry(slice);
        if (m_animation)
            presenter()->startAnimation(m_animation->addSlice(sliceItem, sliceData, startupAnimation));
        else
            sliceItem->setLayout(sliceData);
    }
}

void PieChartItem::handleSlicesRemoved(const QList<QPieSlice *> &slices)
{
    themeManager()->updateSeries(m_series);

    for (auto *slice : slices) {

        PieSliceItem *sliceItem = m_sliceItems.value(slice);

        // this can happen if you call append() & remove() in a row so that PieSliceItem is not even created
        if (!sliceItem)
            continue;

        m_sliceItems.remove(slice);
        slice->disconnect(this);
        QPieSlicePrivate::fromSlice(slice)->disconnect(this);

        if (m_animation)
            presenter()->startAnimation(m_animation->removeSlice(sliceItem)); // animator deletes the PieSliceItem
        else
            delete sliceItem;
    }
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice *slice = qobject_cast<QPieSlice *>(sender());
    if (!slice) {
        QPieSlicePrivate *slicep = qobject_cast<QPieSlicePrivate *>(sender());
        slice = slicep->q_ptr;
    }
    Q_ASSERT(m_sliceItems.contains(slice));

    PieSliceItem *sliceItem = m_sliceItems.value(slice);
    PieSliceData sliceData = updateSliceGeometry(slice);
    if (m_animation)
        presenter()->startAnimation(m_animation->updateValue(sliceItem, sliceData));
    else
        sliceItem->setLayout(sliceData);

    update();
}

void PieChartItem::handleSeriesVisibleChanged()
{
    setVisible(m_series->isVisible());
}

void PieChartItem::handleOpacityChanged()
{
    setOpacity(m_series->opacity());
}

PieSliceData PieChartItem::updateSliceGeometry(QPieSlice *slice)
{
    PieSliceData &sliceData = QPieSlicePrivate::fromSlice(slice)->m_data;
    sliceData.m_center = PieSliceItem::sliceCenter(m_pieCenter, m_pieRadius, slice);
    sliceData.m_radius = m_pieRadius;
    sliceData.m_holeRadius = m_holeSize;
    return sliceData;
}

QT_END_NAMESPACE

#include "moc_piechartitem_p.cpp"
