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


#ifndef BOXPLOTCHARTITEM_H
#define BOXPLOTCHARTITEM_H

#include <private/boxwhiskers_p.h>
#include <QtCharts/QBoxPlotSeries>
#include <QtCharts/private/qchartglobal_p.h>
#include <private/chartitem_p.h>
#include <private/boxplotanimation_p.h>
#include <QtCharts/QBoxSet>
#include <QtWidgets/QGraphicsItem>

QT_BEGIN_NAMESPACE

class BoxPlotSeriesPrivate;

class Q_CHARTS_EXPORT BoxPlotChartItem : public ChartItem
{
    Q_OBJECT
public:
    BoxPlotChartItem(QBoxPlotSeries *series, QGraphicsItem *item = 0);
    ~BoxPlotChartItem();

    void setAnimation(BoxPlotAnimation *animation);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

public Q_SLOTS:
    void handleSeriesVisibleChanged();
    void handleOpacityChanged();
    void handleDataStructureChanged();
    void handleDomainUpdated() override;
    void handleLayoutChanged();
    void handleUpdatedBars();
    void handleBoxsetRemove(const QList<QBoxSet *> &barSets);

private:
    virtual QList<QRectF> calculateLayout();
    void initializeLayout();
    bool updateBoxGeometry(BoxWhiskers *box, int index);

protected:
    friend class QBoxPlotSeriesPrivate;
    QBoxPlotSeries *m_series; // Not owned.
    QList<BoxWhiskers *> m_boxes;
    QHash<QBoxSet *, BoxWhiskers *> m_boxTable;
    int m_seriesIndex;
    int m_seriesCount;

    BoxPlotAnimation *m_animation;

    QRectF m_boundingRect;
};

QT_END_NAMESPACE

#endif // BOXPLOTCHARTITEM_H
