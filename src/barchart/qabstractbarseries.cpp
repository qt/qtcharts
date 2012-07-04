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

#include "qabstractbarseries.h"
#include "qabstractbarseries_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "domain_p.h"
#include "legendmarker_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
#include "qvaluesaxis.h"
#include "qbarcategoriesaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAbstractBarSeries
    \brief Series for creating a bar chart
    \mainclass

    QAbstractBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars to
    the position defined by data. Single bar is defined by QPointF, where x value is the x-coordinate of the bar
    and y-value is the height of the bar. The category names are ignored with this series and x-axis
    shows the x-values.

    See the \l {BarChart Example} {bar chart example} to learn how to create a simple bar chart.
    \image examples_barchart.png

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/
/*!
    \qmlclass AbstractBarSeries QAbstractBarSeries
    \inherits QAbstractSeries

    The following QML shows how to create a simple bar chart:
    \snippet ../demos/qmlchart/qml/qmlchart/View6.qml 1

    \beginfloatleft
    \image demos_qmlchart6.png
    \endfloat
    \clearfloat
*/

/*!
    \property QAbstractBarSeries::barWidth
    The width of the bars of the series. The unit of \a width is the unit of x-axis. The minimum width for bars
    is zero and negative values are treated as zero. Setting the width to zero means that width of the bar on screen
    is one pixel no matter what the scale of x-axis is. Bars wider than zero are scaled with x-axis.
    Note that with QBarSeries this value means the width of one group of bars instead of just one bar.
    \sa QBarSeries
*/
/*!
    \qmlproperty real AbstractBarSeries::barWidth
    The width of the bars of the series. The unit of width is the unit of x-axis. The minimum width for bars
    is zero and negative values are treated as zero. Setting the width to zero means that width of the bar on screen
    is one pixel no matter what the scale of x-axis is. Bars wider than zero are scaled with x-axis.
    Note that with QBarSeries this value means the width of one group of bars instead of just one bar.
*/

/*!
    \property QAbstractBarSeries::count
    Holds the number of sets in series.
*/
/*!
    \qmlproperty int AbstractBarSeries::count
    Holds the number of sets in series.
*/

/*!
    \property QAbstractBarSeries::labelsVisible
    Defines the visibility of the labels in series
*/
/*!
    \qmlproperty bool AbstractBarSeries::labelsVisible
    Defines the visibility of the labels in series
*/

/*!
    \fn void QAbstractBarSeries::clicked(int index, QBarSet *barset)
    The signal is emitted if the user clicks with a mouse on top of QBarSet \a barset.
    Clicked bar inside set is indexed by \a index
*/
/*!
    \qmlsignal AbstractBarSeries::onClicked(int index, BarSet barset)
    The signal is emitted if the user clicks with a mouse on top of BarSet.
    Clicked bar inside set is indexed by \a index
*/

/*!
    \fn void QAbstractBarSeries::hovered(bool status, QBarSet* barset)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
*/
/*!
    \qmlsignal AbstractBarSeries::onHovered(bool status, BarSet barset)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
*/

/*!
    \fn void QAbstractBarSeries::countChanged()
    This signal is emitted when barset count has been changed, for example by append or remove.
*/
/*!
    \qmlsignal AbstractBarSeries::onCountChanged()
    This signal is emitted when barset count has been changed, for example by append or remove.
*/

/*!
    \fn void QAbstractBarSeries::labelsVisibleChanged()
    This signal is emitted when labels visibility have changed.
    \sa isLabelsVisible(), setLabelsVisible()
*/

/*!
    \fn void QAbstractBarSeries::barsetsAdded(QList<QBarSet*> sets)
    This signal is emitted when \a sets have been added to the series.
    \sa append(), insert()
*/
/*!
    \qmlsignal AbstractBarSeries::onAdded(BarSet barset)
    Emitted when \a barset has been added to the series.
*/

