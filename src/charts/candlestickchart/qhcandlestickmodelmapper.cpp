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

#include <QtCharts/QHCandlestickModelMapper>
#include <private/qcandlestickmodelmapper_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QHCandlestickModelMapper
    \since 5.8
    \inmodule Qt Charts
    \brief Horizontal model mapper for a candlestick series.

    Model mappers allow the use of a QAbstractItemModel-derived model as a data source for a chart
    series, creating a connection between a QCandlestickSeries and the model object. A horizontal
    model mapper maintains an equal size across all \l {QCandlestickSet} {QCandlestickSets}, and
    reads the values of the set from the model's rows.

    \note The model used must support adding and removing rows/columns and modifying the data of the
    cells.
*/

/*!
    \qmltype HCandlestickModelMapper
    \since 2.2
    \instantiates QHCandlestickModelMapper
    \inqmlmodule QtCharts
    \brief Horizontal model mapper for a candlestick series.

    HCandlestickModelMapper allows the use of a QAbstractItemModel-derived model with data in rows
    as a data source for a candlestick series. It's possible to manipulate the data either through
    QAbstractItemModel or QCandlestickSeries.

    The following QML example creates a candlestick series with three candlestick sets (assuming the
    model has at least four rows). Each candlestick set would contain data defined by timestamp,
    open, high, low and close columns. The name of a set would be defined by the vertical header of
    the row.
    \qml
        CandlestickSeries {
            HCandlestickModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                timestampColumn: 1
                openColumn: 2
                highColumn: 3
                lowColumn: 4
                closeColumn: 5
                firstSetRow: 1
                lastSetRow: 3
            }
        }
    \endqml

    \note HCandlestickModelMapper keeps the series and the model in sync.
*/

/*!
    \qmlproperty QAbstractItemModel HCandlestickModelMapper::model
    \brief The QAbstractItemModel-based model that is used by the mapper. The model must be
    implemented and exposed to QML.

    \note The model used must support adding and removing rows/columns and modifying the data of the
    cells.
*/

/*!
    \qmlproperty CandlestickSeries HCandlestickModelMapper::series
    \brief Defines the CandlestickSeries based object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper. When a new series is
    specified, the old series is disconnected (preserving its data).
*/

/*!
    \property QHCandlestickModelMapper::timestampColumn
    \brief Defines the column of the model that contains the timestamp values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::timestampColumn
    \brief Defines the column of the model that contains the timestamp values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::openColumn
    \brief Defines the column of the model that contains the open values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::openColumn
    \brief Defines the column of the model that contains the open values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::highColumn
    \brief Defines the column of the model that contains the high values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::highColumn
    \brief Defines the column of the model that contains the high values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::lowColumn
    \brief Defines the column of the model that contains the low values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::lowColumn
    \brief Defines the column of the model that contains the low values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::closeColumn
    \brief Defines the column of the model that contains the close values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::closeColumn
    \brief Defines the column of the model that contains the close values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::firstSetRow
    \brief Defines the row of the model that is used as the data source for the first set. Default
    value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::firstSetRow
    \brief Defines the row of the model that is used as the data source for the first set. Default
    value is -1 (invalid mapping).
*/

/*!
    \property QHCandlestickModelMapper::lastSetRow
    \brief Defines the row of the model that is used as the data source for the last set. Default
    value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int HCandlestickModelMapper::lastSetRow
    \brief Defines the row of the model that is used as the data source for the last set. Default
    value is -1 (invalid mapping).
*/

/*!
    \fn void QHCandlestickModelMapper::timestampColumnChanged()
    \brief Emitted when the column of the model that contains timestamp values is changed
    \sa timestampColumn
*/

/*!
    \fn void QHCandlestickModelMapper::openColumnChanged()
    \brief Emitted when the column of the model that contains open values is changed.
    \sa openColumn
*/
/*!
    \fn void QHCandlestickModelMapper::highColumnChanged()
    \brief Emitted when the column of the model that contains high values is changed.
    \sa highColumn
*/

