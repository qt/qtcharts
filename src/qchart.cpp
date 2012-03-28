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

 \value ChartThemeDefault Follows the GUI style of the Operating System
 \value ChartThemeLight
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
d_ptr(new QChartPrivate(this))
{
    d_ptr->m_legend = new QLegend(this);
    d_ptr->m_dataset = new ChartDataSet(this);
    d_ptr->m_presenter = new ChartPresenter(this,d_ptr->m_dataset);

    connect(d_ptr->m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),d_ptr->m_legend,SLOT(handleSeriesAdded(QSeries*,Domain*)));
    connect(d_ptr->m_dataset,SIGNAL(seriesRemoved(QSeries*)),d_ptr->m_legend,SLOT(handleSeriesRemoved(QSeries*)));
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
    d_ptr->createChartBackgroundItem();
    d_ptr->m_backgroundItem->setBrush(brush);
    d_ptr->m_backgroundItem->update();
}

QBrush QChart::backgroundBrush() const
{
    if (!d_ptr->m_backgroundItem) return QBrush();
    return (d_ptr->m_backgroundItem)->brush();
}

/*!
 Sets the \a pen that is used for painting the background of the chart area.
 */
void QChart::setBackgroundPen(const QPen& pen)
{
    d_ptr->createChartBackgroundItem();
    d_ptr->m_backgroundItem->setPen(pen);
    d_ptr->m_backgroundItem->update();
}

QPen QChart::backgroundPen() const
{
    if (!d_ptr->m_backgroundItem) return QPen();
    return d_ptr->m_backgroundItem->pen();
}

/*!
 Sets the chart \a title. The description text that is drawn above the chart.
 */
void QChart::setTitle(const QString& title)
{
    d_ptr->createChartTitleItem();
    d_ptr->m_titleItem->setText(title);
    d_ptr->updateLayout();
}

/*!
 Returns the chart title. The description text that is drawn above the chart.
 */
QString QChart::title() const
{
    if (d_ptr->m_titleItem)
    return d_ptr->m_titleItem->text();
    else
    return QString();
}

/*!
 Sets the \a font that is used for rendering the description text that is rendered above the chart.
 */
void QChart::setTitleFont(const QFont& font)
{
    d_ptr->createChartTitleItem();
    d_ptr->m_titleItem->setFont(font);
    d_ptr->updateLayout();
}

/*!
 Sets the \a brush used for rendering the title text.
 */
void QChart::setTitleBrush(const QBrush &brush)
{
    d_ptr->createChartTitleItem();
    d_ptr->m_titleItem->setBrush(brush);
    d_ptr->updateLayout();
}

/*!
 Returns the brush used for rendering the title text.
 */
QBrush QChart::titleBrush() const
{
    if (!d_ptr->m_titleItem) return QBrush();
    return d_ptr->m_titleItem->brush();
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
QLegend& QChart::legend() const
{
    return *d_ptr->m_legend;
}

/*!
 Gives ownership of legend to user.
 */
QLegend* QChart::takeLegend()
{
    QLegend* l = d_ptr->m_legend;
    d_ptr->m_legend = 0;
    return l;
}

/*!
 Gives ownership of legend back to chart. QChart takes ownership of \a legend and deletes existing one
 */
void QChart::giveLegend(QLegend *legend)
{
    if (d_ptr->m_legend) {
        // Should not happen.
        qDebug() << "Warning! Giving more than one legend to chart.";
        delete d_ptr->m_legend;
    }

    d_ptr->m_legend = legend;

    // Reconnect legend, in case not already connected.
    disconnect(d_ptr->m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),d_ptr->m_legend,SLOT(handleSeriesAdded(QSeries*,Domain*)));
    disconnect(d_ptr->m_dataset,SIGNAL(seriesRemoved(QSeries*)),d_ptr->m_legend,SLOT(handleSeriesRemoved(QSeries*)));
    connect(d_ptr->m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),d_ptr->m_legend,SLOT(handleSeriesAdded(QSeries*,Domain*)));
    connect(d_ptr->m_dataset,SIGNAL(seriesRemoved(QSeries*)),d_ptr->m_legend,SLOT(handleSeriesRemoved(QSeries*)));
}

/*!
 Resizes and updates the chart area using the \a event data
 */
void QChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    d_ptr->m_rect = QRectF(QPoint(0,0),event->newSize());
    d_ptr->updateLayout();
    QGraphicsWidget::resizeEvent(event);
    update();
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
    d_ptr->m_presenter->scroll(-d_ptr->m_presenter->geometry().width()/(axisX()->ticksCount()-1),0);
}

void QChart::scrollRight()
{
    d_ptr->m_presenter->scroll(d_ptr->m_presenter->geometry().width()/(axisX()->ticksCount()-1),0);
}

void QChart::scrollUp()
{
    d_ptr->m_presenter->scroll(0,d_ptr->m_presenter->geometry().width()/(axisY()->ticksCount()-1));
}

void QChart::scrollDown()
{
    d_ptr->m_presenter->scroll(0,-d_ptr->m_presenter->geometry().width()/(axisY()->ticksCount()-1));
}

void QChart::setBackgroundVisible(bool visible)
{
    d_ptr->createChartBackgroundItem();
    d_ptr->m_backgroundItem->setVisible(visible);
}

bool QChart::isBackgroundVisible() const
{
    if (!d_ptr->m_backgroundItem) return false;
    return d_ptr->m_backgroundItem->isVisible();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartPrivate::QChartPrivate(QChart *parent):
q_ptr(parent),
m_backgroundItem(0),
m_titleItem(0),
m_legend(0),
m_dataset(0),
m_presenter(0)
{

}

QChartPrivate::~QChartPrivate()
{

}

void QChartPrivate::createChartBackgroundItem()
{
    if (!m_backgroundItem) {
        m_backgroundItem = new ChartBackground(q_ptr);
        m_backgroundItem->setPen(Qt::NoPen);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void QChartPrivate::createChartTitleItem()
{
    if (!m_titleItem) {
        m_titleItem = new QGraphicsSimpleTextItem(q_ptr);
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void QChartPrivate::updateLegendLayout()
{
    int padding = m_presenter->padding();
    QRectF plotRect = m_rect.adjusted(padding,padding,-padding,-padding);
    QRectF legendRect;

    switch (m_legend->alignment())
    {
        case QLegend::LayoutTop: {
            legendRect = plotRect.adjusted(0,0,0,-padding - plotRect.height());
            break;
        }
        case QLegend::LayoutBottom: {
            legendRect = plotRect.adjusted(padding,padding + plotRect.height(),-padding,0);
            break;
        }
        case QLegend::LayoutLeft: {
            legendRect = plotRect.adjusted(0,padding,-padding - plotRect.width(),-padding);
            break;
        }
        case QLegend::LayoutRight: {
            legendRect = plotRect.adjusted(padding + plotRect.width(),padding,0,-padding);
            break;
        }
        default: {
            legendRect = plotRect;
            break;
        }
    }

    m_legend->setMaximumSize(legendRect.size());
    m_legend->setPos(legendRect.topLeft());
}

void QChartPrivate::updateLayout()
{
    if (!m_rect.isValid()) return;

    int padding = m_presenter->padding();
    int backgroundPadding = m_presenter->backgroundPadding();

    // recalculate title position
    if (m_titleItem) {
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),m_rect.top()/2 + padding/2);
    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(m_rect.adjusted(backgroundPadding,backgroundPadding, -backgroundPadding, -backgroundPadding));
    }

    // recalculate legend position
    if (m_legend) {
        if (m_legend->parentObject() == q_ptr) {
            updateLegendLayout();
        }
    }
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
