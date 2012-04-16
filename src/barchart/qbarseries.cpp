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

#include "qbarseries.h"
#include "qbarseries_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "domain_p.h"
#include "legendmarker_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"

#include <QAbstractItemModel>
#include <QModelIndex>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.
    \mainclass

    QBarSeries represents a series of data shown as bars. One QBarSeries can contain multiple
    QBarSet data sets. QBarSeries groups the data from sets to categories, which are defined
    by QStringList.

    See the \l {BarChart Example} {bar chart example} to learn how to create a simple bar chart.
    \image examples_barchart.png

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn void QBarSeries::clicked(QBarSet *barset, QString category)

    The signal is emitted if the user clicks with a mouse on top of QBarSet \a barset of category \a category
    contained by the series.
*/

/*!
    \fn void QBarSeries::hovered(QBarSet* barset, bool status)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
*/

/*!
    Constructs empty QBarSeries. Parameter \a categories defines the categories for chart.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QBarCategories categories, QObject *parent) :
    QAbstractSeries(*new QBarSeriesPrivate(categories, this),parent)
{
}

/*!
    Destructs barseries and owned barsets.
*/
QBarSeries::~QBarSeries()
{
    // NOTE: d_ptr destroyed by QObject
}

/*!
    \internal
*/
QBarSeries::QBarSeries(QBarSeriesPrivate &d, QObject *parent) :
    QAbstractSeries(d,parent)
{
}

/*!
    Returns the type of series. Derived classes override this.
*/
QAbstractSeries::QSeriesType QBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeBar;
}

