/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QHBarModelMapper>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QHBarModelMapper
    \inmodule Qt Charts
    \brief Horizontal model mapper for bar series.
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QAbstractBarSeries and QAbstractItemModel derived model object.
    Model mapper maintains equal size of all the BarSets.
    Adding/removing value from the BarSet causes the the same change in the rest of the BarSets added to the same series.
    \note Used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmltype HBarModelMapper
    \instantiates QHBarModelMapper
    \inqmlmodule QtCharts

    \brief Horizontal model mapper for bar series.

    HBarModelMapper allows you to use your own QAbstractItemModel derived model with data in rows as
    a data source for any bar series. It is possible to use both QAbstractItemModel and bar series
    data API to manipulate data. HBarModelMapper keeps the series and the model in sync.

    The following QML example would create a bar series with three bar sets (assuming the model has
    at least four rows). Each bar set would contain data starting from column 1. The name of a set
    would be defined by the vertical header (of the row).
    \code
        BarSeries {
            HBarModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                firstBarSetRow: 1
                lastBarSetRow: 3
                firstColumn: 1
            }
        }
    \endcode
*/

/*!
    \property QHBarModelMapper::series
    \brief Defines the QPieSeries object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty AbstractBarSeries HBarModelMapper::series
    Defines the AbstractBarSeries based object that is used by the mapper. All the data in the series is discarded when it is
    set to the mapper. When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QHBarModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel HBarModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model
    and expose it to QML. Note: the model has to support adding/removing rows/columns and modifying
    the data of the cells.
*/

/*!
    \property QHBarModelMapper::firstBarSetRow
    \brief Defines which column of the model is used as the data source for the first bar set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HBarModelMapper::firstBarSetRow
    Defines which column of the model is used as the data source for the first bar set. The default value is -1
    (invalid mapping).
*/

/*!
    \property QHBarModelMapper::lastBarSetRow
    \brief Defines which column of the model is used as the data source for the last bar set.

    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HBarModelMapper::lastBarSetRow
    Defines which column of the model is used as the data source for the last bar set. The default value is -1
    (invalid mapping).
*/

/*!
    \property QHBarModelMapper::firstColumn
    \brief Defines which column of the model contains the first values of the QBarSets in the series.

    Minimal and default value is: 0
*/
/*!
    \qmlproperty int HBarModelMapper::firstColumn
    Defines which column of the model contains the first values of the QBarSets in the series.
    The default value is 0.
*/

/*!
    \property QHBarModelMapper::columnCount
    \brief Defines the number of columns of the model that are mapped as the data for QAbstractBarSeries.

    Minimal and default value is: -1 (count limited by the number of columns in the model)
*/
/*!
    \qmlproperty int HBarModelMapper::columnCount
    Defines the number of columns of the model that are mapped as the data for QAbstractBarSeries. The default value is
    -1 (count limited by the number of columns in the model)
*/

/*!
    \fn void QHBarModelMapper::seriesReplaced()

    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QHBarModelMapper::modelReplaced()

    Emitted when the model to which mapper is connected to has changed.
*/

/*!
    \fn void QHBarModelMapper::firstBarSetRowChanged()

    Emitted when the firstBarSetRow has changed.
*/

/*!
    \fn void QHBarModelMapper::lastBarSetRowChanged()

    Emitted when the lastBarSetRow has changed.
*/

/*!
    \fn void QHBarModelMapper::firstColumnChanged()
    Emitted when the firstColumn has changed.
*/

/*!
    \fn void QHBarModelMapper::columnCountChanged()
    Emitted when the columnCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHBarModelMapper::QHBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Horizontal);
}

QAbstractItemModel *QHBarModelMapper::model() const
{
    return QBarModelMapper::model();
}

void QHBarModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QBarModelMapper::model()) {
        QBarModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QAbstractBarSeries *QHBarModelMapper::series() const
{
    return QBarModelMapper::series();
}

void QHBarModelMapper::setSeries(QAbstractBarSeries *series)
{
    if (series != QBarModelMapper::series()) {
        QBarModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

int QHBarModelMapper::firstBarSetRow() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QHBarModelMapper::setFirstBarSetRow(int firstBarSetRow)
{
    if (firstBarSetRow != firstBarSetSection()) {
        QBarModelMapper::setFirstBarSetSection(firstBarSetRow);
        emit firstBarSetRowChanged();
    }
}

int QHBarModelMapper::lastBarSetRow() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QHBarModelMapper::setLastBarSetRow(int lastBarSetRow)
{
    if (lastBarSetRow != lastBarSetSection()) {
        QBarModelMapper::setLastBarSetSection(lastBarSetRow);
        emit lastBarSetRowChanged();
    }
}

int QHBarModelMapper::firstColumn() const
{
    return QBarModelMapper::first();
}

void QHBarModelMapper::setFirstColumn(int firstColumn)
{
    if (firstColumn != first()) {
        QBarModelMapper::setFirst(firstColumn);
        emit firstColumnChanged();
    }
}

int QHBarModelMapper::columnCount() const
{
    return QBarModelMapper::count();
}

void QHBarModelMapper::setColumnCount(int columnCount)
{
    if (columnCount != count()) {
        QBarModelMapper::setCount(columnCount);
        emit columnCountChanged();
    }
}

#include "moc_qhbarmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE
