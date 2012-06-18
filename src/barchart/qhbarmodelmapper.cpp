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

#include "qhbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHBarModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QBarSeries and QAbstractItemModel derived model object.
    Curently it is NOT possible to use both QAbstractItemModel and QBarSeries model API.
    When the series is set to the mapper the QBarSeries and QBarSet API that affect the data (append, setValue, remove) should not be used.
    The model and the QBarSeries won't be kept in sync. Model API should be used to insert,remove,modify BarSets.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/

/*!
    \property QHBarModelMapper::firstBarSetRow
    \brief Defines which column of the model is used as the data source for the first bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHBarModelMapper::lastBarSetRow
    \brief Defines which column of the model is used as the data source for the last bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    \fn void QHBarModelMapper::firstBarSetRowChanged()

    Emitted when the firstBarSetRow has changed.
*/

/*!
    \fn void QHBarModelMapper::lastBarSetRowChanged()

    Emitted when the lastBarSetRow has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHBarModelMapper::QHBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Horizontal);
}

int QHBarModelMapper::firstBarSetRow() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QHBarModelMapper::setFirstBarSetRow(int firstBarSetRow)
{
    if (firstBarSetRow != firstBarSetSection()) {
        return QBarModelMapper::setFirstBarSetSection(firstBarSetRow);
        emit firstBarSetRowChanged();
    }
}

int QHBarModelMapper::lastBarSetRow() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QHBarModelMapper::setLastBarSetRow(int lastBarSetRow)
{
    if (lastBarSetRow != lastBarSetSection()) {
        return QBarModelMapper::setLastBarSetSection(lastBarSetRow);
        emit lastBarSetRowChanged();
    }
}

#include "moc_qhbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
