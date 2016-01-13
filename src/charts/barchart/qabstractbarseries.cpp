/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QAbstractBarSeries>
#include <private/qabstractbarseries_p.h>
#include <QtCharts/QBarSet>
#include <private/qbarset_p.h>
#include <private/abstractdomain_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarLegendMarker>
#include <private/baranimation_p.h>
#include <private/abstractbarchartitem_p.h>
#include <private/qchart_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAbstractBarSeries
    \inmodule Qt Charts
    \brief Series for creating a bar chart.

    QAbstractBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars to
    the position defined by data. Single bar is defined by QPointF, where x value is the x-coordinate of the bar
    and y-value is the height of the bar. The category names are ignored with this series and x-axis
    shows the x-values.

    See the \l {BarChart Example} {bar chart example} to learn how to create a simple bar chart.
    \image examples_barchart.png

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/
/*!
    \qmltype AbstractBarSeries
    \instantiates QAbstractBarSeries
    \inqmlmodule QtCharts

    \inherits AbstractSeries

    \brief Series type for creating a bar chart.

    The following QML shows how to create a simple bar chart:
    \snippet qmlchart/qml/qmlchart/View6.qml 1

    \beginfloatleft
    \image examples_qmlchart6.png
    \endfloat
    \clearfloat
*/

/*!
    \qmlproperty AbstractAxis AbstractBarSeries::axisX
    The x axis used for the series. If you leave both axisX and axisXTop undefined, a BarCategoriesAxis is created for
    the series.
    \sa axisXTop
*/

/*!
    \qmlproperty AbstractAxis AbstractBarSeries::axisY
    The y axis used for the series. If you leave both axisY and axisYRight undefined, a ValueAxis is created for
    the series.
    \sa axisYRight
*/

/*!
    \qmlproperty AbstractAxis AbstractBarSeries::axisXTop
    The x axis used for the series, drawn on top of the chart view. Note that you can only provide either axisX or
    axisXTop, but not both.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis AbstractBarSeries::axisYRight
    The y axis used for the series, drawn to the right on the chart view. Note that you can only provide either axisY
    or axisYRight, but not both.
    \sa axisY
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
    \property QAbstractBarSeries::labelsFormat
    The \a format used for showing labels in series.

    QAbstractBarSeries supports the following format tag:
    \table
      \row
        \li @value      \li The value of the bar
    \endtable

    For example, the following usage of the format tags would produce labels that show the value
    followed by unit ('u'):
    \code
    series->setLabelsFormat("@value u");
    \endcode

    By default, the labels shows the value of the bar. For percent bar series '%' is added after
    the value. The labels are shown on the plot area, labels on the edge of the plot area are cut.
    If the bars are close to each other the labels may overlap.

    \sa QAbstractBarSeries::labelsVisible, QAbstractBarSeries::labelsPosition
*/
/*!
    \qmlproperty string AbstractBarSeries::labelsFormat
    The format used for showing labels in series.

    \sa QAbstractBarSeries::labelsFormat, labelsVisible, labelsPosition
*/
/*!
    \fn void QAbstractBarSeries::labelsFormatChanged(const QString &format)
    Signal is emitted when the \a format of data value labels is changed.
*/
/*!
    \qmlsignal XYSeries::onLabelsFormatChanged(string format)
    Signal is emitted when the \a format of data value labels is changed.
*/

/*!
 \enum QAbstractBarSeries::LabelsPosition

 This enum describes the position of the data value labels.

 \value LabelsCenter Label is in the center of the bar.
 \value LabelsInsideEnd Label is inside the bar at the high end of it.
 \value LabelsInsideBase Label is inside the bar at the low end of it.
 \value LabelsOutsideEnd Label is outside the bar at the high end of it.
 */

