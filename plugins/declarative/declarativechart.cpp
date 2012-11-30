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
#include "chartdataset_p.h"
#include "declarativeaxes.h"
#include "qchart_p.h"

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
  \qmlproperty Animation ChartView::animationOptions
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
  \qmlproperty color ChartView::titleColor
  The color of the title text.
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
  \qmlmethod AbstractSeries ChartView::createSeries(SeriesType type, string name, AbstractAxis axisX, AbstractAxis axisY)
  Creates a series object of \a type to the chart with name \a name, optional axis \a axisX and
  optional axis \a axisY. For example:
  \code
    // lineSeries is a LineSeries object that has already been added to the ChartView; re-use it's axes
    var myAxisX = chartView.axisX(lineSeries);
    var myAxisY = chartView.axisY(lineSeries);
    var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter series", myAxisX, myAxisY);
  \endcode
*/

/*!
  \qmlmethod ChartView::removeSeries(AbstractSeries series)
  Removes the \a series from the chart. The series object is also destroyed.
*/

/*!
  \qmlmethod ChartView::removeAllSeries()
  Removes all series from the chart. All the series objects are also destroyed.
*/

/*!
  \qmlmethod Axis ChartView::axisX(AbstractSeries series)
  The x-axis of the series.
*/

/*!
  \qmlmethod Axis ChartView::axisY(AbstractSeries series)
  The y-axis of the series.
*/

/*!
  \qmlmethod ChartView::zoomY(real factor)
  Zooms in by \a factor on the center of the chart.
*/

/*!
  \qmlmethod ChartView::scrollLeft(real pixels)
  Scrolls to left by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollRight(real pixels)
  Scrolls to right by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollUp(real pixels)
  Scrolls up by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollDown(real pixels)
  Scrolls down by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlsignal ChartView::onPlotAreaChanged(rect plotArea)
  The plot area of the chart has changed. This may happen for example, if you modify minimumMargins
  or if you resize the chart, or if you modify font size related properties of the legend or chart
  title.
*/

/*!
  \qmlsignal ChartView::seriesAdded(AbstractSeries series)
  The \a series has been added to the chart.
*/

/*!
  \qmlsignal ChartView::seriesRemoved(AbstractSeries series)
  The \a series has been removed from the chart. Please note that \a series is no longer a valid
  object after the signal handler has completed.
*/

DeclarativeChart::DeclarativeChart(QDeclarativeItem *parent)
    : QDeclarativeItem(parent),
      m_chart(new QChart(this))
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
    m_margins = new DeclarativeMargins(this);
    m_margins->setTop(m_chart->margins().top());
    m_margins->setLeft(m_chart->margins().left());
    m_margins->setRight(m_chart->margins().right());
    m_margins->setBottom(m_chart->margins().bottom());
    connect(m_margins, SIGNAL(topChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(bottomChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(leftChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(rightChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*)), this, SLOT(handleSeriesAdded(QAbstractSeries*)));
    connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), this, SIGNAL(seriesRemoved(QAbstractSeries*)));
}

void DeclarativeChart::handleSeriesAdded(QAbstractSeries *series)
{
    emit seriesAdded(series);
}

void DeclarativeChart::changeMinimumMargins(int top, int bottom, int left, int right)
{
    m_chart->setMargins(QMargins(left, top, right, bottom));
    emit minimumMarginsChanged();
    emit plotAreaChanged(m_chart->plotArea());
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
    foreach (QObject *child, children()) {
        if (qobject_cast<QAbstractSeries *>(child)) {
            // Add series to the chart
            QAbstractSeries *series = qobject_cast<QAbstractSeries *>(child);
            m_chart->addSeries(series);

            // Connect to axis changed signals (unless this is a pie series)
            if (!qobject_cast<DeclarativePieSeries *>(series)) {
                connect(series, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SLOT(handleAxisYRightSet(QAbstractAxis*)));
            }

            initializeAxes(series);
        }
    }

    QDeclarativeItem::componentComplete();
}

void DeclarativeChart::handleAxisXSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Horizontal).contains(axis))
            m_chart->addAxis(axis, Qt::AlignBottom);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisX to null.";
    }
}

void DeclarativeChart::handleAxisXTopSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Horizontal).contains(axis))
            m_chart->addAxis(axis, Qt::AlignTop);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisXTop to null.";
    }
}

void DeclarativeChart::handleAxisYSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Vertical).contains(axis))
            m_chart->addAxis(axis, Qt::AlignLeft);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisY to null.";
    }
}

void DeclarativeChart::handleAxisYRightSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Vertical).contains(axis))
            m_chart->addAxis(axis, Qt::AlignRight);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisYRight to null.";
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

    // It would be better to trigger the plotAreaChanged signal from QChart::plotAreaChanged or
    // similar. Since that kind of a signal is not clearly needed in the C++ API the work-around is
    // to implement it here for the QML API purposes.
    emit plotAreaChanged(m_chart->plotArea());
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
    QList<QAbstractAxis *> axes = m_chart->axes(Qt::Horizontal, series);
    if (axes.count())
        return axes[0];
    return 0;
}

QAbstractAxis *DeclarativeChart::axisY(QAbstractSeries *series)
{
    QList<QAbstractAxis *> axes = m_chart->axes(Qt::Vertical, series);
    if (axes.count())
        return axes[0];
    return 0;
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

void DeclarativeChart::setTitleFont(const QFont &font)
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
    m_chart->scroll(-pixels, 0);
}

