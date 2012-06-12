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

#include "declarativepieseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include <qdeclarativelist.h>
#include <QVPieModelMapper>
#include <QHPieModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \qmlclass PieSeries DeclarativePieSeries

    \section1 Example Usage

    \beginfloatleft
    \image demos_qmlchart1.png
    \endfloat
    \clearfloat

    The following QML shows how to create a simple pie chart.

    \snippet ../demos/qmlchart/qml/qmlchart/View1.qml 1
*/

/*!
    \qmlproperty real PieSeries::horizontalPosition
    \brief Defines the horizontal position of the pie.

    The value is a relative value to the chart rectangle where:

    \list
    \o 0.0 is the absolute left.
    \o 1.0 is the absolute right.
    \endlist

    Default value is 0.5 (center).

    \sa verticalPosition
*/

/*!
    \qmlproperty real PieSeries::verticalPosition
    \brief Defines the vertical position of the pie.

    The value is a relative value to the chart rectangle where:

    \list
    \o 0.0 is the absolute top.
    \o 1.0 is the absolute bottom.
    \endlist

    Default value is 0.5 (center).

    \sa horizontalPosition
*/

DeclarativePieSeries::DeclarativePieSeries(QObject *parent) :
    QPieSeries(parent)
{
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<QPieSlice *>(child)) {
            QPieSeries::append(qobject_cast<QPieSlice *>(child));
        } else if(qobject_cast<QVPieModelMapper *>(child)) {
            QVPieModelMapper *mapper = qobject_cast<QVPieModelMapper *>(child);
            mapper->setSeries(this);
        } else if(qobject_cast<QHPieModelMapper *>(child)) {
            QHPieModelMapper *mapper = qobject_cast<QHPieModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativePieSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativePieSeries::appendSeriesChildren);
}

void DeclarativePieSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

QPieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice*> sliceList = slices();
    if (index < sliceList.count())
        return sliceList[index];

    return 0;
}

QPieSlice* DeclarativePieSeries::find(QString label)
{
    foreach (QPieSlice *slice, slices()) {
        if (slice->label() == label)
            return slice;
    }
    return 0;
}

QPieSlice* DeclarativePieSeries::append(QString label, qreal value)
{
    // TODO: parameter order is wrong, switch it:
    QPieSlice *slice = new QPieSlice(this);
    slice->setLabel(label);
    slice->setValue(value);
    QPieSeries::append(slice);
    return slice;
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
