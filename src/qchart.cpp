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

#include "qchart.h"
#include "qchart_p.h"
#include "legendscroller_p.h"
#include "qlegend_p.h"
#include "chartbackground_p.h"
#include "qabstractaxis.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QGraphicsLayout>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 \enum QChart::ChartTheme

 This enum describes the theme used by the chart.

 \value ChartThemeLight The default theme
 \value ChartThemeBlueCerulean
 \value ChartThemeDark
 \value ChartThemeBrownSand
 \value ChartThemeBlueNcs
 \value ChartThemeHighContrast
 \value ChartThemeBlueIcy
 */

/*!
 \enum QChart::AnimationOption

 For enabling/disabling animations. Defaults to NoAnimation.

 \value NoAnimation
 \value GridAxisAnimations
 \value SeriesAnimations
 \value AllAnimations
 */

/*!
 \class QChart
 \brief QtCommercial chart API.

 QChart is a QGraphicsWidget that you can show in a QGraphicsScene. It manages the graphical
 representation of different types of series and other chart related objects like
 QAxis and QLegend. If you simply want to show a chart in a layout, you can use the
 convenience class QChartView instead of QChart.
 \sa QChartView
 */

/*!
 \property QChart::animationOptions
 The animation \a options for the chart. Animations are enabled/disabled based on this setting.
 */

/*!
 \property QChart::backgroundVisible
 Whether the chart background is visible or not.
 \sa setBackgroundBrush(), setBackgroundPen()
 */

/*!
 \property QChart::dropShadowEnabled
 If set to true, the background drop shadow effect is enabled. If set to false, it is disabled. Note that the drop
 shadow effect depends on theme, which means the setting may be changed if you switch to another theme.
 */

/*!
 \property QChart::margins
 Margins around the plot area. Note that the margin area is used for drawing chart title, legend and axes.
 */

/*!
 \property QChart::theme
 Theme is a built-in collection of UI style related settings applied for all visual elements of a chart, like colors,
 pens, brushes and fonts of series, axes, title and legend. \l {Chart themes demo} shows an example with a few
 different themes.
 Note: changing the theme will overwrite all customizations previously applied to the series.
 */

/*!
 \property QChart::title
 Title is the name (label) of a chart. It is shown as a headline on top of the chart.
 */

/*!
 \fn void QChart::marginsChanged(QRectF newMargins)
 The margins around plot area have changed to \a newMargins. This may happen for example if you change title font size,
 modify axes or hide/show legend.
 */

/*!
 Constructs a chart object which is a child of a\a parent. Parameter \a wFlags is passed to the QGraphicsWidget constructor.
 */
QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    d_ptr(new QChartPrivate())
{
    d_ptr->m_dataset = new ChartDataSet(this);
    d_ptr->m_presenter = new ChartPresenter(this,d_ptr->m_dataset);
    d_ptr->createConnections();
    d_ptr->m_legend = new LegendScroller(this);
    d_ptr->m_presenter->setTheme(QChart::ChartThemeLight, false);
    //connect(d_ptr->m_presenter, SIGNAL(marginsChanged(QRectF)), this, SIGNAL(marginsChanged(QRectF)));
    setLayout(d_ptr->m_presenter->layout());
}

/*!
 Destroys the object and it's children, like series and axis objects added to it.
 */
QChart::~QChart()
{
    //delete first presenter , since this is a root of all the graphical items
    setLayout(0);
    delete d_ptr->m_presenter;
    d_ptr->m_presenter=0;
}

/*!
 Adds the \a series onto the chart and takes the ownership of the object.
 If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
 the y axis).

 \sa removeSeries(), removeAllSeries()
 */
void QChart::addSeries(QAbstractSeries *series)
{
    Q_ASSERT(series);
    d_ptr->m_dataset->addSeries(series);
}

/*!
 Removes the \a series specified in a perameter from the QChartView.
 It releses its ownership of the specified QChartSeries object.
 It does not delete the pointed QChartSeries data object
 \sa addSeries(), removeAllSeries()
 */
void QChart::removeSeries(QAbstractSeries *series)
{
    Q_ASSERT(series);
    d_ptr->m_dataset->removeSeries(series);
}

/*!
 Removes all the QChartSeries that have been added to the QChartView
 It also deletes the pointed QChartSeries data objects
 \sa addSeries(), removeSeries()
 */
void QChart::removeAllSeries()
{
    d_ptr->m_dataset->removeAllSeries();
}

/*!
 Sets the \a brush that is used for painting the background of the chart area.
 */
void QChart::setBackgroundBrush(const QBrush& brush)
{
    d_ptr->m_presenter->setBackgroundBrush(brush);
}

/*!
    Gets the brush that is used for painting the background of the chart area.
 */
QBrush QChart::backgroundBrush() const
{
    return d_ptr->m_presenter->backgroundBrush();
}

/*!
 Sets the \a pen that is used for painting the background of the chart area.
 */
void QChart::setBackgroundPen(const QPen& pen)
{
    d_ptr->m_presenter->setBackgroundPen(pen);
}

/*!
    Gets the pen that is used for painting the background of the chart area.
 */
QPen QChart::backgroundPen() const
{
    return d_ptr->m_presenter->backgroundPen();
}

/*!
 Sets the chart \a title. The description text that is drawn above the chart.
 */
void QChart::setTitle(const QString& title)
{
    d_ptr->m_presenter->setTitle(title);
}

/*!
 Returns the chart title. The description text that is drawn above the chart.
 */
QString QChart::title() const
{
    return d_ptr->m_presenter->title();
}

/*!
 Sets the \a font that is used for drawing the chart description text that is rendered above the chart.
 */
void QChart::setTitleFont(const QFont& font)
{
    d_ptr->m_presenter->setTitleFont(font);
}

/*!
    Gets the font that is used for drawing the chart description text that is rendered above the chart.
 */
QFont QChart::titleFont() const
{
    return d_ptr->m_presenter->titleFont();
}

/*!
 Sets the \a brush used for rendering the title text.
 */
void QChart::setTitleBrush(const QBrush &brush)
{
    d_ptr->m_presenter->setTitleBrush(brush);
}

/*!
 Returns the brush used for rendering the title text.
 */
QBrush QChart::titleBrush() const
{
    return d_ptr->m_presenter->titleBrush();
}

void QChart::setTheme(QChart::ChartTheme theme)
{
    d_ptr->m_presenter->setTheme(theme);
}

QChart::ChartTheme QChart::theme() const
{
    return d_ptr->m_presenter->theme();
}

/*!
 Zooms in the view by a factor of 2
 */
void QChart::zoomIn()
{
    d_ptr->m_presenter->zoomIn(2.0);
}

/*!
 Zooms in the view to a maximum level at which \a rect is still fully visible.
 */
void QChart::zoomIn(const QRectF& rect)
{
    if (!rect.isValid()) return;
    d_ptr->m_presenter->zoomIn(rect);
}

/*!
 Restores the view zoom level to the previous one.
 */
void QChart::zoomOut()
{
    d_ptr->m_presenter->zoomOut(2.0);
}

/*!
 Zooms in the view by a \a factor.

 A factor over 1.0 zooms the view in and factor between 0.0 and 1.0 zooms out.
 */
void QChart::zoom(qreal factor)
{
    if (qFuzzyIsNull(factor))
        return;

    if (qFuzzyCompare(factor, 1.0))
        return;

    if (factor < 0)
        return;

    if (factor > 1.0)
        d_ptr->m_presenter->zoomIn(factor);
    else
        d_ptr->m_presenter->zoomOut(1.0 / factor);
}

/*!
 Returns the pointer to the x axis object of the chart
 */
QAbstractAxis* QChart::axisX(QAbstractSeries* series) const
{
    return d_ptr->m_dataset->axisX(series);
}

/*!
 Returns the pointer to the y axis object of the \a series
 If no \a series is provided then default Y axis of the chart is returned.
 */
QAbstractAxis* QChart::axisY(QAbstractSeries *series) const
{
    return d_ptr->m_dataset->axisY(series);
}

void QChart::createDefaultAxes()
{
	d_ptr->m_dataset->createDefaultAxes();
}

/*!
 Returns the legend object of the chart. Ownership stays in chart.
 */
QLegend* QChart::legend() const
{
    return d_ptr->m_legend;
}

/*!
    Returns the rect that contains information about margins (distance between chart widget edge and axes).
    Individual margins can be obtained by calling left, top, right, bottom on the returned rect.
 */
QRectF QChart::margins() const
{
    return d_ptr->m_presenter->margins();
}

/*!
 Sets animation \a options for the chart
 */

void QChart::setAnimationOptions(AnimationOptions options)
{
    d_ptr->m_presenter->setAnimationOptions(options);
}

QChart::AnimationOptions QChart::animationOptions() const
{
    return d_ptr->m_presenter->animationOptions();
}

/*!
    Scrolls the visible area of the chart by the distance defined in the \a dx and \a dy.
 */
void QChart::scroll(qreal dx, qreal dy)
{
    d_ptr->m_presenter->scroll(dx, dy);
}

void QChart::setBackgroundVisible(bool visible)
{
    d_ptr->m_presenter->setBackgroundVisible(visible);
}

bool QChart::isBackgroundVisible() const
{
    return d_ptr->m_presenter->isBackgroundVisible();
}

void QChart::setDropShadowEnabled(bool enabled)
{
    d_ptr->m_presenter->setBackgroundDropShadowEnabled(enabled);
}

bool QChart::isDropShadowEnabled() const
{
    return d_ptr->m_presenter->isBackgroundDropShadowEnabled();
}

/*!
  Returns all the series that are added to the chart.

  \sa addSeries(), removeSeries(), removeAllSeries()
*/
QList<QAbstractSeries*> QChart::series() const
{
    return d_ptr->m_dataset->series();
}

void QChart::setMarginsMinimum(const QRectF& margins)
{
    d_ptr->m_presenter->setMarginsMinimum(margins);
}

void QChart::setAxisX(QAbstractAxis* axis , QAbstractSeries *series)
{
    d_ptr->m_dataset->setAxisX(series,axis);
}

void QChart::setAxisY( QAbstractAxis* axis , QAbstractSeries *series)
{
    d_ptr->m_dataset->setAxisY(series,axis);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartPrivate::QChartPrivate():
    m_legend(0),
    m_dataset(0),
    m_presenter(0)
{

}

QChartPrivate::~QChartPrivate()
{

}

void QChartPrivate::createConnections()
{
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QAbstractSeries*,Domain*)),m_presenter,SLOT(handleSeriesAdded(QAbstractSeries*,Domain*)));
    QObject::connect(m_dataset,SIGNAL(seriesRemoved(QAbstractSeries*)),m_presenter,SLOT(handleSeriesRemoved(QAbstractSeries*)));
    QObject::connect(m_dataset,SIGNAL(axisAdded(QAbstractAxis*,Domain*)),m_presenter,SLOT(handleAxisAdded(QAbstractAxis*,Domain*)));
    QObject::connect(m_dataset,SIGNAL(axisRemoved(QAbstractAxis*)),m_presenter,SLOT(handleAxisRemoved(QAbstractAxis*)));
    //QObject::connect(m_presenter, SIGNAL(marginsChanged(QRectF)), q_ptr, SIGNAL(marginsChanged(QRectF)));
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