void DeclarativeChart::scrollRight(qreal pixels)
{
    m_chart->scroll(pixels, 0);
}

void DeclarativeChart::scrollUp(qreal pixels)
{
    m_chart->scroll(0, pixels);
}

void DeclarativeChart::scrollDown(qreal pixels)
{
    m_chart->scroll(0, -pixels);
}

QDeclarativeListProperty<QAbstractAxis> DeclarativeChart::axes()
{
    return QDeclarativeListProperty<QAbstractAxis>(this, 0,
                &DeclarativeChart::axesAppendFunc,
                &DeclarativeChart::axesCountFunc,
                &DeclarativeChart::axesAtFunc);
}

void DeclarativeChart::axesAppendFunc(QDeclarativeListProperty<QAbstractAxis> *list, QAbstractAxis *element)
{
    // Empty implementation
    Q_UNUSED(list);
    Q_UNUSED(element);
}

int DeclarativeChart::axesCountFunc(QDeclarativeListProperty<QAbstractAxis> *list)
{
    if (qobject_cast<DeclarativeChart *>(list->object)) {
        DeclarativeChart *chart = qobject_cast<DeclarativeChart *>(list->object);
        return chart->m_chart->axes(Qt::Horizontal | Qt::Vertical).count();
    }
    return 0;
}

QAbstractAxis *DeclarativeChart::axesAtFunc(QDeclarativeListProperty<QAbstractAxis> *list, int index)
{
    if (qobject_cast<DeclarativeChart *>(list->object)) {
        DeclarativeChart *chart = qobject_cast<DeclarativeChart *>(list->object);
        QList<QAbstractAxis *> axes = chart->m_chart->axes(Qt::Horizontal | Qt::Vertical, chart->m_chart->series()[0]);
        return axes.at(index);
    }
    return 0;
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
    foreach (QAbstractSeries *series, m_chart->series()) {
        if (series->name() == seriesName)
            return series;
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::createSeries(DeclarativeChart::SeriesType type, QString name)
{
    return createSeries(type, name, 0, 0);
}

QAbstractSeries *DeclarativeChart::createSeries(DeclarativeChart::SeriesType type, QString name, QAbstractAxis *axisX, QAbstractAxis *axisY)
{
    QAbstractSeries *series = 0;

    switch (type) {
    case DeclarativeChart::SeriesTypeLine:
        series = new DeclarativeLineSeries();
        break;
    case DeclarativeChart::SeriesTypeArea: {
        DeclarativeAreaSeries *area = new DeclarativeAreaSeries();
        area->setUpperSeries(new DeclarativeLineSeries());
        series = area;
        break;
    }
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
        // Connect to axis changed signals (unless this is a pie series)
        if (!qobject_cast<DeclarativePieSeries *>(series)) {
            connect(series, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SLOT(handleAxisYRightSet(QAbstractAxis*)));
        }

        series->setName(name);
        m_chart->addSeries(series);

        if (axisX)
            setAxisX(axisX, series);
        if (axisY)
            setAxisY(axisY, series);

        if (series->attachedAxes().count() < 2)
            initializeAxes(series);
    }

    return series;
}

void DeclarativeChart::removeSeries(QAbstractSeries *series)
{
    if (series)
        m_chart->removeSeries(series);
    else
        qWarning("removeSeries: cannot remove null");
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

QAbstractAxis *DeclarativeChart::defaultAxis(Qt::Orientation orientation, QAbstractSeries *series)
{
    if (!series) {
        qWarning() << "No axis type defined for null series";
        return 0;
    }

    foreach (QAbstractAxis *existingAxis, m_chart->axes(orientation)) {
        if (existingAxis->type() == series->d_ptr->defaultAxisType(orientation))
            return existingAxis;
    }

    switch (series->d_ptr->defaultAxisType(orientation)) {
    case QAbstractAxis::AxisTypeValue:
        return new QValueAxis(this);
    case QAbstractAxis::AxisTypeBarCategory:
        return new QBarCategoryAxis(this);
    case QAbstractAxis::AxisTypeCategory:
        return new QCategoryAxis(this);
#ifndef QT_ON_ARM
    case QAbstractAxis::AxisTypeDateTime:
        return new QDateTimeAxis(this);
#endif
    default:
        // assume AxisTypeNoAxis
        return 0;
    }
}

void DeclarativeChart::initializeAxes(QAbstractSeries *series)
{
    if (qobject_cast<DeclarativeLineSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeLineSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeScatterSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeScatterSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeSplineSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeSplineSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeAreaSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeAreaSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeStackedBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeStackedBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativePercentBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativePercentBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalStackedBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalStackedBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalPercentBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalPercentBarSeries *>(series)->m_axes);
    // else: do nothing
}

void DeclarativeChart::doInitializeAxes(QAbstractSeries *series, DeclarativeAxes *axes)
{
    // Initialize axis X
    if (axes->axisX())
        axes->emitAxisXChanged();
    else if (axes->axisXTop())
        axes->emitAxisXTopChanged();
    else
        axes->setAxisX(defaultAxis(Qt::Horizontal, series));

    // Initialize axis Y
    if (axes->axisY())
        axes->emitAxisYChanged();
    else if (axes->axisYRight())
        axes->emitAxisYRightChanged();
    else
        axes->setAxisY(defaultAxis(Qt::Vertical, series));
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