/*!
    Adds a set of bars to series. Takes ownership of \a set.
*/
void QBarSeries::appendBarSet(QBarSet *set)
{
    Q_D(QBarSeries);
    d->m_barSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), d, SLOT(barsetChanged()));
    emit d->restructuredBars();
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesn't delete \a set.
*/
void QBarSeries::removeBarSet(QBarSet *set)
{
    Q_D(QBarSeries);
    if (d->m_barSets.contains(set)) {
        d->m_barSets.removeOne(set);
        QObject::disconnect(set, SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
        emit d->restructuredBars();
    }
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
*/
void QBarSeries::appendBarSets(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);
    foreach (QBarSet* set, sets) {
        d->m_barSets.append(set);
        QObject::connect(set, SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
    }
    emit d->restructuredBars();
}

/*!
    Removes a list of barsets from series. Releases ownership of \a sets. Doesn't delete \a sets.
*/
void QBarSeries::removeBarSets(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);

    foreach (QBarSet* set, sets) {
        if (d->m_barSets.contains(set)) {
            d->m_barSets.removeOne(set);
            QObject::disconnect(set, SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
        }
    }
    emit d->restructuredBars();
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::barsetCount() const
{
    Q_D(const QBarSeries);
    return d->m_barSets.count();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::categoryCount() const
{
    Q_D(const QBarSeries);
    return d->m_categories.count();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QBarSeries::barSets() const
{
    Q_D(const QBarSeries);
    return d->m_barSets;
}

/*!
     \fn bool QBarSeries::setModel(QAbstractItemModel *model)
     Sets the \a model to be used as a data source
 */
bool QBarSeries::setModel(QAbstractItemModel *model)
{
    Q_D(QBarSeries);
    return d->setModel(model);
}

/*!
     \fn bool QBarSeries::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
     Sets column/row specified by \a categories to be used as a list of bar series categories.
     Parameter \a bottomBoundry indicates the column/row where the first bar set is located in the model.
     Parameter \a topBoundry indicates the column/row where the last bar set is located in the model.
     All the columns/rows inbetween those two values are also used as data for bar sets.
     The \a orientation parameter specifies whether the data is in columns or in rows.
 */
void QBarSeries::setModelMapping(int categories, int bottomBoundary, int topBoundary, Qt::Orientation orientation)
{
    Q_D(QBarSeries);
    d->setModelMapping(categories,bottomBoundary,topBoundary,orientation);
}

void QBarSeries::setModelMappingRange(int first, int count)
{
    Q_D(QBarSeries);
    d->setModelMappingRange(first, count);
}

/*!
    Returns the bar categories of the series.
*/
QBarCategories QBarSeries::categories() const
{
    Q_D(const QBarSeries);
    return d->m_categories;
}

/*!
    Sets the visibility of labels in series to \a visible
*/
void QBarSeries::setLabelsVisible(bool visible)
{
    foreach (QBarSet* s, barSets()) {
        s->setLabelsVisible(visible);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSeriesPrivate::QBarSeriesPrivate(QBarCategories categories, QBarSeries *q) :
    QAbstractSeriesPrivate(q),
    m_categories(categories),
    m_mapCategories(-1),
    m_mapBarBottom(-1),
    m_mapBarTop(-1)
{
}

QBarSet* QBarSeriesPrivate::barsetAt(int index)
{
    return m_barSets.at(index);
}

QString QBarSeriesPrivate::categoryName(int category)
{
    return m_categories.at(category);
}

qreal QBarSeriesPrivate::min()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal min = INT_MAX;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->at(j);
            if (temp < min)
                min = temp;
        }
    }
    return min;
}

qreal QBarSeriesPrivate::max()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal max = INT_MIN;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->at(j);
            if (temp > max)
                max = temp;
        }
    }

    return max;
}

qreal QBarSeriesPrivate::valueAt(int set, int category)
{
    if ((set < 0) || (set >= m_barSets.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_barSets.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    return m_barSets.at(set)->at(category);
}

qreal QBarSeriesPrivate::percentageAt(int set, int category)
{
    if ((set < 0) || (set >= m_barSets.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_barSets.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    qreal value = m_barSets.at(set)->at(category);
    qreal sum = categorySum(category);
    if ( qFuzzyIsNull(sum) ) {
        return 0;
    }

    return value / sum;
}

qreal QBarSeriesPrivate::categorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += m_barSets.at(set)->at(category);
    }
    return sum;
}

qreal QBarSeriesPrivate::absoluteCategorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += qAbs(m_barSets.at(set)->at(category));
    }
    return sum;
}

qreal QBarSeriesPrivate::maxCategorySum()
{
    qreal max = INT_MIN;
    int count = m_categories.count();
    for (int i = 0; i < count; i++) {
        qreal sum = categorySum(i);
        if (sum > max)
            max = sum;
    }
    return max;
}

bool QBarSeriesPrivate::setModel(QAbstractItemModel *model)
{
    // disconnect signals from old model
    if(m_model)
    {
        disconnect(m_model, 0, this, 0);
        m_mapCategories = -1;
        m_mapBarBottom = -1;
        m_mapBarTop = -1;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if(model)
    {
        m_model = model;
        return true;
    }
    else
    {
        m_model = 0;
        return false;
    }
}

void QBarSeriesPrivate::setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation)
{
    Q_Q(QBarSeries);

    if (m_model == 0)
        return;

    m_mapCategories = categories;
    m_mapBarBottom = bottomBoundry;
    m_mapBarTop = topBoundry;
    m_mapOrientation = orientation;

    // connect the signals
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    if (m_mapOrientation == Qt::Vertical) {
        connect(m_model,SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model,SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        connect(m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }

    // create the initial bars
    m_categories.clear();
    if (m_mapOrientation == Qt::Vertical) {
        int rowCount = 0;
        if(m_mapCount == -1)
            rowCount = m_model->rowCount() - m_mapFirst;
        else
            rowCount = qMin(m_mapCount, m_model->rowCount() - m_mapFirst);
        for (int k = m_mapFirst; k < m_mapFirst + rowCount; k++) {
            m_categories << m_model->data(m_model->index(k, m_mapCategories), Qt::DisplayRole).toString();
        }

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
            for(int m = m_mapFirst; m < m_mapFirst + rowCount; m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    } else {
        int columnCount = 0;
        if(m_mapCount == -1)
            columnCount = m_model->columnCount() - m_mapFirst;
        else
            columnCount = qMin(m_mapCount, m_model->columnCount() - m_mapFirst);
        for (int k = m_mapFirst; k < m_mapFirst + columnCount; k++) {
            m_categories << m_model->data(m_model->index(m_mapCategories, k), Qt::DisplayRole).toString();
        }

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Vertical, Qt::DisplayRole).toString());
            for(int m = m_mapFirst; m < m_mapFirst + columnCount; m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    }
}

void QBarSeriesPrivate::setModelMappingRange(int first, int count)
{
    m_mapFirst = first;
    m_mapCount = count;
}

void QBarSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            if (m_mapOrientation == Qt::Vertical)
            {
                // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
                if ( row >= m_mapFirst && (m_mapCount == - 1 || row < m_mapFirst + m_mapCount)) {
                    if (column >= m_mapBarBottom && column <= m_mapBarTop)
                        barsetAt(column - m_mapBarBottom)->replace(row - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    //                    if (column == m_mapCategories);// TODO:
                }
            }
            else
            {
                // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
                if (column >= m_mapFirst && (m_mapCount == - 1 || column < m_mapFirst + m_mapCount)) {
                    if (row >= m_mapBarBottom && row <= m_mapBarTop)
                        barsetAt(row - m_mapBarBottom)->replace(column - m_mapFirst, m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    //                    if (row == m_mapCategories);// TODO:
                }
            }
        }
    }
}

void QBarSeriesPrivate::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    initializeDataFromModel();
//    // series uses model as a data sourceupda
//    int addedCount = end - start + 1;
//    if (m_mapCount != -1 && start >= m_mapFirst + m_mapCount) {
//        return;
//    } else {

//        for (int bar = m_mapBarBottom; bar <= m_mapBarTop; bar++) {
//            QBarSet *barSet = barsetAt(bar - m_mapBarBottom);
//            // adding items to unlimited map
//            if (m_mapCount == -1 && start >= m_mapFirst) {
//                for (int i = start; i <= end; i++) {
//                    if (bar == m_mapBarBottom)
//                        insertCategory(i - m_mapFirst, m_model->data(m_model->index(i, m_mapCategories), Qt::DisplayRole).toString());
//                    barSet->insert(i - m_mapFirst, m_model->data(m_model->index(i, bar), Qt::DisplayRole).toDouble());
//                }
//            } else if (m_mapCount == - 1 && start < m_mapFirst) {
//                // not all newly added items
//                for (int i = m_mapFirst; i < m_mapFirst + addedCount; i++) {
//                    if (bar == m_mapBarBottom)
//                        insertCategory(i - m_mapFirst, m_model->data(m_model->index(i, m_mapCategories), Qt::DisplayRole).toString());
//                    barSet->insert(i - m_mapFirst, m_model->data(m_model->index(i, bar), Qt::DisplayRole).toDouble());
//                }
//            }

//            // adding items to limited map
//            else if (start >= m_mapFirst) {
//                // remove the items that will no longer fit into the map
//                // int toRemove = addedCount - (count - points().size());
//                for (int i = start; i <= end; i++) {
//                    if (bar == m_mapBarBottom)
//                        insertCategory(i - m_mapFirst, m_model->data(m_model->index(i, m_mapCategories), Qt::DisplayRole).toString());
//                    barSet->insert(i - m_mapFirst, m_model->data(m_model->index(i, bar), Qt::DisplayRole).toDouble());
//                }
//                if (m_barSets.size() > m_mapCount)
//                    for (int i = m_barSets.size() - 1; i >= m_mapCount; i--) {
//                        if (bar == m_mapBarBottom)
//                            removeCategory(i);
//                        barSet->remove(i);
//                    }
//            } else {
//                //
//                for (int i = m_mapFirst; i < m_mapFirst + addedCount; i++) {
//                    if (bar == m_mapBarBottom)
//                        insertCategory(i - m_mapFirst, m_model->data(m_model->index(i, m_mapCategories), Qt::DisplayRole).toString());
//                    barSet->insert(i - m_mapFirst, m_model->data(m_model->index(i, bar), Qt::DisplayRole).toDouble());
//                }
//                if (m_barSets.size() > m_mapCount)
//                    for (int i = m_barSets.size() - 1; i >= m_mapCount; i--) {
//                        if (bar == m_mapBarBottom)
//                            removeCategory(i);
//                        barSet->remove(i);
//                    }
//            }
//        }
//        emit restructuredBars();
//        emit barsetChanged();
//        emit categoriesUpdated();
//    }
}

void QBarSeriesPrivate::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    initializeDataFromModel();
}

