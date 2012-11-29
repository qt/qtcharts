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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTBARSERIES_P_H
#define QABSTRACTBARSERIES_P_H

#include "qabstractbarseries.h"
#include "qabstractseries_p.h"
#include <QStringList>
#include <QAbstractSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarModelMapper;
class QBarCategoryAxis;
class QLegendMarker;

class QAbstractBarSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QAbstractBarSeriesPrivate(QAbstractBarSeries *parent);
    int categoryCount() const;

    void setBarWidth(qreal width);
    qreal barWidth() const;

    void setVisible(bool visible);
    void setLabelsVisible(bool visible);

    void initializeDomain();
    void initializeAxes();
    void initializeAnimations(QChart::AnimationOptions options);
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);

    QList<QLegendMarker*> createLegendMarkers(QLegend *legend);

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const;

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool append(QList<QBarSet *> sets);
    bool remove(QList<QBarSet *> sets);
    bool insert(int index, QBarSet *set);

    QBarSet *barsetAt(int index);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();
    qreal minX();
    qreal maxX();
    qreal categoryTop(int category);
    qreal categoryBottom(int category);
    qreal top();
    qreal bottom();

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void updatedBars();
    void updatedLayout();
    void restructuredBars();
    void labelsVisibleChanged(bool visible);
    void visibleChanged();

private:
    void populateCategories(QBarCategoryAxis *axis);

protected:
    QList<QBarSet *> m_barSets;
    qreal m_barWidth;
    bool m_labelsVisible;
    bool m_visible;

private:
    Q_DECLARE_PUBLIC(QAbstractBarSeries)
    friend class HorizontalBarChartItem;
    friend class BarChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QABSTRACTBARSERIES_P_H
