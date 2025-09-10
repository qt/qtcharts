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


#ifndef ABSTRACTBARCHARTITEM_H
#define ABSTRACTBARCHARTITEM_H

#include <private/chartitem_p.h>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtGui/QPen>
#include <QtGui/QBrush>
#include <QtCore/QMap>
#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class Bar;
class QAxisCategories;
class QChart;
class BarAnimation;
class QBarSetPrivate;
class QAbstractAxis;

class Q_CHARTS_EXPORT AbstractBarChartItem : public ChartItem
{
    Q_OBJECT
public:
    AbstractBarChartItem(QAbstractBarSeries *series, QGraphicsItem* item = 0);
    virtual ~AbstractBarChartItem();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    virtual QList<QRectF> calculateLayout() = 0;
    void initializeFullLayout();
    virtual void initializeLayout(int set, int category, int layoutIndex, bool resetAnimation) = 0;
    virtual void applyLayout(const QList<QRectF> &layout);
    virtual void setAnimation(BarAnimation *animation);
    ChartAnimation *animation() const override;
    void setLayout(const QList<QRectF> &layout);
    QRectF geometry() const { return m_rect;}
    void resetAnimation();

public Q_SLOTS:
    void handleDomainUpdated() override;
    void handleLayoutChanged();
    void handleLabelsVisibleChanged(bool visible);
    void handleDataStructureChanged();     // structure of of series has changed, recreate graphic items
    void handleVisibleChanged();
    void handleOpacityChanged();
    void handleUpdatedBars();
    void handleLabelsPositionChanged();
    virtual void positionLabels();
    void handleBarValueChange(int index, QBarSet *barset);
    void handleBarValueAdd(int index, int count, QBarSet *barset);
    void handleBarValueRemove(int index, int count, QBarSet *barset);
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);

protected:
    void positionLabelsVertical();
    void createLabelItems();
    void handleSetStructureChange();
    virtual QString generateLabelText(int set, int category, qreal value);
    void updateBarItems();
    virtual void markLabelsDirty(QBarSet *barset, int index, int count);
    void calculateSeriesPositionAdjustmentAndWidth();

    QRectF m_rect;
    QList<QRectF> m_layout;

    BarAnimation *m_animation;

    QAbstractBarSeries *m_series; // Not owned.
    QMap<QBarSet *, QList<Bar *> > m_barMap;
    QMap<QBarSet *, QHash<int, Bar *> > m_indexForBarMap;
    int m_firstCategory;
    int m_lastCategory;
    int m_categoryCount;
    QSizeF m_oldSize;
    bool m_labelItemsMissing;
    Qt::Orientation m_orientation;
    bool m_resetAnimation;
    qreal m_seriesPosAdjustment;
    qreal m_seriesWidth;
};

QT_END_NAMESPACE

#endif // ABSTRACTBARCHARTITEM_H