void QBarSeriesPrivate::initializeDataFromModel()
{
    Q_Q(QBarSeries);

    if (m_model == 0)
        return;

    // connect the signals
//    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex,QModelIndex)));
//    if (m_mapOrientation == Qt::Vertical) {
//        connect(m_model,SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
//        connect(m_model,SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
//    } else {
//        connect(m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
//        connect(m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
//    }

    // create the initial bars
    m_categories.clear();
    m_barSets.clear();
    emit restructuredBars();
    if (m_mapOrientation == Qt::Vertical) {
        int rowCount = 0;
        if(m_mapCount == -1)
            rowCount = m_model->rowCount() - m_mapFirst;
        else
            rowCount = qMin(m_mapCount, m_model->rowCount() - m_mapFirst);
        for (int k = m_mapFirst; k < m_mapFirst + rowCount; k++) {
            m_categories << m_model->data(m_model->index(k, m_mapCategories), Qt::DisplayRole).toString();
        }

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
            for(int m = m_mapFirst; m < m_mapFirst + rowCount; m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    } else {
        int columnCount = 0;
        if(m_mapCount == -1)
            columnCount = m_model->columnCount() - m_mapFirst;
        else
            columnCount = qMin(m_mapCount, m_model->columnCount() - m_mapFirst);
        for (int k = m_mapFirst; k < m_mapFirst + columnCount; k++) {
            m_categories << m_model->data(m_model->index(m_mapCategories, k), Qt::DisplayRole).toString();
        }

        for (int i = m_mapBarBottom; i <= m_mapBarTop; i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Vertical, Qt::DisplayRole).toString());
            for(int m = m_mapFirst; m < m_mapFirst + columnCount; m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            q->appendBarSet(barSet);
        }
    }
    emit restructuredBars();
    emit updatedBars();
}

void QBarSeriesPrivate::insertCategory(int index, const QString category)
{
    m_categories.insert(index, category);
    emit categoriesUpdated();
}

void QBarSeriesPrivate::removeCategory(int index)
{
    m_categories.removeAt(index);
    emit categoriesUpdated();
}

void QBarSeriesPrivate::barsetChanged()
{
    emit updatedBars();
}

void QBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = m_categories.count();
    qreal y = max();
    minX = qMin(minX, x);
    minY = qMin(minY, y);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRangeX(minX,maxX,tickXCount);
    domain.setRangeY(minY,maxY,tickYCount);
}

Chart* QBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QBarSeries);

    BarChartItem* bar = new BarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;

}

QList<LegendMarker*> QBarSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QBarSeries);
    QList<LegendMarker*> markers;
    foreach(QBarSet* set, q->barSets()) {
        BarLegendMarker* marker = new BarLegendMarker(q,set,legend);
        markers << marker;
    }

    return markers;
}

#include "moc_qbarseries.cpp"
#include "moc_qbarseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
