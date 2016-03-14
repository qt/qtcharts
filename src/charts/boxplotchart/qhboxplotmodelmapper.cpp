/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2016 Klaralvdalens Datakonsult AB (KDAB).
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

#include <QtCharts/QHBoxPlotModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QHBoxPlotModelMapper
    \inmodule Qt Charts
    \brief Horizontal model mapper for box plot series.

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QBoxPlotSeries and QAbstractItemModel derived model object.
    Model mapper maintains equal size of all the QBoxSets.
    \note used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmltype HBoxPlotModelMapper
    \instantiates QHBoxPlotModelMapper
    \inqmlmodule QtCharts

    \brief Horizontal model mapper for box plot series.

    HBoxPlotModelMapper allows you to use your own QAbstractItemModel derived model with data in
    rows as a data source for any box-and-whiskers series. It is possible to use both
    QAbstractItemModel and box-and-whiskers series data API to manipulate data. HBoxPlotModelMapper
    keeps the series and the model in sync.

    The following QML example would create a box-and-whiskers series with three box sets (assuming
    the model has at least four rows). Each box set would contain data starting from column 1. The
    name of a set would be defined by the vertical header (of the row).
    \code
        BoxPlotSeries {
            HBoxPlotModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                firstBoxSetRow: 1
                lastBoxSetRow: 3
                firstColumn: 1
            }
        }
    \endcode
*/

/*!
    \property QHBoxPlotModelMapper::series
    \brief Defines the QBoxPlotSeries object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty AbstractBarSeries HBoxPlotModelMapper::series
    Defines the AbstractBarSeries based object that is used by the mapper. All the data in the series is discarded when it is
    set to the mapper. When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QHBoxPlotModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel HBoxPlotModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model
    and expose it to QML. \note the model has to support adding/removing rows/columns and modifying
    the data of the cells.
*/

/*!
    \property QHBoxPlotModelMapper::firstBoxSetRow
    \brief Defines which row of the model is used as the data source for the first box-and-whiskers set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HBoxPlotModelMapper::firstBoxSetRow
    Defines which row of the model is used as the data source for the first box-and-whiskers set. Default value
    is: -1 (invalid mapping).
*/

/*!
    \property QHBoxPlotModelMapper::lastBoxSetRow
    \brief Defines which row of the model is used as the data source for the last box-and-whiskers set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HBoxPlotModelMapper::lastBoxSetRow
    Defines which row of the model is used as the data source for the last box-and-whiskers set. Default
    value is: -1 (invalid mapping).
*/

/*!
    \property QHBoxPlotModelMapper::firstColumn
    \brief Defines which column of the model contains the first values of the QBoxSets in the series.

    Minimal and default value is: 0
*/
/*!
    \qmlproperty int HBoxPlotModelMapper::firstColumn
    Defines which column of the model contains the first values of the QBoxSets in the series.
    The default value is 0.
*/

/*!
    \property QHBoxPlotModelMapper::columnCount
    \brief Defines the number of column of the model that are mapped as the data for QBoxPlotSeries

    Minimal and default value is: -1 (count limited by the number of columns in the model)
*/
/*!
    \qmlproperty int HBoxPlotModelMapper::columnCount
    Defines the number of columns of the model that are mapped as the data for QBoxPlotSeries. The default value is
    -1 (count limited by the number of columns in the model)
*/

/*!
    \fn void QHBoxPlotModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QHBoxPlotModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
*/

/*!
    \fn void QHBoxPlotModelMapper::firstBoxSetRowChanged()
    Emitted when the firstBoxSetRow has changed.
*/

/*!
    \fn void QHBoxPlotModelMapper::lastBoxSetRowChanged()
    Emitted when the lastBoxSetRow has changed.
*/

/*!
    \fn void QHBoxPlotModelMapper::firstColumnChanged()
    Emitted when the firstColumn has changed.
*/

/*!
    \fn void QHBoxPlotModelMapper::columnCountChanged()
    Emitted when the columnCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHBoxPlotModelMapper::QHBoxPlotModelMapper(QObject *parent) :
    QBoxPlotModelMapper(parent)
{
    QBoxPlotModelMapper::setOrientation(Qt::Horizontal);
}

QAbstractItemModel *QHBoxPlotModelMapper::model() const
{
    return QBoxPlotModelMapper::model();
}

void QHBoxPlotModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QBoxPlotModelMapper::model()) {
        QBoxPlotModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QBoxPlotSeries *QHBoxPlotModelMapper::series() const
{
    return QBoxPlotModelMapper::series();
}

void QHBoxPlotModelMapper::setSeries(QBoxPlotSeries *series)
{
    if (series != QBoxPlotModelMapper::series()) {
        QBoxPlotModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

int QHBoxPlotModelMapper::firstBoxSetRow() const
{
    return QBoxPlotModelMapper::firstBoxSetSection();
}

void QHBoxPlotModelMapper::setFirstBoxSetRow(int firstBoxSetRow)
{
    if (firstBoxSetRow != firstBoxSetSection()) {
        QBoxPlotModelMapper::setFirstBoxSetSection(firstBoxSetRow);
        emit firstBoxSetRowChanged();
    }
}

int QHBoxPlotModelMapper::lastBoxSetRow() const
{
    return QBoxPlotModelMapper::lastBoxSetSection();
}

void QHBoxPlotModelMapper::setLastBoxSetRow(int lastBoxSetRow)
{
    if (lastBoxSetRow != lastBoxSetSection()) {
        QBoxPlotModelMapper::setLastBoxSetSection(lastBoxSetRow);
        emit lastBoxSetRowChanged();
    }
}

int QHBoxPlotModelMapper::firstColumn() const
{
    return QBoxPlotModelMapper::first();
}

void QHBoxPlotModelMapper::setFirstColumn(int firstColumn)
{
    if (firstColumn != first()) {
        QBoxPlotModelMapper::setFirst(firstColumn);
        emit firstColumnChanged();
    }
}

int QHBoxPlotModelMapper::columnCount() const
{
    return QBoxPlotModelMapper::count();
}

void QHBoxPlotModelMapper::setColumnCount(int columnCount)
{
    if (columnCount != count()) {
        QBoxPlotModelMapper::setCount(columnCount);
        emit columnCountChanged();
    }
}

#include "moc_qhboxplotmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE

