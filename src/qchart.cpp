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
#include "qaxis.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>

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
    connect(d_ptr->m_presenter, SIGNAL(marginsChanged(QRectF)), this, SIGNAL(marginsChanged(QRectF)));
}

/*!
 Destroys the object and it's children, like series and axis objects added to it.
 */
QChart::~QChart()
{
    //delete first presenter , since this is a root of all the graphical items
    delete d_ptr->m_presenter;
    d_ptr->m_presenter=0;
}

/*!
 Adds the \a series and optional \a axisY onto the chart and takes the ownership of the objects.
 If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
 the y axis).

 \sa removeSeries(), removeAllSeries()
 */
void QChart::addSeries(QAbstractSeries *series, QAxis *axisY)
{
    Q_ASSERT(series);
    d_ptr->m_dataset->addSeries(series, axisY);
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
    //TODO: refactor me
    d_ptr->m_presenter->createChartBackgroundItem();
    d_ptr->m_presenter->m_backgroundItem->setBrush(brush);
    d_ptr->m_presenter->m_backgroundItem->update();
}

/*!
    Gets the brush that is used for painting the background of the chart area.
 */
QBrush QChart::backgroundBrush() const
{
    //TODO: refactor me
    if (!d_ptr->m_presenter->m_backgroundItem) return QBrush();
    return (d_ptr->m_presenter->m_backgroundItem)->brush();
}

/*!
 Sets the \a pen that is used for painting the background of the chart area.
 */
void QChart::setBackgroundPen(const QPen& pen)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartBackgroundItem();
    d_ptr->m_presenter->m_backgroundItem->setPen(pen);
    d_ptr->m_presenter->m_backgroundItem->update();
}

/*!
    Gets the pen that is used for painting the background of the chart area.
 */
QPen QChart::backgroundPen() const
{
    //TODO: refactor me
    if (!d_ptr->m_presenter->m_backgroundItem) return QPen();
    return d_ptr->m_presenter->m_backgroundItem->pen();
}

/*!
 Sets the chart \a title. The description text that is drawn above the chart.
 */
void QChart::setTitle(const QString& title)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartTitleItem();
    d_ptr->m_presenter->m_titleItem->setText(title);
    d_ptr->m_presenter->updateLayout();
}

/*!
 Returns the chart title. The description text that is drawn above the chart.
 */
QString QChart::title() const
{
    //TODO: refactor me
    if (d_ptr->m_presenter->m_titleItem)
        return d_ptr->m_presenter->m_titleItem->text();
    else
        return QString();
}

/*!
 Sets the \a font that is used for drawing the chart description text that is rendered above the chart.
 */
void QChart::setTitleFont(const QFont& font)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartTitleItem();
    d_ptr->m_presenter->m_titleItem->setFont(font);
    d_ptr->m_presenter->updateLayout();
}

/*!
    Gets the font that is used for drawing the chart description text that is rendered above the chart.
 */
QFont QChart::titleFont() const
{
    if (d_ptr->m_presenter->m_titleItem)
        return d_ptr->m_presenter->m_titleItem->font();
    else
        return QFont();
}

/*!
 Sets the \a brush used for rendering the title text.
 */
void QChart::setTitleBrush(const QBrush &brush)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartTitleItem();
    d_ptr->m_presenter->m_titleItem->setBrush(brush);
    d_ptr->m_presenter->updateLayout();
}

/*!
 Returns the brush used for rendering the title text.
 */
QBrush QChart::titleBrush() const
{
    //TODO: refactor me
    if (!d_ptr->m_presenter->m_titleItem) return QBrush();
    return d_ptr->m_presenter->m_titleItem->brush();
}

/*!
 Sets the \a theme used by the chart for rendering the graphical representation of the data.

 Note: changing the theme will overwrite all customizations (pen, brush, font, ect.) done to the series.
 \sa theme()
 */
void QChart::setTheme(QChart::ChartTheme theme)
{
    d_ptr->m_presenter->setTheme(theme);
}