/*!
    \property QAbstractBarSeries::labelsPosition
    Defines the \a position of value labels.

    \sa QAbstractBarSeries::labelsVisible, QAbstractBarSeries::labelsFormat
*/
/*!
    \qmlproperty string AbstractBarSeries::labelsPosition
    Defines the \a position of value labels.

    \sa labelsVisible, labelsFormat
*/
/*!
    \fn void QAbstractBarSeries::labelsPositionChanged(QAbstractBarSeries::LabelsPosition position)
    Signal is emitted when the \a position of value labels is changed.
*/
/*!
    \qmlsignal AbstractBarSeries::onLabelsPositionChanged(LabelsPosition position)
    Signal is emitted when the \a position of value labels is changed.
*/

/*!
    \property QAbstractBarSeries::labelsAngle
    The angle of the value labels in degrees.
*/
/*!
    \qmlproperty qreal QAbstractBarSeries::labelsAngle
    The angle of the value labels in degrees.
*/
/*!
    \fn void QAbstractBarSeries::labelsAngleChanged(qreal angle)
    Signal is emitted when the \a angle of the value labels is changed.
*/
/*!
    \qmlsignal AbstractBarSeries::onLabelsAngleChanged(qreal angle)
    Signal is emitted when the \a angle of the value labels is changed.
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
    \fn void QAbstractBarSeries::pressed(int index, QBarSet *barset)
    The signal is emitted if the user presses with a mouse on top of QBarSet \a barset.
    Pressed bar inside set is indexed by \a index
*/
/*!
    \qmlsignal AbstractBarSeries::onPressed(int index, BarSet barset)
    The signal is emitted if the user presses with a mouse on top of BarSet.
    Pressed bar inside set is indexed by \a index
*/

/*!
    \fn void QAbstractBarSeries::released(int index, QBarSet *barset)
    The signal is emitted if the user releases with a mouse on top of QBarSet \a barset.
    Released bar inside set is indexed by \a index
*/
/*!
    \qmlsignal AbstractBarSeries::onReleased(int index, BarSet barset)
    The signal is emitted if the user releases with a mouse on top of BarSet.
    Released bar inside set is indexed by \a index
*/

/*!
    \fn void QAbstractBarSeries::doubleClicked(int index, QBarSet *barset)
    The signal is emitted if the user doubleclicks with a mouse on top of QBarSet \a barset.
    DoubleClicked bar inside set is indexed by \a index
*/
/*!
    \qmlsignal AbstractBarSeries::onDoubleClicked(int index, BarSet barset)
    The signal is emitted if the user doubleclicks with a mouse on top of BarSet.
    Doubleclicked bar inside set is indexed by \a index
*/

/*!
    \fn void QAbstractBarSeries::hovered(bool status, int index, QBarSet* barset)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
    Hovered bar inside the set is indexed by \a index.
*/
/*!
    \qmlsignal AbstractBarSeries::onHovered(bool status, int index, BarSet barset)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
    Hovered bar inside the set is indexed by \a index.
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
    \qmlsignal AbstractBarSeries::onBarsetsAdded(BarSet barset)
    Emitted when \a barset has been added to the series.
*/

/*!
    \fn void QAbstractBarSeries::barsetsRemoved(QList<QBarSet*> sets)
    This signal is emitted when \a sets have been removed from the series.
    \sa remove()
*/
/*!
    \qmlsignal AbstractBarSeries::onBarsetsRemoved(BarSet barset)
    Emitted when \a barset has been removed from the series.
*/

/*!
    \qmlmethod BarSet AbstractBarSeries::at(int index)
    Returns bar set at \a index. Returns null if the index is not valid.
*/

/*!
    \qmlmethod BarSet AbstractBarSeries::append(string label, VariantList values)
    Adds a new bar set with \a label and \a values to \a index. Values is a list of reals.
    For example:
    \code
        myBarSeries.append("set 1", [0, 0.2, 0.2, 0.5, 0.4, 1.5, 0.9]);
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
    Removes the barset from the series. Returns true if successful, false otherwise.
*/

