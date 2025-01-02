// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QHBarModelMapper>

QT_BEGIN_NAMESPACE

/*!
    \class QHBarModelMapper
    \inmodule QtCharts
    \brief The QHBarModelMapper class is a horizontal model mapper for bar series.

    Model mappers enable using a data model derived from the QAbstractItemModel class
    as a data source for a chart. A horizontal model mapper is used to create a connection
    between a data model and QAbstractBarSeries, so that each row in the data model
    defines a bar set and each column maps to a category in a bar series.

    Both model and bar series properties can be used to manipulate the data. The model mapper
    keeps the bar series and the data model in sync.

    The model mapper ensures that all the bar sets in the bar series have equal sizes.
    Therefore, adding or removing a value from a bar set causes the same change to be
    made in all the bar sets in the bar series.

    \sa QVBarModelMapper
*/
/*!
    \qmltype HBarModelMapper
    \instantiates QHBarModelMapper
    \inqmlmodule QtCharts

    \brief Horizontal model mapper for bar series.

    The HBarModelMapper type enables using a data model derived from the QAbstractItemModel
    class as a data source for a chart. A horizontal model mapper is used to create a connection
    between a data model and AbstractBarSeries, so that each row in the data model
    defines a bar set and each column maps to a category in a bar series. You need to implement
    the data model and expose it to QML.

    Both model and bar series properties can be used to manipulate the data. The model mapper
    keeps the bar series and the data model in sync.

    The model mapper ensures that all the bar sets in the bar series have equal sizes.
    Therefore, adding or removing a value from a bar set causes the same change to be
    made in all the bar sets in the bar series.

    The following QML code snippet creates a bar series with three bar sets (assuming the model
    has at least four rows). Each bar set contains data starting from column 1. The name
    of a bar set is defined by the row header.
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

    \sa VBarModelMapper
*/

/*!
    \property QHBarModelMapper::series
    \brief The bar series that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When a new series is specified, the old series is disconnected (but it preserves its data).
*/
/*!
    \qmlproperty AbstractBarSeries HBarModelMapper::series
    The bar series that is used by the mapper. All the data in the series is discarded when it is
    set to the mapper. When the new series is specified, the old series is disconnected (but it
    preserves its data).
*/

/*!
    \property QHBarModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel HBarModelMapper::model
    The data model that is used by the mapper. You need to implement the model and expose it to QML.

    \note The model has to support adding and removing rows or columns and modifying
    the data in the cells.
*/

/*!
    \property QHBarModelMapper::firstBarSetRow
    \brief The row of the model that is used as the data source for the first bar set.

    The default value is -1 (invalid mapping).
*/
/*!
    \qmlproperty int HBarModelMapper::firstBarSetRow
    Defines which row of the model is used as the data source for the first bar set. The default value is -1
    (invalid mapping).
*/

/*!
    \property QHBarModelMapper::lastBarSetRow
    \brief The row of the model that is used as the data source for the last bar set.

    The default value is -1 (invalid mapping).
*/
/*!
    \qmlproperty int HBarModelMapper::lastBarSetRow
    The row of the model that is used as the data source for the last bar set. The default
    value is -1 (invalid mapping).
*/

/*!
    \property QHBarModelMapper::firstColumn
    \brief The column of the model that contains the first values of the bar sets in the bar series.

    The minimum and default value is 0.
*/
/*!
    \qmlproperty int HBarModelMapper::firstColumn
    The column of the model that contains the first values of the bar sets in the bar series.
    The default value is 0.
*/

/*!
    \property QHBarModelMapper::columnCount
    \brief The number of columns of the model that are mapped as the data for the bar series.

    The minimum and default value is -1 (number limited to the number of columns in the model).
*/
/*!
    \qmlproperty int HBarModelMapper::columnCount
    The number of columns of the model that are mapped as the data for the bar series. The default
    value is -1 (number limited to the number of columns in the model).
*/

/*!
    \fn void QHBarModelMapper::seriesReplaced()

    This signal is emitted when the series that the mapper is connected to changes.
*/

/*!
    \fn void QHBarModelMapper::modelReplaced()

    This signal is emitted when the model that the mapper is connected to changes.
*/

/*!
    \fn void QHBarModelMapper::firstBarSetRowChanged()

    This signal is emitted when the first bar set row changes.
*/

/*!
    \fn void QHBarModelMapper::lastBarSetRowChanged()

    This signal is emitted when the last bar set row changes.
*/

/*!
    \fn void QHBarModelMapper::firstColumnChanged()
    This signal is emitted when the first column changes.
*/

/*!
    \fn void QHBarModelMapper::columnCountChanged()
    This signal is emitted when the number of columns changes.
*/

/*!
    Constructs a mapper object that is a child of \a parent.
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

QT_END_NAMESPACE

#include "moc_qhbarmodelmapper.cpp"
