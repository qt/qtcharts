// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "declarativecategoryaxis_p.h"
#include <QtCore/QDebug>

#include <algorithm>

QT_BEGIN_NAMESPACE

/*!
    \qmltype CategoryRange
    \inqmlmodule QtCharts

    \brief Defines a range on a category axis.

    The CategoryRange type is used together with the CategoryAxis type to
    specify labeled ranges on category axes. The widths of the category ranges
    can be specified freely.

    \sa CategoryAxis
*/

/*!
    \qmlproperty int CategoryRange::endValue
    The high end of the category.
*/

/*!
    \qmlproperty string CategoryRange::label
    The label of the category.
*/

DeclarativeCategoryRange::DeclarativeCategoryRange(QObject *parent) :
    QObject(parent),
    m_endValue(0),
    m_label(QString())
{
}

void DeclarativeCategoryRange::setLabel(const QString &label)
{
    auto catAxis = qobject_cast<QCategoryAxis *>(parent());
    if (catAxis)
        catAxis->replaceLabel(m_label, label);
    m_label = label;
}

DeclarativeCategoryAxis::DeclarativeCategoryAxis(QObject *parent) :
    QCategoryAxis(parent),
    m_labelsPosition(AxisLabelsPositionCenter)
{
}

void DeclarativeCategoryAxis::classBegin()
{
}

void DeclarativeCategoryAxis::componentComplete()
{
    QList<QPair<QString, qreal> > ranges;
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeCategoryRange *>(child)) {
            DeclarativeCategoryRange *range = qobject_cast<DeclarativeCategoryRange *>(child);
            ranges.append(QPair<QString, qreal>(range->label(), range->endValue()));
        }
    }

    // Sort and append the range objects according to end value
    std::sort(ranges.begin(), ranges.end(), endValueLessThan);
    for (int i(0); i < ranges.size(); i++)
        append(ranges.at(i).first, ranges.at(i).second);
}

bool DeclarativeCategoryAxis::endValueLessThan(const QPair<QString, qreal> &value1, const QPair<QString, qreal> &value2)
{
    return value1.second < value2.second;
}

QQmlListProperty<QObject> DeclarativeCategoryAxis::axisChildren()
{
    return QQmlListProperty<QObject>(this, 0, &DeclarativeCategoryAxis::appendAxisChildren ,0,0,0);
}

void DeclarativeCategoryAxis::append(const QString &label, qreal categoryEndValue)
{
    QCategoryAxis::append(label, categoryEndValue);
}

void DeclarativeCategoryAxis::remove(const QString &label)
{
    QCategoryAxis::remove(label);
}

void DeclarativeCategoryAxis::replace(const QString &oldLabel, const QString &newLabel)
{
    QCategoryAxis::replaceLabel(oldLabel, newLabel);
}

void DeclarativeCategoryAxis::appendAxisChildren(QQmlListProperty<QObject> *list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeCategoryAxis::AxisLabelsPosition DeclarativeCategoryAxis::labelsPosition() const
{
    return (DeclarativeCategoryAxis::AxisLabelsPosition) QCategoryAxis::labelsPosition();
}

void DeclarativeCategoryAxis::setLabelsPosition(AxisLabelsPosition position)
{
    if (position != m_labelsPosition) {
        QCategoryAxis::setLabelsPosition((QCategoryAxis::AxisLabelsPosition)position);
        emit labelsPositionChanged(position);
    }
}

QT_END_NAMESPACE

#include "moc_declarativecategoryaxis_p.cpp"
