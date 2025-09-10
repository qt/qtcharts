// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef PIECHARTITEM_H
#define PIECHARTITEM_H

#include <QtCharts/QPieSeries>
#include <private/chartitem_p.h>
#include <private/piesliceitem_p.h>
#include <QtCore/QPointer>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QPieSlice;
class ChartPresenter;
class PieAnimation;

class Q_CHARTS_EXPORT PieChartItem : public ChartItem
{
    Q_OBJECT

public:
    explicit PieChartItem(QPieSeries *series, QGraphicsItem* item = 0);
    ~PieChartItem();

    // from QGraphicsItem
    QRectF boundingRect() const override { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override {}

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public Q_SLOTS:
    // from Chart
    void handleDomainUpdated() override;

    void updateLayout();
    void handleSlicesAdded(const QList<QPieSlice *> &slices);
    void handleSlicesRemoved(const QList<QPieSlice *> &slices);
    void handleSliceChanged();
    void handleSeriesVisibleChanged();
    void handleOpacityChanged();

    void setAnimation(PieAnimation *animation);
    ChartAnimation *animation() const override;

    // From ChartItem
    void cleanup() override;
private:
    PieSliceData updateSliceGeometry(QPieSlice *slice);

private:
    QHash<QPieSlice *, PieSliceItem *> m_sliceItems;
    QPointer<QPieSeries> m_series;
    QRectF m_rect;
    QPointF m_pieCenter;
    qreal m_pieRadius;
    qreal m_holeSize;
    PieAnimation *m_animation;

};

QT_END_NAMESPACE

#endif // PIECHARTITEM_H
