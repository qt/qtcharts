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


#ifndef ABSTRACTBARCHARTITEM_H
#define ABSTRACTBARCHARTITEM_H

#include <private/chartitem_p.h>
#include <QtCharts/QAbstractBarSeries>
#include <QtGui/QPen>
#include <QtGui/QBrush>

QT_CHARTS_BEGIN_NAMESPACE

class Bar;
class QAxisCategories;
class QChart;
class BarAnimation;

class AbstractBarChartItem : public ChartItem
{
    Q_OBJECT
public:
    AbstractBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item = 0);
    virtual ~AbstractBarChartItem();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    virtual QVector<QRectF> calculateLayout() = 0;
    virtual void initializeLayout() = 0;
    virtual void applyLayout(const QVector<QRectF> &layout);
    virtual void setAnimation(BarAnimation *animation);
    void setLayout(const QVector<QRectF> &layout);
    void updateLayout(const QVector<QRectF> &layout);
    QRectF geometry() const { return m_rect;}

public Q_SLOTS:
    void handleDomainUpdated();
    void handleLayoutChanged();
    void handleLabelsVisibleChanged(bool visible);
    void handleDataStructureChanged();     // structure of of series has changed, recreate graphic items
    void handleVisibleChanged();
    void handleOpacityChanged();
    virtual void handleUpdatedBars();
    void handleLabelsPositionChanged();
    virtual void positionLabels();

protected:

    qreal m_domainMinX;
    qreal m_domainMaxX;
    qreal m_domainMinY;
    qreal m_domainMaxY;

    QRectF m_rect;
    QVector<QRectF> m_layout;

    BarAnimation *m_animation;

    QAbstractBarSeries *m_series; // Not owned.
    QList<Bar *> m_bars;
    QList<QGraphicsTextItem *> m_labels;
    QSizeF m_oldSize;
};

QT_CHARTS_END_NAMESPACE

#endif // ABSTRACTBARCHARTITEM_H