/*!
    \qmlmethod AbstractBarSeries::clear()
    Removes all barsets from the series.
*/

/*!
    Destructs abstractbarseries and owned barsets.
*/
QAbstractBarSeries::~QAbstractBarSeries()
{

}

/*!
    \internal
*/
QAbstractBarSeries::QAbstractBarSeries(QAbstractBarSeriesPrivate &o, QObject *parent)
    : QAbstractSeries(o, parent)
{
    Q_D(QAbstractSeries);
    QObject::connect(this, SIGNAL(countChanged()), d, SIGNAL(countChanged()));
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
        QList<QBarSet *> sets;
        sets.append(set);
        set->setParent(this);
        emit barsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes barset from series. Releases ownership of \a set. Deletes the set, if remove
    was successful.
    Returns true, if set was removed.
*/
bool QAbstractBarSeries::remove(QBarSet *set)
{
    Q_D(QAbstractBarSeries);
    bool success = d->remove(set);
    if (success) {
        QList<QBarSet *> sets;
        sets.append(set);
        set->setParent(0);
        emit barsetsRemoved(sets);
        emit countChanged();
        delete set;
        set = 0;
    }
    return success;
}

/*!
    Takes a single \a set from the series. Does not delete the barset object.

    NOTE: The series remains as the barset's parent object. You must set the
    parent object to take full ownership.

    Returns true if take was successful.
*/
bool QAbstractBarSeries::take(QBarSet *set)
{
    Q_D(QAbstractBarSeries);
    bool success = d->remove(set);
    if (success) {
        QList<QBarSet *> sets;
        sets.append(set);
        emit barsetsRemoved(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
    Returns true, if all sets were appended successfully. If any of the sets is null or is already appended to series,
    nothing is appended and function returns false. If any of the sets is in list more than once, nothing is appended
    and function returns false.
*/
bool QAbstractBarSeries::append(QList<QBarSet *> sets)
{
    Q_D(QAbstractBarSeries);
    bool success = d->append(sets);
    if (success) {
        foreach (QBarSet *set, sets)
            set->setParent(this);
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
        QList<QBarSet *> sets;
        sets.append(set);
        emit barsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes all barsets from the series. Deletes removed sets.
*/
void QAbstractBarSeries::clear()
{
    Q_D(QAbstractBarSeries);
    QList<QBarSet *> sets = barSets();
    bool success = d->remove(sets);
    if (success) {
        emit barsetsRemoved(sets);
        emit countChanged();
        foreach (QBarSet *set, sets)
            delete set;
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
QList<QBarSet *> QAbstractBarSeries::barSets() const
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

void QAbstractBarSeries::setLabelsFormat(const QString &format)
{
    Q_D(QAbstractBarSeries);
    if (d->m_labelsFormat != format) {
        d->m_labelsFormat = format;
        emit labelsFormatChanged(format);
    }
}

QString QAbstractBarSeries::labelsFormat() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_labelsFormat;
}

void QAbstractBarSeries::setLabelsAngle(qreal angle)
{
    Q_D(QAbstractBarSeries);
    if (d->m_labelsAngle != angle) {
        d->m_labelsAngle = angle;
        emit labelsAngleChanged(angle);
    }
}

qreal QAbstractBarSeries::labelsAngle() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_labelsAngle;
}

void QAbstractBarSeries::setLabelsPosition(QAbstractBarSeries::LabelsPosition position)
{
    Q_D(QAbstractBarSeries);
    if (d->m_labelsPosition != position) {
        d->m_labelsPosition = position;
        emit labelsPositionChanged(position);
    }
}

QAbstractBarSeries::LabelsPosition QAbstractBarSeries::labelsPosition() const
{
    Q_D(const QAbstractBarSeries);
    return d->m_labelsPosition;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractBarSeriesPrivate::QAbstractBarSeriesPrivate(QAbstractBarSeries *q) :
    QAbstractSeriesPrivate(q),
    m_barWidth(0.5),  // Default value is 50% of category width
    m_labelsVisible(false),
    m_visible(true),
    m_blockBarUpdate(false),
    m_labelsFormat(),
    m_labelsPosition(QAbstractBarSeries::LabelsCenter),
    m_labelsAngle(0)
{
}

int QAbstractBarSeriesPrivate::categoryCount() const
{
    // No categories defined. return count of longest set.
    int count = 0;
    for (int i = 0; i < m_barSets.count(); i++) {
        if (m_barSets.at(i)->count() > count)
            count = m_barSets.at(i)->count();
    }

    return count;
}

void QAbstractBarSeriesPrivate::setBarWidth(qreal width)
{
    if (width < 0.0)
        width = 0.0;
    m_barWidth = width;
    emit updatedLayout();
}

qreal QAbstractBarSeriesPrivate::barWidth() const
{
    return m_barWidth;
}

QBarSet *QAbstractBarSeriesPrivate::barsetAt(int index)
{
    return m_barSets.at(index);
}

void QAbstractBarSeriesPrivate::setVisible(bool visible)
{
    m_visible = visible;
    emit visibleChanged();
}

void QAbstractBarSeriesPrivate::setLabelsVisible(bool visible)
{
    m_labelsVisible = visible;
    emit labelsVisibleChanged(visible);
}

qreal QAbstractBarSeriesPrivate::min()
{
    if (m_barSets.count() <= 0)
        return 0;

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
    if (m_barSets.count() <= 0)
        return 0;

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
    if ((set < 0) || (set >= m_barSets.count()))
        return 0; // No set, no value.
    else if ((category < 0) || (category >= m_barSets.at(set)->count()))
        return 0; // No category, no value.

    return m_barSets.at(set)->at(category);
}

qreal QAbstractBarSeriesPrivate::percentageAt(int set, int category)
{
    if ((set < 0) || (set >= m_barSets.count()))
        return 0; // No set, no value.
    else if ((category < 0) || (category >= m_barSets.at(set)->count()))
        return 0; // No category, no value.

    qreal value = m_barSets.at(set)->at(category);
    qreal sum = categorySum(category);
    if (qFuzzyCompare(sum, 0))
        return 0;

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
    if (m_barSets.count() <= 0)
        return 0;

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
    if (m_barSets.count() <= 0)
        return 0;

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

qreal QAbstractBarSeriesPrivate::categoryTop(int category)
{
    // Returns top (sum of all positive values) of category.
    // Returns 0, if all values are negative
    qreal top(0);
    int count = m_barSets.count();
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count()) {
            qreal temp = m_barSets.at(set)->at(category);
            if (temp > 0) {
                top += temp;
            }
        }
    }
    return top;
}

qreal QAbstractBarSeriesPrivate::categoryBottom(int category)
{
    // Returns bottom (sum of all negative values) of category
    // Returns 0, if all values are positive
    qreal bottom(0);
    int count = m_barSets.count();
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count()) {
            qreal temp = m_barSets.at(set)->at(category);
            if (temp < 0) {
                bottom += temp;
            }
        }
    }
    return bottom;
}

qreal QAbstractBarSeriesPrivate::top()
{
    // Returns top of all categories
    qreal top(0);
    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        qreal temp = categoryTop(i);
        if (temp > top)
            top = temp;
    }
    return top;
}

qreal QAbstractBarSeriesPrivate::bottom()
{
    // Returns bottom of all categories
    qreal bottom(0);
    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        qreal temp = categoryBottom(i);
        if (temp < bottom)
            bottom = temp;
    }
    return bottom;
}

bool QAbstractBarSeriesPrivate::blockBarUpdate()
{
    return m_blockBarUpdate;
}

qreal QAbstractBarSeriesPrivate::labelsAngle() const
{
    return m_labelsAngle;
}

void QAbstractBarSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal seriesMinX = this->minX();
    qreal seriesMaxX = this->maxX();
    qreal y = max();
    minX = qMin(minX, seriesMinX - (qreal)0.5);
    minY = qMin(minY, y);
    maxX = qMax(maxX, seriesMaxX + (qreal)0.5);
    maxY = qMax(maxY, y);

    domain()->setRange(minX, maxX, minY, maxY);
}

QList<QLegendMarker*> QAbstractBarSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QAbstractBarSeries);
    QList<QLegendMarker*> markers;

    foreach(QBarSet* set, q->barSets()) {
        QBarLegendMarker* marker = new QBarLegendMarker(q,set,legend);
        markers << marker;
    }
    return markers;
}