/*!
    \fn void QHCandlestickModelMapper::lowColumnChanged()
    \brief Emitted when the column of the model that contains low values is changed.
    \sa lowColumn
*/

/*!
    \fn void QHCandlestickModelMapper::closeColumnChanged()
    \brief Emitted when the column of the model that contains close values is changed.
    \sa closeColumn
*/

/*!
    \fn void QHCandlestickModelMapper::firstSetRowChanged()
    \brief Emitted when the row of the model that contains the data of the first set is changed.
    \sa firstSetRow
*/

/*!
    \fn void QHCandlestickModelMapper::lastSetRowChanged()
    \brief Emitted when the row of the model that contains the data of the last set is changed.
    \sa lastSetRow
*/

/*!
    Constructs a horizontal model mapper object which is a child of \a parent.
*/
QHCandlestickModelMapper::QHCandlestickModelMapper(QObject *parent)
    : QCandlestickModelMapper(parent)
{
    connect(d_ptr, SIGNAL(timestampChanged()), this, SIGNAL(timestampColumnChanged()));
    connect(d_ptr, SIGNAL(openChanged()), this, SIGNAL(openColumnChanged()));
    connect(d_ptr, SIGNAL(highChanged()), this, SIGNAL(highColumnChanged()));
    connect(d_ptr, SIGNAL(lowChanged()), this, SIGNAL(lowColumnChanged()));
    connect(d_ptr, SIGNAL(closeChanged()), this, SIGNAL(closeColumnChanged()));
    connect(d_ptr, SIGNAL(firstSetSectionChanged()), this, SIGNAL(firstSetRowChanged()));
    connect(d_ptr, SIGNAL(lastSetSectionChanged()), this, SIGNAL(lastSetRowChanged()));
}

/*!
    Returns Qt::Horizontal. This means that values of the set are read from rows.
*/
Qt::Orientation QHCandlestickModelMapper::orientation() const
{
    return Qt::Horizontal;
}

void QHCandlestickModelMapper::setTimestampColumn(int timestampColumn)
{
    QCandlestickModelMapper::setTimestamp(timestampColumn);
}

int QHCandlestickModelMapper::timestampColumn() const
{
    return QCandlestickModelMapper::timestamp();
}

void QHCandlestickModelMapper::setOpenColumn(int openColumn)
{
    QCandlestickModelMapper::setOpen(openColumn);
}

int QHCandlestickModelMapper::openColumn() const
{
    return QCandlestickModelMapper::open();
}

void QHCandlestickModelMapper::setHighColumn(int highColumn)
{
    QCandlestickModelMapper::setHigh(highColumn);
}

int QHCandlestickModelMapper::highColumn() const
{
    return QCandlestickModelMapper::high();
}

void QHCandlestickModelMapper::setLowColumn(int lowColumn)
{
    QCandlestickModelMapper::setLow(lowColumn);
}

int QHCandlestickModelMapper::lowColumn() const
{
    return QCandlestickModelMapper::low();
}

void QHCandlestickModelMapper::setCloseColumn(int closeColumn)
{
    QCandlestickModelMapper::setClose(closeColumn);
}

int QHCandlestickModelMapper::closeColumn() const
{
    return QCandlestickModelMapper::close();
}

void QHCandlestickModelMapper::setFirstSetRow(int firstSetRow)
{
    QCandlestickModelMapper::setFirstSetSection(firstSetRow);
}

int QHCandlestickModelMapper::firstSetRow() const
{
    return QCandlestickModelMapper::firstSetSection();
}

void QHCandlestickModelMapper::setLastSetRow(int lastSetRow)
{
    QCandlestickModelMapper::setLastSetSection(lastSetRow);
}

int QHCandlestickModelMapper::lastSetRow() const
{
    return QCandlestickModelMapper::lastSetSection();
}

#include "moc_qhcandlestickmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE
