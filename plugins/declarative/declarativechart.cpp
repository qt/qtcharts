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

#include "declarativechart.h"
#include <QPainter>
#include "declarativelineseries.h"
#include "declarativeareaseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include "declarativesplineseries.h"
#include "declarativescatterseries.h"
#include "qbarcategoriesaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \qmlclass ChartView DeclarativeChart

    ChartView element is the parent that is responsible for showing different chart series types.

    The following QML shows how to create a simple chart with one pie series:
    \snippet ../examples/qmlpiechart/qml/qmlpiechart/main.qml 1
    \snippet ../examples/qmlpiechart/qml/qmlpiechart/main.qml 2
    \snippet ../examples/qmlpiechart/qml/qmlpiechart/main.qml 3

    \beginfloatleft
    \image examples_qmlpiechart.png
    \endfloat
    \clearfloat
*/

/*!
  \qmlproperty Theme ChartView::theme
  Theme defines the visual appearance of the chart, including for example colors, fonts, line
  widths and chart background.
*/

/*!
  \qmlproperty Animation ChartView::animation
  Animation configuration of the chart. One of ChartView.NoAnimation, ChartView.GridAxisAnimations,
  ChartView.SeriesAnimations or ChartView.AllAnimations.
*/

/*!
  \qmlproperty Font ChartView::titleFont
  The title font of the chart

  See the \l {Font} {QML Font Element} for detailed documentation.
*/

/*!
  \qmlproperty string ChartView::title
  The title of the chart, shown on top of the chart.
  \sa ChartView::titleColor
*/

/*!
  \qmlproperty string ChartView::titleColor
  The color of the title text.
*/

/*!
  \qmlproperty Axis ChartView::axisX
  The x-axis of the chart.
*/

/*!
  \qmlproperty Axis ChartView::axisY
  The default y-axis of the chart.
*/

/*!
  \qmlproperty Legend ChartView::legend
  The legend of the chart. Legend lists all the series, pie slices and bar sets added on the chart.
*/

/*!
  \qmlproperty int ChartView::count
  The count of series added to the chart.
*/

/*!
  \qmlproperty color ChartView::backgroundColor
  The color of the chart's background. By default background color is defined by chart theme.
  \sa ChartView::theme
*/

/*!
  \qmlproperty bool ChartView::dropShadowEnabled
  The chart's border drop shadow. Set to true to enable drop shadow.
*/

/*!
  \qmlproperty real ChartView::topMargin
  The space between the top of chart view and the top of the plot area. The title (if non-empty) is drawn on top margin
  area of the chart view. Top margin area is also used by legend, if aligned to top.
*/

/*!
  \qmlproperty real ChartView::bottomMargin
  The space between the bottom of chart view and the bottom of the plot area. The bottom margin area may be used by
  legend (if aligned to bottom), x-axis, x-axis labels and x-axis tick marks.
*/

/*!
  \qmlproperty real ChartView::leftMargin
  The space between the left side of chart view and the left side of the plot area. The left margin area may be used by
  legend (if aligned to left), y-axis, y-axis labels and y-axis tick marks.
*/

/*!
  \qmlproperty real ChartView::rightMargin
  The space between the right side of chart view and the right side of the plot area. The right margin area may be used
  by legend (if aligned to right).
*/

/*!
  \qmlmethod AbstractSeries ChartView::series(int index)
  Returns the series with \a index on the chart. This allows you to loop through the series of a chart together with
  the count property of the chart.
*/

/*!
  \qmlmethod AbstractSeries ChartView::series(string name)
  Returns the first series on the chart with \a name. If there is no series with that name, returns null.
*/

/*!
  \qmlmethod AbstractSeries ChartView::createSeries(SeriesType type, string name)
  Creates a series object of \a type to the chart. For example:
  \code
    var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter series");
    scatter.markerSize = 22;
    scatter.append(1.1, 2.0);
  \endcode
*/

/*!
  \qmlmethod Axis ChartView::axisY(QAbstractSeries *series)
  The y-axis of the series. This is the same as the default y-axis of the chart as multiple y-axes are not yet supported.
*/

/*!
  \qmlmethod ChartView::zoomY(real factor)
  Zooms in by \a factor on the center of the chart.
*/

/*!
  \qmlmethod ChartView::scrollLeft(real pixels)
  Scrolls to left by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValuesAxis::min, ValuesAxis::max, BarCategoriesAxis::min, BarCategoriesAxis::max
*/

/*!
  \qmlmethod ChartView::scrollRight(real pixels)
  Scrolls to right by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValuesAxis::min, ValuesAxis::max, BarCategoriesAxis::min, BarCategoriesAxis::max
*/