/*!
 Returns the theme enum used by the chart.
 \sa ChartTheme, setTheme()
 */
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
QAxis* QChart::axisX() const
{
    return d_ptr->m_dataset->axisX();
}

/*!
 Returns the pointer to the y axis object of the \a series
 If no \a series is provided then default Y axis of the chart is returned.
 */
QAxis* QChart::axisY(QAbstractSeries *series) const
{
    return d_ptr->m_dataset->axisY(series);
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
 Resizes and updates the chart area using the \a event data
 */
void QChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    d_ptr->m_rect = QRectF(QPoint(0,0),event->newSize());
    QGraphicsWidget::resizeEvent(event);
    d_ptr->m_presenter->setGeometry(d_ptr->m_rect);
}

/*!
 Sets animation \a options for the chart
 */
void QChart::setAnimationOptions(AnimationOptions options)
{
    d_ptr->m_presenter->setAnimationOptions(options);
}

/*!
 Returns animation options for the chart
 */
QChart::AnimationOptions QChart::animationOptions() const
{
    return d_ptr->m_presenter->animationOptions();
}

/*!
    Scrolls the visible area of the chart to the left by the distance between two x axis ticks
 */
void QChart::scrollLeft()
{
    d_ptr->m_presenter->scroll(-d_ptr->m_presenter->chartGeometry().width()/(axisX()->ticksCount()-1),0);
}

/*!
    Scrolls the visible area of the chart to the right by the distance between two x axis ticks
 */
void QChart::scrollRight()
{
    d_ptr->m_presenter->scroll(d_ptr->m_presenter->chartGeometry().width()/(axisX()->ticksCount()-1),0);
}

/*!
    Scrolls the visible area of the chart up by the distance between two y axis ticks
 */
void QChart::scrollUp()
{
    d_ptr->m_presenter->scroll(0,d_ptr->m_presenter->chartGeometry().width()/(axisY()->ticksCount()-1));
}

/*!
    Scrolls the visible area of the chart down by the distance between two y axis ticks
 */
void QChart::scrollDown()
{
    d_ptr->m_presenter->scroll(0,-d_ptr->m_presenter->chartGeometry().width()/(axisY()->ticksCount()-1));
}

/*!
    Scrolls the visible area of the chart by the distance defined in the \a delta.
 */
void QChart::scroll(const QPointF &delta)
{
    d_ptr->m_presenter->scroll(-delta.x(), delta.y());
}

/*!
    Sets the chart background visibility state to \a visible
 */
void QChart::setBackgroundVisible(bool visible)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartBackgroundItem();
    d_ptr->m_presenter->m_backgroundItem->setVisible(visible);
}

/*!
    Returns the chart's background visibility state
 */
bool QChart::isBackgroundVisible() const
{
    //TODO: refactor me
    if (!d_ptr->m_presenter->m_backgroundItem)
        return false;

    return d_ptr->m_presenter->m_backgroundItem->isVisible();
}

/*!
    Sets the background drop shadow effect state to \a enabled.
*/
void QChart::setDropShadowEnabled(bool enabled)
{
    d_ptr->m_presenter->createChartBackgroundItem();
    d_ptr->m_presenter->m_backgroundItem->setDropShadowEnabled(enabled);
}

/*!
    Returns true if the drop shadow effect is enabled for the chart background.
*/
bool QChart::isDropShadowEnabled() const
{
    if (!d_ptr->m_presenter->m_backgroundItem)
        return false;

    return d_ptr->m_presenter->m_backgroundItem->isDropShadowEnabled();
}

/*!
  Returns all the series that are added to the chart.

  \sa addSeries(), removeSeries(), removeAllSeries()
*/
QList<QAbstractSeries*> QChart::series() const
{
    return d_ptr->m_dataset->series();
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
    QObject::connect(m_dataset,SIGNAL(axisAdded(QAxis*,Domain*)),m_presenter,SLOT(handleAxisAdded(QAxis*,Domain*)));
    QObject::connect(m_dataset,SIGNAL(axisRemoved(QAxis*)),m_presenter,SLOT(handleAxisRemoved(QAxis*)));
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
