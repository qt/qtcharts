/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
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
