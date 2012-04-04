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
 \value ChartThemeCount Not really a theme; the total count of themes.
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
 representation of different types of QChartSeries and other chart related objects like
 QChartAxis and QChartLegend. If you simply want to show a chart in a layout, you can use the
 convenience class QChartView instead of QChart.
 \sa QChartView
 */

/*!
 Constructs a chart object which is a child of a\a parent. Parameter \a wFlags is passed to the QGraphicsWidget constructor.
 */
QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
d_ptr(new QChartPrivate())
{
    d_ptr->m_legend = new  ScrolledQLegend(this);
    d_ptr->m_dataset = new ChartDataSet(this);
    d_ptr->m_presenter = new ChartPresenter(this,d_ptr->m_dataset);
    d_ptr->m_presenter->setTheme(QChart::ChartThemeLight, false);
    d_ptr->createConnections();
    //TODO:fix me setMinimumSize(d_ptr->m_padding.left() * 3, d_ptr->m_padding.top() * 3);
}

/*!
 Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
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
 */
void QChart::addSeries(QSeries* series, QChartAxis* axisY)
{
    d_ptr->m_dataset->addSeries(series, axisY);
}

/*!
 Removes the \a series specified in a perameter from the QChartView.
 It releses its ownership of the specified QChartSeries object.
 It does not delete the pointed QChartSeries data object
 \sa addSeries(), removeAllSeries()
 */
void QChart::removeSeries(QSeries* series)
{
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
 Sets the \a font that is used for rendering the description text that is rendered above the chart.
 */
void QChart::setTitleFont(const QFont& font)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartTitleItem();
    d_ptr->m_presenter->m_titleItem->setFont(font);
    d_ptr->m_presenter->updateLayout();
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
 Sets the \a theme used by the chart for rendering the graphical representation of the data
 \sa ChartTheme, chartTheme()
 */
void QChart::setTheme(QChart::ChartTheme theme)
{
    d_ptr->m_presenter->setTheme(theme);
}

/*!
 Returns the theme enum used by the chart.
 \sa ChartTheme, setChartTheme()
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
    d_ptr->m_presenter->zoomIn();
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
    d_ptr->m_presenter->zoomOut();
}

/*!
 Returns the pointer to the x axis object of the chart
 */
QChartAxis* QChart::axisX() const
{
    return d_ptr->m_dataset->axisX();
}

/*!
 Returns the pointer to the y axis object of the chart
 */
QChartAxis* QChart::axisY() const
{
    return d_ptr->m_dataset->axisY();
}

/*!
 Returns the legend object of the chart. Ownership stays in chart.
 */
QLegend* QChart::legend() const
{
    return d_ptr->m_legend;
}

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

void QChart::scrollLeft()
{
    d_ptr->m_presenter->scroll(-d_ptr->m_presenter->chartGeometry().width()/(axisX()->ticksCount()-1),0);
}

void QChart::scrollRight()
{
    d_ptr->m_presenter->scroll(d_ptr->m_presenter->chartGeometry().width()/(axisX()->ticksCount()-1),0);
}

void QChart::scrollUp()
{
    d_ptr->m_presenter->scroll(0,d_ptr->m_presenter->chartGeometry().width()/(axisY()->ticksCount()-1));
}

void QChart::scrollDown()
{
    d_ptr->m_presenter->scroll(0,-d_ptr->m_presenter->chartGeometry().width()/(axisY()->ticksCount()-1));
}

void QChart::setBackgroundVisible(bool visible)
{
    //TODO: refactor me
    d_ptr->m_presenter->createChartBackgroundItem();
    d_ptr->m_presenter->m_backgroundItem->setVisible(visible);
}

bool QChart::isBackgroundVisible() const
{
    //TODO: refactor me
    if (!d_ptr->m_presenter->m_backgroundItem) return false;
    return d_ptr->m_presenter->m_backgroundItem->isVisible();
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
   QObject::connect(m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),m_legend,SLOT(handleSeriesAdded(QSeries*,Domain*)));
   QObject::connect(m_dataset,SIGNAL(seriesRemoved(QSeries*)),m_legend,SLOT(handleSeriesRemoved(QSeries*)));
   QObject::connect(m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),m_presenter,SLOT(handleSeriesAdded(QSeries*,Domain*)));
   QObject::connect(m_dataset,SIGNAL(seriesRemoved(QSeries*)),m_presenter,SLOT(handleSeriesRemoved(QSeries*)));
   QObject::connect(m_dataset,SIGNAL(axisAdded(QChartAxis*,Domain*)),m_presenter,SLOT(handleAxisAdded(QChartAxis*,Domain*)));
   QObject::connect(m_dataset,SIGNAL(axisRemoved(QChartAxis*)),m_presenter,SLOT(handleAxisRemoved(QChartAxis*)));
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
