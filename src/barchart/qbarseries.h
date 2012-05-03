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

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QStringList QBarCategories;

class QBarSet;
class BarCategory;
class QBarSeriesPrivate;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QAbstractSeries
{
    Q_OBJECT
public:
    explicit QBarSeries(QBarCategories categories, QObject *parent = 0);
    virtual ~QBarSeries();

    QAbstractSeries::SeriesType type() const;

    void appendBarSet(QBarSet *set);            // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    void appendBarSets(QList<QBarSet* > sets);
    void removeBarSets(QList<QBarSet* > sets);
    int barsetCount() const;
    int categoryCount() const;
    QList<QBarSet*> barSets() const;
    QBarCategories categories() const;

    void setLabelsVisible(bool visible = true);

    bool setModel(QAbstractItemModel *model);
    void setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation = Qt::Vertical);
    void setModelMappingRange(int first, int count = -1);

protected:
    explicit QBarSeries(QBarSeriesPrivate &d,QObject *parent = 0);

Q_SIGNALS:
    void clicked(QBarSet *barset, QString category);
    void hovered(QBarSet* barset, bool status);

protected:
    Q_DECLARE_PRIVATE(QBarSeries)
    friend class BarChartItem;
    friend class PercentBarChartItem;
    friend class StackedBarChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
