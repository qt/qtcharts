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

#include "qhpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHPieModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QPieSeries and QAbstractItemModel derived model object that keeps the consecutive pie slices data in rows.
    It is possible to use both QAbstractItemModel and QPieSeries model API. QHPieModelMapper makes sure that Pie and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/

/*!
    \property QHPieModelMapper::valuesRow
    \brief Defines which row of the model is kept in sync with the values of the pie's slices

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHPieModelMapper::labelsRow
    \brief Defines which row of the model is kept in sync with the labels of the pie's slices

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHPieModelMapper::QHPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    QPieModelMapper::setOrientation(Qt::Horizontal);
}

/*!
    Returns which row of the model is kept in sync with the values of the pie's slices
*/
int QHPieModelMapper::valuesRow() const
{
    return QPieModelMapper::valuesSection();
}

/*!
    Sets the model row that is kept in sync with the pie slices values.
    Parameter \a valuesRow specifies the row of the model.
*/
void QHPieModelMapper::setValuesRow(int valuesRow)
{
    if (valuesRow != valuesSection()) {
        QPieModelMapper::setValuesSection(valuesRow);
        emit valuesRowChanged();
    }
}

/*!
    Returns which row of the model is kept in sync with the labels of the pie's slices
*/
int QHPieModelMapper::labelsRow() const
{
    return QPieModelMapper::labelsSection();
}

/*!
    Sets the model row that is kept in sync with the pie's slices labels.
    Parameter \a labelsRow specifies the row of the model.
*/
void QHPieModelMapper::setLabelsRow(int labelsRow)
{
    if (labelsRow != labelsSection()) {
        QPieModelMapper::setLabelsSection(labelsRow);
        emit labelsRowChanged();
    }
}

#include "moc_qhpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
