/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "declarativemargins_p.h"
#include <QtCore/QDataStream>
#include <QtCore/QDebug>

QT_BEGIN_NAMESPACE

/*!
    \qmltype Margins
    \inqmlmodule QtCharts

    \brief Defines margins between the edge of the chart rectangle and the plot
    area.

    An uncreatable type that is used to define the top, bottom, left, and right
    margins. The margins are used for drawing the title, axes, and legend.

    \sa {ChartView::margins}{ChartView.margins}
*/

/*!
    \qmlproperty int Margins::top
    The top margin.
*/

/*!
    \qmlproperty int Margins::bottom
    The bottom margin.
*/

/*!
    \qmlproperty int Margins::left
    The left margin.
*/

/*!
    \qmlproperty int Margins::right
    The right margin.
*/

DeclarativeMargins::DeclarativeMargins(QObject *parent) :
    QObject(parent)
{
    QMargins::setTop(0);
    QMargins::setBottom(0);
    QMargins::setLeft(0);
    QMargins::setRight(0);
}

void DeclarativeMargins::setTop(int top)
{
    if (top < 0) {
        qWarning() << "Cannot set top margin to a negative value:" << top;
    } else {
        if (top != QMargins::top()) {
            QMargins::setTop(top);
            emit topChanged(QMargins::top(), QMargins::bottom(), QMargins::left(), QMargins::right());
        }
    }
}

void DeclarativeMargins::setBottom(int bottom)
{
    if (bottom < 0) {
        qWarning() << "Cannot set bottom margin to a negative value:" << bottom;
    } else {
        if (bottom != QMargins::bottom()) {
            QMargins::setBottom(bottom);
            emit bottomChanged(QMargins::top(), QMargins::bottom(), QMargins::left(), QMargins::right());
        }
    }
}

void DeclarativeMargins::setLeft(int left)
{
    if (left < 0) {
        qWarning() << "Cannot set left margin to a negative value:" << left;
    } else {
        if (left != QMargins::left()) {
            QMargins::setLeft(left);
            emit leftChanged(QMargins::top(), QMargins::bottom(), QMargins::left(), QMargins::right());
        }
    }
}

void DeclarativeMargins::setRight(int right)
{
    if (right < 0) {
        qWarning() << "Cannot set left margin to a negative value:" << right;
    } else {
        if (right != QMargins::right()) {
            QMargins::setRight(right);
            emit rightChanged(QMargins::top(), QMargins::bottom(), QMargins::left(), QMargins::right());
        }
    }
}

QT_END_NAMESPACE

#include "moc_declarativemargins_p.cpp"
