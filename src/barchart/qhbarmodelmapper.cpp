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
    Model mapper maintains equal size of all the BarSets.
    Adding/removing value from the BarSet causes the the same change in the rest of the BarSets added to the same series.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmlclass HBarModelMapper
    \inherits BarModelMapper
    \mainclass

    HBarModelMapper allows you to use your own QAbstractItemModel derived model with data in rows as a data source
    for any bar series. The following QML example would create a bar series with three bar sets (assuming the model has
    at least four rows). Each bar set would contain data starting from column 1. The name of a set would be defined
    by the vertical header (of the row).
    \code
        BarSeries {
            HBarModelMapper {
                model: myCustomModel
                firstBarSetRow: 1
                lastBarSetRow: 3
                firstColumn: 1
            }
        }
    \endcode
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
    \property QHBarModelMapper::firstColumn
    \brief Defines which column of the model contains the first values of the QBarSets in the series.
    Minimal and default value is: 0
*/
/*!
    \qmlproperty int BarModelMapper::firstColumn
    Defines which column of the model contains the first values of the QBarSets in the series.
    The default value is 0.
*/

/*!
    \property QHBarModelMapper::columnCount
    \brief Defines the number of rows of the model that are mapped as the data for QBarSeries
    Minimal and default value is: -1 (count limited by the number of rows in the model)
*/
/*!
    \qmlproperty int BarModelMapper::columnCount
    Defines the number of rows of the model that are mapped as the data for QBarSeries. The default value is
    -1 (count limited by the number of rows in the model)
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
    \fn void QHBarModelMapper::firstColumnChanged()
    Emitted when the firstColumn has changed.
*/

/*!
    \fn void QHBarModelMapper::columnCountChanged()
    Emitted when the columnCount has changed.
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
        QBarModelMapper::setFirstBarSetSection(firstBarSetRow);
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
        QBarModelMapper::setLastBarSetSection(lastBarSetRow);
        emit lastBarSetRowChanged();
    }
}

int QHBarModelMapper::firstColumn() const
{
    return QBarModelMapper::first();
}

void QHBarModelMapper::setFirstColumn(int firstColumn)
{
    if (firstColumn != first()) {
        QBarModelMapper::setFirst(firstColumn);
        emit firstColumnChanged();
    }
}

int QHBarModelMapper::columnCount() const
{
    return QBarModelMapper::count();
}

void QHBarModelMapper::setColumnCount(int columnCount)
{
    if (columnCount != count()) {
        QBarModelMapper::setCount(columnCount);
        emit firstColumnChanged();
    }
}

#include "moc_qhbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