bool QAbstractBarSeriesPrivate::append(QBarSet *set)
{
    if ((m_barSets.contains(set)) || (set == 0))
        return false; // Fail if set is already in list or set is null.

    m_barSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));

    emit restructuredBars(); // this notifies barchartitem
    return true;
}

bool QAbstractBarSeriesPrivate::remove(QBarSet *set)
{
    if (!m_barSets.contains(set))
        return false; // Fail if set is not in list

    m_barSets.removeOne(set);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));

    emit restructuredBars(); // this notifies barchartitem
    return true;
}

bool QAbstractBarSeriesPrivate::append(QList<QBarSet * > sets)
{
    foreach (QBarSet *set, sets) {
        if ((set == 0) || (m_barSets.contains(set)))
            return false; // Fail if any of the sets is null or is already appended.
        if (sets.count(set) != 1)
            return false; // Also fail if same set is more than once in given list.
    }

    foreach (QBarSet *set, sets) {
        m_barSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
        QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    }

    emit restructuredBars(); // this notifies barchartitem
    return true;
}

bool QAbstractBarSeriesPrivate::remove(QList<QBarSet * > sets)
{
    if (sets.count() == 0)
        return false;

    foreach (QBarSet *set, sets) {
        if ((set == 0) || (!m_barSets.contains(set)))
            return false; // Fail if any of the sets is null or is not in series
        if (sets.count(set) != 1)
            return false; // Also fail if same set is more than once in given list.
    }

    foreach (QBarSet *set, sets) {
        m_barSets.removeOne(set);
        QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
        QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
        QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));
    }

    emit restructuredBars();        // this notifies barchartitem

    return true;
}

