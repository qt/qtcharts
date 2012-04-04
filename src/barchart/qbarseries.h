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

#include <qseries.h>
#include <QStringList>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QStringList QBarCategories;

class QBarSet;
class BarChartModel;
class BarCategory;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QSeries
{
    Q_OBJECT
public:
    QBarSeries(QStringList categories, QObject *parent = 0);

    virtual QSeriesType type() const { return QSeries::SeriesTypeBar; }

    void appendBarSet(QBarSet *set);            // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    void appendBarSets(QList<QBarSet* > sets);
    void removeBarSets(QList<QBarSet* > sets);
    void insertBarSet(int i, QBarSet *set);
    void insertCategory(int i, QString category);
    void removeCategory(int i);
    int barsetCount() const;
    int categoryCount() const;
    QList<QBarSet*> barSets() const;
    QBarCategories categories() const;

    void setLabelsVisible(bool visible = true);

    bool setModel(QAbstractItemModel *model);
    void setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation = Qt::Vertical);
    void setModelMappingShift(int first, int count);

public:
    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it
    // TODO: TO PIMPL --->
    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();
    BarChartModel& modelInternal();
    // <--- TO PIMPL

Q_SIGNALS:
    void clicked(QBarSet *barset, QString category, Qt::MouseButtons button);        // Up to user of api, what to do with these signals
    void selected();
    //
    void updatedBars();
    void restructuredBars();

    // TODO: internal signals, these to private implementation.
    // TODO: TO PIMPL --->
    void showToolTip(QPoint pos, QString tip);
    // <--- TO PIMPL

public Q_SLOTS:
    void setToolTipEnabled(bool enabled = true);           // enables tooltips

    // TODO: TO PIMPL --->
    void barsetClicked(QString category, Qt::MouseButtons button);
    // <--- TO PIMPL

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);
    void barsetChanged();

protected:
    BarChartModel *m_internalModel;     // TODO: this may change... current "2 models" situation doesn't look good.

//    QAbstractItemModel* m_model;
    int m_mapCategories;
    int m_mapBarBottom;
    int m_mapBarTop;
    int m_mapFirst;
    int m_mapCount;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
