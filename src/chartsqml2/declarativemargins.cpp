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

#include "declarativemargins.h"
#include <QtCore/QDataStream>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \qmltype Margins
    \inqmlmodule QtCharts

    \brief Type is used to define margins.

    Uncreatable type that is used to define top, bottom, left and right margins.
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

#include "moc_declarativemargins.cpp"

QT_CHARTS_END_NAMESPACE
