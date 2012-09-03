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
#include <QDeclarativeEngine>
#include "declarativelineseries.h"
#include "declarativeareaseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include "declarativesplineseries.h"
#include "declarativescatterseries.h"
#include "qbarcategoryaxis.h"
#include "qvalueaxis.h"
#include "qcategoryaxis.h"
#include "qabstractseries_p.h"
#include "declarativemargins.h"

#ifndef QT_ON_ARM
    #include "qdatetimeaxis.h"
#endif

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
  Deprecated. Use minimumMargins and plotArea instead.
*/

/*!
  \qmlproperty real ChartView::bottomMargin
  Deprecated. Use minimumMargins and plotArea instead.
*/

/*!
  \qmlproperty real ChartView::leftMargin
  Deprecated. Use minimumMargins and plotArea instead.
*/

/*!
  \qmlproperty real ChartView::rightMargin
  Deprecated. Use minimumMargins and plotArea instead.
*/

/*!
  \qmlproperty Margins ChartView::minimumMargins
  The minimum margins allowed between the outer bounds and the plotArea of the ChartView. Margins
  area of ChartView is used for drawing title, axes and legend. Please note that setting the
  properties of minimumMargins may be bigger than the defined value, depending on other ChartView
  properties that affect it's layout. If you need to know the actual plotting area used at any
  given time, you can check ChartView::plotArea instead.
*/

/*!
  \qmlproperty rect ChartView::plotArea
  The area on the ChartView that is used for drawing series. This is the ChartView rect without the
  margins.
  \sa ChartView::minimumMargins
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
  \sa ValueAxis::min, ValueAxis::max, BarCategoryAxis::min, BarCategoryAxis::max
*/

/*!
  \qmlmethod ChartView::scrollRight(real pixels)
  Scrolls to right by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValueAxis::min, ValueAxis::max, BarCategoryAxis::min, BarCategoryAxis::max
*/

/*!
  \qmlmethod ChartView::scrollUp(real pixels)
  Scrolls up by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValueAxis::min, ValueAxis::max, BarCategoryAxis::min, BarCategoryAxis::max
*/

