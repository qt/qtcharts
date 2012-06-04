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

#include "qvpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVPieModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Vertical model mapper is used to create a connection between QPieSeries and QAbstractItemModel derived model object that keeps the consecutive pie slices data in columns.
    It is possible to use both QAbstractItemModel and QPieSeries model API. QVPieModelMapper makes sure that Pie and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/

/*!
    \property QVPieModelMapper::valuesColumn
    \brief Defines which column of the model is kept in sync with the values of the pie's slices

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QVPieModelMapper::labelsColumn
    \brief Defines which column of the model is kept in sync with the labels of the pie's slices

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVPieModelMapper::QVPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    QPieModelMapper::setOrientation(Qt::Vertical);
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
    QPieModelMapper::setValuesSection(valuesColumn);
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
    QPieModelMapper::setLabelsSection(labelsColumn);
}

#include "moc_qvpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
