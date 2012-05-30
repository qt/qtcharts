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

DeclarativePieSlice::DeclarativePieSlice(QObject *parent) :
    QPieSlice(parent)
{
}

QColor DeclarativePieSlice::color()
{
    return brush().color();
}

void DeclarativePieSlice::setColor(QColor color)
{
    QBrush b = brush();
    b.setColor(color);
    setBrush(b);
}

QColor DeclarativePieSlice::borderColor()
{
    return pen().color();
}

void DeclarativePieSlice::setBorderColor(QColor color)
{
    QPen p = pen();
    p.setColor(color);
    setPen(p);
}

int DeclarativePieSlice::borderWidth()
{
    return pen().width();
}

void DeclarativePieSlice::setBorderWidth(int width)
{
    QPen p = pen();
    p.setWidth(width);
    setPen(p);
}

QColor DeclarativePieSlice::labelColor()
{
    return labelPen().color();
}

void DeclarativePieSlice::setLabelColor(QColor color)
{
    QPen p = labelPen();
    p.setColor(color);
    setLabelPen(p);
}

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
        if (qobject_cast<DeclarativePieSlice *>(child)) {
            QPieSeries::append(qobject_cast<DeclarativePieSlice *>(child));
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

DeclarativePieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice*> sliceList = slices();
    if (index < sliceList.count())
        return qobject_cast<DeclarativePieSlice *>(sliceList[index]);

    return 0;
}

DeclarativePieSlice* DeclarativePieSeries::find(QString label)
{
    foreach (QPieSlice *slice, slices()) {
        if (slice->label() == label)
            return qobject_cast<DeclarativePieSlice *>(slice);
    }
    return 0;
}

DeclarativePieSlice* DeclarativePieSeries::append(QString label, qreal value)
{
    // TODO: parameter order is wrong, switch it:
    DeclarativePieSlice *slice = new DeclarativePieSlice(this);
    slice->setLabel(label);
    slice->setValue(value);
    QPieSeries::append(slice);
    return slice;
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
