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

#include "qvxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QXYSeries and QAbstractItemModel derived model object.
    It is possible to use both QAbstractItemModel and QXYSeries model API. QXYModelMapper makes sure that QXYSeries and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/

/*!
    \property QVXYModelMapper::xColumn
    \brief Defines which column of the model is kept in sync with the x values of QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QVXYModelMapper::yColumn
    \brief Defines which column of the model is kept in sync with the y values of QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    \fn void QVXYModelMapper::xColumnChanged()

    Emitted when the xColumn has changed.
*/

/*!
    \fn void QVXYModelMapper::yColumnChanged()

    Emitted when the yColumn has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVXYModelMapper::QVXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Vertical);
}

int QVXYModelMapper::xColumn() const
{
    return QXYModelMapper::xSection();
}

void QVXYModelMapper::setXColumn(int xColumn)
{
    if (xColumn != xSection()) {
        return QXYModelMapper::setXSection(xColumn);
        emit xColumnChanged();
    }
}

int QVXYModelMapper::yColumn() const
{
    return QXYModelMapper::ySection();
}

void QVXYModelMapper::setYColumn(int yColumn)
{
    if (yColumn != ySection()) {
        return QXYModelMapper::setYSection(yColumn);
        emit yColumnChanged();
    }
}

#include "moc_qvxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