bool QAbstractBarSeriesPrivate::insert(int index, QBarSet *set)
{
    if ((m_barSets.contains(set)) || (set == 0))
        return false; // Fail if set is already in list or set is null.

    m_barSets.insert(index, set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SIGNAL(updatedBars()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBars()), this, SIGNAL(restructuredBars()));

    emit restructuredBars();      // this notifies barchartitem
    return true;
}

void QAbstractBarSeriesPrivate::initializeAxes()
{
    Q_Q(QAbstractBarSeries);

    foreach(QAbstractAxis* axis, m_axes) {

        if (axis->type() == QAbstractAxis::AxisTypeBarCategory) {
            switch (q->type()) {
            case QAbstractSeries::SeriesTypeHorizontalBar:
            case QAbstractSeries::SeriesTypeHorizontalPercentBar:
            case QAbstractSeries::SeriesTypeHorizontalStackedBar:
                if (axis->orientation() == Qt::Vertical)
                populateCategories(qobject_cast<QBarCategoryAxis *>(axis));
            break;
            case QAbstractSeries::SeriesTypeBar:
            case QAbstractSeries::SeriesTypePercentBar:
            case QAbstractSeries::SeriesTypeStackedBar:
            case QAbstractSeries::SeriesTypeBoxPlot:
                if (axis->orientation() == Qt::Horizontal)
                    populateCategories(qobject_cast<QBarCategoryAxis *>(axis));
            break;
            default:
                qWarning() << "Unexpected series type";
            break;
            }
        }
    }
}

