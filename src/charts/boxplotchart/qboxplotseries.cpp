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

#include <QtCharts/QBoxPlotSeries>
#include <private/qboxplotseries_p.h>
#include <QtCharts/QBoxPlotLegendMarker>
#include <QtCharts/QBarCategoryAxis>
#include <private/boxplotchartitem_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>
#include <private/charttheme_p.h>
#include <private/boxplotanimation_p.h>
#include <private/qchart_p.h>
#include <QtCharts/QBoxSet>
#include <private/qboxset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QBoxPlotSeries
    \inmodule Qt Charts
    \brief Series for creating box-and-whiskers chart.

    QBoxPlotSeries represents a series of data shown as box-and-whisker bars. The purpose of this
    class is to act as a container for single box-and-whisker items. Each item is drawn to own slot.
    If chart includes multiple instances of QBoxPlotSeries then box-and-whiskers items with the same
    index are drawn to same slot.

    \note The slot, each item in QBoxPlotSeries is drawn, represents a category in QBarCategoryAxis.
    The category labels have to be unique. If same category label is defined for several
    box-and-whisker items only the first one is drawn.

    See the \l {Box and Whiskers Example} {box-and-whiskers chart example} to learn how to create a
    box-and-whiskers chart.
    \image examples_boxplotchart.png

    \sa QBoxSet, QBarCategoryAxis
*/
/*!
    \fn QBoxPlotSeries::boxsetsAdded(QList<QBoxSet *> sets)
    \brief Signal is emitted when a new \a sets of box-and-whiskers data is added to the series.
*/
/*!
    \fn QBoxPlotSeries::boxsetsRemoved(QList<QBoxSet *> sets)
    \brief Signal is emitted when \a sets of box-and-whiskers data is removed from the series.
*/
/*!
    \fn QBoxPlotSeries::clicked(QBoxSet *boxset)
    \brief Signal is emitted when the user clicks the \a boxset on the chart.
*/
/*!
    \fn QBoxPlotSeries::pressed(QBoxSet *boxset)
    \brief Signal is emitted when the user presses the \a boxset on the chart.
*/
/*!
    \fn QBoxPlotSeries::released(QBoxSet *boxset)
    \brief Signal is emitted when the user releases the \a boxset on the chart.
*/
/*!
    \fn QBoxPlotSeries::doubleClicked(QBoxSet *boxset)
    \brief Signal is emitted when the user doubleclicks the \a boxset on the chart.
*/
/*!
    \fn QBoxPlotSeries::hovered(bool status, QBoxSet *boxset)
    \brief Signal is emitted when there is change in hover \a status over \a boxset.
*/
/*!
    \fn QBoxPlotSeries::countChanged()
    \brief Signal is emitted when there is change in count of box-and-whiskers items in the series.
*/
/*!
    \property QBoxPlotSeries::boxOutlineVisible
    \brief This property configures the visibility of the middle box outline.
*/
/*!
    \property QBoxPlotSeries::boxWidth
    \brief This property configures the width of the box-and-whiskers item. The value signifies the relative
    width of the box-and-whiskers item inside its own slot. The value can between 0.0 and 1.0. Negative values
    are clamped to 0.0 and values over 1.0 are clamped to 1.0.
*/
/*!
    \property QBoxPlotSeries::pen
    \brief This property configures the pen of the box-and-whiskers items.
*/
/*!
    \property QBoxPlotSeries::brush
    \brief This property configures the brush of the box-and-whiskers items.
*/
/*!
    \property QBoxPlotSeries::count
    \brief The count of sets in series.
*/

/*!
    \qmlproperty QString BoxPlotSeries::brushFilename
    The name of the file used as a brush for the series.
*/

/*!
    \fn void QBoxPlotSeries::boxOutlineVisibilityChanged()
    Signal is emitted when the middle box outline visibility is changed.
*/
/*!
    \fn void QBoxPlotSeries::boxWidthChanged()
    Signal is emitted when the width of the box-and-whiskers item is changed.
*/
/*!
    \fn void QBoxPlotSeries::penChanged()
    This signal is emitted when the pen of the box-and-whiskers has changed.
    \sa brush
*/
/*!
    \fn void QBoxPlotSeries::brushChanged()
    This signal is emitted when the brush of the box-and-whiskers has changed.
    \sa brush
*/
/*!
    \fn virtual SeriesType QBoxPlotSeries::type() const
    \brief Returns type of series.
    \sa QAbstractSeries, SeriesType
*/

/*!
    Constructs empty QBoxPlotSeries.
    QBoxPlotSeries is QObject which is a child of a \a parent.
*/
QBoxPlotSeries::QBoxPlotSeries(QObject *parent)
    : QAbstractSeries(*new QBoxPlotSeriesPrivate(this), parent)
{
}

/*!
    Destructor. Removes series from chart.
*/
QBoxPlotSeries::~QBoxPlotSeries()
{
    Q_D(QBoxPlotSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Adds a single box and whiskers set to series. Takes ownership of the \a set. If the set is null or is already in series, it won't be appended.
    Returns true, if appending succeeded.
*/
bool QBoxPlotSeries::append(QBoxSet *set)
{
    Q_D(QBoxPlotSeries);

    bool success = d->append(set);
    if (success) {
        QList<QBoxSet *> sets;
        sets.append(set);
        set->setParent(this);
        emit boxsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes boxset from the series. Deletes the \a set and returns true if successful.
*/
bool QBoxPlotSeries::remove(QBoxSet *set)
{
    Q_D(QBoxPlotSeries);
    bool success = d->remove(set);
    if (success) {
        QList<QBoxSet *> sets;
        sets.append(set);
        set->setParent(0);
        emit boxsetsRemoved(sets);
        emit countChanged();
        delete set;
        set = 0;
    }
    return success;
}

/*!
    Takes a single \a set from the series. Does not delete the boxset object.

    NOTE: The series remains as the boxset's parent object. You must set the
    parent object to take full ownership.

    Returns true if take was successful.
*/
bool QBoxPlotSeries::take(QBoxSet *set)
{
    Q_D(QBoxPlotSeries);

    bool success = d->remove(set);
    if (success) {
        QList<QBoxSet *> sets;
        sets.append(set);
        emit boxsetsRemoved(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Adds a list of boxsets to series. Takes ownership of the \a sets.
    Returns true, if all sets were appended successfully. If any of the sets is null or is already appended to series,
    nothing is appended and function returns false. If any of the sets is in list more than once, nothing is appended
    and function returns false.
*/
bool QBoxPlotSeries::append(QList<QBoxSet *> sets)
{
    Q_D(QBoxPlotSeries);
    bool success = d->append(sets);
    if (success) {
        emit boxsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Insert a box-and-whiskers set to the series at \a index postion. Takes ownership of the \a set. If the set is null or
    is already in series, it won't be appended. Returns true, if inserting succeeded.

*/
bool QBoxPlotSeries::insert(int index, QBoxSet *set)
{
    Q_D(QBoxPlotSeries);
    bool success = d->insert(index, set);
    if (success) {
        QList<QBoxSet *> sets;
        sets.append(set);
        emit boxsetsAdded(sets);
        emit countChanged();
    }
    return success;
}

/*!
    Removes all boxsets from the series. Deletes removed sets.
*/
void QBoxPlotSeries::clear()
{
    Q_D(QBoxPlotSeries);
    QList<QBoxSet *> sets = boxSets();
    bool success = d->remove(sets);
    if (success) {
        emit boxsetsRemoved(sets);
        emit countChanged();
        foreach (QBoxSet *set, sets)
            delete set;
    }
}

/*!
    Returns number of sets in series.
*/
int QBoxPlotSeries::count() const
{
    Q_D(const QBoxPlotSeries);
    return d->m_boxSets.count();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBoxSet *> QBoxPlotSeries::boxSets() const
{
    Q_D(const QBoxPlotSeries);
    return d->m_boxSets;
}

/*
    Returns QAbstractSeries::SeriesTypeBoxPlot.
*/
QAbstractSeries::SeriesType QBoxPlotSeries::type() const
{
    return QAbstractSeries::SeriesTypeBoxPlot;
}

void QBoxPlotSeries::setBoxOutlineVisible(bool visible)
{
    Q_D(QBoxPlotSeries);

    if (d->m_boxOutlineVisible != visible) {
        d->m_boxOutlineVisible = visible;
        emit d->updated();
        emit boxOutlineVisibilityChanged();
    }
}

bool QBoxPlotSeries::boxOutlineVisible()
{
    Q_D(QBoxPlotSeries);

    return d->m_boxOutlineVisible;
}

void QBoxPlotSeries::setBoxWidth(qreal width)
{
    Q_D(QBoxPlotSeries);

    if (width != d->m_boxWidth) {
        if (width < 0.0)
            width = 0.0;
        if (width > 1.0)
            width = 1.0;
        d->m_boxWidth = width;
        emit d->updatedLayout();
        emit boxWidthChanged();
    }
}

qreal QBoxPlotSeries::boxWidth()
{
    Q_D(QBoxPlotSeries);

    return d->m_boxWidth;
}

void QBoxPlotSeries::setBrush(const QBrush &brush)
{
    Q_D(QBoxPlotSeries);

    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
        emit brushChanged();
    }
}

QBrush QBoxPlotSeries::brush() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_brush;
}

void QBoxPlotSeries::setPen(const QPen &pen)
{
    Q_D(QBoxPlotSeries);

    if (d->m_pen != pen) {
        d->m_pen = pen;
        emit d->updated();
        emit penChanged();
    }
}

QPen QBoxPlotSeries::pen() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_pen;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxPlotSeriesPrivate::QBoxPlotSeriesPrivate(QBoxPlotSeries *q)
    : QAbstractSeriesPrivate(q),
      m_pen(QChartPrivate::defaultPen()),
      m_brush(QChartPrivate::defaultBrush()),
      m_boxOutlineVisible(true),
      m_boxWidth(0.5)
{
}

QBoxPlotSeriesPrivate::~QBoxPlotSeriesPrivate()
{
    disconnect(this, 0, 0, 0);
}

void QBoxPlotSeriesPrivate::initializeDomain()
{
    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    qreal x = m_boxSets.count();
    minX = qMin(minX, qreal(-0.5));
    minY = qMin(minY, min());
    maxX = qMax(maxX, x - qreal(0.5));
    maxY = qMax(maxY, max());

    domain()->setRange(minX, maxX, minY, maxY);
}

void QBoxPlotSeriesPrivate::initializeAxes()
{
    foreach (QAbstractAxis* axis, m_axes) {
        if (axis->type() == QAbstractAxis::AxisTypeBarCategory) {
            if (axis->orientation() == Qt::Horizontal)
                populateCategories(qobject_cast<QBarCategoryAxis *>(axis));
        }
    }
}

QAbstractAxis::AxisType QBoxPlotSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    if (orientation == Qt::Horizontal)
        return QAbstractAxis::AxisTypeBarCategory;

    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis* QBoxPlotSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    if (defaultAxisType(orientation) == QAbstractAxis::AxisTypeBarCategory)
        return new QBarCategoryAxis;
    else
        return new QValueAxis;
}

void QBoxPlotSeriesPrivate::populateCategories(QBarCategoryAxis *axis)
{
    QStringList categories;
    if (axis->categories().isEmpty()) {
        for (int i(1); i < m_boxSets.count() + 1; i++) {
            QBoxSet *set = m_boxSets.at(i - 1);
            if (set->label().isEmpty())
                categories << presenter()->numberToString(i);
            else
                categories << set->label();
        }
        axis->append(categories);
    }
}

void QBoxPlotSeriesPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QBoxPlotSeries);

    BoxPlotChartItem *boxPlot = new BoxPlotChartItem(q, parent);
    m_item.reset(boxPlot);
    QAbstractSeriesPrivate::initializeGraphics(parent);

    if (m_chart) {
        connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*)), this, SLOT(handleSeriesChange(QAbstractSeries*)) );
        connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), this, SLOT(handleSeriesRemove(QAbstractSeries*)) );

        QList<QAbstractSeries *> serieses = m_chart->series();

        // Tries to find this series from the Chart's list of series and deduce the index
        int index = 0;
        foreach (QAbstractSeries *s, serieses) {
            if (s->type() == QAbstractSeries::SeriesTypeBoxPlot) {
                if (q == static_cast<QBoxPlotSeries *>(s)) {
                    boxPlot->m_seriesIndex = index;
                    m_index = index;
                }
                index++;
            }
        }
        boxPlot->m_seriesCount = index;
    }

    // Make BoxPlotChartItem to instantiate box & whisker items
    boxPlot->handleDataStructureChanged();
}

void QBoxPlotSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QBoxPlotSeries);

    const QList<QGradient> gradients = theme->seriesGradients();

    if (forced || QChartPrivate::defaultBrush() == m_brush) {
        QColor brushColor = ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.5);
        q->setBrush(brushColor);
    }

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen = theme->outlinePen();
        pen.setCosmetic(true);
        q->setPen(pen);
    }
}

void QBoxPlotSeriesPrivate::initializeAnimations(QChart::AnimationOptions options, int duration,
                                                 QEasingCurve &curve)
{
    BoxPlotChartItem *item = static_cast<BoxPlotChartItem *>(m_item.data());
    Q_ASSERT(item);
    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        m_animation = new BoxPlotAnimation(item, duration, curve);
    else
        m_animation = 0;
    item->setAnimation(m_animation);

    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);

    // Make BoxPlotChartItem to instantiate box & whisker items
    item->handleDataStructureChanged();
}

QList<QLegendMarker*> QBoxPlotSeriesPrivate::createLegendMarkers(QLegend *legend)
{
    Q_Q(QBoxPlotSeries);
    QList<QLegendMarker *> list;
    return list << new QBoxPlotLegendMarker(q, legend);
}

void QBoxPlotSeriesPrivate::handleSeriesRemove(QAbstractSeries *series)
{
    Q_Q(QBoxPlotSeries);

    QBoxPlotSeries *removedSeries = static_cast<QBoxPlotSeries *>(series);

    if (q == removedSeries && m_animation) {
        m_animation->stopAll();
        QObject::disconnect(m_chart->d_ptr->m_dataset, 0, removedSeries->d_func(), 0);
    }

    // Test if series removed is me, then don't do anything
    if (q != removedSeries) {
        BoxPlotChartItem *item = static_cast<BoxPlotChartItem *>(m_item.data());
        if (item) {
            item->m_seriesCount = item->m_seriesCount - 1;
            if (removedSeries->d_func()->m_index < m_index) {
                m_index--;
                item->m_seriesIndex = m_index;
            }

            item->handleDataStructureChanged();
        }
    }
}

