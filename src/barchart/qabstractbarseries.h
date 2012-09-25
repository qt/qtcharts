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

#ifndef QABSTRACTBARSERIES_H
#define QABSTRACTBARSERIES_H

#include <qabstractseries.h>
#include <QStringList>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;
class QAbstractBarSeriesPrivate;

// Container for series
class QTCOMMERCIALCHART_EXPORT QAbstractBarSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(qreal barWidth READ barWidth WRITE setBarWidth)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool labelsVisible READ isLabelsVisible WRITE setLabelsVisible NOTIFY labelsVisibleChanged)

public:
    virtual ~QAbstractBarSeries();

    void setBarWidth(qreal width);
    qreal barWidth() const;

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool take(QBarSet *set);
    bool append(QList<QBarSet *> sets);
    bool insert(int index, QBarSet *set);
    int count() const;
    QList<QBarSet *> barSets() const;
    void clear();

    void setLabelsVisible(bool visible = true);
    bool isLabelsVisible() const;

protected:
    explicit QAbstractBarSeries(QAbstractBarSeriesPrivate &d, QObject *parent = 0);

Q_SIGNALS:
    void clicked(int index, QBarSet *barset);
    void hovered(bool status, QBarSet *barset);
    void countChanged();
    void labelsVisibleChanged();

    void barsetsAdded(QList<QBarSet *> sets);
    void barsetsRemoved(QList<QBarSet *> sets);

protected:
    Q_DECLARE_PRIVATE(QAbstractBarSeries)
    friend class AbstractBarChartItem;
    friend class PercentBarChartItem;
    friend class StackedBarChartItem;
    friend class BarChartItem;
    friend class HorizontalBarChartItem;
    friend class HorizontalStackedBarChartItem;
    friend class HorizontalPercentBarChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QABSTRACTBARSERIES_H
