// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QVXYModelMapper>

QT_BEGIN_NAMESPACE

/*!
    \class QVXYModelMapper
    \inmodule QtCharts
    \brief The QVXYModelMapper class is a vertical model mapper for line,
    spline, and scatter series.

    Model mappers enable using a data model derived from the QAbstractItemModel
    class as a data source for a chart. A vertical model mapper is used to
    create a connection between a line, spline, or scatter series and the data
    model that has \e X and \e Y columns for the coordinates and holds the data
    points for the XYSeries as rows. A \e TableModel is a natural choice
    for the model.

    Both model and series properties can be used to manipulate the data. The
    model mapper keeps the series and the data model in sync.

    \sa QHXYModelMapper, QXYSeries, {Charts with Widgets Gallery}
*/
/*!
    \qmltype VXYModelMapper
    \nativetype QVXYModelMapper
    \inqmlmodule QtCharts

    \brief A vertical model mapper for XYSeries.

    Model mappers enable using a data model derived from the QAbstractItemModel
    class as a data source for a chart. A vertical model mapper is used to
    create a connection between a line, spline, or scatter series and the data
    model that has \e X and \e Y columns for the coordinates and holds the data
    points for the XYSeries as rows. A \e TableModel is a natural choice
    for the model.

    Both model and series properties can be used to manipulate the data. The
    model mapper keeps the series and the data model in sync.

   \sa HXYModelMapper, XYSeries, {Charts with Widgets Gallery}
*/

/*!
    \property QVXYModelMapper::series
    \brief The series that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When a new series is specified, the old series is disconnected (but it
    preserves its data).
*/
/*!
    \qmlproperty XYSeries VXYModelMapper::series
    The series that is used by the mapper. All the data in the series is
    discarded when it is set to the mapper. When a new series is specified, the
    old series is disconnected (but it preserves its data).
*/

/*!
    \property QVXYModelMapper::model
    \brief The model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel VXYModelMapper::model
    The data model that is used by the mapper. You need to implement the model
    and expose it to QML.

    \note The model has to support adding and removing rows or columns and
    modifying the data in the cells.
*/

/*!
    \property QVXYModelMapper::xColumn
    \brief The column of the model that contains the x-coordinates of data
    points.

    The default value is -1 (invalid mapping).
*/
/*!
    \qmlproperty int VXYModelMapper::xColumn
    The column of the model that contains the x-coordinates of data points.
    The default value is -1 (invalid mapping).
*/

/*!
    \property QVXYModelMapper::yColumn
    \brief The column of the model that contains the y-coordinates of data
    points.

    The default value is -1 (invalid mapping).
*/
/*!
    \qmlproperty int VXYModelMapper::yColumn
    The column of the model that contains the y-coordinates of data points.
    The default value is -1 (invalid mapping).
*/

/*!
    \property QVXYModelMapper::firstRow
    \brief The row of the model that contains the data for the first point
    of the series.

    The minimum and default value is 0.
*/
/*!
    \qmlproperty int VXYModelMapper::firstRow
    The row of the model that contains the data for the first point of the series.
    The default value is 0.
*/

/*!
    \property QVXYModelMapper::rowCount
    \brief The number of rows of the model that are mapped as the data for series.

    The minimum and default value is -1 (the number is limited by the number of
    rows in the model).
*/
/*!
    \qmlproperty int VXYModelMapper::rowCount
    The number of rows of the model that are mapped as the data for series. The default value is
    -1 (the number is limited by the number of rows in the model).
*/

/*!
    \fn void QVXYModelMapper::seriesReplaced()

    This signal is emitted when the series that the mapper is connected to changes.
*/

/*!
    \fn void QVXYModelMapper::modelReplaced()

    This signal is emitted when the model that the mapper is connected to changes.
*/

/*!
    \fn void QVXYModelMapper::xColumnChanged()

    This signal is emitted when the column that contains the x-coordinates of
    data points changes.
*/

/*!
    \fn void QVXYModelMapper::yColumnChanged()

    This signal is emitted when the column that contains the y-coordinates of
    data points changes.
*/

/*!
    \fn void QVXYModelMapper::firstRowChanged()
    This signal is emitted when the first row changes.
*/

/*!
    \fn void QVXYModelMapper::rowCountChanged()
    This signal is emitted when the number of rows changes.
*/

/*!
    Constructs a mapper object that is a child of \a parent.
*/
QVXYModelMapper::QVXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Vertical);
}

QAbstractItemModel *QVXYModelMapper::model() const
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

QXYSeries *QVXYModelMapper::series() const
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
        emit rowCountChanged();
    }
}

QT_END_NAMESPACE

#include "moc_qvxymodelmapper.cpp"
