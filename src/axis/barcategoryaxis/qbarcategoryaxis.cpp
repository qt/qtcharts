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

#include "qbarcategoryaxis.h"
#include "qbarcategoryaxis_p.h"
#include "chartbarcategoryaxisx_p.h"
#include "chartbarcategoryaxisy_p.h"
#include "domain_p.h"
#include "chartdataset_p.h"
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QBarCategoryAxis
    \brief The QBarCategoryAxis class is used for manipulating chart's axis.
    \mainclass

    BarCategoryAxis can be setup to show axis line with tick marks, grid lines and shades.
    Categories are drawn between ticks. Note that you can use this also with lineseries too.
    See the \l {Line and BarChart Example} {Line and BarChart Example} to learn how to do that.

    Example code on how to use QBarCategoryAxis.
    \code
    QChartView *chartView = new QChartView;
    QBarSeries *series = new QBarSeries;
    // ...
    chartView->chart()->addSeries(series);
    chartView->chart()->createDefaultAxes();

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    QStringList categories;
    categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
    axisX->append(categories);
    chartView->chart()->setAxisX(series, axisX);
    \endcode
*/

/*!
    \qmlclass BarCategoryAxis QBarCategoryAxis
    \inherits AbstractAxis
    \brief The Axis element is used for manipulating chart's axes.

    Axis can be setup to show axis line with tick marks, grid lines and shades.
    Categories are drawn between ticks. Note that you can use this also with lineseries too.

    To access BarCategoryAxis you can use ChartView API. For example:
    \code
        ChartView {
            BarCategoryAxis {
                id: categoryAxis
                categories: ["Jan", "Feb", "Mar", "Apr", "May", "Jun" ]
            }
        // Add a few series...
        }
    \endcode
*/

/*!
  \property QBarCategoryAxis::categories
  Defines the categories of axis
*/
/*!
  \qmlproperty QStringList BarCategoryAxis::categories
  Defines the categories of axis
*/

/*!
  \property QBarCategoryAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty QString BarCategoryAxis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QBarCategoryAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty QString BarCategoryAxis::max
  Defines the maximum value on the axis.
*/


/*!
  \fn void QBarCategoryAxis::categoriesChanged()
  Axis emits signal when the categories of the axis has changed.
*/
/*!
  \fn void QBarCategoryAxis::minChanged(const QString &min)
  Axis emits signal when \a min of axis has changed.
*/
/*!
  \qmlsignal BarCategoryAxis::onMinChanged(const QString &min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QBarCategoryAxis::maxChanged(const QString &max)
  Axis emits signal when \a max of axis has changed.
*/
/*!
  \qmlsignal BarCategoryAxis::onMaxChanged(const QString &max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QBarCategoryAxis::rangeChanged(const QString &min, const QString &max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QBarCategoryAxis::QBarCategoryAxis(QObject *parent):
    QAbstractAxis(*new QBarCategoryAxisPrivate(this), parent)
{
}

/*!
    Destroys the object
*/
QBarCategoryAxis::~QBarCategoryAxis()
{
    Q_D(QBarCategoryAxis);
    if (d->m_dataset)
        d->m_dataset->removeAxis(this);
}

/*!
    \internal
*/
QBarCategoryAxis::QBarCategoryAxis(QBarCategoryAxisPrivate &d, QObject *parent)
    : QAbstractAxis(d, parent)
{

}

/*!
    Appends \a categories to axis
*/
void QBarCategoryAxis::append(const QStringList &categories)
{
    if (categories.isEmpty())
        return;

    Q_D(QBarCategoryAxis);
    if (d->m_categories.isEmpty()) {
        d->m_categories.append(categories);
        setRange(categories.first(), categories.last());
    } else {
        d->m_categories.append(categories);
        d->emitUpdated();
    }
    emit categoriesChanged();
}

/*!
    Appends \a category to axis
*/
void QBarCategoryAxis::append(const QString &category)
{
    Q_D(QBarCategoryAxis);
    if (d->m_categories.isEmpty()) {
        d->m_categories.append(category);
        setRange(category, category);
    } else {
        d->m_categories.append(category);
        d->emitUpdated();
    }
    emit categoriesChanged();
}

