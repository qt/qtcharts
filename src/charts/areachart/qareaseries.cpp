/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCharts/QAreaSeries>
#include <private/qareaseries_p.h>
#include <QtCharts/QLineSeries>
#include <private/areachartitem_p.h>
#include <private/abstractdomain_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <QtCharts/QValueAxis>
#include <QtCharts/QAreaLegendMarker>
#include <private/qchart_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAreaSeries
    \inmodule Qt Charts
    \brief The QAreaSeries class is used for making area charts.

    An area series is used to show quantitative data. It is based on line series, in the way that
    the area between the boundary lines is emphasized with color. Since the area series is based on
    line series, QAreaSeries constructor needs a QLineSeries instance, which defines "upper"
    boundary of the area. The area chart is drawn using the bottom of the plot area as the "lower"
    boundary by default. Instead of the bottom of the plot area, the "lower" boundary can be
    specified by another line. In that case QAreaSeries should be initialized with two QLineSeries
    instances. Please note that the terms "upper" and "lower" boundary can be misleading in cases
    where the "lower" boundary has bigger values than the "upper" one. The main point is that the
    area between these two boundary lines will be filled.

    See the \l {AreaChart Example} {area chart example} to learn how to create a simple area chart.
    \image examples_areachart.png
*/

/*!
    \qmltype AreaSeries
    \instantiates QAreaSeries
    \inqmlmodule QtCharts

    \inherits AbstractSeries

    \brief The AreaSeries type is used for making area charts.

    The following QML shows how to create a simple area chart:
    \snippet qmlchart/qml/qmlchart/View4.qml 1
    \beginfloatleft
    \image examples_qmlchart4.png
    \endfloat
    \clearfloat

    \note Adding the same line series to chart and area series is not supported. The series used as
    boundary lines should be defined only for the area series.
*/

/*!
   \property QAreaSeries::upperSeries
   \brief The upper one of the two line series used to define area series boundaries.
*/
/*!
   \qmlproperty LineSeries AreaSeries::upperSeries
   The upper one of the two line series used to define area series boundaries.
*/

/*!
    \property QAreaSeries::lowerSeries
    The lower one of the two line series used to define are series boundaries. Note if
    QAreaSeries was constructed without a\ lowerSeries this is null.
*/
/*!
    \qmlproperty LineSeries AreaSeries::lowerSeries
    The lower one of the two line series used to define are series boundaries. Note if
    AreaSeries was constructed without a\ lowerSeries this is null.
*/

/*!
    \property QAreaSeries::color
    Fill (brush) color of the series. This is a convenience property for modifying the color of brush.
    \sa QAreaSeries::brush()
*/
/*!
    \qmlproperty color AreaSeries::color
    Fill (brush) color of the series.
*/

/*!
    \property QAreaSeries::borderColor
    Line (pen) color of the series. This is a convenience property for modifying the color of pen.
    \sa QAreaSeries::pen()
*/
/*!
    \qmlproperty color AreaSeries::borderColor
    Line (pen) color of the series.
*/

/*!
    \qmlproperty real AreaSeries::borderWidth
    The width of the border line. By default the width is 2.0.
*/

/*!
   \fn QPen QAreaSeries::pen() const
   \brief  Returns the pen used to draw line for this series.
    \sa setPen()
*/

/*!
   \fn QPen QAreaSeries::brush() const
   \brief  Returns the brush used to draw line for this series.
    \sa setBrush()
*/

/*!
    \qmlproperty QString AreaSeries::brushFilename
    The name of the file used as a brush image for the series.
*/

/*!
    \fn void QAreaSeries::colorChanged(QColor color)
    \brief Signal is emitted when the fill (brush) color has changed to \a color.
*/
/*!
    \qmlsignal AreaSeries::onColorChanged(color color)
    Signal is emitted when the fill (brush) color has changed to \a color.
*/

