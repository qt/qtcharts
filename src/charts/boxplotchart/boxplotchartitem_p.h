/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

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
#include <private/chartitem_p.h>
#include <private/boxplotanimation_p.h>
#include <QtCharts/QBoxSet>
#include <QtWidgets/QGraphicsItem>

QT_CHARTS_BEGIN_NAMESPACE

class BoxPlotSeriesPrivate;

class BoxPlotChartItem : public ChartItem
{
    Q_OBJECT
public:
    BoxPlotChartItem(QBoxPlotSeries *series, QGraphicsItem *item = 0);
    ~BoxPlotChartItem();

    void setAnimation(BoxPlotAnimation *animation);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public Q_SLOTS:
    void handleDataStructureChanged();
    void handleDomainUpdated();
    void handleLayoutChanged();
    void handleUpdatedBars();
    void handleBoxsetRemove(QList<QBoxSet *> barSets);

private:
    virtual QVector<QRectF> calculateLayout();
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

QT_CHARTS_END_NAMESPACE

#endif // BOXPLOTCHARTITEM_H
