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

#ifndef BARSERIES_H
#define BARSERIES_H

#include <qabstractseries.h>
#include <QStringList>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;
class QBarSeriesPrivate;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QAbstractSeries
{
    Q_OBJECT
    Q_PROPERTY(qreal barWidth READ barWidth WRITE setBarWidth)
    Q_PROPERTY(int count READ barsetCount)
    Q_PROPERTY(bool labelsVisible READ isLabelsVisible WRITE setLabelsVisible)

public:
    explicit QBarSeries(QObject *parent = 0);
    virtual ~QBarSeries();

    QAbstractSeries::SeriesType type() const;

    void setBarWidth(qreal width);
    qreal barWidth() const;

    bool append(QBarSet *set);
    bool remove(QBarSet *set);
    bool append(QList<QBarSet* > sets);
    bool insert(int index, QBarSet *set);
    int barsetCount() const;
    QList<QBarSet*> barSets() const;
    void clear();

    void setLabelsVisible(bool visible = true);
    bool isLabelsVisible() const;

protected:
    explicit QBarSeries(QBarSeriesPrivate &d,QObject *parent = 0);

Q_SIGNALS:
    void clicked(QBarSet *barset, int index);
    void hovered(QBarSet* barset, bool status);
    void labelsVisibleChanged();

    void barsetsAdded(QList<QBarSet*> sets);
    void barsetsRemoved(QList<QBarSet*> sets);

protected:
    Q_DECLARE_PRIVATE(QBarSeries)
    friend class BarChartItem;
    friend class PercentBarChartItem;
    friend class StackedBarChartItem;
    friend class GroupedBarChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