QAbstractAxis::AxisType QAbstractBarSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_Q(const QAbstractBarSeries);

    switch (q->type()) {
    case QAbstractSeries::SeriesTypeHorizontalBar:
    case QAbstractSeries::SeriesTypeHorizontalPercentBar:
    case QAbstractSeries::SeriesTypeHorizontalStackedBar:
        if (orientation == Qt::Vertical)
            return QAbstractAxis::AxisTypeBarCategory;
        break;
    case QAbstractSeries::SeriesTypeBar:
    case QAbstractSeries::SeriesTypePercentBar:
    case QAbstractSeries::SeriesTypeStackedBar:
    case QAbstractSeries::SeriesTypeBoxPlot:
        if (orientation == Qt::Horizontal)
            return QAbstractAxis::AxisTypeBarCategory;
        break;
    default:
        qWarning() << "Unexpected series type";
        break;
    }
    return QAbstractAxis::AxisTypeValue;

}

void QAbstractBarSeriesPrivate::populateCategories(QBarCategoryAxis *axis)
{
    QStringList categories;
    if (axis->categories().isEmpty()) {
        for (int i(1); i < categoryCount() + 1; i++)
            categories << presenter()->numberToString(i);
        axis->append(categories);
    }
}

QAbstractAxis* QAbstractBarSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    if (defaultAxisType(orientation) == QAbstractAxis::AxisTypeBarCategory)
        return new QBarCategoryAxis;
    else
        return new QValueAxis;
}

void QAbstractBarSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    m_blockBarUpdate = true; // Ensures that the bars are not updated before the theme is ready

    const QList<QGradient> gradients = theme->seriesGradients();

    qreal takeAtPos = 0.5;
    qreal step = 0.2;
    if (m_barSets.count() > 1) {
        step = 1.0 / (qreal) m_barSets.count();
        if (m_barSets.count() % gradients.count())
        step *= gradients.count();
        else
        step *= (gradients.count() - 1);
    }

    for (int i(0); i < m_barSets.count(); i++) {
        int colorIndex = (index + i) % gradients.count();
        if (i > 0 && i %gradients.count() == 0) {
            // There is no dedicated base color for each sets, generate more colors
            takeAtPos += step;
            if (takeAtPos == 1.0)
            takeAtPos += step;
            takeAtPos -= (int) takeAtPos;
        }
        if (forced || QChartPrivate::defaultBrush() == m_barSets.at(i)->d_ptr->m_brush)
            m_barSets.at(i)->setBrush(ChartThemeManager::colorAt(gradients.at(colorIndex), takeAtPos));

        // Pick label color from the opposite end of the gradient.
        // 0.3 as a boundary seems to work well.
        if (forced || QChartPrivate::defaultBrush() == m_barSets.at(i)->d_ptr->m_labelBrush) {
            if (takeAtPos < 0.3)
                m_barSets.at(i)->setLabelBrush(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 1));
            else
                m_barSets.at(i)->setLabelBrush(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0));
        }
        if (forced || QChartPrivate::defaultPen() == m_barSets.at(i)->d_ptr->m_pen) {
            QColor c = ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.0);
            m_barSets.at(i)->setPen(c);
        }
    }
    m_blockBarUpdate = false;
    emit updatedBars();
}

void QAbstractBarSeriesPrivate::initializeAnimations(QChart::AnimationOptions options, int duration,
                                                     QEasingCurve &curve)
{
    AbstractBarChartItem *bar = static_cast<AbstractBarChartItem *>(m_item.data());
    Q_ASSERT(bar);
    if (bar->animation())
        bar->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        bar->setAnimation(new BarAnimation(bar, duration, curve));
    else
        bar->setAnimation(0);
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

#include "moc_qabstractbarseries.cpp"
#include "moc_qabstractbarseries_p.cpp"

QT_CHARTS_END_NAMESPACE
