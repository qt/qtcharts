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

#include "qvbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVBarModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

/*!
    \property QVBarModelMapper::firstBarSetColumn
    \brief Defines which column of the model is used as the data source for the first bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QVBarModelMapper::lastBarSetColumn
    \brief Defines which column of the model is used as the data source for the last bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVBarModelMapper::QVBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Vertical);
}

int QVBarModelMapper::firstBarSetColumn() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QVBarModelMapper::setFirstBarSetColumn(int firstBarSetColumn)
{
    return QBarModelMapper::setFirstBarSetSection(firstBarSetColumn);
}

int QVBarModelMapper::lastBarSetColumn() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QVBarModelMapper::setLastBarSetColumn(int lastBarSetColumn)
{
    return QBarModelMapper::setLastBarSetSection(lastBarSetColumn);
}

#include "moc_qvbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
