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

#include "qhxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QXYSeries and QAbstractItemModel derived model object.
    It is possible to use both QAbstractItemModel and QXYSeries model API. QXYModelMapper makes sure that QXYSeries and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/

/*!
    \property QHXYModelMapper::xRow
    \brief Defines which row of the model is kept in sync with the x values of the QXYSeries
    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHXYModelMapper::yRow
    \brief Defines which row of the model is kept in sync with the  y values of the QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHXYModelMapper::QHXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Horizontal);
}

int QHXYModelMapper::xRow() const
{
    return QXYModelMapper::xSection();
}

void QHXYModelMapper::setXRow(int xRow)
{
    return QXYModelMapper::setXSection(xRow);
}

int QHXYModelMapper::yRow() const
{
    return QXYModelMapper::ySection();
}

void QHXYModelMapper::setYRow(int yRow)
{
    return QXYModelMapper::setYSection(yRow);
}

#include "moc_qhxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
