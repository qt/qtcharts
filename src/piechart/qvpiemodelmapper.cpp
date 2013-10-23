/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qvpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVPieModelMapper
    \inmodule Qt Charts
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QPieSeries and QAbstractItemModel derived model object that keeps the consecutive pie slices data in columns.
    It is possible to use both QAbstractItemModel and QPieSeries model API. QVPieModelMapper makes sure that Pie and the model are kept in sync.
    \note Used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
#ifdef QDOC_QT5
/*!
    \qmltype VPieModelMapper
    \instantiates QVPieModelMapper
    \inqmlmodule QtCommercial.Chart

    \include /doc/src/vpiemodelmapper.qdocinc
*/
#else
/*!
    \qmlclass VPieModelMapper QVPieModelMapper

    \include ../doc/src/vpiemodelmapper.qdocinc
*/
#endif

/*!
    \property QVPieModelMapper::series
    \brief Defines the QPieSeries object that is used by the mapper.
    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty PieSeries VPieModelMapper::series
    Defines the PieSeries object that is used by the mapper. If you define the mapper element as a child for a
    PieSeries, leave this property undefined. All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QVPieModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel VPieModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model
    and expose it to QML. Note: the model has to support adding/removing rows/columns and modifying
    the data of the cells.
*/

/*!
    \property QVPieModelMapper::valuesColumn
    \brief Defines which column of the model is kept in sync with the values of the pie's slices.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VPieModelMapper::valuesColumn
    Defines which column of the model is kept in sync with the values of the pie's slices. Default value is -1 (invalid
    mapping).
*/

/*!
    \property QVPieModelMapper::labelsColumn
    \brief Defines which column of the model is kept in sync with the labels of the pie's slices.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VPieModelMapper::labelsColumn
    Defines which column of the model is kept in sync with the labels of the pie's slices. Default value is -1 (invalid
    mapping).
*/

/*!
    \property QVPieModelMapper::firstRow
    \brief Defines which row of the model contains the first slice value.

    Minimal and default value is: 0
*/
/*!
    \qmlproperty int VPieModelMapper::firstRow
    Defines which row of the model contains the first slice value.
    The default value is 0.
*/

/*!
    \property QVPieModelMapper::rowCount
    \brief Defines the number of rows of the model that are mapped as the data for QPieSeries.

    Minimal and default value is: -1 (count limited by the number of rows in the model)
*/
/*!
    \qmlproperty int VPieModelMapper::columnCount
    Defines the number of rows of the model that are mapped as the data for QPieSeries. The default value is
    -1 (count limited by the number of rows in the model)
*/

/*!
    \fn void QVPieModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QVPieModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
*/

/*!
    \fn void QVPieModelMapper::valuesColumnChanged()

    Emitted when the valuesColumn has changed.
*/

/*!
    \fn void QVPieModelMapper::labelsColumnChanged()

    Emitted when the labelsColumn has changed.
*/

/*!
    \fn void QVPieModelMapper::firstRowChanged()
    Emitted when the firstRow has changed.
*/

/*!
    \fn void QVPieModelMapper::rowCountChanged()
    Emitted when the rowCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVPieModelMapper::QVPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    QPieModelMapper::setOrientation(Qt::Vertical);
}

QAbstractItemModel *QVPieModelMapper::model() const
{
    return QPieModelMapper::model();
}

void QVPieModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QPieModelMapper::model()) {
        QPieModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QPieSeries *QVPieModelMapper::series() const
{
    return QPieModelMapper::series();
}

void QVPieModelMapper::setSeries(QPieSeries *series)
{
    if (series != QPieModelMapper::series()) {
        QPieModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

/*!
    Returns which column of the model is kept in sync with the values of the pie's slices
*/
int QVPieModelMapper::valuesColumn() const
{
    return QPieModelMapper::valuesSection();
}

/*!
    Sets the model column that is kept in sync with the pie slices values.
    Parameter \a valuesColumn specifies the row of the model.
*/
void QVPieModelMapper::setValuesColumn(int valuesColumn)
{
    if (valuesColumn != valuesSection()) {
        QPieModelMapper::setValuesSection(valuesColumn);
        emit valuesColumnChanged();
    }
}

/*!
    Returns which column of the model is kept in sync with the labels of the pie's slices
*/
int QVPieModelMapper::labelsColumn() const
{
    return QPieModelMapper::labelsSection();
}

/*!
    Sets the model column that is kept in sync with the pie's slices labels.
    Parameter \a labelsColumn specifies the row of the model.
*/
void QVPieModelMapper::setLabelsColumn(int labelsColumn)
{
    if (labelsColumn != labelsSection()) {
        QPieModelMapper::setLabelsSection(labelsColumn);
        emit labelsColumnChanged();
    }
}

int QVPieModelMapper::firstRow() const
{
    return first();
}

void QVPieModelMapper::setFirstRow(int firstRow)
{
    if (firstRow != first()) {
        setFirst(firstRow);
        emit firstRowChanged();
    }
}

int QVPieModelMapper::rowCount() const
{
    return count();
}

void QVPieModelMapper::setRowCount(int rowCount)
{
    if (rowCount != count()) {
        setCount(rowCount);
        emit rowCountChanged();
    }
}

#include "moc_qvpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
