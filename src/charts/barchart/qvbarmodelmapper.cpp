/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QVBarModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QVBarModelMapper
    \inmodule Qt Charts
    \brief Vertical model mapper for bar series.

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QAbstractBarSeries and QAbstractItemModel derived model object.
    Model mapper maintains equal size of all the BarSets.
    Adding/removing value from the BarSet causes the the same change in the rest of the BarSets added to the same series.
    \note Used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmltype VBarModelMapper
    \instantiates QVBarModelMapper
    \inqmlmodule QtCharts

    \inherits BarModelMapper

    \brief Vertical model mapper for bar series.

    VBarModelMapper allows you to use your own QAbstractItemModel derived model with data in columns
    as a data source for any bar series. It is possible to use both QAbstractItemModel and bar
    series data API to manipulate data. VBarModelMapper keeps the series and the model in sync.

    The following QML example would create a bar series with three bar sets (assuming the model has
    at least four columns). Each bar set would contain data starting from row 1. The name of a set
    would be defined by the horizontal header (of the column).
    \code
        BarSeries {
            VBarModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                firstBarSetColumn: 1
                lastBarSetColumn: 3
                firstRow: 1
            }
        }
    \endcode
*/

/*!
    \property QVBarModelMapper::series
    \brief Defines the QBarSeries object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty AbstractBarSeries VBarModelMapper::series
    Defines the AbstractBarSeries based object that is used by the mapper. All the data in the series is discarded when it is
    set to the mapper. When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QVBarModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel VBarModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model
    and expose it to QML. Note: the model has to support adding/removing rows/columns and modifying
    the data of the cells.
*/

/*!
    \property QVBarModelMapper::firstBarSetColumn
    \brief Defines which column of the model is used as the data source for the first bar set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::firstBarSetColumn
    Defines which column of the model is used as the data source for the first bar set. Default value
    is: -1 (invalid mapping).
*/

/*!
    \property QVBarModelMapper::lastBarSetColumn
    \brief Defines which column of the model is used as the data source for the last bar set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::lastBarSetColumn
    Defines which column of the model is used as the data source for the last bar set. Default
    value is: -1 (invalid mapping).
*/

/*!
    \property QVBarModelMapper::firstRow
    \brief Defines which row of the model contains the first values of the QBarSets in the series.

    Minimal and default value is: 0
*/
/*!
    \qmlproperty int VBarModelMapper::firstRow
    Defines which row of the model contains the first values of the QBarSets in the series.
    The default value is 0.
*/

/*!
    \property QVBarModelMapper::rowCount
    \brief Defines the number of rows of the model that are mapped as the data for QAbstractBarSeries.

    Minimal and default value is: -1 (count limited by the number of rows in the model)
*/
/*!
    \qmlproperty int VBarModelMapper::rowCount
    Defines the number of rows of the model that are mapped as the data for QAbstractBarSeries. The default value is
    -1 (count limited by the number of rows in the model)
*/

/*!
    \fn void QVBarModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QVBarModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
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
    \fn void QVBarModelMapper::firstRowChanged()
    Emitted when the firstRow has changed.
*/

/*!
    \fn void QVBarModelMapper::rowCountChanged()
    Emitted when the rowCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVBarModelMapper::QVBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Vertical);
}

QAbstractItemModel *QVBarModelMapper::model() const
{
    return QBarModelMapper::model();
}

void QVBarModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QBarModelMapper::model()) {
        QBarModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QAbstractBarSeries *QVBarModelMapper::series() const
{
    return QBarModelMapper::series();
}

void QVBarModelMapper::setSeries(QAbstractBarSeries *series)
{
    if (series != QBarModelMapper::series()) {
        QBarModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

int QVBarModelMapper::firstBarSetColumn() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QVBarModelMapper::setFirstBarSetColumn(int firstBarSetColumn)
{
    if (firstBarSetColumn != firstBarSetSection()) {
        QBarModelMapper::setFirstBarSetSection(firstBarSetColumn);
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
        QBarModelMapper::setLastBarSetSection(lastBarSetColumn);
        emit lastBarSetColumnChanged();
    }
}

int QVBarModelMapper::firstRow() const
{
    return QBarModelMapper::first();
}

void QVBarModelMapper::setFirstRow(int firstRow)
{
    if (firstRow != first()) {
        QBarModelMapper::setFirst(firstRow);
        emit firstRowChanged();
    }
}

int QVBarModelMapper::rowCount() const
{
    return QBarModelMapper::count();
}

void QVBarModelMapper::setRowCount(int rowCount)
{
    if (rowCount != count()) {
        QBarModelMapper::setCount(rowCount);
        emit rowCountChanged();
    }
}

#include "moc_qvbarmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE
