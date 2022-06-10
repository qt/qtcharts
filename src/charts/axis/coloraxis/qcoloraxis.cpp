// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtCharts/QColorAxis>
#include <QtCharts/QXYSeries>
#include <private/abstractdomain_p.h>
#include <private/qcoloraxis_p.h>
#include <private/qxyseries_p.h>
#include <private/chartcoloraxisx_p.h>
#include <private/chartcoloraxisy_p.h>
#include <private/chartvalueaxisy_p.h>
#include <private/charthelpers_p.h>

#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
/*!
    \class QColorAxis
    \inmodule QtCharts
    \brief The QColorAxis class displays a color scale as one of the chart's axes.
    \since 6.2

    A color axis can be set up to show a color scale based on the passed gradient.
    The scale has tick marks with labels based on data passed in QXYSeries::colorby method.
*/

/*!
  \property QColorAxis::min
  \brief The minimum value on the axis.

  When setting this property, the maximum value is adjusted if necessary, to ensure that
  the range remains valid.
*/

/*!
  \property QColorAxis::max
  \brief The maximum value on the axis.

  When setting this property, the minimum value is adjusted if necessary, to ensure that
  the range remains valid.
*/

/*!
  \property QColorAxis::tickCount
  \brief The number of tick marks on the axis. This indicates how many grid lines are drawn on the
  chart if QColorAxis::gridVisible is equal to \c true. The default value is 5, and the number
  cannot be less than 2.

  \note Grid lines are intentionally invisible by default in QColorAxis as this type of axis
  does not represent geometric values.
*/

/*!
  \property QColorAxis::size
  \brief The size of the color scale.

  Depending on the alignment the value indicates either width or height.
*/

/*!
  \property QColorAxis::autoRange
  \brief The property indicating if the range should be set from the list of values
  passed in QXYSeries::colorBy method or rather taken from the axis itself.

  The default value is \c true.
*/

/*!
  \fn void QColorAxis::minChanged(qreal min)
  This signal is emitted when the minimum value of the axis, specified by \a min, changes.
*/

/*!
  \fn void QColorAxis::maxChanged(qreal max)
  This signal is emitted when the maximum value of the axis, specified by \a max, changes.
*/

/*!
  \fn void QColorAxis::tickCountChanged(int tickCount)
  This signal is emitted when the number of tick marks on the axis, specified by \a tickCount,
  changes.
*/

/*!
  \fn void QColorAxis::sizeChanged(qreal size)
  This signal is emitted when the size of the color scale, specified by \a size, changes.
*/

/*!
  \fn void QColorAxis::autoRangeChanged(bool autoRange)
  This signal is emitted when the auto range mode, specified by \a autoRange, changes.
*/

/*!
  \fn void QColorAxis::rangeChanged(qreal min, qreal max)
  This signal is emitted when the minimum or maximum value of the axis, specified by \a min
  and \a max, changes.
*/

QColorAxis::QColorAxis(QObject *parent)
    : QAbstractAxis(*new QColorAxisPrivate(this), parent)
{
    setGridLineVisible(false);
    QPen linePen = QPen(Qt::black);
    linePen.setWidthF(2.0);
    setLinePen(linePen);
}

/*!
    \internal
*/
QColorAxis::QColorAxis(QColorAxisPrivate &d, QObject *parent)
    : QAbstractAxis(d, parent)
{

}

/*!
    Destroys the object.
*/
QColorAxis::~QColorAxis()
{
    Q_D(QColorAxis);
    if (d->m_chart)
        d->m_chart->removeAxis(this);
}

QAbstractAxis::AxisType QColorAxis::type() const
{
    return QAbstractAxis::AxisTypeColor;
}

void QColorAxis::setMin(qreal min)
{
    Q_D(QColorAxis);
    setRange(min, qMax(d->m_max, min));
}

qreal QColorAxis::min() const
{
    Q_D(const QColorAxis);
    return d->m_min;
}

void QColorAxis::setMax(qreal max)
{
    Q_D(QColorAxis);
    setRange(qMin(d->m_min, max), max);
}

qreal QColorAxis::max() const
{
    Q_D(const QColorAxis);
    return d->m_max;
}

void QColorAxis::setRange(qreal min, qreal max)
{
    Q_D(QColorAxis);
    d->setRange(min, max);
}

void QColorAxis::setTickCount(int count)
{
    Q_D(QColorAxis);
    if (d->m_tickCount != count && count >= 2) {
        d->m_tickCount = count;
        emit tickCountChanged(count);
    }
}

int QColorAxis::tickCount() const
{
    Q_D(const QColorAxis);
    return d->m_tickCount;
}

void QColorAxis::setSize(const qreal size)
{
    Q_D(QColorAxis);
    if (d->m_size != size) {
        d->m_size = size;
        emit sizeChanged(size);
    }
}

qreal QColorAxis::size() const
{
    Q_D(const QColorAxis);
    return d->m_size;
}

