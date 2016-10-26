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

#include <QtCharts/QCandlestickSet>
#include <private/qcandlestickset_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QCandlestickSet
    \since 5.8
    \inmodule Qt Charts
    \brief Building block for a candlestick chart.

    QCandlestickSet represents a single candlestick item in a QCandlestickSeries. It takes five
    values to create a graphical representation of a candlestick item: \e open, \e high, \e low,
    \e close, and \e timestamp. These values can be either passed to a QCandlestickSet constructor,
    or set by using setOpen(), setHigh(), setLow(), setClose(), and setTimestamp().

    \sa QCandlestickSeries
*/

/*!
    \qmltype CandlestickSet
    \since 2.2
    \instantiates QCandlestickSet
    \inqmlmodule QtCharts
    \brief Building block for a candlestick chart.

    CandlestickSet represents a single candlestick item in a CandlestickSeries. It takes five
    values to create a graphical representation of a candlestick item: \l open, \l high, \l low,
    \l close, and \l timestamp.

    \sa CandlestickSeries
*/

/*!
    \property QCandlestickSet::timestamp
    \brief The timestamp value of the set.
*/

/*!
    \qmlproperty qreal CandlestickSet::timestamp
    \brief The timestamp value of the set.
*/

/*!
    \property QCandlestickSet::open
    \brief The open value of the set.
*/

/*!
    \qmlproperty qreal CandlestickSet::open
    \brief The open value of the set.
*/

/*!
    \property QCandlestickSet::high
    \brief The high value of the set.
*/

/*!
    \qmlproperty qreal CandlestickSet::high
    \brief The high value of the set.
*/

/*!
    \property QCandlestickSet::low
    \brief The low value of the set.
*/

/*!
    \qmlproperty qreal CandlestickSet::low
    \brief The low value of the set.
*/

/*!
    \property QCandlestickSet::close
    \brief The close value of the set.
*/

/*!
    \qmlproperty qreal CandlestickSet::close
    \brief The close value of the set.
*/

/*!
    \property QCandlestickSet::brush
    \brief The brush used for drawing the candlestick.
*/

/*!
    \property QCandlestickSet::pen
    \brief The pen used for drawing the candlestick.
*/

/*!
    \qmlproperty QString CandlestickSet::brushFilename
    \brief The name of the file used as a brush for the set.
*/

/*!
    \fn void QCandlestickSet::clicked()
    \brief Emitted when the candlestick item is clicked (pressed and released).
*/

/*!
    \qmlsignal CandlestickSet::clicked()
    \brief Emitted when the candlestick item is clicked (pressed and released).

    The corresponding signal handler is \c {onClicked}.
*/

/*!
    \fn void QCandlestickSet::hovered(bool status)
    \brief Emitted when there is change in hover \a status over a candlestick item.

    Parameter \a status indicates whether the mouse has entered (\c true) or left (\c false) the
    area of the candlestick item.
*/

/*!
    \qmlsignal CandlestickSet::hovered(bool status)
    \brief Emitted when there is change in hover \a status over a candlestick item.

    Parameter \a status indicates whether the mouse has entered (\c true) or left (\c false) the
    area of the candlestick item.

    The corresponding signal handler is \c {onHovered}.
*/

/*!
    \fn void QCandlestickSet::pressed()
    \brief Emitted when there is a press on a candlestick item.
*/

/*!
    \qmlsignal CandlestickSet::pressed()
    \brief Emitted when there is a press on a candlestick item.

    The corresponding signal handler is \c {onPressed}.
*/

/*!
    \fn void QCandlestickSet::released()
    \brief Emitted when there is a release on a candlestick item.
*/

/*!
    \qmlsignal CandlestickSet::released()
    \brief Emitted when there is a release on a candlestick item.

    The corresponding signal handler is \c {onReleased}.
*/

/*!
    \fn void QCandlestickSet::doubleClicked()
    \brief Emitted when there is a double-click on a candlestick item.
*/

/*!
    \qmlsignal CandlestickSet::doubleClicked()
    \brief Emitted when there is a double-click on a candlestick item.

    The corresponding signal handler is \c {onDoubleClicked}.
*/

/*!
    \fn void QCandlestickSet::timestampChanged()
    \brief Emitted when the candlestick item timestamp is changed.
    \sa timestamp
*/

/*!
    \qmlsignal CandlestickSet::timestampChanged()
    \brief Emitted when the candlestick item timestamp is changed.
    \sa timestamp

    The corresponding signal handler is \c {onTimestampChanged}.
*/

/*!
    \fn void QCandlestickSet::openChanged()
    \brief Emitted when the candlestick item open value is changed.
    \sa open
*/

/*!
    \qmlsignal CandlestickSet::openChanged()
    \brief Emitted when the candlestick item open value is changed.
    \sa open

    The corresponding signal handler is \c {onOpenChanged}.
*/

/*!
    \fn void QCandlestickSet::highChanged()
    \brief Emitted when the candlestick item high value is changed.
    \sa high
*/

/*!
    \qmlsignal CandlestickSet::highChanged()
    \brief Emitted when the candlestick item high value is changed.
    \sa high

    The corresponding signal handler is \c {onHighChanged}.
*/

/*!
    \fn void QCandlestickSet::lowChanged()
    \brief Emitted when the candlestick item low value is changed.
    \sa low
*/