/*!
    \fn void QAreaSeries::borderColorChanged(QColor color)
    \brief Signal is emitted when the line (pen) color has changed to \a color.
*/
/*!
    \qmlsignal AreaSeries::onBorderColorChanged(color color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/

/*!
    \fn void QAreaSeries::clicked(const QPointF& point)
    \brief Signal is emitted when user clicks the \a point on area chart. The \a point is the point
    where the press was triggered.
    \sa pressed, released, doubleClicked
*/
/*!
    \qmlsignal AreaSeries::onClicked(QPointF point)
    Signal is emitted when user clicks the \a point on area chart. The \a point is the point where
    the press was triggered.
    \sa onPressed, onReleased, onDoubleClicked
*/

/*!
    \fn void QAreaSeries::hovered(const QPointF &point, bool state)
    This signal is emitted when user has hovered over or away from the series. \a point shows the origin (coordinate)
    of the hover event. \a state is true when user has hovered over the series and false when hover has moved away from
    the series.
*/
/*!
    \qmlsignal AreaSeries::onHovered(point point, bool state)
    This signal is emitted when user has hovered over or away from the series. \a point shows the origin (coordinate)
    of the hover event. \a state is true when user has hovered over the series and false when hover has moved away from
    the series.
*/

/*!
    \fn void QAreaSeries::pressed(const QPointF& point)
    \brief Signal is emitted when user presses the \a point on area chart.
    \sa clicked, released, doubleClicked
*/
/*!
    \qmlsignal AreaSeries::onPressed(QPointF point)
    Signal is emitted when user presses the \a point on area chart.
    \sa onClicked, onReleased, onDoubleClicked
*/

/*!
    \fn void QAreaSeries::released(const QPointF& point)
    \brief Signal is emitted when user releases a press that was triggered on a \a point on area
    chart.
    \sa pressed, clicked, doubleClicked
*/
/*!
    \qmlsignal AreaSeries::onReleased(QPointF point)
    Signal is emitted when user releases a press that was triggered on a \a point on area chart.
    \sa onPressed, onClicked, onDoubleClicked
*/

/*!
    \fn void QAreaSeries::doubleClicked(const QPointF& point)
    \brief Signal is emitted when user doubleclicks the \a point on area chart. The \a point is the
    point where the first press was triggered.
    \sa pressed, released, clicked
*/
/*!
    \qmlsignal AreaSeries::onDoubleClicked(QPointF point)
    Signal is emitted when user doubleclicks the \a point on area chart. The \a point is the point
    where the first press was triggered.
    \sa onPressed, onReleased, onClicked
*/

/*!
    \fn void QAreaSeries::selected()
    The signal is emitted if the user selects/deselects the XY series. The logic for maintaining selections should be
    implemented by the user of QAreaSeries API.
*/
/*!
    \qmlsignal AreaSeries::onSelected()
    The signal is emitted if the user selects/deselects the XY series. The logic for maintaining selections should be
    implemented by the user of AreaSeries API.
*/

/*!
    \fn void QAreaSeriesPrivate::updated()
    \brief \internal
*/

/*!
    \property QAreaSeries::pointLabelsFormat
    The \a format used for showing labels with series points.

    QAreaSeries supports the following format tags:
    \table
      \row
        \li @xPoint      \li The x value of the data point
      \row
        \li @yPoint      \li The y value of the data point
    \endtable

    For example, the following usage of the format tags would produce labels that have the data
    point (x, y) shown inside brackets separated by a comma:
    \code
    series->setPointLabelsFormat("(@xPoint, @yPoint)");
    \endcode

    By default, the labels format is set to '@xPoint, @yPoint'. The labels are shown on the plot
    area, labels on the edge of the plot area are cut. If the points are close to each other the
    labels may overlap.

    \sa QAreaSeries::pointLabelsVisible, QAreaSeries::pointLabelsFont, QAreaSeries::pointLabelsColor
*/
/*!
    \qmlproperty string AreaSeries::pointLabelsFormat
    The \a format used for showing labels with series points.

    \sa QAreaSeries::pointLabelsFormat, pointLabelsVisible, pointLabelsFont, pointLabelsColor
*/
/*!
    \fn void QAreaSeries::pointLabelsFormatChanged(const QString &format)
    Signal is emitted when the \a format of data point labels is changed.
*/
/*!
    \qmlsignal AreaSeries::onPointLabelsFormatChanged(string format)
    Signal is emitted when the \a format of data point labels is changed.
*/

