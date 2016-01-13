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

#include <QtCharts/QVBoxPlotModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QVBoxPlotModelMapper
    \inmodule Qt Charts
    \brief Vertical model mapper for box plot series.

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Vertical model mapper is used to create a connection between QBoxPlotSeries and QAbstractItemModel derived model object.
    Model mapper maintains equal size of all the QBoxSets.
    \note used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmltype VBoxPlotModelMapper
    \instantiates QVBoxPlotModelMapper
    \inqmlmodule QtCharts

    \brief Vertical model mapper for box plot series.

    VBoxPlotModelMapper allows you to use your own QAbstractItemModel derived model with data in
    columns as a data source for any box-and-whiskers series. It is possible to use both
    QAbstractItemModel and box-and-whiskers series data API to manipulate data. VBoxPlotModelMapper
    keeps the series and the model in sync.

    The following QML example would create a box-and-whiskers series with three box sets (assuming
    the model has at least four columns). Each box set would contain data starting from row 1. The
    name of a set would be defined by the horizontal header (of the column).
    \code
        BoxPlotSeries {
            VBoxPlotModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                firstBoxSetColumn: 1
                lastBoxSetColumn: 3
                firstRow: 1
            }
        }
    \endcode
*/

/*!
    \property QVBoxPlotModelMapper::series
    \brief Defines the QBoxPlotSeries object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty AbstractBarSeries VBoxPlotModelMapper::series
    Defines the AbstractBarSeries based object that is used by the mapper. All the data in the series is discarded when it is
    set to the mapper. When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QVBoxPlotModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel VBoxPlotModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model
    and expose it to QML. \note the model has to support adding/removing rows/columns and modifying
    the data of the cells.
*/

/*!
    \property QVBoxPlotModelMapper::firstBoxSetColumn
    \brief Defines which column of the model is used as the data source for the first box-and-whiskers set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::firstBoxSetColumn
    Defines which column of the model is used as the data source for the first box-and-whiskers set. Default value
    is: -1 (invalid mapping).
*/

/*!
    \property QVBoxPlotModelMapper::lastBoxSetColumn
    \brief Defines which column of the model is used as the data source for the last box-and-whiskers set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int VBarModelMapper::lastBoxSetColumn
    Defines which column of the model is used as the data source for the last box-and-whiskers set. Default
    value is: -1 (invalid mapping).
*/

/*!
    \property QVBoxPlotModelMapper::firstRow
    \brief Defines which row of the model contains the first values of the QBoxSets in the series.

    Minimal and default value is: 0
*/
/*!
    \qmlproperty int VBoxPlotModelMapper::firstRow
    Defines which row of the model contains the first values of the QBoxSets in the series.
    The default value is 0.
*/

/*!
    \property QVBoxPlotModelMapper::rowCount
    \brief Defines the number of rows of the model that are mapped as the data for QBoxPlotSeries

    Minimal and default value is: -1 (count limited by the number of rows in the model)
*/
/*!
    \qmlproperty int VBoxModelMapper::rowCount
    Defines the number of rows of the model that are mapped as the data for QBoxPlotSeries. The default value is
    -1 (count limited by the number of rows in the model)
*/

/*!
    \fn void QVBoxPlotModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QVBoxPlotModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
*/

/*!
    \fn void QVBoxPlotModelMapper::firstBoxSetColumnChanged()
    Emitted when the firstBoxSetColumn has changed.
*/

/*!
    \fn void QVBoxPlotModelMapper::lastBoxSetColumnChanged()
    Emitted when the lastBoxSetColumn has changed.
*/

/*!
    \fn void QVBoxPlotModelMapper::firstRowChanged()
    Emitted when the firstRow has changed.
*/

/*!
    \fn void QVBoxPlotModelMapper::rowCountChanged()
    Emitted when the rowCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVBoxPlotModelMapper::QVBoxPlotModelMapper(QObject *parent) :
    QBoxPlotModelMapper(parent)
{
    QBoxPlotModelMapper::setOrientation(Qt::Vertical);
}

QAbstractItemModel *QVBoxPlotModelMapper::model() const
{
    return QBoxPlotModelMapper::model();
}

void QVBoxPlotModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QBoxPlotModelMapper::model()) {
        QBoxPlotModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QBoxPlotSeries *QVBoxPlotModelMapper::series() const
{
    return QBoxPlotModelMapper::series();
}

void QVBoxPlotModelMapper::setSeries(QBoxPlotSeries *series)
{
    if (series != QBoxPlotModelMapper::series()) {
        QBoxPlotModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

int QVBoxPlotModelMapper::firstBoxSetColumn() const
{
    return QBoxPlotModelMapper::firstBoxSetSection();
}

void QVBoxPlotModelMapper::setFirstBoxSetColumn(int firstBoxSetColumn)
{
    if (firstBoxSetColumn != firstBoxSetSection()) {
        QBoxPlotModelMapper::setFirstBoxSetSection(firstBoxSetColumn);
        emit firstBoxSetColumnChanged();
    }
}

int QVBoxPlotModelMapper::lastBoxSetColumn() const
{
    return QBoxPlotModelMapper::lastBoxSetSection();
}

void QVBoxPlotModelMapper::setLastBoxSetColumn(int lastBoxSetColumn)
{
    if (lastBoxSetColumn != lastBoxSetSection()) {
        QBoxPlotModelMapper::setLastBoxSetSection(lastBoxSetColumn);
        emit lastBoxSetColumnChanged();
    }
}

int QVBoxPlotModelMapper::firstRow() const
{
    return QBoxPlotModelMapper::first();
}

void QVBoxPlotModelMapper::setFirstRow(int firstRow)
{
    if (firstRow != first()) {
        QBoxPlotModelMapper::setFirst(firstRow);
        emit firstRowChanged();
    }
}

int QVBoxPlotModelMapper::rowCount() const
{
    return QBoxPlotModelMapper::count();
}

void QVBoxPlotModelMapper::setRowCount(int rowCount)
{
    if (rowCount != count()) {
        QBoxPlotModelMapper::setCount(rowCount);
        emit rowCountChanged();
    }
}

#include "moc_qvboxplotmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE

