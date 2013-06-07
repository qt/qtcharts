/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qboxplotseries.h"
#include "qboxplotseries_p.h"
#include "qboxplotlegendmarker.h"
#include "qbarcategoryaxis.h"
#include "boxplotchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "qvalueaxis.h"
#include "charttheme_p.h"
#include "boxplotanimation_p.h"
#include "qchart_p.h"
#include "qboxset.h"
#include "qboxset_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBoxPlotSeries
    \brief Series for creating box-and-whiskers chart
    \mainclass

    QBoxPlotSeries represents a series of data shown as box-and-whisker bars. The purpose of this class is to act as
    a container for single box-and-whisker items. Each item is drawn to own slot. If chart includes multiple instances of
    QBoxPlotSeries then box-and-whiskers items with the same index are drawn to same slot.

    See the \l {Box and Whiskers Example} {box-and-whiskers chart example} to learn how to create a box-and-whiskers chart.
    \image examples_boxplotchart.png

    \sa QBoxSet
*/

/*!
    \qmlclass BoxPlotSeries QBoxPlotSeries
    \inherits QAbstractSeries

    BoxPlotSeries represents a series of data shown as box-and-whisker bars. The purpose of this class is to act as
    a container for single box-and-whisker items. Each item is drawn to own slot. If chart includes multiple instances of
    BoxPlotSeries then box-and-whiskers items with the same index are drawn to same slot.

    The following QML shows how to create a simple box-and-whiskers chart:
    \code
    import QtQuick 1.0
    import QtCommercial.Chart 1.1

    ChartView {
        title: "Box Plot series"
        width: 400
        height: 300
        theme: ChartView.ChartThemeBrownSand
        legend.alignment: Qt.AlignBottom

        BoxPlotSeries {
            id: plotSeries
            name: "Income"
            BoxSet { label: "Jan"; values: [3, 4, 5.1, 6.2, 8.5] }
            BoxSet { label: "Feb"; values: [5, 6, 7.5, 8.6, 11.8] }
            BoxSet { label: "Mar"; values: [3.2, 5, 5.7, 8, 9.2] }
            BoxSet { label: "Apr"; values: [3.8, 5, 6.4, 7, 8] }
            BoxSet { label: "May"; values: [4, 5, 5.2, 6, 7] }
        }
    }
    \endcode

    \beginfloatleft
    \image examples_qmlboxplot.png
    \endfloat
    \clearfloat
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
    \fn QBoxPlotSeries::hovered(bool status, QBoxSet *boxset)
    \brief Signal is emitted when there is change in hover \a status over \a boxset.
*/

/*!
    \fn QBoxPlotSeries::countChanged()
    \brief Signal is emitted when there is change in count of box-and-whiskers items in the series.
*/
/*!
    \fn virtual SeriesType QBoxPlotSeries::type() const
    \brief Returns type of series.
    \sa QAbstractSeries, SeriesType
*/
/*!
    \qmlmethod BoxPlotSeries::append(const QString label, QVariantList values)
    Appends a new box-and-whiskers set with \a label and \a values to the series.
 */
/*!
    \qmlmethod BoxPlotSeries::append(BoxSet *box)
    Appends the \a box to the series.
*/
/*!
    \qmlmethod BoxPlotSeries::insert(int index, const QString label, QVariantList values)
    Inserts a new box-and-whiskers set with \a label and \a values at the \a index position.
*/
/*!
    \qmlmethod BoxPlotSeries::remove(QBoxSet *boxset)
    Removes the \a boxset from the series.
*/
/*!
    \qmlmethod BoxPlotSeries::clear()
    Removes all boxsets from the series. Deletes removed sets.
*/

/*!
    \qmlsignal BoxPlotSeries::onClicked(BoxSet boxset);
    Signal is emitted when the user clicks the \a boxset on the chart.
*/
/*!
    \qmlsignal BoxPlotSeries::onHovered(bool status, BoxSet boxset);
    Signal is emitted when there is change in hover \a status over \a boxset.
*/
/*!
    \qmlsignal BoxPlotSeries::onCountChanged();
    Signal is emitted when there is change in count of box-and-whiskers items in the series.
*/
/*!
    \qmlsignal BoxPlotSeries::onBoxsetsAdded()
    Signal is emitted when new box-and-whiskers sets are added to the series.
 */
/*!
    \qmlsignal BoxPlotSeries::boxsetsRemoved()
    Signal is emitted when new box-and-whiskers sets are removed from the series.
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

/*!
    Sets brush for the series. Box-and-whiskers items are drawn using \a brush
*/
void QBoxPlotSeries::setBrush(const QBrush &brush)
{
    Q_D(QBoxPlotSeries);

    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->updated();
    }
}

/*!
    Returns brush of the series.
*/
QBrush QBoxPlotSeries::brush() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_brush;
}

/*!
    Sets pen for the series. Box-and-whiskers items are drawn using \a pen
*/
void QBoxPlotSeries::setPen(const QPen &pen)
{
    Q_D(QBoxPlotSeries);

    if (d->m_pen != pen) {
        d->m_pen = pen;
        emit d->updated();
    }
}

/*!
    Returns the pen of this series.
*/
QPen QBoxPlotSeries::pen() const
{
    Q_D(const QBoxPlotSeries);

    return d->m_pen;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBoxPlotSeriesPrivate::QBoxPlotSeriesPrivate(QBoxPlotSeries *q)
    : QAbstractSeriesPrivate(q),
      m_pen(QChartPrivate::defaultPen()),
      m_brush(QChartPrivate::defaultBrush())
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
    Q_UNUSED(orientation);

    return 0;
}

void QBoxPlotSeriesPrivate::populateCategories(QBarCategoryAxis *axis)
{
    QStringList categories;
    if (axis->categories().isEmpty()) {
        for (int i(1); i < m_boxSets.count() + 1; i++) {
            QBoxSet *set = m_boxSets.at(i - 1);
            if (set->label().isEmpty())
                categories << QString::number(i);
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

void QBoxPlotSeriesPrivate::initializeAnimations(QChart::AnimationOptions options)
{
    BoxPlotChartItem *item = static_cast<BoxPlotChartItem *>(m_item.data());
    Q_ASSERT(item);
    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        m_animation = new BoxPlotAnimation(item);
    else
        m_animation = 0;
    item->setAnimation(m_animation);

    QAbstractSeriesPrivate::initializeAnimations(options);
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
    if ((m_boxSets.contains(set)) || (set == 0))
        return false; // Fail if set is already in list or set is null.

    m_boxSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
    QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));

    emit restructuredBoxes(); // this notifies boxplotchartitem
    return true;
}

bool QBoxPlotSeriesPrivate::remove(QBoxSet *set)
{
    if (!m_boxSets.contains(set))
        return false; // Fail if set is not in list

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
        if ((set == 0) || (m_boxSets.contains(set)))
            return false; // Fail if any of the sets is null or is already appended.
        if (sets.count(set) != 1)
            return false; // Also fail if same set is more than once in given list.
    }

    foreach (QBoxSet *set, sets) {
        m_boxSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedLayout()), this, SIGNAL(updatedLayout()));
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBox()), this, SIGNAL(updatedBoxes()));
        QObject::connect(set->d_ptr.data(), SIGNAL(restructuredBox()), this, SIGNAL(restructuredBoxes()));
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
    if ((m_boxSets.contains(set)) || (set == 0))
        return false; // Fail if set is already in list or set is null.

    m_boxSets.insert(index, set);
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

QTCOMMERCIALCHART_END_NAMESPACE