/*!
    \property QAreaSeries::pointLabelsVisible
    Defines the visibility for data point labels. False by default.

    \sa QAreaSeries::pointLabelsFormat, QAreaSeries::pointLabelsClipping
*/
/*!
    \qmlproperty bool AreaSeries::pointLabelsVisible
    Defines the visibility for data point labels.

    \sa pointLabelsFormat, pointLabelsClipping
*/
/*!
    \fn void QAreaSeries::pointLabelsVisibilityChanged(bool visible)
    The visibility of the data point labels is changed to \a visible.
*/
/*!
    \qmlsignal AreaSeries::onPointLabelsVisibilityChanged(bool visible)
    The visibility of the data point labels is changed to \a visible.
*/

/*!
    \property QAreaSeries::pointLabelsFont
    Defines the font used for data point labels.

    \sa QAreaSeries::pointLabelsFormat
*/
/*!
    \qmlproperty font AreaSeries::pointLabelsFont
    Defines the font used for data point labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QAreaSeries::pointLabelsFontChanged(const QFont &font);
    The font used for data point labels is changed to \a font.
*/
/*!
    \qmlsignal AreaSeries::onPointLabelsFontChanged(Font font)
    The font used for data point labels is changed to \a font.
*/

/*!
    \property QAreaSeries::pointLabelsColor
    Defines the color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa QAreaSeries::pointLabelsFormat
*/
/*!
    \qmlproperty font AreaSeries::pointLabelsColor
    Defines the color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QAreaSeries::pointLabelsColorChanged(const QColor &color);
    The color used for data point labels is changed to \a color.
*/
/*!
    \qmlsignal AreaSeries::onPointLabelsColorChanged(Color color)
    The color used for data point labels is changed to \a color.
*/

/*!
    \property QAreaSeries::pointLabelsClipping
    Defines the clipping for data point labels. True by default. The labels on the edge of the plot
    area are cut when clipping is enabled.

    \sa pointLabelsVisible
*/
/*!
    \qmlproperty bool AreaSeries::pointLabelsClipping
    Defines the clipping for data point labels. True by default. The labels on the edge of the plot
    area are cut when clipping is enabled.

    \sa pointLabelsVisible
*/
/*!
    \fn void QAreaSeries::pointLabelsClippingChanged(bool clipping)
    The clipping of the data point labels is changed to \a clipping.
*/
/*!
    \qmlsignal AreaSeries::onPointLabelsClippingChanged(bool clipping)
    The clipping of the data point labels is changed to \a clipping.
*/

/*!
    Constructs area series object which is a child of \a upperSeries. Area will be spanned between \a
    upperSeries line and \a lowerSeries line.  If no \a lowerSeries is passed to constructor, area is specified by axis x (y=0) instead.
    When series object is added to QChartView or QChart instance ownerships is transferred.
*/
QAreaSeries::QAreaSeries(QLineSeries *upperSeries, QLineSeries *lowerSeries)
    : QAbstractSeries(*new QAreaSeriesPrivate(upperSeries, lowerSeries, this), upperSeries)
{
    if (upperSeries)
        upperSeries->d_ptr->setBlockOpenGL(true);
    if (lowerSeries)
        lowerSeries->d_ptr->setBlockOpenGL(true);
}

/*!
    Constructs area series object without upper or lower series with \a parent object.
*/
QAreaSeries::QAreaSeries(QObject *parent)
    : QAbstractSeries(*new QAreaSeriesPrivate(0, 0, this), parent)
{
}

