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

#include <QtCharts/QAbstractSeries>
#include <private/qabstractseries_p.h>
#include <private/chartdataset_p.h>
#include <QtCharts/QChart>
#include <private/qchart_p.h>
#include <private/chartitem_p.h>
#include <private/xydomain_p.h>
#include <private/xlogydomain_p.h>
#include <private/logxydomain_p.h>
#include <private/logxlogydomain_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAbstractSeries
    \inmodule Qt Charts
    \brief Base class for all Qt Chart series.
    \mainclass

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QXYSeries, QLineSeries, QSplineSeries, QScatterSeries, QAreaSeries, QAbstractBarSeries, QStackedBarSeries,
    QPercentBarSeries, QPieSeries
*/
/*!
    \qmltype AbstractSeries
    \instantiates QAbstractSeries
    \inqmlmodule QtCharts

    \brief Base class for all Qt Chart series.

    AbstractSeries is the base class for all series.
    The class cannot be instantiated by the user.
*/

/*!
    \enum QAbstractSeries::SeriesType

    The type of the series object.

    \value SeriesTypeLine
    \value SeriesTypeArea
    \value SeriesTypeBar
    \value SeriesTypeStackedBar
    \value SeriesTypePercentBar
    \value SeriesTypePie
    \value SeriesTypeScatter
    \value SeriesTypeSpline
    \value SeriesTypeHorizontalBar
    \value SeriesTypeHorizontalStackedBar
    \value SeriesTypeHorizontalPercentBar
    \value SeriesTypeBoxPlot
*/

/*!
    \property QAbstractSeries::type
    The type of the series.
*/
/*!
    \qmlproperty ChartView.SeriesType AbstractSeries::type
    The type of the series.
*/

/*!
    \property QAbstractSeries::name
    \brief name of the series property. The name is shown in legend for series and supports html formatting.
*/
/*!
    \qmlproperty string AbstractSeries::name
    Name of the series. The name is shown in legend for series and supports html formatting.
*/

/*!
    \fn void QAbstractSeries::nameChanged()
    This signal is emitted when the series name changes.
*/
/*!
    \qmlsignal AbstractSeries::onNameChanged()
    This signal is emitted when the series name changes.
*/

/*!
    \property QAbstractSeries::visible
    \brief whether the series is visible or not; true by default.
*/
/*!
    \qmlproperty bool AbstractSeries::visible
    Visibility of the series. True by default.
*/

/*!
    \fn void QAbstractSeries::visibleChanged()
    Emitted when the series visibility changes.
*/
/*!
    \qmlsignal AbstractSeries::onVisibleChanged()
    Emitted when the series visibility changes.
*/

/*!
    \property QAbstractSeries::opacity
    \brief The opacity of the series.

    By default the opacity is 1.0. The valid values range from 0.0 (transparent) to 1.0 (opaque).
*/
/*!
    \qmlproperty real AbstractSeries::opacity
    The opacity of the series. By default the opacity is 1.0.
    The valid values range from 0.0 (transparent) to 1.0 (opaque).
*/

/*!
    \fn void QAbstractSeries::opacityChanged()
    Emitted when the opacity of the series changes.
*/
/*!
    \qmlsignal AbstractSeries::onOpacityChanged()
    Emitted when the opacity of the series changes.
*/

/*!
    \internal
    \brief Constructs QAbstractSeries object with \a parent.
*/
QAbstractSeries::QAbstractSeries(QAbstractSeriesPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

/*!
    \brief Virtual destructor for the chart series.
*/
QAbstractSeries::~QAbstractSeries()
{
    if (d_ptr->m_chart)
        qFatal("Series still bound to a chart when destroyed!");
}

void QAbstractSeries::setName(const QString &name)
{
    if (name != d_ptr->m_name) {
        d_ptr->m_name = name;
        emit nameChanged();
    }
}

QString QAbstractSeries::name() const
{
    return d_ptr->m_name;
}

void QAbstractSeries::setVisible(bool visible)
{
    if (visible != d_ptr->m_visible) {
        d_ptr->m_visible = visible;
        emit visibleChanged();
    }
}

bool QAbstractSeries::isVisible() const
{
    return d_ptr->m_visible;
}

qreal QAbstractSeries::opacity() const
{
    return d_ptr->m_opacity;
}

void QAbstractSeries::setOpacity(qreal opacity)
{
    if (opacity != d_ptr->m_opacity) {
        d_ptr->m_opacity = opacity;
        emit opacityChanged();
    }
}

/*!
    \brief Returns the chart where series belongs to.

    Set automatically when the series is added to the chart
    and unset when the series is removed from the chart.
*/
QChart *QAbstractSeries::chart() const
{
    return d_ptr->m_chart;
}

/*!
    \brief Sets the visibility of the series to true.

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::show()
{
    setVisible(true);
}

/*!
    \brief Sets the visibility of the series to false.

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::hide()
{
    setVisible(false);
}

/*!
 Attach \a axis to the series.
 \return true if the axis was attached successfully, false otherwise.
 \note If multiple axes of same orientation are attached to same series,
       they will have same min/max ranges.
 \sa QChart::addAxis(), QChart::createDefaultAxes()
 */
bool QAbstractSeries::attachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->attachAxis(this, axis);
    } else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

/*!
 Detach \a axis from the series.
 \return true if the axis was detached successfully, false otherwise.
 \sa QChart::removeAxis()
 */
bool QAbstractSeries::detachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->detachAxis(this, axis);
    }
    else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

/*!
 Returns the list of axes attached to the series. Usually there is an x-axis and a y-axis attached to a series, except
 in case of a QPieSeries, which does not have any axes attached.
 \sa attachAxis(), detachAxis()
 */
QList<QAbstractAxis*> QAbstractSeries::attachedAxes()
{
    return d_ptr->m_axes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractSeriesPrivate::QAbstractSeriesPrivate(QAbstractSeries *q)
    : q_ptr(q),
      m_chart(0),
      m_item(0),
      m_domain(new XYDomain()),
      m_visible(true),
      m_opacity(1.0)
{
}

QAbstractSeriesPrivate::~QAbstractSeriesPrivate()
{
}

void QAbstractSeriesPrivate::setDomain(AbstractDomain* domain)
{
    Q_ASSERT(domain);
    if(m_domain.data()!=domain) {
        if(!m_item.isNull()) QObject::disconnect(m_domain.data(), SIGNAL(updated()), m_item.data(), SLOT(handleDomainUpdated()));
        m_domain.reset(domain);
        if(!m_item.isNull()) {
            QObject::connect(m_domain.data(), SIGNAL(updated()),m_item.data(), SLOT(handleDomainUpdated()));
            m_item->handleDomainUpdated();
        }
    }
}

void QAbstractSeriesPrivate::setPresenter(ChartPresenter *presenter)
{
    m_presenter = presenter;
}

ChartPresenter *QAbstractSeriesPrivate::presenter() const
{
    return m_presenter;
}

void QAbstractSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_ASSERT(!m_item.isNull());
    Q_UNUSED(parent);
    QObject::connect(m_domain.data(), SIGNAL(updated()),m_item.data(), SLOT(handleDomainUpdated()));
}

void QAbstractSeriesPrivate::initializeAnimations(QChart::AnimationOptions options)
{
    Q_UNUSED(options);
}

#include "moc_qabstractseries.cpp"
#include "moc_qabstractseries_p.cpp"

QT_CHARTS_END_NAMESPACE


