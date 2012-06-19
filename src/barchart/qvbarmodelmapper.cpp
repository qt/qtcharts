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

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QBarSeries and QAbstractItemModel derived model object.
    Model mapper maintains equal size of all the BarSets.
    Adding/removing value from the BarSet causes the the same change in the rest of the BarSets added to the same series.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmlclass VBarModelMapper
    \inherits BarModelMapper
    \mainclass

    VBarModelMapper allows you to use your own QAbstractItemModel derived model with data in columns as a data source
    for any bar series. The following QML example would create a bar series with three bar sets (assuming the model has
    at least four columns). Each bar set would contain data starting from row 1. The name of a set would be defined
    by the horizontal header (of the column).
    \code
        GroupedBarSeries {
            VBarModelMapper {
                model: myCustomModel
                firstBarSetColumn: 1
                lastBarSetColumn: 3
                first: 1
            }
        }
    \endcode
*/

/*!
    \property QVBarModelMapper::firstBarSetColumn
    \brief Defines which column of the model is used as the data source for the first bar set
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::firstBarSetColumn
    Defines which column of the model is used as the data source for the first bar set. Default value
    is: -1 (invalid mapping).
*/

/*!
    \property QVBarModelMapper::lastBarSetColumn
    \brief Defines which column of the model is used as the data source for the last bar set
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::lastBarSetColumn
    Defines which column of the model is used as the data source for the last bar set. Default
    value is: -1 (invalid mapping).
*/

/*!
    \fn void QVBarModelMapper::firstBarSetColumnChanged()
    Emitted when the firstBarSetColumn has changed.
*/

/*!
    \fn void QVBarModelMapper::lastBarSetColumnChanged()
    Emitted when the lastBarSetColumn has changed.
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
    if (firstBarSetColumn != firstBarSetSection()) {
        return QBarModelMapper::setFirstBarSetSection(firstBarSetColumn);
        emit firstBarSetColumnChanged();
    }
}

int QVBarModelMapper::lastBarSetColumn() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QVBarModelMapper::setLastBarSetColumn(int lastBarSetColumn)
{
    if (lastBarSetColumn != lastBarSetSection()) {
        return QBarModelMapper::setLastBarSetSection(lastBarSetColumn);
        emit lastBarSetColumnChanged();
    }
}

#include "moc_qvbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
