/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qabstractseries.h"
#include "qabstractseries_p.h"
#include "chartdataset_p.h"
#include "qchart.h"
#include "qchart_p.h"
#include "chartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAbstractSeries
    \brief Base class for all QtCommercial Chart series.
    \mainclass

    Usually you use the series type specific inherited classes instead of the base class.
    \sa QXYSeries, QLineSeries, QSplineSeries, QScatterSeries, QAreaSeries, QAbstractBarSeries, QStackedBarSeries,
    QPercentBarSeries, QPieSeries
*/
/*!
    \qmlclass AbstractSeries
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
    \brief name of the series property. The name is shown in legend for QXYSeries.
*/
/*!
    \qmlproperty string AbstractSeries::name
    Name of the series. The name is shown in legend for QXYSeries.
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
    \brief Constructs ChartSeries object with \a parent.
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
        qFatal("Still binded series detected !");
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

/*!
    Sets the visibility of series to \a visible
*/
void QAbstractSeries::setVisible(bool visible)
{
    if (visible != d_ptr->m_visible) {
        d_ptr->m_visible = visible;
        emit visibleChanged();
    }
}

/*!
    Returns the visibility of series
*/
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

//void QAbstractSeries::adjustView()
//{
//    //TODO:
//}

/*!
    \brief Sets the visibility of the series to true

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::show()
{
    setVisible(true);
}

/*!
    \brief Sets the visibility of the series to false

    \sa setVisible(), isVisible()
*/
void QAbstractSeries::hide()
{
    setVisible(false);
}

bool QAbstractSeries::attachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->attachAxis(this,axis);
    } else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

bool QAbstractSeries::detachAxis(QAbstractAxis* axis)
{
    if(d_ptr->m_chart) {
        return d_ptr->m_chart->d_ptr->m_dataset->detachAxis(this,axis);
    }
    else {
        qWarning()<<"Series not in the chart. Please addSeries to chart first.";
        return false;
    }
}

QList<QAbstractAxis*> QAbstractSeries::attachedAxes()
{
    return d_ptr->m_axes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractSeriesPrivate::QAbstractSeriesPrivate(QAbstractSeries *q)
    : q_ptr(q),
      m_chart(0),
      m_item(0),
      m_domain(new Domain()),
      m_visible(true),
      m_opacity(1.0)
{
}

QAbstractSeriesPrivate::~QAbstractSeriesPrivate()
{
}

void QAbstractSeriesPrivate::setDomain(QSharedPointer<Domain> domain)
{
    Q_ASSERT(!domain.isNull());
    if(m_domain!=domain) {
        if(!m_item.isNull()) QObject::disconnect(m_domain.data(), SIGNAL(updated()), m_item.data(), SLOT(handleDomainUpdated()));
        m_domain = domain;
        if(!m_item.isNull()) {
            QObject::connect(m_domain.data(), SIGNAL(updated()),m_item.data(), SLOT(handleDomainUpdated()));
            m_item->handleDomainUpdated();
        }
    }
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

QTCOMMERCIALCHART_END_NAMESPACE


