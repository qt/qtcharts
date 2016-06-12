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

#include <QtCharts/QVCandlestickModelMapper>
#include <private/qcandlestickmodelmapper_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QVCandlestickModelMapper
    \since 5.8
    \inmodule Qt Charts
    \brief Vertical model mapper for a candlestick series.

    Model mappers allow the use of a QAbstractItemModel-derived model as a data source for a chart
    series, creating a connection between a QCandlestickSeries and the model object. A vertical
    model mapper maintains an equal size across all \l {QCandlestickSet} {QCandlestickSets}, and
    reads the values of the set from the model's columns.

    \note The model used must support adding and removing rows/columns and modifying the data of the
    cells.
*/

/*!
    \qmltype VCandlestickModelMapper
    \since 2.2
    \instantiates QVCandlestickModelMapper
    \inqmlmodule QtCharts
    \brief Vertical model mapper for a candlestick series.

    VCandlestickModelMapper allows the use of a QAbstractItemModel-derived model with data in
    columns as a data source for a candlestick series. It's possible to manipulate the data either
    through QAbstractItemModel or QCandlestickSeries.

    The following QML example creates a candlestick series with three candlestick sets (assuming the
    model has at least four columns). Each candlestick set would contain data defined by timestamp,
    open, high, low and close rows. The name of a set would be defined by the horizontal header of
    the column.
    \qml
        CandlestickSeries {
            VCandlestickModelMapper {
                model: myCustomModel // QAbstractItemModel derived implementation
                timestampRow: 1
                openRow: 2
                highRow: 3
                lowRow: 4
                closeRow: 5
                firstSetColumn: 1
                lastSetColumn: 3
            }
        }
    \endqml

    \note VCandlestickModelMapper keeps the series and the model in sync.
*/

/*!
    \qmlproperty QAbstractItemModel VCandlestickModelMapper::model
    \brief The QAbstractItemModel-based model that is used by the mapper. The model must be
    implemented and exposed to QML.

    \note The model used must support adding and removing rows/columns and modifying the data of the
    cells.
*/

/*!
    \qmlproperty CandlestickSeries VCandlestickModelMapper::series
    \brief Defines the CandlestickSeries based object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper. When a new series is
    specified, the old series is disconnected (preserving its data).
*/

/*!
    \property QVCandlestickModelMapper::timestampRow
    \brief Defines the row of the model that contains the timestamp values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::timestampRow
    \brief Defines the row of the model that contains the timestamp values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::openRow
    \brief Defines the row of the model that contains the open values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::openRow
    \brief Defines the row of the model that contains the open values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::highRow
    \brief Defines the row of the model that contains the high values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::highRow
    \brief Defines the row of the model that contains the high values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::lowRow
    \brief Defines the row of the model that contains the low values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::lowRow
    \brief Defines the row of the model that contains the low values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::closeRow
    \brief Defines the row of the model that contains the close values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::closeRow
    \brief Defines the row of the model that contains the close values of the
    \l {QCandlestickSet} {QCandlestickSets} in the series. Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::firstSetColumn
    \brief Defines the column of the model that is used as the data source for the first set.
    Default value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::firstSetColumn
    \brief Defines the column of the model that is used as the data source for the first set.
    Default value is -1 (invalid mapping).
*/

/*!
    \property QVCandlestickModelMapper::lastSetColumn
    \brief Defines the column of the model that is used as the data source for the last set. Default
    value is -1 (invalid mapping).
*/

/*!
    \qmlproperty int VCandlestickModelMapper::lastSetColumn
    \brief Defines the column of the model that is used as the data source for the last set. Default
    value is -1 (invalid mapping).
*/

/*!
    \fn void QVCandlestickModelMapper::timestampRowChanged()
    \brief Emitted when the row of the model that contains timestamp values is changed.
    \sa timestampRow
*/

/*!
    \fn void QVCandlestickModelMapper::openRowChanged()
    \brief Emitted when the row of the model that contains open values is changed.
    \sa openRow
*/