/*!
    \fn void QAbstractBarSeries::barsetsRemoved(QList<QBarSet*> sets)
    This signal is emitted when \a sets have been removed from the series.
    \sa remove()
*/
/*!
    \qmlsignal AbstractBarSeries::onRemoved(BarSet barset)
    Emitted when \a barset has been removed from the series.
*/

/*!
    \qmlmethod BarSet AbstractBarSeries::at(int index)
    Returns bar set at \a index. Returns null if the index is not valid.
*/

/*!
    \qmlmethod BarSet AbstractBarSeries::append(string label, VariantList values)
    Adds a new bar set with \a label and \a values to \a index. Values can be a list of reals or a list of XYPoints.
    For example:
    \code
        myBarSeries.append("set 1", [0, 0.2, 0.2, 0.5, 0.4, 1.5, 0.9]);
        myBarSeries.append("set 2", [Qt.point(0, 1), Qt.point(2, 2.5), Qt.point(3.5, 2.2)]);
    \endcode
*/

/*!
    \qmlmethod BarSet AbstractBarSeries::insert(int index, string label, VariantList values)
    Inserts a new bar set with \a label and \a values to \a index. Values can be a list of reals or a list of XYPoints.
    If index is zero or smaller, the new barset is prepended. If the index is count or bigger, the new barset is
    appended.
    \sa AbstractBarSeries::append()
*/

/*!
    \qmlmethod bool AbstractBarSeries::remove(BarSet barset)
    Removes the barset from the series. Returns true if successfull, false otherwise.
*/

/*!
    \qmlmethod AbstractBarSeries::clear()
    Removes all barsets from the series.
*/

/*!
    Constructs empty QAbstractBarSeries.
    QAbstractBarSeries is QObject which is a child of a \a parent.
*/
QAbstractBarSeries::QAbstractBarSeries(QObject *parent) :
    QAbstractSeries(*new QAbstractBarSeriesPrivate(this),parent)
{
}

/*!
    Destructs abstractbarseries and owned barsets.
*/
QAbstractBarSeries::~QAbstractBarSeries()
{
    Q_D(QAbstractBarSeries);
    if(d->m_dataset){
        d->m_dataset->removeSeries(this);
    }
}

/*!
    \internal
*/
QAbstractBarSeries::QAbstractBarSeries(QAbstractBarSeriesPrivate &d, QObject *parent) :
    QAbstractSeries(d,parent)
{
}

/*!
    Sets the width of the bars of the series. The unit of \a width is the unit of x-axis. The minimum width for bars
    is zero and negative values are treated as zero. Setting the width to zero means that width of the bar on screen
    is one pixel no matter what the scale of x-axis is. Bars wider than zero are scaled with x-axis.
    Note that with \link QBarSeries \endlink this value means the width of one group of bars instead of just one bar.
*/
void QAbstractBarSeries::setBarWidth(qreal width)
{
    Q_D(QAbstractBarSeries);
    d->setBarWidth(width);
}

/*!
    Returns the width of the bars of the series.
    \sa setBarWidth()
*/
qreal QAbstractBarSeries::barWidth() const
{
    Q_D(const QAbstractBarSeries);
    return d->barWidth();
}

/*!
    Adds a set of bars to series. Takes ownership of \a set. If the set is null or is already in series, it won't be appended.
    Returns true, if appending succeeded.
*/
bool QAbstractBarSeries::append(QBarSet *set)
{
    Q_D(QAbstractBarSeries);
    bool success = d->append(set);
    if (success) {
        QList<QBarSet*> sets;
        sets.append(set);
        emit barsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesn't delete \a set.
    Returns true, if set was removed.
*/
bool QAbstractBarSeries::remove(QBarSet *set)
{
    Q_D(QAbstractBarSeries);
    bool success = d->remove(set);
    if (success) {
        QList<QBarSet*> sets;
        sets.append(set);
        emit barsetsRemoved(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
    Returns true, if all sets were appended succesfully. If any of the sets is null or is already appended to series,
    nothing is appended and function returns false. If any of the sets is in list more than once, nothing is appended
    and function returns false.
*/
bool QAbstractBarSeries::append(QList<QBarSet* > sets)
{
    Q_D(QAbstractBarSeries);
    bool success = d->append(sets);
    if (success) {
        emit barsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Insert a set of bars to series at \a index postion. Takes ownership of \a set. If the set is null or is already in series, it won't be appended.
    Returns true, if inserting succeeded.

*/
bool QAbstractBarSeries::insert(int index, QBarSet *set)
{
    Q_D(QAbstractBarSeries);
    bool success = d->insert(index, set);
    if (success) {
        QList<QBarSet*> sets;
        sets.append(set);
        emit barsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes all of the bar sets from the series
*/
void QAbstractBarSeries::clear()
{
    Q_D(QAbstractBarSeries);
    QList<QBarSet *> sets = barSets();
    bool success = d->remove(sets);
    if (success) {
        emit barsetsRemoved(sets);
        emit countChanged();
    }
}

/*!
    Returns number of sets in series.
*/
int QAbstractBarSeries::count() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_barSets.count();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QAbstractBarSeries::barSets() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_barSets;
}

/*!
    Sets the visibility of labels in series to \a visible
*/
void QAbstractBarSeries::setLabelsVisible(bool visible)
{
    Q_D(QAbstractBarSeries);
    if (d->m_labelsVisible != visible) {
        d->setLabelsVisible(visible);
        emit labelsVisibleChanged();
    }
}

/*!
    Returns the visibility of labels
*/
bool QAbstractBarSeries::isLabelsVisible() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_labelsVisible;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractBarSeriesPrivate::QAbstractBarSeriesPrivate(QAbstractBarSeries *q) :
    QAbstractSeriesPrivate(q),
    m_barWidth(0.5),  // Default value is 50% of category width
    m_labelsVisible(false),
    m_visible(true)
{
}

int QAbstractBarSeriesPrivate::categoryCount() const
{
    // No categories defined. return count of longest set.
    int count = 0;
    for (int i=0; i<m_barSets.count(); i++) {
        if (m_barSets.at(i)->count() > count) {
            count = m_barSets.at(i)->count();
        }
    }

    return count;
}

void QAbstractBarSeriesPrivate::setBarWidth(qreal width)
{
    if (width < 0.0) {
        width = 0.0;
    }
    m_barWidth = width;
    emit updatedBars();
}

qreal QAbstractBarSeriesPrivate::barWidth() const
{
    return m_barWidth;
}

QBarSet* QAbstractBarSeriesPrivate::barsetAt(int index)
{
    return m_barSets.at(index);
}

void QAbstractBarSeriesPrivate::setVisible(bool visible)
{
    m_visible = visible;
    emit updatedBars();
}

void QAbstractBarSeriesPrivate::setLabelsVisible(bool visible)
{
    m_labelsVisible = visible;
    emit labelsVisibleChanged(visible);
}

qreal QAbstractBarSeriesPrivate::min()
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

qreal QAbstractBarSeriesPrivate::max()
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

qreal QAbstractBarSeriesPrivate::valueAt(int set, int category)
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

qreal QAbstractBarSeriesPrivate::percentageAt(int set, int category)
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

qreal QAbstractBarSeriesPrivate::categorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += m_barSets.at(set)->at(category);
    }
    return sum;
}

qreal QAbstractBarSeriesPrivate::absoluteCategorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += qAbs(m_barSets.at(set)->at(category));
    }
    return sum;
}

qreal QAbstractBarSeriesPrivate::maxCategorySum()
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

qreal QAbstractBarSeriesPrivate::minX()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal min = INT_MAX;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->d_ptr.data()->m_values.at(j).x();
            if (temp < min)
                min = temp;
        }
    }
    return min;
}

qreal QAbstractBarSeriesPrivate::maxX()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal max = INT_MIN;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->d_ptr.data()->m_values.at(j).x();
            if (temp > max)
                max = temp;
        }
    }

    return max;
}


void QAbstractBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal seriesMinX = this->minX();
    qreal seriesMaxX = this->maxX();
    qreal y = max();
    minX = qMin(minX, seriesMinX - 0.5);
    minY = qMin(minY, y);
    maxX = qMax(maxX, seriesMaxX + 0.5);
    maxY = qMax(maxY, y);
    tickXCount = categoryCount()+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}

Chart* QAbstractBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QAbstractBarSeries);

    BarChartItem* bar = new BarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;

}

QList<LegendMarker*> QAbstractBarSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QAbstractBarSeries);
    QList<LegendMarker*> markers;
    foreach(QBarSet* set, q->barSets()) {
        BarLegendMarker* marker = new BarLegendMarker(q,set,legend);
        markers << marker;
    }

    return markers;
}

bool QAbstractBarSeriesPrivate::append(QBarSet *set)
{
    Q_Q(QAbstractBarSeries);
    if ((m_barSets.contains(set)) || (set == 0)) {
        // Fail if set is already in list or set is null.
        return false;
    }
    m_barSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    emit restructuredBars();      // this notifies barchartitem
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    return true;
}

bool QAbstractBarSeriesPrivate::remove(QBarSet *set)
{
    Q_Q(QAbstractBarSeries);
    if (!m_barSets.contains(set)) {
        // Fail if set is not in list
        return false;
    }
    m_barSets.removeOne(set);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    emit restructuredBars();        // this notifies barchartitem
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    return true;
}

bool QAbstractBarSeriesPrivate::append(QList<QBarSet* > sets)
{
    Q_Q(QAbstractBarSeries);
    foreach (QBarSet* set, sets) {
        if ((set == 0) || (m_barSets.contains(set))) {
            // Fail if any of the sets is null or is already appended.
            return false;
        }
        if (sets.count(set) != 1) {
            // Also fail if same set is more than once in given list.
            return false;
        }
    }

    foreach (QBarSet* set, sets) {
        m_barSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
        QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    }
    emit restructuredBars();        // this notifies barchartitem
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    return true;
}

bool QAbstractBarSeriesPrivate::remove(QList<QBarSet* > sets)
{
    Q_Q(QAbstractBarSeries);
    if (sets.count() == 0) {
        return false;
    }
    foreach (QBarSet* set, sets) {
        if ((set == 0) || (!m_barSets.contains(set))) {
            // Fail if any of the sets is null or is not in series
            return false;
        }
        if (sets.count(set) != 1) {
            // Also fail if same set is more than once in given list.
            return false;
        }
    }

    foreach (QBarSet* set, sets) {
        m_barSets.removeOne(set);
        QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
        QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    }

    emit restructuredBars();        // this notifies barchartitem
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    return true;
}

bool QAbstractBarSeriesPrivate::insert(int index, QBarSet *set)
{
    Q_Q(QAbstractBarSeries);
    if ((m_barSets.contains(set)) || (set == 0)) {
        // Fail if set is already in list or set is null.
        return false;
    }
    m_barSets.insert(index, set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    emit restructuredBars();      // this notifies barchartitem
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    return true;
}

void QAbstractBarSeriesPrivate::initializeAxisX(QAbstractAxis* axis)
{
    if(axis->type()==QAbstractAxis::AxisTypeCategories)
    {
        QBarCategoriesAxis* cataxis = qobject_cast<QBarCategoriesAxis*>(axis);
        Q_ASSERT(cataxis);
        QStringList categories;
        for (int i(1); i < categoryCount()+1; i++)
        categories << QString::number(i);
        cataxis->append(categories);
    }
}

void QAbstractBarSeriesPrivate::initializeAxisY(QAbstractAxis* axis)
{
    Q_UNUSED(axis)
}

QAbstractAxis::AxisType QAbstractBarSeriesPrivate::defaultAxisXType() const
{
    return QAbstractAxis::AxisTypeCategories;
}

QAbstractAxis::AxisType QAbstractBarSeriesPrivate::defaultAxisYType() const
{
    return QAbstractAxis::AxisTypeValues;
}

#include "moc_qabstractbarseries.cpp"
#include "moc_qabstractbarseries_p.cpp"


QTCOMMERCIALCHART_END_NAMESPACE
