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

#include "qcategoryaxis.h"
#include "qcategoryaxis_p.h"
#include "chartcategoryaxisx_p.h"
#include "chartcategoryaxisy_p.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QCategoryAxis
    \brief The QCategoryAxis class allows putting a named ranges on the axis.
    \mainclass

    This class can be used when the underlying data needs to be given extra meaning.
    Unlike with the QBarCategoryAxis the QCategoryAxis allows the categories ranges widths to be specified freely.

    Example code on how to use QCategoryAxis.
    \code
    QChartView *chartView = new QChartView;
    QLineSeries *series = new QLineSeries;
    // ...
    chartView->chart()->addSeries(series);

    QCategoryAxis *axisX = new QCategoryAxis;
    axisX->setStartValue(15);
    axisX->append("First", 20);
    axisX->append("Second", 37);
    axisX->append("Third", 52);
    chartView->chart()->setAxisX(axisX, series);
    \endcode
*/
/*!
    \qmlclass CategoryAxis QCategoryAxis
    \inherits AbstractAxis
    \brief CategoryAxis allows putting a named ranges on the axis.

    For example:
    \table
        \row
            \o  \br
                \br
                \br
                \snippet ../demos/qmlaxes/qml/qmlaxes/View3.qml 1
            \o \inlineimage demos_qmlaxes3.png
    \endtable
*/

/*!
  \property QCategoryAxis::startValue
  Defines the low end of the first category on the axis.
*/
/*!
  \qmlproperty int CategoryAxis::startValue
  Defines the low end of the first category on the axis.
*/

/*!
    Constructs an axis object which is a child of \a parent.
*/
QCategoryAxis::QCategoryAxis(QObject *parent):
    QValueAxis(*new QCategoryAxisPrivate(this), parent)
{
}

/*!
    Destroys the object
*/
QCategoryAxis::~QCategoryAxis()
{
}

/*!
    \internal
*/
QCategoryAxis::QCategoryAxis(QCategoryAxisPrivate &d, QObject *parent): QValueAxis(d, parent)
{

}

/*!
    \qmlmethod CategoryAxis::append(string label, real endValue)
    Appends new category to the axis with an \a label. Category label has to be unique.
    Parameter \a endValue specifies the high end limit of the category.
    It has to be greater than the high end limit of the previous category.
    Otherwise the method returns without adding a new category.
*/
/*!
    Appends new category to the axis with an \a categoryLabel.
    Category label has to be unique.
    Parameter \a categoryEndValue specifies the high end limit of the category.
    It has to be greater than the high end limit of the previous category.
    Otherwise the method returns without adding a new category.
*/
void QCategoryAxis::append(const QString &categoryLabel, qreal categoryEndValue)
{
    Q_D(QCategoryAxis);

    if (!d->m_categories.contains(categoryLabel)) {
        if (d->m_categories.isEmpty()) {
            Range range(d->m_categoryMinimum, categoryEndValue);
            d->m_categoriesMap.insert(categoryLabel, range);
            d->m_categories.append(categoryLabel);
        } else if (categoryEndValue > endValue(d->m_categories.last())) {
            Range previousRange = d->m_categoriesMap.value(d->m_categories.last());
            d->m_categoriesMap.insert(categoryLabel, Range(previousRange.second, categoryEndValue));
            d->m_categories.append(categoryLabel);
        }
    }
}

/*!
    Sets \a min to be the low end limit of the first category on the axis.
    If there is already some categories added to the axis then passed value must be lower than the high end value of the already defined first category range.
    Otherwise nothing is done.
*/
void QCategoryAxis::setStartValue(qreal min)
{
    Q_D(QCategoryAxis);
    if (d->m_categories.isEmpty()) {
        d->m_categoryMinimum = min;
    } else {
        Range range = d->m_categoriesMap.value(d->m_categories.first());
        if (min < range.second)
            d->m_categoriesMap.insert(d->m_categories.first(), Range(min, range.second));
    }
}

/*!
    Returns the low end limit of the category specified by an \a categoryLabel
*/
qreal QCategoryAxis::startValue(const QString &categoryLabel) const
{
    Q_D(const QCategoryAxis);
    if (categoryLabel.isEmpty())
        return d->m_categoryMinimum;
    return d->m_categoriesMap.value(categoryLabel).first;
}

/*!
    Returns the high end limit of the interval specified by an \a categoryLabel
*/
qreal QCategoryAxis::endValue(const QString &categoryLabel) const
{
    Q_D(const QCategoryAxis);
    return d->m_categoriesMap.value(categoryLabel).second;
}

/*!
    \qmlmethod CategoryAxis::remove(string label)
    Removes a category specified by the \a label from the axis
*/
/*!
    Removes an interval specified by the \a categoryLabel from the axis
*/
void QCategoryAxis::remove(const QString &categoryLabel)
{
    Q_D(QCategoryAxis);
    int labelIndex = d->m_categories.indexOf(categoryLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_categories.removeAt(labelIndex);
        d->m_categoriesMap.remove(categoryLabel);

        // the range of the interval that follows (if exists) needs to be updated
        if (labelIndex < d->m_categories.count()) {
            QString label = d->m_categories.at(labelIndex);
            Range range = d->m_categoriesMap.value(label);

            // set the range
            if (labelIndex == 0) {
                range.first = d->m_categoryMinimum;
                d->m_categoriesMap.insert(label, range);
            } else {
                range.first = d->m_categoriesMap.value(d->m_categories.at(labelIndex - 1)).second;
                d->m_categoriesMap.insert(label, range);
            }
        }
        d->emitUpdated();
    }
}

/*!
  \qmlmethod CategoryAxis::replace(string oldLabel, string newLabel)
  Replaces \a oldLabel of an existing category with a \a newLabel.
  If the old label does not exist the method returns without making any changes.
*/
/*!
  Replaces \a oldLabel of an existing category with a \a newLabel
  If the old label does not exist the method returns without making any changes.
 */
void QCategoryAxis::replaceLabel(const QString &oldLabel, const QString &newLabel)
{
    Q_D(QCategoryAxis);
    int labelIndex = d->m_categories.indexOf(oldLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_categories.replace(labelIndex, newLabel);
        Range range = d->m_categoriesMap.value(oldLabel);
        d->m_categoriesMap.remove(oldLabel);
        d->m_categoriesMap.insert(newLabel, range);
        d->emitUpdated();
    }
}

/*!
  Returns the list of the intervals labels
 */
QStringList QCategoryAxis::categoriesLabels()
{
    Q_D(QCategoryAxis);
    return d->m_categories;
}

/*!
  Returns number of intervals.
 */
int QCategoryAxis::count() const
{
    Q_D(const QCategoryAxis);
    return d->m_categories.count();
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QCategoryAxis::type() const
{
    return QAbstractAxis::AxisTypeCategory;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCategoryAxisPrivate::QCategoryAxisPrivate(QCategoryAxis *q)
    : QValueAxisPrivate(q),
      m_categoryMinimum(0)
{

}

QCategoryAxisPrivate::~QCategoryAxisPrivate()
{

}

int QCategoryAxisPrivate::ticksCount() const
{
    return m_categories.count() + 1;
}

void QCategoryAxisPrivate::handleAxisRangeChanged(qreal min, qreal max, int count)
{
    Q_UNUSED(count);
    Q_UNUSED(min);
    Q_UNUSED(max);
}

ChartAxis *QCategoryAxisPrivate::createGraphics(ChartPresenter *presenter)
{
    Q_Q(QCategoryAxis);
    if (m_orientation == Qt::Vertical)
        return new ChartCategoryAxisY(q, presenter);
    return new ChartCategoryAxisX(q, presenter);
}

#include "moc_qcategoryaxis.cpp"
#include "moc_qcategoryaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
