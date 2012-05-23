/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "piechartitem_p.h"
#include "piesliceitem_p.h"
#include "qpieslice.h"
#include "qpieseries.h"
#include "qpieseries_p.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartanimator_p.h"
#include <QPainter>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieChartItem::PieChartItem(QPieSeries *series, ChartPresenter* presenter)
    :ChartItem(presenter),
    m_series(series)
{
    Q_ASSERT(series);

    connect(series, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleSlicesAdded(QList<QPieSlice*>)));
    connect(series, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleSlicesRemoved(QList<QPieSlice*>)));
    QPieSeriesPrivate *d = QPieSeriesPrivate::seriesData(*series);
    connect(d, SIGNAL(piePositionChanged()), this, SLOT(updateLayout()));
    connect(d, SIGNAL(pieSizeChanged()), this, SLOT(updateLayout()));

    QTimer::singleShot(0, this, SLOT(initialize())); // TODO: get rid of this

    // Note: the following does not affect as long as the item does not have anything to paint
    setZValue(ChartPresenter::PieSeriesZValue);
}

PieChartItem::~PieChartItem()
{
    // slices deleted automatically through QGraphicsItem
}

void PieChartItem::handleGeometryChanged(const QRectF& rect)
{
    prepareGeometryChange();
    m_rect = rect;
    updateLayout();
}

void PieChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    Q_UNUSED(minX);
    Q_UNUSED(maxX);
    Q_UNUSED(minY);
    Q_UNUSED(maxY);
    // does not apply to pie
}

void PieChartItem::rangeXChanged(qreal min, qreal max, int tickXCount)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(tickXCount);
    // does not apply to pie
}

void PieChartItem::rangeYChanged(qreal min, qreal max, int tickYCount)
{
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(tickYCount);
    // does not apply to pie
}

void PieChartItem::initialize()
{
    handleSlicesAdded(m_series->slices());
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

    // apply size factor
    m_pieRadius *= m_series->pieSize();

    // set layouts for existing slice items
    foreach (QPieSlice* slice, m_series->slices()) {
        PieSliceItem *sliceItem = m_sliceItems.value(slice);
        if (sliceItem) {
            PieSliceData sliceData = updateSliceGeometry(slice);
            if (animator())
                animator()->updateAnimation(this, sliceItem, sliceData);
            else
                sliceItem->setLayout(sliceData);
        }
    }

    update();
}

void PieChartItem::handleSlicesAdded(QList<QPieSlice*> slices)
{
    presenter()->chartTheme()->decorate(m_series, presenter()->dataSet()->seriesIndex(m_series));

    bool startupAnimation = m_sliceItems.isEmpty();

    foreach (QPieSlice *slice, slices) {
        PieSliceItem* sliceItem = new PieSliceItem(this);
        m_sliceItems.insert(slice, sliceItem);

        // note: do need to connect to slice valueChanged(). calculatedDataChanged() is enough.
        // to update the slice.
        connect(slice, SIGNAL(calculatedDataChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(labelChanged()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(appearanceChanged()), this, SLOT(handleSliceChanged()));
        connect(sliceItem, SIGNAL(clicked(Qt::MouseButtons)), slice, SIGNAL(clicked()));
        connect(sliceItem, SIGNAL(hovered(bool)), slice, SIGNAL(hovered(bool)));

        PieSliceData sliceData = updateSliceGeometry(slice);
        if (animator())
            animator()->addAnimation(this, sliceItem, sliceData, startupAnimation);
        else
            sliceItem->setLayout(sliceData);
    }
}

void PieChartItem::handleSlicesRemoved(QList<QPieSlice*> slices)
{
    presenter()->chartTheme()->decorate(m_series, presenter()->dataSet()->seriesIndex(m_series));

    foreach (QPieSlice *slice, slices) {
        PieSliceItem *sliceItem = m_sliceItems.value(slice);
        Q_ASSERT(sliceItem);
        m_sliceItems.remove(slice);

        if (animator())
            animator()->removeAnimation(this, sliceItem); // animator deletes the PieSliceItem
        else
            delete sliceItem;
    }
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_sliceItems.contains(slice));

    PieSliceItem *sliceItem = m_sliceItems.value(slice);
    PieSliceData sliceData = updateSliceGeometry(slice);
    if (animator())
        animator()->updateAnimation(this, sliceItem, sliceData);
    else
        sliceItem->setLayout(sliceData);

    update();
}

PieSliceData PieChartItem::updateSliceGeometry(QPieSlice *slice)
{
    PieSliceData &sliceData = PieSliceData::fromSlice(slice);
    sliceData.m_center = PieSliceItem::sliceCenter(m_pieCenter, m_pieRadius, slice);
    sliceData.m_radius = m_pieRadius;
    return sliceData;
}

#include "moc_piechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
