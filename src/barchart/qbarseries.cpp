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
#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.
    \mainclass

    QBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars to
    the position defined by data. Single bar is defined by QPointF, where x value is the x-coordinate of the bar
    and y-value is the height of the bar. The category names are ignored with this series and x-axis
    shows the x-values.

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
    Constructs empty QBarSeries.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QObject *parent) :
    QAbstractSeries(*new QBarSeriesPrivate(this),parent)
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
QAbstractSeries::SeriesType QBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeBar;
}

/*!
    Sets the \a categories, which are used to to group the data.
*/
void QBarSeries::setCategories(QBarCategories categories)
{
    Q_D(QBarSeries);
    d->setCategories(categories);
    emit d->categoriesUpdated();
}

/*!
    Adds a set of bars to series. Takes ownership of \a set. If the set is null or is already in series, it won't be appended.
    Returns true, if appending succeeded.

*/
bool QBarSeries::append(QBarSet *set)
{
    Q_D(QBarSeries);
    if ((d->m_barSets.contains(set)) || (set == 0)) {
        // Fail if set is already in list or set is null.
        return false;
    }
    d->m_barSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), d, SLOT(barsetChanged()));
    emit d->restructuredBars();
    return true;
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesn't delete \a set.
    Returns true, if set was removed.
*/
bool QBarSeries::remove(QBarSet *set)
{
    Q_D(QBarSeries);
    if (!d->m_barSets.contains(set)) {
        // Fail if set is not in list
        return false;
    }
    d->m_barSets.removeOne(set);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), d, SLOT(barsetChanged()));
    emit d->restructuredBars();
    return true;
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
    Returns true, if all sets were appended succesfully. If any of the sets is null or is already appended to series,
    nothing is appended and function returns false. If any of the sets is in list more than once, nothing is appended
    and function returns false.
*/
bool QBarSeries::append(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);
    foreach (QBarSet* set, sets) {
        if ((set == 0) || (d->m_barSets.contains(set))) {
            // Fail if any of the sets is null or is already appended.
            return false;
        }
        if (sets.count(set) != 1) {
            // Also fail if same set is more than once in given list.
            return false;
        }
    }

    foreach (QBarSet* set, sets) {
        d->m_barSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), d, SLOT(barsetChanged()));
    }
    emit d->restructuredBars();
    return true;
}

/*!
    Removes a list of barsets from series. Releases ownership of \a sets. Doesn't delete \a sets.
*/
bool QBarSeries::remove(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);

    bool setsRemoved = false;
    foreach (QBarSet* set, sets) {
        if (d->m_barSets.contains(set)) {
            d->m_barSets.removeOne(set);
            QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), d, SLOT(barsetChanged()));
            setsRemoved = true;
        }
    }

    if (setsRemoved) {
        emit d->restructuredBars();
    }
    return setsRemoved;
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
    return d->categoryCount();
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
void QBarSeries::setModel(QAbstractItemModel *model)
{
    Q_D(QBarSeries);
    // disconnect signals from old model
    if(d->m_model)
    {
        disconnect(d->m_model, 0, this, 0);
    }

    // set new model
    if(model)
    {
        d->m_model = model;

        // connect the signals
        connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
        connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelDataRemoved(QModelIndex,int,int)));

        if (d->m_mapper)
            d->initializeDataFromModel();
    }
    else
    {
        d->m_model = 0;
    }
}

void QBarSeries::setModelMapper(QBarModelMapper *mapper)
{
    Q_D(QBarSeries);
    // disconnect signals from old mapper
    if (d->m_mapper) {
        QObject::disconnect(d->m_mapper, 0, this, 0);
    }

    if (mapper) {
        d->m_mapper = mapper;
        // connect the signal from the mapper
        connect(d->m_mapper, SIGNAL(updated()), d, SLOT(initializeDataFromModel()));

        if (d->m_model)
            d->initializeDataFromModel();
    } else {
        d->m_mapper = 0;
    }
}

QBarModelMapper* QBarSeries::modelMapper() const
{
    Q_D(const QBarSeries);
    return d->m_mapper;
}

/*!
    Returns the bar categories of the series.
*/
QBarCategories QBarSeries::categories() const
{
    Q_D(const QBarSeries);
    return d->categories();
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

QBarSeriesPrivate::QBarSeriesPrivate(QBarSeries *q) :
    QAbstractSeriesPrivate(q),
    m_barMargin(0.05),  // Default value is 5% of category width
    m_mapper(0)
{
}

void QBarSeriesPrivate::setCategories(QBarCategories categories)
{
    m_categories = categories;
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

int QBarSeriesPrivate::categoryCount() const
{
    if (m_categories.count() > 0) {
        return m_categories.count();
    }

    // No categories defined. return count of longest set.
    int count = 0;
    for (int i=0; i<m_barSets.count(); i++) {
        if (m_barSets.at(i)->count() > count) {
            count = m_barSets.at(i)->count();
        }
    }

    return count;
}

QBarCategories QBarSeriesPrivate::categories() const
{
    if (m_categories.count() > 0) {
        return m_categories;
    }

    // No categories defined. retun list of indices.
    QBarCategories categories;

    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        categories.append(QString::number(i));
    }
    return categories;
}

void QBarSeriesPrivate::setBarMargin(qreal margin)
{
    if (margin > 1.0) {
        margin = 1.0;
    } else if (margin < 0.0) {
        margin = 0.0;
    }

    m_barMargin = margin;
    emit updatedBars();
}

qreal QBarSeriesPrivate::barMargin()
{
    return m_barMargin;
}

QBarSet* QBarSeriesPrivate::barsetAt(int index)
{
    return m_barSets.at(index);
}

QString QBarSeriesPrivate::categoryName(int category)
{
    if ((category >= 0) && (category < m_categories.count())) {
        return m_categories.at(category);
    }

    return QString::number(category);
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
            qreal temp = m_barSets.at(i)->at(j).y();
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
            qreal temp = m_barSets.at(i)->at(j).y();
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

    return m_barSets.at(set)->at(category).y();
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

    qreal value = m_barSets.at(set)->at(category).y();
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
            sum += m_barSets.at(set)->at(category).y();
    }
    return sum;
}