void QBoxPlotSeriesPrivate::handleSeriesChange(QAbstractSeries *series)
{
    Q_UNUSED(series);

    Q_Q(QBoxPlotSeries);

    BoxPlotChartItem *boxPlot = static_cast<BoxPlotChartItem *>(m_item.data());

    if (m_chart) {
        QList<QAbstractSeries *> serieses = m_chart->series();

        // Tries to find this series from the Chart's list of series and deduce the index
        int index = 0;
        foreach (QAbstractSeries *s, serieses) {
            if (s->type() == QAbstractSeries::SeriesTypeBoxPlot) {
                if (q == static_cast<QBoxPlotSeries *>(s)) {
                    boxPlot->m_seriesIndex = index;
                    m_index = index;
                }
                index++;
            }
        }
        boxPlot->m_seriesCount = index;
    }

    boxPlot->handleDataStructureChanged();
}

bool QBoxPlotSeriesPrivate::append(QBoxSet *set)
{
    if (m_boxSets.contains(set) || (set == 0) || set->d_ptr->m_series)
        return false; // Fail if set is already in list or set is null.

    m_boxSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));
    set->d_ptr->m_series = this;

    emit restructuredBoxes(); // this notifies boxplotchartitem
    return true;
}

bool QBoxPlotSeriesPrivate::remove(QBoxSet *set)
{
    if (!m_boxSets.contains(set))
        return false; // Fail if set is not in list

    set->d_ptr->m_series = 0;
    m_boxSets.removeOne(set);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
    QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));

    emit restructuredBoxes(); // this notifies boxplotchartitem
    return true;
}

bool QBoxPlotSeriesPrivate::append(QList<QBoxSet *> sets)
{
    foreach (QBoxSet *set, sets) {
        if ((set == 0) || m_boxSets.contains(set) || set->d_ptr->m_series)
            return false; // Fail if any of the sets is null or is already appended.
        if (sets.count(set) != 1)
            return false; // Also fail if same set is more than once in given list.
    }

    foreach (QBoxSet *set, sets) {
        m_boxSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
        QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));
        set->d_ptr->m_series = this;
    }

    emit restructuredBoxes(); // this notifies boxplotchartitem
    return true;
}

bool QBoxPlotSeriesPrivate::remove(QList<QBoxSet *> sets)
{
    if (sets.count() == 0)
        return false;

    foreach (QBoxSet *set, sets) {
        if ((set == 0) || (!m_boxSets.contains(set)))
            return false; // Fail if any of the sets is null or is not in series
        if (sets.count(set) != 1)
            return false; // Also fail if same set is more than once in given list.
    }

    foreach (QBoxSet *set, sets) {
        set->d_ptr->m_series = 0;
        m_boxSets.removeOne(set);
        QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
        QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
        QObject::disconnect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));
    }

    emit restructuredBoxes();        // this notifies boxplotchartitem

    return true;
}

bool QBoxPlotSeriesPrivate::insert(int index, QBoxSet *set)
{
    if ((m_boxSets.contains(set)) || (set == 0) || set->d_ptr->m_series)
        return false; // Fail if set is already in list or set is null.

    m_boxSets.insert(index, set);
    set->d_ptr->m_series = this;
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));

    emit restructuredBoxes();      // this notifies boxplotchartitem
    return true;
}

QBoxSet *QBoxPlotSeriesPrivate::boxSetAt(int index)
{
    return m_boxSets.at(index);
}

qreal QBoxPlotSeriesPrivate::min()
{
    if (m_boxSets.count() <= 0)
        return 0;

    qreal min = m_boxSets.at(0)->at(0);

    foreach (QBoxSet *set, m_boxSets) {
        for (int i = 0; i < 5; i++) {
            if (set->at(i) < min)
                min = set->at(i);
        }
    }

    return min;
}

qreal QBoxPlotSeriesPrivate::max()
{
    if (m_boxSets.count() <= 0)
        return 0;

    qreal max = m_boxSets.at(0)->at(0);

    foreach (QBoxSet *set, m_boxSets) {
        for (int i = 0; i < 5; i++) {
            if (set->at(i) > max)
                max = set->at(i);
        }
    }

    return max;
}

#include "moc_qboxplotseries.cpp"
#include "moc_qboxplotseries_p.cpp"

QT_CHARTS_END_NAMESPACE