/*!
    Sets the gradient on the color scale to \a gradient.

    \note If the axis is attached to a series, the gradient is also used
    by the QXYSeries::colorBy method.
    \sa gradient
*/
void QColorAxis::setGradient(const QLinearGradient &gradient)
{
    Q_D(QColorAxis);
    if (d->m_gradient != gradient) {
        d->m_gradient = gradient;
        emit gradientChanged(gradient);
    }
}

/*!
    Returns the gradient currently used on the color scale.

    \note If the axis is attached to a series, the gradient is also used
    by the QXYSeries::colorBy method.
    \sa setGradient
*/
QLinearGradient QColorAxis::gradient() const
{
    Q_D(const QColorAxis);
    return d->m_gradient;
}

void QColorAxis::setAutoRange(bool autoRange)
{
    Q_D(QColorAxis);
    if (d->m_autoRange != autoRange) {
        d->m_autoRange = autoRange;
        emit autoRangeChanged(d->m_autoRange);
    }
}

bool QColorAxis::autoRange() const
{
    Q_D(const QColorAxis);
    return d->m_autoRange;
}

QColorAxisPrivate::QColorAxisPrivate(QColorAxis *q)
    : QAbstractAxisPrivate(q)
    , m_min(0)
    , m_max(1)
    , m_tickCount(5)
    , m_size(15)
    , m_autoRange(true)
{
    m_gradient = QLinearGradient(QPointF(0, 0), QPointF(0, 100));
    m_gradient.setColorAt(0, Qt::white);
    m_gradient.setColorAt(1, Qt::black);
}

QColorAxisPrivate::~QColorAxisPrivate()
{

}

void QColorAxisPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QColorAxis);
    ChartAxisElement *axis(0);
    if (m_chart->chartType() == QChart::ChartTypeCartesian) {
        if (orientation() == Qt::Vertical)
            axis = new ChartColorAxisY(q, parent);
        else if (orientation() == Qt::Horizontal)
            axis = new ChartColorAxisX(q, parent);
    }

    if (m_chart->chartType() == QChart::ChartTypePolar)
        qWarning() << "Polar chart is not supported by color axis.";

    m_item.reset(axis);
    QAbstractAxisPrivate::initializeGraphics(parent);
}

void QColorAxisPrivate::initializeDomain(AbstractDomain *domain)
{
    Q_UNUSED(domain);
    if (orientation() == Qt::Vertical) {
        if (m_autoRange)
            updateSeries();
        else
            setRange(m_min, m_max);
    }

    if (orientation() == Qt::Horizontal) {
        if (m_autoRange)
            updateSeries();
        else
            setRange(m_min, m_max);
    }
}

void QColorAxisPrivate::setRange(qreal min, qreal max)
{
    Q_Q(QColorAxis);
    bool changed = false;

    if (min > max)
        return;

    if (!isValidValue(min, max)) {
        qWarning() << "Attempting to set invalid range for value axis: ["
                   << min << " - " << max << "]";
        return;
    }

    if (m_min != min) {
        m_min = min;
        changed = true;
        emit q->minChanged(min);
    }

    if (m_max != max) {
        m_max = max;
        changed = true;
        emit q->maxChanged(max);
    }

    if (changed) {
        emit rangeChanged(min,max);
        emit q->rangeChanged(min, max);

        if (!m_autoRange)
            updateSeries();
    }
}

void QColorAxisPrivate::updateSeries()
{
    const QList<QAbstractSeries *> series = m_series;
    for (const auto &serie : series) {
        if (serie->type() == QAbstractSeries::SeriesTypeLine
                || serie->type() == QAbstractSeries::SeriesTypeSpline
                || serie->type() == QAbstractSeries::SeriesTypeScatter) {
            QXYSeries *xySeries = static_cast<QXYSeries *>(serie);
            const auto &colorByData = xySeries->d_func()->colorByData();
            if (!colorByData.isEmpty())
                xySeries->colorBy(colorByData);
        }
    }
}

void QColorAxisPrivate::setMin(const QVariant &min)
{
    Q_Q(QColorAxis);
    bool ok;
    qreal value = min.toReal(&ok);
    if (ok)
        q->setMin(value);
}

void QColorAxisPrivate::setMax(const QVariant &max)
{
    Q_Q(QColorAxis);
    bool ok;
    qreal value = max.toReal(&ok);
    if (ok)
        q->setMax(value);
}

void QColorAxisPrivate::setRange(const QVariant &min, const QVariant &max)
{
    Q_Q(QColorAxis);
    bool ok1;
    bool ok2;
    qreal value1 = min.toReal(&ok1);
    qreal value2 = max.toReal(&ok2);
    if (ok1 && ok2)
        q->setRange(value1, value2);
}

QT_END_NAMESPACE

#include "moc_qcoloraxis.cpp"
#include "moc_qcoloraxis_p.cpp"
