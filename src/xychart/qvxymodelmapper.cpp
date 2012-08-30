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
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QXYSeries and QAbstractItemModel derived model object.
    It is possible to use both QAbstractItemModel and QXYSeries model API. QXYModelMapper makes sure that QXYSeries and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmlclass VXYModelMapper QHXYModelMapper

    VXYModelMapper allows you to use your own QAbstractItemModel derived model with data in columns as a data source
    for XYSeries based series. It is possible to use both QAbstractItemModel and XYSeries data API to manipulate data.
    VYModelMapper keeps the series and the model in sync.
*/

/*!
    \property QVXYModelMapper::series
    \brief Defines the QXYSeries object that is used by the mapper.
    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty XYSeries VXYModelMapper::series
    Defines the XYSeries object that is used by the mapper. All the data in the series is discarded when it is set to
    the mapper. When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QVXYModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel VXYModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model and expose it to
    QML as shown in \l {QML Custom Model} demo application. NOTE: the model has to support adding/removing rows/columns
    and modifying the data of the cells.
*/

/*!
    \property QVXYModelMapper::xColumn
    \brief Defines which column of the model is kept in sync with the x values of QXYSeries
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VXYModelMapper::xColumn
    Defines which column of the model is kept in sync with the x values of the series. Default value is -1 (invalid
    mapping).
*/

/*!
    \property QVXYModelMapper::yColumn
    \brief Defines which column of the model is kept in sync with the y values of QXYSeries
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VXYModelMapper::yColumn
    Defines which column of the model is kept in sync with the y values of the series. Default value is -1 (invalid
    mapping).
*/

/*!
    \property QVXYModelMapper::firstRow
    \brief Defines which row of the model contains the data for the first point of the series.
    Minimal and default value is: 0
*/
/*!
    \qmlproperty int VXYModelMapper::firstRow
    Defines which row of the model contains the data for the first point of the series.
    The default value is 0.
*/

/*!
    \property QVXYModelMapper::rowCount
    \brief Defines the number of rows of the model that are mapped as the data for series
    Minimal and default value is: -1 (count limited by the number of rows in the model)
*/
/*!
    \qmlproperty int VXYModelMapper::columnCount
    Defines the number of rows of the model that are mapped as the data for series. The default value is
    -1 (count limited by the number of rows in the model).
*/

/*!
    \fn void QVXYModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QVXYModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
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
    \fn void QVXYModelMapper::firstRowChanged()
    Emitted when the firstRow has changed.
*/

/*!
    \fn void QVXYModelMapper::rowCountChanged()
    Emitted when the rowCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVXYModelMapper::QVXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Vertical);
}

QAbstractItemModel* QVXYModelMapper::model() const
{
    return QXYModelMapper::model();
}

void QVXYModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QXYModelMapper::model()) {
        QXYModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QXYSeries* QVXYModelMapper::series() const
{
    return QXYModelMapper::series();
}

void QVXYModelMapper::setSeries(QXYSeries *series)
{
    if (series != QXYModelMapper::series()) {
        QXYModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

int QVXYModelMapper::xColumn() const
{
    return QXYModelMapper::xSection();
}

void QVXYModelMapper::setXColumn(int xColumn)
{
    if (xColumn != xSection()) {
        QXYModelMapper::setXSection(xColumn);
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
        QXYModelMapper::setYSection(yColumn);
        emit yColumnChanged();
    }
}

int QVXYModelMapper::firstRow() const
{
    return first();
}

void QVXYModelMapper::setFirstRow(int firstRow)
{
    if (firstRow != first()) {
        setFirst(firstRow);
        emit firstRowChanged();
    }
}

int QVXYModelMapper::rowCount() const
{
    return count();
}

void QVXYModelMapper::setRowCount(int rowCount)
{
    if (rowCount != count()) {
        setCount(rowCount);
        emit firstRowChanged();
    }
}

#include "moc_qvxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
