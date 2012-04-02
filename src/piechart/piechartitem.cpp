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
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartanimator_p.h"
#include <QDebug>
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
    handleSlicesAdded(m_series->slices());
}

void PieChartItem::handleSlicesAdded(QList<QPieSlice*> slices)
{
    bool isEmpty = m_slices.isEmpty();

    presenter()->chartTheme()->decorate(m_series, presenter()->dataSet()->seriesIndex(m_series), false);

    foreach (QPieSlice *s, slices) {
        PieSliceItem* item = new PieSliceItem(this);
        m_slices.insert(s, item);
        connect(s, SIGNAL(changed()), this, SLOT(handleSliceChanged()));
        connect(item, SIGNAL(clicked(Qt::MouseButtons)), s, SIGNAL(clicked(Qt::MouseButtons)));
        connect(item, SIGNAL(hoverEnter()), s, SIGNAL(hoverEnter()));
        connect(item, SIGNAL(hoverLeave()), s, SIGNAL(hoverLeave()));

        PieSliceData data = sliceData(s);

        if (animator())
            animator()->addAnimation(this, s, data, isEmpty);
        else
            setLayout(s, data);
    }
}

void PieChartItem::handleSlicesRemoved(QList<QPieSlice*> slices)
{
    presenter()->chartTheme()->decorate(m_series, presenter()->dataSet()->seriesIndex(m_series), false);

    foreach (QPieSlice *s, slices) {
        if (animator())
            animator()->removeAnimation(this, s);
        else
            destroySlice(s);
    }
}

void PieChartItem::handlePieLayoutChanged()
{
    PieLayout layout = calculateLayout();
    applyLayout(layout);
    update();
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    PieSliceData data = sliceData(slice);
    updateLayout(slice, data);
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

PieSliceData PieChartItem::sliceData(QPieSlice *slice)
{
	// TODO: This function is kid of useless now. Refactor.
    PieSliceData sliceData = *slice->data_ptr();
    sliceData.m_center = PieSliceItem::sliceCenter(m_pieCenter, m_pieRadius, slice);
    sliceData.m_radius = m_pieRadius;
    return sliceData;
}

PieLayout PieChartItem::calculateLayout()
{
    calculatePieLayout();
    PieLayout layout;
    foreach (QPieSlice* s, m_series->slices()) {
        if (m_slices.contains(s)) // calculate layout only for those slices that are already visible
            layout.insert(s, sliceData(s));
    }
    return layout;
}

void PieChartItem::applyLayout(const PieLayout &layout)
{
    if (animator())
        animator()->updateLayout(this, layout);
    else
        setLayout(layout);
}

void PieChartItem::updateLayout(QPieSlice *slice, const PieSliceData &sliceData)
{
    if (animator())
        animator()->updateLayout(this, slice, sliceData);
    else
        setLayout(slice, sliceData);
}

void PieChartItem::setLayout(const PieLayout &layout)
{
    foreach (QPieSlice *slice, layout.keys()) {
        PieSliceItem *item = m_slices.value(slice);
        Q_ASSERT(item);
        item->setSliceData(layout.value(slice));
        item->updateGeometry();
        item->update();
    }
}

void PieChartItem::setLayout(QPieSlice *slice, const PieSliceData &sliceData)
{
    // find slice
    PieSliceItem *item = m_slices.value(slice);
    Q_ASSERT(item);
    item->setSliceData(sliceData);
    item->updateGeometry();
    item->update();
}

void PieChartItem::destroySlice(QPieSlice *slice)
{
    delete m_slices.take(slice);
}

#include "moc_piechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