/*!
  \qmlmethod ChartView::scrollDown(real pixels)
  Scrolls down by \a pixels. This is a convenience function that suits for example for key navigation.
  \sa ValueAxis::min, ValueAxis::max, BarCategoryAxis::min, BarCategoryAxis::max
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
    m_minMargins = new DeclarativeMargins(this);
    connect(m_minMargins, SIGNAL(topChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_minMargins, SIGNAL(bottomChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_minMargins, SIGNAL(leftChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_minMargins, SIGNAL(rightChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    // TODO: connect to plotAreaChanged signal from m_chart
}

void DeclarativeChart::changeMinimumMargins(int top, int bottom, int left, int right)
{
    m_chart->setMinimumMargins(QMargins(left, top, right, bottom));
    plotAreaChanged(m_chart->plotArea());
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
            // Add series to the chart
            QAbstractSeries *series = qobject_cast<QAbstractSeries *>(child);
            m_chart->addSeries(series);

            // Set optional user defined axes and connect axis related signals
            if (qobject_cast<DeclarativeLineSeries *>(child)) {
                DeclarativeLineSeries *s = qobject_cast<DeclarativeLineSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeSplineSeries *>(child)) {
                DeclarativeSplineSeries *s = qobject_cast<DeclarativeSplineSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeScatterSeries *>(child)) {
                DeclarativeScatterSeries *s = qobject_cast<DeclarativeScatterSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeAreaSeries *>(child)) {
                DeclarativeAreaSeries *s = qobject_cast<DeclarativeAreaSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeBarSeries *>(child)) {
                DeclarativeBarSeries *s = qobject_cast<DeclarativeBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeStackedBarSeries *>(child)) {
                DeclarativeStackedBarSeries *s = qobject_cast<DeclarativeStackedBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativePercentBarSeries *>(child)) {
                DeclarativePercentBarSeries *s = qobject_cast<DeclarativePercentBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeHorizontalBarSeries *>(child)) {
                DeclarativeHorizontalBarSeries *s = qobject_cast<DeclarativeHorizontalBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeHorizontalStackedBarSeries *>(child)) {
                DeclarativeHorizontalStackedBarSeries *s = qobject_cast<DeclarativeHorizontalStackedBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            } else if (qobject_cast<DeclarativeHorizontalPercentBarSeries *>(child)) {
                DeclarativeHorizontalPercentBarSeries *s = qobject_cast<DeclarativeHorizontalPercentBarSeries *>(child);
                connect(s, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(s, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                setAxisX(s->axisX(), s);
                setAxisY(s->axisY(), s);
            }

            // Create the missing axes for the series that cannot be painted without axes
            createDefaultAxes(series);
        } else if(qobject_cast<QAbstractAxis *>(child)) {
            // Do nothing, axes are set for the chart in the context of series
        }
    }

    QDeclarativeItem::componentComplete();
}

void DeclarativeChart::handleAxisXSet(QAbstractAxis* axis)
{
//    qDebug() << "DeclarativeChart::handleAxisXSet" << sender() << axis;
    if (axis && qobject_cast<DeclarativeLineSeries *>(sender())) {
        m_chart->setAxisX(axis, qobject_cast<DeclarativeLineSeries *>(sender()));
    }
}

void DeclarativeChart::handleAxisYSet(QAbstractAxis* axis)
{
//    qDebug() << "DeclarativeChart::handleAxisYSet" << sender() << axis;
    if (axis && qobject_cast<DeclarativeLineSeries *>(sender())) {
        m_chart->setAxisY(axis, qobject_cast<DeclarativeLineSeries *>(sender()));
    }
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
    qWarning() << "ChartView.topMargin is deprecated. Use minimumMargins and plotArea instead.";
    return m_chart->plotArea().top();
}

qreal DeclarativeChart::bottomMargin()
{
    qWarning() << "ChartView.bottomMargin is deprecated. Use minimumMargins and plotArea instead.";
    return m_chart->plotArea().bottom();
}

qreal DeclarativeChart::leftMargin()
{
    qWarning() << "ChartView.leftMargin is deprecated. Use minimumMargins and plotArea instead.";
    return m_chart->plotArea().left();
}

qreal DeclarativeChart::rightMargin()
{
    qWarning() << "ChartView.rightMargin is deprecated. Use minimumMargins and plotArea instead.";
    return m_chart->plotArea().right();
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
    case DeclarativeChart::SeriesTypeHorizontalBar:
        series = new DeclarativeHorizontalBarSeries();
        break;
    case DeclarativeChart::SeriesTypeHorizontalPercentBar:
        series = new DeclarativeHorizontalPercentBarSeries();
        break;
    case DeclarativeChart::SeriesTypeHorizontalStackedBar:
        series = new DeclarativeHorizontalStackedBarSeries();
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

    if (series) {
        series->setName(name);
        m_chart->addSeries(series);
        createDefaultAxes(series);
    }

    return series;
}

void DeclarativeChart::setAxisX(QAbstractAxis *axis, QAbstractSeries *series)
{
    if (axis)
        m_chart->setAxisX(axis, series);
}

void DeclarativeChart::setAxisY(QAbstractAxis *axis, QAbstractSeries *series)
{
    if (axis)
        m_chart->setAxisY(axis, series);
}

void DeclarativeChart::createDefaultAxes()
{
    qWarning() << "ChartView.createDefaultAxes() is deprecated. Axes are created automatically.";
}

void DeclarativeChart::createDefaultAxes(QAbstractSeries* series)
{
    foreach (QAbstractSeries *s, m_chart->series()) {
        // If there is already an x axis of the correct type, re-use it
        if (!m_chart->axisX(series) && s != series && m_chart->axisX(s)
                && m_chart->axisX(s)->type() == series->d_ptr->defaultAxisType(Qt::Horizontal))
            m_chart->setAxisX(m_chart->axisX(s), series);

        // If there is already a y axis of the correct type, re-use it
        if (!m_chart->axisY(series) && s != series && m_chart->axisY(s)
                && m_chart->axisY(s)->type() == series->d_ptr->defaultAxisType(Qt::Vertical))
            m_chart->setAxisY(m_chart->axisY(s), series);
    }

    // If no x axis of correct type was found, create a new x axis based of default axis type
    if (!m_chart->axisX(series)) {
        switch (series->d_ptr->defaultAxisType(Qt::Horizontal)) {
        case QAbstractAxis::AxisTypeValue:
            m_chart->setAxisX(new QValueAxis(this), series);
            break;
        case QAbstractAxis::AxisTypeBarCategory:
            m_chart->setAxisX(new QBarCategoryAxis(this), series);
            break;
        case QAbstractAxis::AxisTypeCategory:
            m_chart->setAxisX(new QCategoryAxis(this), series);
            break;
#ifndef QT_ON_ARM
        case QAbstractAxis::AxisTypeDateTime:
            m_chart->setAxisX(new QDateTimeAxis(this), series);
            break;
#endif
        default:
            // Do nothing, assume AxisTypeNoAxis
            break;
        }
    }

    // If no y axis of correct type was found, create a new y axis based of default axis type
    if (!m_chart->axisY(series)) {
        switch (series->d_ptr->defaultAxisType(Qt::Vertical)) {
        case QAbstractAxis::AxisTypeValue:
            m_chart->setAxisY(new QValueAxis(this), series);
            break;
        case QAbstractAxis::AxisTypeBarCategory:
            m_chart->setAxisY(new QBarCategoryAxis(this), series);
            break;
        case QAbstractAxis::AxisTypeCategory:
            m_chart->setAxisY(new QCategoryAxis(this), series);
            break;
#ifndef QT_ON_ARM
        case QAbstractAxis::AxisTypeDateTime:
            m_chart->setAxisY(new QDateTimeAxis(this), series);
            break;
#endif
        default:
            // Do nothing, assume AxisTypeNoAxis
            break;
        }
    }

    //qDebug() << "axis for series" << series << "x:" << m_chart->axisX(series) << "y:" << m_chart->axisY(series);
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