/*!
    Removes \a category from axis
*/
void QBarCategoryAxis::remove(const QString &category)
{
    Q_D(QBarCategoryAxis);
    if (d->m_categories.contains(category)) {
        d->m_categories.removeAt(d->m_categories.indexOf(category));
        if (!d->m_categories.isEmpty())
            setRange(d->m_categories.first(), d->m_categories.last());
        else
            setRange(QString::null, QString::null);
        emit categoriesChanged();
    }
}

/*!
    Inserts \a category to axis at \a index
*/
void QBarCategoryAxis::insert(int index, const QString &category)
{
    Q_D(QBarCategoryAxis);
    if (d->m_categories.isEmpty()) {
        d->m_categories.insert(index, category);
        setRange(category, category);
    } else {
        d->m_categories.insert(index, category);
        d->emitUpdated();
    }
    emit categoriesChanged();
}

/*!
    Replaces \a oldCategory with \a newCategory.
    If \a oldCategory does not exits on the axis nothing is done.
*/
void QBarCategoryAxis::replace(const QString &oldCategory, const QString &newCategory)
{
    Q_D(QBarCategoryAxis);
    int pos = d->m_categories.indexOf(oldCategory);
    if (pos != -1) {
        d->m_categories.replace(pos, newCategory);
        d->emitUpdated();
        emit categoriesChanged();
    }
}

/*!
  Removes all categories.
 */
void QBarCategoryAxis::clear()
{
    Q_D(QBarCategoryAxis);
    d->m_categories.clear();
    setRange(QString::null, QString::null);
    emit categoriesChanged();
}

void QBarCategoryAxis::setCategories(const QStringList &categories)
{
    Q_D(QBarCategoryAxis);
    if (d->m_categories != categories) {
        d->m_categories = categories;
        setRange(categories.first(), categories.last());
        emit categoriesChanged();
    }
}

QStringList QBarCategoryAxis::categories()
{
    Q_D(QBarCategoryAxis);
    return d->m_categories;
}

/*!
  Returns number of categories.
 */
int QBarCategoryAxis::count() const
{
    Q_D(const QBarCategoryAxis);
    return d->m_categories.count();
}

/*!
    Returns category at \a index. Index must be valid.
*/
QString QBarCategoryAxis::at(int index) const
{
    Q_D(const QBarCategoryAxis);
    return d->m_categories.at(index);
}

/*!
    Sets minimum category to \a min.
*/
void QBarCategoryAxis::setMin(const QString& min)
{
    Q_D(QBarCategoryAxis);
    setRange(min, d->m_maxCategory);
}

/*!
    Returns minimum category.
*/
QString QBarCategoryAxis::min() const
{
    Q_D(const QBarCategoryAxis);
    return d->m_minCategory;
}

/*!
    Sets maximum category to \a max.
*/
void QBarCategoryAxis::setMax(const QString& max)
{
    Q_D(QBarCategoryAxis);
    setRange(d->m_minCategory, max);
}

/*!
    Returns maximum category
*/
QString QBarCategoryAxis::max() const
{
    Q_D(const QBarCategoryAxis);
    return d->m_maxCategory;
}