/*!
  \qmlmethod ChartView::scrollUp(real pixels)
  Scrolls up by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValuesAxis::min, ValuesAxis::max, BarCategoriesAxis::min, BarCategoriesAxis::max
*/

/*!
  \qmlmethod ChartView::scrollDown(real pixels)
  Scrolls down by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValuesAxis::min, ValuesAxis::max, BarCategoriesAxis::min, BarCategoriesAxis::max
*/

/*!
  \qmlsignal ChartView::onTopMarginChanged(real margin)
  The top margin of the chart view has changed to \a margin. This may happen for example if you modify font size
  related properties of the legend or chart title.
*/

/*!
  \qmlsignal ChartView::onBottomMarginChanged(real margin)
  The bottom margin of the chart view has changed to \a margin. This may happen for example if you modify font size
  related properties of the legend or chart title.
*/

/*!
  \qmlsignal ChartView::onLeftMarginChanged(real margin)
  The left margin of the chart view has changed to \a margin. This may happen for example if you modify font size
  related properties of the legend or chart title.
*/

/*!
  \qmlsignal ChartView::onRightMarginChanged(real margin)
  The right margin of the chart view has changed to \a margin. This may happen for example if you modify font size
  related properties of the legend or chart title.
*/

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
//    m_chart->axisX()->setNiceNumbersEnabled(false);
    m_chartMargins = m_chart->margins();
    connect(m_chart, SIGNAL(marginsChanged(QRectF)), this, SLOT(handleMarginsChanged(QRectF)));
}

void DeclarativeChart::handleMarginsChanged(QRectF newMargins)
{
    if (m_chartMargins.top() != newMargins.top())
        topMarginChanged(m_chart->margins().top());
    if (m_chartMargins.bottom() != newMargins.bottom())
        bottomMarginChanged(m_chart->margins().bottom());
    if (m_chartMargins.left() != newMargins.left())
        leftMarginChanged(m_chart->margins().left());
    if (m_chartMargins.right() != newMargins.right())
        rightMarginChanged(m_chart->margins().right());

    m_chartMargins = m_chart->margins();
}

DeclarativeChart::~DeclarativeChart()
{
    delete m_chart;
}

void DeclarativeChart::childEvent(QChildEvent *event)
{
    if (event->type() == QEvent::ChildAdded) {
        if (qobject_cast<QAbstractSeries *>(event->child())) {
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(event->child()));
        }
    }
}

void DeclarativeChart::componentComplete()
{
    foreach(QObject *child, children()) {
        if (qobject_cast<QAbstractSeries *>(child)) {
//            qDebug() << "DeclarativeChart::componentComplete(), add: " << child;
            // TODO: how about optional y-axis?
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(child));
        }else if(qobject_cast<QAbstractAxis *>(child)){

        }
    }
    QDeclarativeItem::componentComplete();
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
//    qDebug() << "DeclarativeChart::geometryChanged" << newGeometry.width() << newGeometry.height();
    if (newGeometry.isValid()) {
        if (newGeometry.width() > 0 && newGeometry.height() > 0) {
            m_chart->resize(newGeometry.width(), newGeometry.height());
        }
    }
    QDeclarativeItem::geometryChanged(newGeometry, oldGeometry);
}

void DeclarativeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    // TODO: optimized?
    painter->setRenderHint(QPainter::Antialiasing, true);
}

void DeclarativeChart::setTheme(DeclarativeChart::Theme theme)
{
    QChart::ChartTheme chartTheme = (QChart::ChartTheme) theme;
    if (chartTheme != m_chart->theme())
        m_chart->setTheme(chartTheme);
}

DeclarativeChart::Theme DeclarativeChart::theme()
{
    return (DeclarativeChart::Theme) m_chart->theme();
}

void DeclarativeChart::setAnimationOptions(DeclarativeChart::Animation animations)
{
    QChart::AnimationOption animationOptions = (QChart::AnimationOption) animations;
    if (animationOptions != m_chart->animationOptions())
        m_chart->setAnimationOptions(animationOptions);
}

DeclarativeChart::Animation DeclarativeChart::animationOptions()
{
    if (m_chart->animationOptions().testFlag(QChart::AllAnimations))
        return DeclarativeChart::AllAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::GridAxisAnimations))
        return DeclarativeChart::GridAxisAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::SeriesAnimations))
        return DeclarativeChart::SeriesAnimations;
    else
        return DeclarativeChart::NoAnimation;
}

void DeclarativeChart::setTitle(QString title)
{
    if (title != m_chart->title())
        m_chart->setTitle(title);
}
QString DeclarativeChart::title()
{
    return m_chart->title();
}

QAbstractAxis *DeclarativeChart::axisX(QAbstractSeries *series)
{
    return m_chart->axisX(series);
}

QAbstractAxis *DeclarativeChart::axisY(QAbstractSeries *series)
{
    return m_chart->axisY(series);
}

QLegend *DeclarativeChart::legend()
{
    return m_chart->legend();
}

void DeclarativeChart::setTitleColor(QColor color)
{
    QBrush b = m_chart->titleBrush();
    if (color != b.color()) {
        b.setColor(color);
        m_chart->setTitleBrush(b);
        emit titleColorChanged(color);
    }
}

QFont DeclarativeChart::titleFont() const
{
    return m_chart->titleFont();
}

void DeclarativeChart::setTitleFont(const QFont& font)
{
    m_chart->setTitleFont(font);
}

QColor DeclarativeChart::titleColor()
{
    return m_chart->titleBrush().color();
}

void DeclarativeChart::setBackgroundColor(QColor color)
{
    QBrush b = m_chart->backgroundBrush();
    if (b.style() != Qt::SolidPattern || color != b.color()) {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        m_chart->setBackgroundBrush(b);
        emit backgroundColorChanged();
    }
}

QColor DeclarativeChart::backgroundColor()
{
    return m_chart->backgroundBrush().color();
}

int DeclarativeChart::count()
{
    return m_chart->series().count();
}

void DeclarativeChart::setDropShadowEnabled(bool enabled)
{
    if (enabled != m_chart->isDropShadowEnabled()) {
        m_chart->setDropShadowEnabled(enabled);
        dropShadowEnabledChanged(enabled);
    }
}

bool DeclarativeChart::dropShadowEnabled()
{
    return m_chart->isDropShadowEnabled();
}

qreal DeclarativeChart::topMargin()
{
    return m_chart->margins().top();
}

qreal DeclarativeChart::bottomMargin()
{
    return m_chart->margins().bottom();
}

qreal DeclarativeChart::leftMargin()
{
    return m_chart->margins().left();
}

qreal DeclarativeChart::rightMargin()
{
    return m_chart->margins().right();
}

void DeclarativeChart::zoom(qreal factor)
{
    m_chart->zoom(factor);
}

void DeclarativeChart::scrollLeft(qreal pixels)
{
    m_chart->scroll(pixels, 0);
}

void DeclarativeChart::scrollRight(qreal pixels)
{
    m_chart->scroll(-pixels, 0);
}

void DeclarativeChart::scrollUp(qreal pixels)
{
    m_chart->scroll(0, pixels);
}

void DeclarativeChart::scrollDown(qreal pixels)
{
    m_chart->scroll(0, -pixels);
}

QAbstractSeries *DeclarativeChart::series(int index)
{
    if (index < m_chart->series().count()) {
        return m_chart->series().at(index);
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::series(QString seriesName)
{
    foreach(QAbstractSeries *series, m_chart->series()) {
        if (series->name() == seriesName)
            return series;
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::createSeries(DeclarativeChart::SeriesType type, QString name)
{
    QAbstractSeries *series = 0;
    switch (type) {
    case DeclarativeChart::SeriesTypeLine:
        series = new DeclarativeLineSeries();
        break;
    case DeclarativeChart::SeriesTypeArea:
        series = new DeclarativeAreaSeries();
        break;
    case DeclarativeChart::SeriesTypeStackedBar:
        series = new DeclarativeStackedBarSeries();
        break;
    case DeclarativeChart::SeriesTypePercentBar:
        series = new DeclarativePercentBarSeries();
        break;
    case DeclarativeChart::SeriesTypeBar:
        series = new DeclarativeBarSeries();
        break;
    case DeclarativeChart::SeriesTypePie:
        series = new DeclarativePieSeries();
        break;
    case DeclarativeChart::SeriesTypeScatter:
        series = new DeclarativeScatterSeries();
        break;
    case DeclarativeChart::SeriesTypeSpline:
        series = new DeclarativeSplineSeries();
        break;
    default:
        qWarning() << "Illegal series type";
    }
    series->setName(name);
    m_chart->addSeries(series);
    return series;
}

void DeclarativeChart::setAxisX(QAbstractAxis* axis, QAbstractSeries *series)
{
    m_chart->setAxisX(axis,series);
}

void DeclarativeChart::setAxisY(QAbstractAxis* axis, QAbstractSeries *series)
{
    m_chart->setAxisY(axis,series);
}

void DeclarativeChart::createDefaultAxes()
{
    m_chart->createDefaultAxes();
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
