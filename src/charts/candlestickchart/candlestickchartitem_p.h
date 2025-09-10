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

#ifndef CANDLESTICKCHARTITEM_P_H
#define CANDLESTICKCHARTITEM_P_H

#include <private/chartitem_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Candlestick;
class CandlestickAnimation;
class QCandlestickSeries;
class QCandlestickSet;

class Q_CHARTS_EXPORT CandlestickChartItem : public ChartItem
{
    Q_OBJECT

public:
    CandlestickChartItem(QCandlestickSeries *series, QGraphicsItem *item = nullptr);
    ~CandlestickChartItem();

    void setAnimation(CandlestickAnimation *animation);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public Q_SLOTS:
    void handleDomainUpdated() override;
    void handleLayoutUpdated();
    void handleCandlesticksUpdated();
    void handleCandlestickSeriesChange();

private Q_SLOTS:
    void handleCandlestickSetsAdd(const QList<QCandlestickSet *> &sets);
    void handleCandlestickSetsRemove(const QList<QCandlestickSet *> &sets);
    void handleDataStructureChanged();

private:
    bool updateCandlestickGeometry(Candlestick *item, int index);
    void updateCandlestickAppearance(Candlestick *item, QCandlestickSet *set);

    void addTimestamp(qreal timestamp);
    void removeTimestamp(qreal timestamp);
    void updateTimePeriod();

protected:
    QRectF m_boundingRect;
    QCandlestickSeries *m_series; // Not owned.
    int m_seriesIndex;
    int m_seriesCount;
    QHash<QCandlestickSet *, Candlestick *> m_candlesticks;
    QList<qreal> m_timestamps;
    qreal m_timePeriod;
    CandlestickAnimation *m_animation;
};

QT_END_NAMESPACE

#endif // CANDLESTICKCHARTITEM_P_H