/*!
    Sets range from \a minCategory to \a maxCategory
*/
void QBarCategoryAxis::setRange(const QString& minCategory, const QString& maxCategory)
{
    Q_D(QBarCategoryAxis);

    bool changed = false;

    //special case
    if (minCategory.isNull() && maxCategory.isNull()) {
        d->m_minCategory = minCategory;
        d->m_maxCategory = maxCategory;
        d->m_min = 0;
        d->m_max = 0;
        emit minChanged(minCategory);
        emit maxChanged(maxCategory);
        d->m_count = 0;
        emit rangeChanged(d->m_minCategory, d->m_maxCategory);
        d->emitUpdated();
    }

    if (d->m_categories.indexOf(d->m_maxCategory) < d->m_categories.indexOf(d->m_minCategory))
        return;

    if (!minCategory.isEmpty() && d->m_minCategory != minCategory && d->m_categories.contains(minCategory)) {
        d->m_minCategory = minCategory;
        d->m_min = d->m_categories.indexOf(d->m_minCategory) - 0.5;
        changed = true;
        emit minChanged(minCategory);
    }

    if (!maxCategory.isEmpty() && d->m_maxCategory != maxCategory && d->m_categories.contains(maxCategory)) {
        d->m_maxCategory = maxCategory;
        d->m_max = d->m_categories.indexOf(d->m_maxCategory) + 0.5;
        changed = true;
        emit maxChanged(maxCategory);
    }

    if (changed) {
        d->m_count = d->m_max - d->m_min;
        emit rangeChanged(d->m_minCategory, d->m_maxCategory);
        d->emitUpdated();
    }
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QBarCategoryAxis::type() const
{
    return AxisTypeBarCategory;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarCategoryAxisPrivate::QBarCategoryAxisPrivate(QBarCategoryAxis* q):
    QAbstractAxisPrivate(q),
    m_min(0.0),
    m_max(0.0),
    m_count(0)
{

}

QBarCategoryAxisPrivate::~QBarCategoryAxisPrivate()
{

}

void QBarCategoryAxisPrivate::setMin(const QVariant &min)
{
    setRange(min, m_maxCategory);
}

void QBarCategoryAxisPrivate::setMax(const QVariant &max)
{
    setRange(m_minCategory, max);
}

void QBarCategoryAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QBarCategoryAxis);
    QString value1 = min.toString();
    QString value2 = max.toString();
    q->setRange(value1, value2);
}

void QBarCategoryAxisPrivate::handleDomainUpdated()
{
    Q_Q(QBarCategoryAxis);
    Domain* domain = qobject_cast<Domain*>(sender());

    if (m_orientation == Qt::Horizontal) {
        m_min = domain->minX();
        m_max = domain->maxX();
    } else if (m_orientation == Qt::Vertical) {
        m_min = domain->minY();
        m_max = domain->maxY();
    }

    bool changed = false;

    int min = m_min + 0.5;
    if (min >= 0 && min < m_categories.count()) {
        QString minCategory = m_categories.at(min);
        if (m_minCategory != minCategory && !minCategory.isEmpty()) {
            m_minCategory = minCategory;
            changed = true;
            emit q->minChanged(minCategory);
        }
    }
    int max = m_max - 0.5;
    if (max >= 0 && max < m_categories.count()) {
        QString maxCategory = m_categories.at(max);
        if (m_maxCategory != maxCategory && !maxCategory.isEmpty()) {
            m_maxCategory = maxCategory;
            emit q->maxChanged(maxCategory);
        }
    }

    if (changed)
        emit q->rangeChanged(m_minCategory, m_maxCategory);
}

ChartAxis* QBarCategoryAxisPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QBarCategoryAxis);
    if (m_orientation == Qt::Vertical)
        return new ChartBarCategoryAxisY(q, presenter);
    return new ChartBarCategoryAxisX(q, presenter);
}

void QBarCategoryAxisPrivate::intializeDomain(Domain* domain)
{

    Q_Q(QBarCategoryAxis);
    if (m_max == m_min) {
        int min;
        int max;
        if (m_orientation == Qt::Vertical) {
            min = domain->minY() + 0.5;
            max = domain->maxY() - 0.5;
        } else {
            min = domain->minX() + 0.5;
            max = domain->maxX() - 0.5;
        }

        if (min > 0 && min < m_categories.count() && max > 0 && max < m_categories.count())
            q->setRange(m_categories.at(min), m_categories.at(max));
    } else {
        if (m_orientation == Qt::Vertical)
            domain->setRangeY(m_min, m_max);
        else
            domain->setRangeX(m_min, m_max);
    }
}

#include "moc_qbarcategoryaxis.cpp"
#include "moc_qbarcategoryaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
