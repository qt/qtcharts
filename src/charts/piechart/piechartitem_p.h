/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
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

class QGraphicsItem;
QT_CHARTS_BEGIN_NAMESPACE
class QPieSlice;
class ChartPresenter;
class PieAnimation;

class PieChartItem : public ChartItem
{
    Q_OBJECT

public:
    explicit PieChartItem(QPieSeries *series, QGraphicsItem* item = 0);
    ~PieChartItem();

    // from QGraphicsItem
    QRectF boundingRect() const { return m_rect; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

public Q_SLOTS:
    // from Chart
    virtual void handleDomainUpdated();

    void updateLayout();
    void handleSlicesAdded(QList<QPieSlice *> slices);
    void handleSlicesRemoved(QList<QPieSlice *> slices);
    void handleSliceChanged();
    void handleSeriesVisibleChanged();
    void handleOpacityChanged();

    void setAnimation(PieAnimation *animation);
    ChartAnimation *animation() const;

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

QT_CHARTS_END_NAMESPACE

#endif // PIECHARTITEM_H