/*!
    Destroys the object.
*/
QAreaSeries::~QAreaSeries()
{
    Q_D(QAreaSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

/*!
    Returns QAbstractSeries::SeriesTypeArea.
*/
QAbstractSeries::SeriesType QAreaSeries::type() const
{
    return QAbstractSeries::SeriesTypeArea;
}

/*!
    Sets the \a series that is to be used as the area chart upper series.
*/
void QAreaSeries::setUpperSeries(QLineSeries *series)
{
    Q_D(QAreaSeries);
    if (d->m_upperSeries != series) {
        series->d_ptr->setBlockOpenGL(true);
        d->m_upperSeries = series;
    }
}

QLineSeries *QAreaSeries::upperSeries() const
{
    Q_D(const QAreaSeries);
    return d->m_upperSeries;
}

/*!
    Sets the \a series that is to be used as the area chart lower series.
*/
void QAreaSeries::setLowerSeries(QLineSeries *series)
{
    Q_D(QAreaSeries);
    series->d_ptr->setBlockOpenGL(true);
    d->m_lowerSeries = series;
}

QLineSeries *QAreaSeries::lowerSeries() const
{
    Q_D(const QAreaSeries);
    return d->m_lowerSeries;
}

/*!
    Sets \a pen used for drawing area outline.
*/
void QAreaSeries::setPen(const QPen &pen)
{
    Q_D(QAreaSeries);
    if (d->m_pen != pen) {
        d->m_pen = pen;
        emit d->updated();
    }
}

QPen QAreaSeries::pen() const
{
    Q_D(const QAreaSeries);
    if (d->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_pen;
}

/*!
    Sets \a brush used for filling the area.
*/
void QAreaSeries::setBrush(const QBrush &brush)
{
    Q_D(QAreaSeries);
    if (d->m_brush != brush) {
        bool emitColorChanged = brush.color() != d->m_brush.color();
        d->m_brush = brush;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(brush.color());
    }
}

QBrush QAreaSeries::brush() const
{
    Q_D(const QAreaSeries);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QAreaSeries::setColor(const QColor &color)
{
    QBrush b = brush();
    if (b == QBrush())
        b.setStyle(Qt::SolidPattern);
    b.setColor(color);
    setBrush(b);
}

QColor QAreaSeries::color() const
{
    return brush().color();
}

void QAreaSeries::setBorderColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
        emit borderColorChanged(color);
    }
}

QColor QAreaSeries::borderColor() const
{
    return pen().color();
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QAreaSeries::setPointsVisible(bool visible)
{
    Q_D(QAreaSeries);
    if (d->m_pointsVisible != visible) {
        d->m_pointsVisible = visible;
        emit d->updated();
    }
}

/*!
    Returns if the points are drawn for this series.
    \sa setPointsVisible()
*/
bool QAreaSeries::pointsVisible() const
{
    Q_D(const QAreaSeries);
    return d->m_pointsVisible;
}

void QAreaSeries::setPointLabelsFormat(const QString &format)
{
    Q_D(QAreaSeries);
    if (d->m_pointLabelsFormat != format) {
        d->m_pointLabelsFormat = format;
        emit pointLabelsFormatChanged(format);
    }
}

QString QAreaSeries::pointLabelsFormat() const
{
    Q_D(const QAreaSeries);
    return d->m_pointLabelsFormat;
}

void QAreaSeries::setPointLabelsVisible(bool visible)
{
    Q_D(QAreaSeries);
    if (d->m_pointLabelsVisible != visible) {
        d->m_pointLabelsVisible = visible;
        emit pointLabelsVisibilityChanged(visible);
    }
}

bool QAreaSeries::pointLabelsVisible() const
{
    Q_D(const QAreaSeries);
    return d->m_pointLabelsVisible;
}

void QAreaSeries::setPointLabelsFont(const QFont &font)
{
    Q_D(QAreaSeries);
    if (d->m_pointLabelsFont != font) {
        d->m_pointLabelsFont = font;
        emit pointLabelsFontChanged(font);
    }
}

QFont QAreaSeries::pointLabelsFont() const
{
    Q_D(const QAreaSeries);
    return d->m_pointLabelsFont;
}

void QAreaSeries::setPointLabelsColor(const QColor &color)
{
    Q_D(QAreaSeries);
    if (d->m_pointLabelsColor != color) {
        d->m_pointLabelsColor = color;
        emit pointLabelsColorChanged(color);
    }
}

QColor QAreaSeries::pointLabelsColor() const
{
    Q_D(const QAreaSeries);
    if (d->m_pointLabelsColor == QChartPrivate::defaultPen().color())
        return QPen().color();
    else
        return d->m_pointLabelsColor;
}

void QAreaSeries::setPointLabelsClipping(bool enabled)
{
    Q_D(QAreaSeries);
    if (d->m_pointLabelsClipping != enabled) {
        d->m_pointLabelsClipping = enabled;
        emit pointLabelsClippingChanged(enabled);
    }
}

bool QAreaSeries::pointLabelsClipping() const
{
    Q_D(const QAreaSeries);
    return d->m_pointLabelsClipping;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAreaSeriesPrivate::QAreaSeriesPrivate(QLineSeries *upperSeries, QLineSeries *lowerSeries, QAreaSeries *q)
    : QAbstractSeriesPrivate(q),
      m_brush(QChartPrivate::defaultBrush()),
      m_pen(QChartPrivate::defaultPen()),
      m_upperSeries(upperSeries),
      m_lowerSeries(lowerSeries),
      m_pointsVisible(false),
      m_pointLabelsFormat(QLatin1String("@xPoint, @yPoint")),
      m_pointLabelsVisible(false),
      m_pointLabelsFont(QChartPrivate::defaultFont()),
      m_pointLabelsColor(QChartPrivate::defaultPen().color()),
      m_pointLabelsClipping(true)
{
}

void QAreaSeriesPrivate::initializeDomain()
{
    Q_Q(QAreaSeries);

    qreal minX(domain()->minX());
    qreal minY(domain()->minY());
    qreal maxX(domain()->maxX());
    qreal maxY(domain()->maxY());

    QLineSeries *upperSeries = q->upperSeries();
    QLineSeries *lowerSeries = q->lowerSeries();

    if (upperSeries) {
        const QVector<QPointF> &points = upperSeries->pointsVector();

        for (int i = 0; i < points.count(); i++) {
            qreal x = points[i].x();
            qreal y = points[i].y();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }
    if (lowerSeries) {
        const QVector<QPointF> &points = lowerSeries->pointsVector();

        for (int i = 0; i < points.count(); i++) {
            qreal x = points[i].x();
            qreal y = points[i].y();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
        }
    }

    domain()->setRange(minX, maxX, minY, maxY);
}

void QAreaSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QAreaSeries);
    AreaChartItem *area = new AreaChartItem(q,parent);
    m_item.reset(area);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}
void  QAreaSeriesPrivate::initializeAnimations(QChart::AnimationOptions options, int duration,
                                               QEasingCurve &curve)
{
    Q_Q(QAreaSeries);
    AreaChartItem *area = static_cast<AreaChartItem *>(m_item.data());

    if (q->upperSeries() && area->upperLineItem()->animation())
        area->upperLineItem()->animation()->stopAndDestroyLater();
    if (q->lowerSeries() && area->lowerLineItem()->animation())
        area->lowerLineItem()->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations)) {
        area->upperLineItem()->setAnimation(new XYAnimation(area->upperLineItem(), duration,
                                                            curve));
        if (q->lowerSeries())
            area->lowerLineItem()->setAnimation(new XYAnimation(area->lowerLineItem(), duration,
                                                                curve));
    } else {
        if (q->upperSeries())
            area->upperLineItem()->setAnimation(0);
        if (q->lowerSeries())
               area->lowerLineItem()->setAnimation(0);
    }
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

QList<QLegendMarker*> QAreaSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QAreaSeries);
    QList<QLegendMarker*> list;
    return list << new QAreaLegendMarker(q,legend);
}


void QAreaSeriesPrivate::initializeAxes()
{

}

QAbstractAxis::AxisType QAreaSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis* QAreaSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return new QValueAxis;
}

void QAreaSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QAreaSeries);

    const QList<QGradient> gradients = theme->seriesGradients();
    const QList<QColor> colors = theme->seriesColors();

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen;
        pen.setColor(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.0));
        pen.setWidthF(2);
        q->setPen(pen);
    }

    if (forced || QChartPrivate::defaultBrush() == m_brush) {
        QBrush brush(colors.at(index % colors.size()));
        q->setBrush(brush);
    }

    if (forced || QChartPrivate::defaultPen().color() == m_pointLabelsColor) {
        QColor color = theme->labelBrush().color();
        q->setPointLabelsColor(color);
    }
}


#include "moc_qareaseries.cpp"
#include "moc_qareaseries_p.cpp"

QT_CHARTS_END_NAMESPACE