qreal QBarSeriesPrivate::absoluteCategorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += qAbs(m_barSets.at(set)->at(category).y());
    }
    return sum;
}

qreal QBarSeriesPrivate::maxCategorySum()
{
    qreal max = INT_MIN;
    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        qreal sum = categorySum(i);
        if (sum > max)
            max = sum;
    }
    return max;
}

void QBarSeriesPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (m_model == 0 || m_mapper == 0)
        return;

    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            if (m_mapper->orientation() == Qt::Vertical)
            {
                // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
                if ( row >= m_mapper->first() && (m_mapper->count() == - 1 || row < m_mapper->first() + m_mapper->count())) {
                    if (column >= m_mapper->mapBarBottom() && column <= m_mapper->mapBarTop())
                        barsetAt(column - m_mapper->mapBarBottom())->replace(row - m_mapper->first(), m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    //                    if (column == m_mapper->mapCategories());// TODO:
                }
            }
            else
            {
                // model update is relevant to BarSeries if the change was made to the part of the model that was mapped to BarSeries
                if (column >= m_mapper->first() && (m_mapper->count() == - 1 || column < m_mapper->first() + m_mapper->count())) {
                    if (row >= m_mapper->mapBarBottom() && row <= m_mapper->mapBarTop())
                        barsetAt(row - m_mapper->mapBarBottom())->replace(column - m_mapper->first(), m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    //                    if (row == m_mapper->mapCategories());// TODO:
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

    // create the initial bars
    m_categories.clear();
    m_barSets.clear();

    if (m_model == 0 || m_mapper == 0)
        return;

    // check if mappings are set
    if (m_mapper->mapBarBottom() == -1 || m_mapper->mapBarTop() == -1 || m_mapper->mapCategories() == -1)
        return;

    //    emit restructuredBars();
    if (m_mapper->orientation() == Qt::Vertical) {
        if (m_mapCategories >= m_model->columnCount())
            return;
        int rowCount = 0;
        if(m_mapper->count() == -1)
            rowCount = m_model->rowCount() - m_mapper->first();
        else
            rowCount = qMin(m_mapper->count(), m_model->rowCount() - m_mapper->first());
        for (int k = m_mapper->first(); k < m_mapper->first() + rowCount; k++) {
            m_categories << m_model->data(m_model->index(k, m_mapper->mapCategories()), Qt::DisplayRole).toString();
        }

        int lastAvailableBarSet = qMin(m_model->columnCount() - 1, m_mapper->mapBarTop());
        for (int i = m_mapper->mapBarBottom(); i <= lastAvailableBarSet; i++) {
//        for (int i = m_mapper->mapBarBottom(); i <= m_mapper->mapBarTop(); i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
            for(int m = m_mapper->first(); m < m_mapper->first() + rowCount; m++)
                *barSet << m_model->data(m_model->index(m, i), Qt::DisplayRole).toDouble();
            q->append(barSet);
        }
    } else {
        if (m_mapCategories >= m_model->rowCount())
            return;
        int columnCount = 0;
        if(m_mapper->count() == -1)
            columnCount = m_model->columnCount() - m_mapper->first();
        else
            columnCount = qMin(m_mapper->count(), m_model->columnCount() - m_mapper->first());
        for (int k = m_mapper->first(); k < m_mapper->first() + columnCount; k++) {
            m_categories << m_model->data(m_model->index(m_mapper->mapCategories(), k), Qt::DisplayRole).toString();
        }

        int lastAvailableBarSet = qMin(m_model->rowCount() - 1, m_mapper->mapBarTop());
        for (int i = m_mapper->mapBarBottom(); i <= lastAvailableBarSet; i++) {
//        for (int i = m_mapper->mapBarBottom(); i <= m_mapper->mapBarTop(); i++) {
            QBarSet* barSet = new QBarSet(m_model->headerData(i, Qt::Vertical, Qt::DisplayRole).toString());
            for(int m = m_mapper->first(); m < m_mapper->first() + columnCount; m++)
                *barSet << m_model->data(m_model->index(i, m), Qt::DisplayRole).toDouble();
            q->append(barSet);
        }
    }
    emit restructuredBars();
    //    emit updatedBars();
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

    qreal x = categoryCount();
    qreal y = max();
    minX = qMin(minX, x);
    minY = qMin(minY, y);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
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
