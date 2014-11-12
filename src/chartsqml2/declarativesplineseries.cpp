/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "declarativesplineseries.h"

QT_CHARTS_BEGIN_NAMESPACE

DeclarativeSplineSeries::DeclarativeSplineSeries(QObject *parent) :
    QSplineSeries(parent),
    m_axes(new DeclarativeAxes(this))
{
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisXChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisYChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SIGNAL(axisXTopChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SIGNAL(axisYRightChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisXChanged(QAbstractAxis*)), this, SIGNAL(axisAngularChanged(QAbstractAxis*)));
    connect(m_axes, SIGNAL(axisYChanged(QAbstractAxis*)), this, SIGNAL(axisRadialChanged(QAbstractAxis*)));
    connect(this, SIGNAL(pointAdded(int)), this, SLOT(handleCountChanged(int)));
    connect(this, SIGNAL(pointRemoved(int)), this, SLOT(handleCountChanged(int)));
}

void DeclarativeSplineSeries::handleCountChanged(int index)
{
    Q_UNUSED(index)
    emit countChanged(points().count());
}

qreal DeclarativeSplineSeries::width() const
{
    return pen().widthF();
}

void DeclarativeSplineSeries::setWidth(qreal width)
{
    if (width != pen().widthF()) {
        QPen p = pen();
        p.setWidthF(width);
        setPen(p);
        emit widthChanged(width);
    }
}

Qt::PenStyle DeclarativeSplineSeries::style() const
{
    return pen().style();
}

void DeclarativeSplineSeries::setStyle(Qt::PenStyle style)
{
    if (style != pen().style()) {
        QPen p = pen();
        p.setStyle(style);
        setPen(p);
        emit styleChanged(style);
    }
}

Qt::PenCapStyle DeclarativeSplineSeries::capStyle() const
{
    return pen().capStyle();
}

void DeclarativeSplineSeries::setCapStyle(Qt::PenCapStyle capStyle)
{
    if (capStyle != pen().capStyle()) {
        QPen p = pen();
        p.setCapStyle(capStyle);
        setPen(p);
        emit capStyleChanged(capStyle);
    }
}

QQmlListProperty<QObject> DeclarativeSplineSeries::declarativeChildren()
{
    return QQmlListProperty<QObject>(this, 0, &appendDeclarativeChildren ,0,0,0);
}

void DeclarativeSplineSeries::appendDeclarativeChildren(QQmlListProperty<QObject> *list, QObject *element)
{
    Q_UNUSED(list)
    Q_UNUSED(element)
    // Empty implementation, children are parsed in componentComplete
}

#include "moc_declarativesplineseries.cpp"

QT_CHARTS_END_NAMESPACE