/*!
    \fn void QVCandlestickModelMapper::highRowChanged()
    \brief Emitted when the row of the model that contains high values is changed.
    \sa highRow
*/

/*!
    \fn void QVCandlestickModelMapper::lowRowChanged()
    \brief Emitted when the row of the model that contains low values is changed.
    \sa lowRow
*/

/*!
    \fn void QVCandlestickModelMapper::closeRowChanged()
    \brief Emitted when the row of the model that contains close values is changed.
    \sa closeRow
*/

/*!
    \fn void QVCandlestickModelMapper::firstSetColumnChanged()
    \brief Emitted when the column of the model that contains the data of the first set is changed.
    \sa firstSetColumn
*/

/*!
    \fn void QVCandlestickModelMapper::lastSetColumnChanged()
    \brief Emitted when the column of the model that contains the data of the last set is changed.
    \sa lastSetColumn
*/

/*!
    Constructs a vertical model mapper object which is a child of \a parent.
*/
QVCandlestickModelMapper::QVCandlestickModelMapper(QObject *parent)
    : QCandlestickModelMapper(parent)
{
    connect(d_ptr, SIGNAL(timestampChanged()), this, SIGNAL(timestampRowChanged()));
    connect(d_ptr, SIGNAL(openChanged()), this, SIGNAL(openRowChanged()));
    connect(d_ptr, SIGNAL(highChanged()), this, SIGNAL(highRowChanged()));
    connect(d_ptr, SIGNAL(lowChanged()), this, SIGNAL(lowRowChanged()));
    connect(d_ptr, SIGNAL(closeChanged()), this, SIGNAL(closeRowChanged()));
    connect(d_ptr, SIGNAL(firstSetSectionChanged()), this, SIGNAL(firstSetColumnChanged()));
    connect(d_ptr, SIGNAL(lastSetSectionChanged()), this, SIGNAL(lastSetColumnChanged()));
}

/*!
    Returns Qt::Vertical. This means that values of the set are read from columns.
*/
Qt::Orientation QVCandlestickModelMapper::orientation() const
{
    return Qt::Vertical;
}

void QVCandlestickModelMapper::setTimestampRow(int timestampRow)
{
    QCandlestickModelMapper::setTimestamp(timestampRow);
}

int QVCandlestickModelMapper::timestampRow() const
{
    return QCandlestickModelMapper::timestamp();
}

void QVCandlestickModelMapper::setOpenRow(int openRow)
{
    QCandlestickModelMapper::setOpen(openRow);
}

int QVCandlestickModelMapper::openRow() const
{
    return QCandlestickModelMapper::open();
}

void QVCandlestickModelMapper::setHighRow(int highRow)
{
    QCandlestickModelMapper::setHigh(highRow);
}

int QVCandlestickModelMapper::highRow() const
{
    return QCandlestickModelMapper::high();
}

void QVCandlestickModelMapper::setLowRow(int lowRow)
{
    QCandlestickModelMapper::setLow(lowRow);
}

int QVCandlestickModelMapper::lowRow() const
{
    return QCandlestickModelMapper::low();
}

void QVCandlestickModelMapper::setCloseRow(int closeRow)
{
    QCandlestickModelMapper::setClose(closeRow);
}

int QVCandlestickModelMapper::closeRow() const
{
    return QCandlestickModelMapper::close();
}

void QVCandlestickModelMapper::setFirstSetColumn(int firstSetColumn)
{
    QCandlestickModelMapper::setFirstSetSection(firstSetColumn);
}

int QVCandlestickModelMapper::firstSetColumn() const
{
    return QCandlestickModelMapper::firstSetSection();
}

void QVCandlestickModelMapper::setLastSetColumn(int lastSetColumn)
{
    QCandlestickModelMapper::setLastSetSection(lastSetColumn);
}

int QVCandlestickModelMapper::lastSetColumn() const
{
    return QCandlestickModelMapper::lastSetSection();
}

#include "moc_qvcandlestickmodelmapper.cpp"

QT_CHARTS_END_NAMESPACE
