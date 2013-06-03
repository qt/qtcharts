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

#include "declarativebarseries.h"
#include "declarativeboxplotseries.h"
#include "qboxset.h"
#include "qvboxplotmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeBoxSet::DeclarativeBoxSet(const QString label, QObject *parent)
    : QBoxSet(label, parent)
{
    connect(this, SIGNAL(valuesChanged()), this, SIGNAL(changedValues()));
    connect(this, SIGNAL(valueChanged(int)), this, SIGNAL(changedValue(int)));
}

QVariantList DeclarativeBoxSet::values()
{
    QVariantList values;
    for (int i(0); i < 5; i++)
        values.append(QVariant(QBoxSet::at(i)));
    return values;
}

void DeclarativeBoxSet::setValues(QVariantList values)
{
    for (int i(0); i < values.count(); i++) {
        if (values.at(i).canConvert(QVariant::Double))
            QBoxSet::append(values[i].toDouble());
    }
}

// =====================================================

DeclarativeBoxPlotSeries::DeclarativeBoxPlotSeries(QDeclarativeItem *parent) :
    QBoxPlotSeries(parent),
    m_axes(new DeclarativeAxes(this))
{
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
    connect(this, SIGNAL(hovered(bool, QBoxSet*)), this, SLOT(onHovered(bool, QBoxSet*)));
    connect(this, SIGNAL(clicked(QBoxSet*)), this, SLOT(onClicked(QBoxSet*)));
}

void DeclarativeBoxPlotSeries::classBegin()
{
}

void DeclarativeBoxPlotSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeBoxSet *>(child)) {
            QBoxPlotSeries::append(qobject_cast<DeclarativeBoxSet *>(child));
        } else if (qobject_cast<QVBoxPlotModelMapper *>(child)) {
            QVBoxPlotModelMapper *mapper = qobject_cast<QVBoxPlotModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDeclarativeListProperty<QObject> DeclarativeBoxPlotSeries::seriesChildren()
{
    return QDeclarativeListProperty<QObject>(this, 0, &DeclarativeBoxPlotSeries::appendSeriesChildren);
}

void DeclarativeBoxPlotSeries::appendSeriesChildren(QDeclarativeListProperty<QObject> *list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

DeclarativeBoxSet *DeclarativeBoxPlotSeries::at(int index)
{
    QList<QBoxSet *> setList = boxSets();
    if (index >= 0 && index < setList.count())
        return qobject_cast<DeclarativeBoxSet *>(setList[index]);

    return 0;
}

DeclarativeBoxSet *DeclarativeBoxPlotSeries::insert(int index, const QString label, QVariantList values)
{
    DeclarativeBoxSet *barset = new DeclarativeBoxSet(label, this);
    barset->setValues(values);
    if (QBoxPlotSeries::insert(index, barset))
        return barset;
    delete barset;
    return 0;
}

void DeclarativeBoxPlotSeries::onHovered(bool status, QBoxSet *boxset)
{
    emit hovered(status, qobject_cast<DeclarativeBoxSet *>(boxset));
}

void DeclarativeBoxPlotSeries::onClicked(QBoxSet *boxset)
{
    emit clicked(qobject_cast<DeclarativeBoxSet *>(boxset));
}

#include "moc_declarativeboxplotseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