/*!
    \qmlsignal CandlestickSet::lowChanged()
    \brief Emitted when the candlestick item low value is changed.
    \sa low

    The corresponding signal handler is \c {onLowChanged}.
*/

/*!
    \fn void QCandlestickSet::closeChanged()
    \brief Emitted when the candlestick item close value is changed.
    \sa close
*/

/*!
    \qmlsignal CandlestickSet::closeChanged()
    \brief Emitted when the candlestick item close value is changed.
    \sa close

    The corresponding signal handler is \c {onCloseChanged}.
*/

/*!
    \fn void QCandlestickSet::brushChanged()
    \brief Emitted when the candlestick item brush is changed.
    \sa brush
*/

/*!
    \fn void QCandlestickSet::penChanged()
    \brief Emitted when the candlestick item pen is changed.
    \sa pen
*/

/*!
    Constructs a QCandlestickSet with an optional \a timestamp and a \a parent.
*/
QCandlestickSet::QCandlestickSet(qreal timestamp, QObject *parent)
    : QObject(parent),
      d_ptr(new QCandlestickSetPrivate(timestamp, this))
{
}

/*!
    Constructs a QCandlestickSet with given ordered values. The values \a open, \a high, \a low
    and \a close are mandatory. The values \a timestamp and \a parent are optional.
*/
QCandlestickSet::QCandlestickSet(qreal open, qreal high, qreal low, qreal close, qreal timestamp,
                                 QObject *parent)
    : QObject(parent),
      d_ptr(new QCandlestickSetPrivate(timestamp, this))
{
    Q_D(QCandlestickSet);

    d->m_open = open;
    d->m_high = high;
    d->m_low = low;
    d->m_close = close;

    emit d->updatedLayout();
}

/*!
    Destroys the set.
*/
QCandlestickSet::~QCandlestickSet()
{
}

void QCandlestickSet::setTimestamp(qreal timestamp)
{
    Q_D(QCandlestickSet);

    bool changed = d->setTimestamp(timestamp);
    if (!changed)
        return;

    emit d->updatedLayout();
    emit timestampChanged();
}

qreal QCandlestickSet::timestamp() const
{
    Q_D(const QCandlestickSet);

    return d->m_timestamp;
}

void QCandlestickSet::setOpen(qreal open)
{
    Q_D(QCandlestickSet);

    if (d->m_open == open)
        return;

    d->m_open = open;

    emit d->updatedLayout();
    emit openChanged();
}

qreal QCandlestickSet::open() const
{
    Q_D(const QCandlestickSet);

    return d->m_open;
}

void QCandlestickSet::setHigh(qreal high)
{
    Q_D(QCandlestickSet);

    if (d->m_high == high)
        return;

    d->m_high = high;

    emit d->updatedLayout();
    emit highChanged();
}

qreal QCandlestickSet::high() const
{
    Q_D(const QCandlestickSet);

    return d->m_high;
}

void QCandlestickSet::setLow(qreal low)
{
    Q_D(QCandlestickSet);

    if (d->m_low == low)
        return;

    d->m_low = low;

    emit d->updatedLayout();
    emit lowChanged();
}

qreal QCandlestickSet::low() const
{
    Q_D(const QCandlestickSet);

    return d->m_low;
}

void QCandlestickSet::setClose(qreal close)
{
    Q_D(QCandlestickSet);

    if (d->m_close == close)
        return;

    d->m_close = close;

    emit d->updatedLayout();
    emit closeChanged();
}

qreal QCandlestickSet::close() const
{
    Q_D(const QCandlestickSet);

    return d->m_close;
}

void QCandlestickSet::setBrush(const QBrush &brush)
{
    Q_D(QCandlestickSet);

    if (d->m_brush == brush)
        return;

    d->m_brush = brush;

    emit d->updatedCandlestick();
    emit brushChanged();
}

QBrush QCandlestickSet::brush() const
{
    Q_D(const QCandlestickSet);

    return d->m_brush;
}

void QCandlestickSet::setPen(const QPen &pen)
{
    Q_D(QCandlestickSet);

    if (d->m_pen == pen)
        return;

    d->m_pen = pen;

    emit d->updatedCandlestick();
    emit penChanged();
}

QPen QCandlestickSet::pen() const
{
    Q_D(const QCandlestickSet);

    return d->m_pen;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

QCandlestickSetPrivate::QCandlestickSetPrivate(qreal timestamp, QCandlestickSet *parent)
    : QObject(parent),
      q_ptr(parent),
      m_timestamp(0.0),
      m_open(0.0),
      m_high(0.0),
      m_low(0.0),
      m_close(0.0),
      m_brush(QBrush(Qt::NoBrush)),
      m_pen(QPen(Qt::NoPen)),
      m_series(nullptr)
{
    setTimestamp(timestamp);
}

QCandlestickSetPrivate::~QCandlestickSetPrivate()
{
}

bool QCandlestickSetPrivate::setTimestamp(qreal timestamp)
{
    timestamp = qMax(timestamp, qreal(0.0));
    timestamp = qRound64(timestamp);

    if (m_timestamp == timestamp)
        return false;

    m_timestamp = timestamp;

    return true;
}

#include "moc_qcandlestickset.cpp"
#include "moc_qcandlestickset_p.cpp"

QT_CHARTS_END_NAMESPACE
