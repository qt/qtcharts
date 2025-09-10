// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include <QtCharts/QXYSeries>
#include <QtCharts/QColorAxis>
#include <private/qxyseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QValueAxis>
#include <private/xychart_p.h>
#include <QtCharts/QXYLegendMarker>
#include <private/charthelpers_p.h>
#include <private/qchart_p.h>
#include <QtGui/QPainter>
#include <QtMath>

QT_BEGIN_NAMESPACE

/*!
    \class QXYSeries
    \inmodule QtCharts
    \brief The QXYSeries class is a base class for line, spline, and scatter
    series.

    QXYSeries supports displaying best fit line on a chart. Best fit line is a line
    through a chart that expresses the relationship between points.
*/
/*!
    \qmltype XYSeries
    \nativetype QXYSeries
    \inqmlmodule QtCharts

    \inherits AbstractSeries

    \brief A base type for line, spline, and scatter series.

    XYSeries supports displaying best fit line on a chart. Best fit line is a line
    through a chart that expresses the relationship between points.
*/

/*!
    \enum QXYSeries::PointConfiguration

    This enum value describes the particular configuration of a point.

    \value Color
           This enum value can be used to change a point's color. If used together
           with QXYSeries::setPointConfiguration, the configuration's value should
           be a valid QColor.
    \value Size
           This enum value can be used to change a point's size. If used together
           with QXYSeries::setPointConfiguration, the configuration's value should
           be a number, such as \c qreal or \c int.
    \value Visibility
           This enum value can be used to hide or show the point. If used
           together with QXYSeries::setPointConfiguration, the configuration's value
           should be boolean.
    \value LabelVisibility
           This enum value can be used to hide or show the label of the point. If used
           together with QXYSeries::setPointConfiguration, the configuration's value
           should be boolean.
    \value [since 6.5] LabelFormat
           This enum value can be used to set custom label text per-point. If used together with
           QXYSeries::setPointConfiguration, the configuration's value should be a string.
           \note If an empty string is set as the LabelFormat, it will be ignored, and the series
           pointLabelsFormat will be used.
           \sa pointLabelsFormat

    \sa setPointConfiguration()
    \since 6.2
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisX
    The x-axis used for the series. If you leave both axisX and axisXTop
    undefined, a value axis is created for the series.
    \sa axisXTop, ValueAxis
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisY
    The y-axis used for the series. If you leave both axisY and axisYRight
    undefined, a value axis is created for the series.
    \sa axisYRight, ValueAxis
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisXTop
    The x-axis used for the series, drawn on top of the chart view.

    \note You can only provide either axisX or axisXTop, not both.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisYRight
    The y-axis used for the series, drawn to the right on the chart view.

    \note You can only provide either axisY or axisYRight, not both.
    \sa axisY
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisAngular
    The angular axis used for the series, drawn around the polar chart view.
    \sa axisX
*/

/*!
    \qmlproperty AbstractAxis XYSeries::axisRadial
    The radial axis used for the series, drawn inside the polar chart view.
    \sa axisY
*/

/*!
    \property QXYSeries::pointsVisible
    \brief Whether the data points are visible and should be drawn.
*/
/*!
    \qmlproperty bool XYSeries::pointsVisible
    Whether the data points are visible and should be drawn.
*/

/*!
   \fn QPen QXYSeries::pen() const
   Returns the pen used to draw the outline of the data points for the series.
    \sa setPen()
*/

/*!
   \fn QBrush QXYSeries::brush() const
   Returns the brush used to fill the data points for the series.
    \sa setBrush()
*/

/*!
    \property QXYSeries::color
    \brief The color of the series.

    This is the line (pen) color in case of QLineSeries or QSplineSeries and the
    fill (brush) color in case of QScatterSeries or QAreaSeries.
    \sa pen(), brush()
*/
/*!
    \qmlproperty color XYSeries::color
    The color of the series. This is the line (pen) color in case of LineSeries
    or SplineSeries and the fill (brush) color in case of ScatterSeries or
    AreaSeries.
*/

/*!
    \property QXYSeries::pointLabelsFormat
    \brief The format used for showing labels with data points.

    QXYSeries supports the following format tags:
    \table
      \row
        \li @index       \li The index in the series of the data point. [since 6.5]
      \row
        \li @xPoint      \li The x-coordinate of the data point.
      \row
        \li @yPoint      \li The y-coordinate of the data point.
    \endtable

    For example, the following usage of the format tags would produce labels
    that display the data point shown inside brackets separated by a comma
    (x, y):

    \code
    series->setPointLabelsFormat("@index: (@xPoint, @yPoint)");
    \endcode

    By default, the labels' format is set to \c {@xPoint, @yPoint}. The labels
    are shown on the plot area, and the labels on the edge of the plot area are
    cut. If the points are close to each other, the labels may overlap.

    \sa pointLabelsVisible, pointLabelsFont, pointLabelsColor
*/
/*!
    \qmlproperty string XYSeries::pointLabelsFormat
    The format used for showing labels with data points.

    \sa pointLabelsVisible, pointLabelsFont, pointLabelsColor
*/
/*!
    \fn void QXYSeries::pointLabelsFormatChanged(const QString &format)
    This signal is emitted when the format of data point labels changes to
    \a format.
*/

/*!
    \property QXYSeries::pointLabelsVisible
    \brief The visibility of data point labels.

    This property is \c false by default.

    \sa pointLabelsFormat, pointLabelsClipping
*/
/*!
    \qmlproperty bool XYSeries::pointLabelsVisible
    The visibility of data point labels. This property is \c false by default.

    \sa pointLabelsFormat, pointLabelsClipping
*/
/*!
    \fn void QXYSeries::pointLabelsVisibilityChanged(bool visible)
    This signal is emitted when the visibility of the data point labels
    changes to \a visible.
*/

/*!
    \property QXYSeries::pointLabelsFont
    \brief The font used for data point labels.

    \sa pointLabelsFormat
*/
/*!
    \qmlproperty font XYSeries::pointLabelsFont
    The font used for data point labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QXYSeries::pointLabelsFontChanged(const QFont &font);
    This signal is emitted when the font used for data point labels changes to
    \a font.
*/

/*!
    \property QXYSeries::pointLabelsColor
    \brief The color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa pointLabelsFormat
*/
/*!
    \qmlproperty font XYSeries::pointLabelsColor
    The color used for data point labels. By default, the color is the color of the brush
    defined in theme for labels.

    \sa pointLabelsFormat
*/
/*!
    \fn void QXYSeries::pointLabelsColorChanged(const QColor &color);
    This signal is emitted when the color used for data point labels changes to
    \a color.
*/

/*!
    \property QXYSeries::pointLabelsClipping
    \brief The clipping for data point labels.

    This property is \c true by default. The labels on the edge of the plot area
    are cut when clipping is enabled.

    \sa pointLabelsVisible
*/
/*!
    \qmlproperty bool XYSeries::pointLabelsClipping
    The clipping for data point labels. This property is \c true by default. The
    labels on the edge of the plot area are cut when clipping is enabled.

    \sa pointLabelsVisible
*/

/*!
    \property QXYSeries::selectedColor
    \brief The color of the selected points.

    This is the fill (brush) color of points marked as selected. If not specified,
    value of QXYSeries::color is used as default.
    \sa color
    \since 6.2
*/
/*!
    \qmlproperty color XYSeries::selectedColor
    The color of the selected points. This is the fill (brush) color of points marked
    as selected.
    If not specified, value of QXYSeries::color is used as default.
    \sa color
*/

/*!
    \fn void QXYSeries::markerSizeChanged(qreal size)
    This signal is emitted when the marker size changes to \a size.
*/

/*!
    \fn void QXYSeries::pointLabelsClippingChanged(bool clipping)
    This signal is emitted when the clipping of the data point labels changes to
    \a clipping.
*/
/*!
    \property QXYSeries::bestFitLineVisible
    \brief The visibility of the best fit line.

    This property is \c false by default.

    \sa bestFitLineEquation
    \since 6.2
*/
/*!
    \qmlproperty bool XYSeries::bestFitLineVisible
    The visibility of the best fit line.
    This property is \c false by default.
*/
/*!
    \fn void QXYSeries::bestFitLineVisibilityChanged(bool visible)
    This signal is emitted when the visibility of the best fit line changes to
    \a visible.
*/
/*!
    \property QXYSeries::bestFitLineColor
    \brief The color of best fit line.

    \sa bestFitLineEquation, bestFitLineVisible
    \since 6.2
*/
/*!
    \qmlproperty color XYSeries::bestFitLineColor
    The color of best fit line.
    \sa bestFitLineVisible
*/
/*!
    \fn void QXYSeries::bestFitLineColorChanged(const QColor &color)
    This signal is emitted when the color used for the best fit line changes to
    \a color.
*/

/*!
    \fn void QXYSeries::clicked(const QPointF& point)
    This signal is emitted when the user triggers a mouse event by
    clicking the point \a point in the chart.

    \sa pressed(), released(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::clicked(point point)
    This signal is emitted when the user triggers a mouse event by clicking the
    point \a point in the chart. For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onClicked: console.log("onClicked: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onClicked().

    \sa pressed(), released(), doubleClicked()
*/

/*!
    \fn void QXYSeries::hovered(const QPointF &point, bool state)
    This signal is emitted when a mouse is hovered over the point \a point in
    the chart. When the mouse moves over the point, \a state turns \c true,
    and when the mouse moves away again, it turns \c false.
*/
/*!
    \qmlsignal XYSeries::hovered(point point, bool state)
    This signal is emitted when a mouse is hovered over the point \a point in
    the chart. When the mouse moves over the point, \a state turns \c true,
    and when the mouse moves away again, it turns \c false.

    The corresponding signal handler is \c onHovered().
*/

/*!
    \fn void QXYSeries::pressed(const QPointF& point)
    This signal is emitted when the user presses the data point \a point in the
    chart and holds down the mouse button.

    \sa clicked(), released(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::pressed(point point)
    This signal is emitted when the user presses the data point \a point in the
    chart and holds down the mouse button. For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onPressed: console.log("onPressed: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onPressed().

    \sa clicked(), released(), doubleClicked()
*/

/*!
    \fn void QXYSeries::released(const QPointF& point)
    This signal is emitted when the user releases the mouse press on the data
    point specified by \a point.
    \sa pressed(), clicked(), doubleClicked()
*/
/*!
    \qmlsignal XYSeries::released(point point)
    This signal is emitted when the user releases the mouse press on the data
    point specified by \a point.
    For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onReleased: console.log("onReleased: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onReleased().

    \sa pressed(), clicked(), doubleClicked()
*/

/*!
    \fn void QXYSeries::doubleClicked(const QPointF& point)
    This signal is emitted when the user double-clicks the data point \a point
    in the chart. The \a point is the point where the first press was triggered.
    \sa pressed(), released(), clicked()
*/
/*!
    \qmlsignal XYSeries::doubleClicked(point point)
    This signal is emitted when the user double-clicks the data point \a point
    in the chart. The \a point is the point where the first press was triggered.
    For example:
    \code
    LineSeries {
        XYPoint { x: 0; y: 0 }
        XYPoint { x: 1.1; y: 2.1 }
        onDoubleClicked: console.log("onDoubleClicked: " + point.x + ", " + point.y);
    }
    \endcode

    The corresponding signal handler is \c onDoubleClicked().

    \sa pressed(), released(), clicked()
*/

/*!
    \fn void QXYSeries::pointReplaced(int index)
    This signal is emitted when a point is replaced at the position specified by
    \a index.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::pointReplaced(int index)
    This signal is emitted when a point is replaced at the position specified by
    \a index.

    The corresponding signal handler is \c onPointReplaced().
*/

/*!
    \fn void QXYSeries::pointsReplaced()
    This signal is emitted when all points are replaced with other points.
    \sa replace()
*/
/*!
    \qmlsignal XYSeries::pointsReplaced()
    This signal is emitted when all points are replaced with other points.

    The corresponding signal handler is \c onPointsReplaced().
*/

/*!
    \fn void QXYSeries::pointAdded(int index)
    This signal is emitted when a point is added at the position specified by
    \a index.
    \sa append(), insert()
*/
/*!
    \qmlsignal XYSeries::pointAdded(int index)
    This signal is emitted when a point is added at the position specified by
    \a index.

    The corresponding signal handler is \c onPointAdded().
*/

/*!
    \fn void QXYSeries::pointRemoved(int index)
    This signal is emitted when a point is removed from the position specified
    by \a index.
    \sa remove()
*/

/*!
    \qmlsignal XYSeries::pointRemoved(int index)
    This signal is emitted when a point is removed from the position specified
    by \a index.

    The corresponding signal handler is \c onPointRemoved().
*/

/*!
    \fn void QXYSeries::pointsRemoved(int index, int count)
    This signal is emitted when the number of points specified by \a count
    is removed starting at the position specified by \a index.
    \sa removePoints(), clear()
*/

/*!
    \qmlsignal XYSeries::pointsRemoved(int index, int count)
    This signal is emitted when the number of points specified by \a count
    is removed starting at the position specified by \a index.

    The corresponding signal handler is \c onPointRemoved().
*/

/*!
    \fn void QXYSeries::colorChanged(QColor color)
    This signal is emitted when the line (pen) color changes to \a color.
*/

/*!
    \fn void QXYSeries::penChanged(const QPen &pen)
    This signal is emitted when the pen changes to \a pen.
*/

/*!
    \fn void QXYSeries::selectedPointsChanged()
    This signal is emitted when the points selection changes.
*/

/*!
    \fn void QXYSeries::lightMarkerChanged(const QImage &lightMarker)
    This signal is emitted when the light marker image changes to \a lightMarker.
    \sa QXYSeries::setLightMarker()
    \since 6.2
*/

/*!
    \fn void QXYSeriesPrivate::seriesUpdated()
    \internal
*/

/*!
    \qmlmethod XYSeries::append(real x, real y)
    Appends a point with the coordinates \a x and \a y to the series.
*/

/*!
    \qmlmethod XYSeries::replace(real oldX, real oldY, real newX, real newY)
    Replaces the point with the coordinates \a oldX and \a oldY with the point
    with the coordinates \a newX and \a newY. Does nothing if the old point does
    not exist.
*/

/*!
    \qmlmethod XYSeries::remove(real x, real y)
    Removes the point with the coordinates \a x and \a y from the series. Does
    nothing if the point does not exist.
*/

/*!
    \qmlmethod XYSeries::remove(int index)
    Removes the point at the position specified by \a index from the series.
*/

/*!
    \qmlmethod XYSeries::removePoints(int index, int count)
    Removes the number of points specified by \a count from the series starting
    at the position specified by \a index.
*/

/*!
    \qmlmethod XYSeries::insert(int index, real x, real y)
    Inserts a point with the coordinates \a x and \a y to the position specified
    by \a index in the series. If the index is 0 or less than 0, the point is
    prepended to the list of points. If the index is equal to or greater than
    than the number of points in the series, the point is appended to the
    list of points.
*/

/*!
    \qmlmethod QPointF XYSeries::at(int index)
    Returns the point at the position specified by \a index. Returns (0, 0) if
    the index is not valid.
*/

/*!
    \internal

    Constructs an empty series object that is a child of \a parent.
    When the series object is added to QChart, instance ownerships is transferred.
*/
QXYSeries::QXYSeries(QXYSeriesPrivate &d, QObject *parent)
    : QAbstractSeries(d, parent)
{
}

/*!
    Deletes the series. Series added to QChart instances are owned by them,
    and are deleted when the QChart instances are deleted.
*/
QXYSeries::~QXYSeries()
{
}

/*!
    Adds the data point with the coordinates \a x and \a y to the series.
 */
void QXYSeries::append(qreal x, qreal y)
{
    append(QPointF(x, y));
}

/*!
   \overload
   Adds the data point \a point to the series.
 */
void QXYSeries::append(const QPointF &point)
{
    Q_D(QXYSeries);

    if (isValidValue(point)) {
        d->m_points << point;
        emit pointAdded(d->m_points.size() - 1);
    }
}

/*!
   \overload
   Adds the list of data points specified by \a points to the series.
 */
void QXYSeries::append(const QList<QPointF> &points)
{
    foreach (const QPointF &point , points)
        append(point);
}

/*!
    Replaces the point with the coordinates \a oldX and \a oldY with the point
    with the coordinates \a newX and \a newY. Does nothing if the old point does
    not exist.

    \sa pointReplaced()
*/
void QXYSeries::replace(qreal oldX, qreal oldY, qreal newX, qreal newY)
{
    replace(QPointF(oldX, oldY), QPointF(newX, newY));
}

/*!
  Replaces the point specified by \a oldPoint with the one specified by
  \a newPoint.
  \sa pointReplaced()
*/
void QXYSeries::replace(const QPointF &oldPoint, const QPointF &newPoint)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(oldPoint);
    if (index == -1)
        return;
    replace(index, newPoint);
}

/*!
  Replaces the point at the position specified by \a index with the point that
  has the coordinates \a newX and \a newY.
  \sa pointReplaced()
*/
void QXYSeries::replace(int index, qreal newX, qreal newY)
{
    replace(index, QPointF(newX, newY));
}

/*!
  Replaces the point at the position specified by \a index with the point
  specified by \a newPoint.
  \sa pointReplaced()
*/
void QXYSeries::replace(int index, const QPointF &newPoint)
{
    Q_D(QXYSeries);
    if (isValidValue(newPoint)) {
        d->m_points[index] = newPoint;
        emit pointReplaced(index);
    }
}

/*!
  Replaces the current points with the points specified by \a points.
  \note This is much faster than replacing data points one by one,
  or first clearing all data, and then appending the new data. Emits QXYSeries::pointsReplaced()
  when the points have been replaced.
  \sa pointsReplaced()
*/
void QXYSeries::replace(const QList<QPointF> &points)
{
    Q_D(QXYSeries);
    const bool needUpdateSelection = d->m_points.size() > points.size();
    d->m_points = points;
    if (needUpdateSelection) {
        d->m_selectedPoints.removeIf([maxIdx = points.size() - 1](int idx) {
            return idx > maxIdx;
        });
    }
    emit pointsReplaced();
    if (needUpdateSelection)
        emit selectedPointsChanged();
}

/*!
    Removes the configuration of a point located at \a index
    and restores the default look derived from the series' settings.

    \note It doesn't affect the configuration of other points.
    \sa clearPointsConfiguration(), setPointConfiguration()
    \since 6.2
*/
void QXYSeries::clearPointConfiguration(const int index)
{
    Q_D(QXYSeries);
    if (d->m_pointsConfiguration.contains(index)) {
        d->m_pointsConfiguration.remove(index);
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
    }
}

/*!
    Removes the configuration property identified by \a key from the point at \a index
    and restores the default look derived from the series' settings.

    Removes the configuration type, such as color or size,
    specified by \a key from the point at \a index with configuration customizations,
    allowing that configuration property to be rendered as the default
    specified in the series' properties.

    \note It doesn't affect the configuration of other points.
    \sa clearPointsConfiguration(), setPointConfiguration()
    \since 6.2
*/
void QXYSeries::clearPointConfiguration(const int index, const QXYSeries::PointConfiguration key)
{
    Q_D(QXYSeries);
    if (d->m_pointsConfiguration.contains(index)) {
        auto &conf = d->m_pointsConfiguration[index];
        if (conf.contains(key)) {
            conf.remove(key);
            d->m_pointsConfiguration[index] = conf;
            emit pointsConfigurationChanged(d->m_pointsConfiguration);
        }
    }
}

/*!
    Removes the configuration of all points in the series and restores
    the default look derived from the series' settings.

    \sa setPointConfiguration()
    \since 6.2
*/
void QXYSeries::clearPointsConfiguration()
{
    Q_D(QXYSeries);
    d->m_pointsConfiguration.clear();
    emit pointsConfigurationChanged(d->m_pointsConfiguration);
}

/*!
    Removes the configuration property identified by \a key from all
    points and restores the default look derived from the series' settings.

    Removes the configuration type, such as color or size,
    specified by \a key from all points with configuration customizations,
    allowing that configuration property to be rendered as the default
    specified in the series properties.

    \sa clearPointsConfiguration(), setPointConfiguration()
    \since 6.2
*/
void QXYSeries::clearPointsConfiguration(const QXYSeries::PointConfiguration key)
{
    Q_D(QXYSeries);
    bool needsUpdate = false;
    for (const int &index : d->m_pointsConfiguration.keys()) {
        auto &conf = d->m_pointsConfiguration[index];
        if (conf.contains(key)) {
            conf.remove(key);
            d->m_pointsConfiguration[index] = conf;
            needsUpdate = true;
        }
    }

    if (needsUpdate)
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
}

/*!
    Enables customizing the appearance of a point located at \a index with
    desired \a configuration.

    With points configuration you can change various aspects of every point's appearance.

    A point's configuration is represented as a hash map with QXYSeries::pointConfiguration
    keys and QVariant values. For example:
    \code
    QLineSeries *series = new QLineSeries();
    series->setName("Customized series");
    series->setPointsVisible(true);

    *series << QPointF(0, 6) << QPointF(2, 4) << QPointF(3, 6) << QPointF(7, 4) << QPointF(10, 5)
            << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3)
            << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QHash<QXYSeries::PointConfiguration, QVariant> conf;
    conf[QXYSeries::PointConfiguration::Color] = QColor(Qt::red);
    conf[QXYSeries::PointConfiguration::Size] = 8;
    conf[QXYSeries::PointConfiguration::LabelVisibility] = true;

    series->setPointConfiguration(4, conf);

    conf.remove(QXYSeries::PointConfiguration::Color);
    conf[QXYSeries::PointConfiguration::LabelFormat] = "This Point";
    series->setPointConfiguration(6, conf);
    \endcode

    In this example, you can see a default QLineSeries with 10 points and with changed configuration
    of two points. Both changed points are visibly bigger than the others with a look derived from
    the series configuration.
    By default, points don't have labels, but the point at index 4 has a label thanks to the
    QXYSeries::PointConfiguration::LabelVisibility and QXYSeries::PointConfiguration::LabelFormat
    configuration values.
    The point at index 6 has a custom label \e {This Point} thanks to the
    QXYSeries::PointConfiguration::LabelFormat configuration value.
    Below is an example of a chart created in this way:
    \image xyseries_point_configuration.png

    \sa pointsConfiguration(), clearPointsConfiguration()
    \since 6.2
*/
void QXYSeries::setPointConfiguration(
        const int index, const QHash<QXYSeries::PointConfiguration, QVariant> &configuration)
{
    Q_D(QXYSeries);
    if (d->m_pointsConfiguration[index] != configuration) {
        d->m_pointsConfiguration[index] = configuration;
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
    }
}

/*!
    Enables customizing a particular aspect of a point's configuration.

    \note Points configuration concept provides a flexible way to configure various aspects
    of a point's appearance. Thus, values need to have an elastic type such as QVariant.
    See QXYSeries::PointConfiguration to see what \a value should be passed
    for certain \a key.
    \sa pointsConfiguration()
    \since 6.2
*/
void QXYSeries::setPointConfiguration(const int index, const QXYSeries::PointConfiguration key,
                                      const QVariant &value)
{
    Q_D(QXYSeries);
    if (d->setPointConfiguration(index, key, value))
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
}

/*!
    Enables customizing the configuration of multiple points as specified
    by \a pointsConfiguration.

    \sa pointsConfiguration()
    \since 6.2
*/
void QXYSeries::setPointsConfiguration(
        const QHash<int, QHash<QXYSeries::PointConfiguration, QVariant>> &pointsConfiguration)
{
    Q_D(QXYSeries);
    if (d->m_pointsConfiguration != pointsConfiguration) {
        d->m_pointsConfiguration = pointsConfiguration;
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
    }
}

/*!
    Returns a map representing the configuration of a point at \a index.

    With points configuration you can change various aspects of each point's look.

    \sa setPointConfiguration()
    \since 6.2
*/
QHash<QXYSeries::PointConfiguration, QVariant> QXYSeries::pointConfiguration(const int index) const
{
    Q_D(const QXYSeries);
    return d->m_pointsConfiguration[index];
}

/*!
    Returns a map with points' indexes as keys and points' configuration as values.

    \sa setPointConfiguration(), pointConfiguration()
    \since 6.2
*/
QHash<int, QHash<QXYSeries::PointConfiguration, QVariant>> QXYSeries::pointsConfiguration() const
{
    Q_D(const QXYSeries);
    return d->m_pointsConfiguration;
}

/*!
    Sets the points' sizes according to a passed list of values. Values from
    \a sourceData are sorted and mapped to a point size which is between \a minSize
    and \a maxSize.

    \note If \a sourceData length is smaller than number of points in the series, then
    size of the points at the end of the series will stay the same.
    \sa setPointConfiguration(), pointConfiguration()
    \since 6.2
*/
void QXYSeries::sizeBy(const QList<qreal> &sourceData, const qreal minSize, const qreal maxSize)
{
    Q_D(QXYSeries);

    Q_ASSERT(minSize <= maxSize);
    Q_ASSERT(minSize >= 0);

    qreal min = std::numeric_limits<qreal>::max();
    qreal max = -std::numeric_limits<qreal>::max();
    for (const auto &p : sourceData) {
        min = qMin(min, p);
        max = qMax(max, p);
    }

    const qreal range = max - min;
    const qreal sizeRange = maxSize - minSize;
    bool changed = false;

    for (int i = 0; i < sourceData.size() && i < d->m_points.size(); ++i) {
        qreal pointSize = minSize;
        if (range != 0) {
            const qreal startValue = sourceData.at(i) - min;
            const qreal percentage = startValue / range;
            pointSize = minSize + (percentage * sizeRange);
        }
        if (d->setPointConfiguration(i, QXYSeries::PointConfiguration::Size, pointSize))
            changed = true;
    }

    if (changed)
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
}

/*!
    Sets the points' color according to a passed list of values. Values from
    \a sourceData are sorted and mapped to the \a gradient.

    If the series has a QColorAxis attached, then a gradient from the axis
    is going to be used.

    \sa setPointConfiguration(), pointConfiguration(), QColorAxis
    \since 6.2
*/
void QXYSeries::colorBy(const QList<qreal> &sourceData, const QLinearGradient &gradient)
{
    Q_D(QXYSeries);

    d->m_colorByData = sourceData;
    if (d->m_colorByData.isEmpty())
        return;

    const qreal imgSize = 100.0;

    qreal min = std::numeric_limits<qreal>::max();
    qreal max = std::numeric_limits<qreal>::min();
    for (const auto &p : sourceData) {
        min = qMin(min, p);
        max = qMax(max, p);
    }

    qreal range = max - min;

    QLinearGradient usedGradient = gradient;

    // Gradient will be taked from the first attached color axis.
    // If there are more color axis, they will have just changed range.
    bool axisFound = false;
    const auto axes = attachedAxes();
    for (const auto &axis : axes) {
        if (axis->type() == QAbstractAxis::AxisTypeColor) {
            QColorAxis *colorAxis = static_cast<QColorAxis *>(axis);
            if (!axisFound) {
                usedGradient = QLinearGradient(QPointF(0,0), QPointF(0, imgSize));
                const auto stops = colorAxis->gradient().stops();
                for (const auto &stop : stops)
                    usedGradient.setColorAt(stop.first, stop.second);

                if (!colorAxis->autoRange()) {
                    min = colorAxis->min();
                    max = colorAxis->max();
                    range = max - min;
                }

                axisFound = true;
            }

            if (colorAxis->autoRange())
                colorAxis->setRange(min, max);
        }
    }

    QImage image(imgSize, imgSize, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.fillRect(image.rect(), usedGradient);

    // To ensure that negative values will be well handled, distance from min to 0
    // will be added to min and every single value. This will move entire values
    // list to positive only values.
    const qreal diff = min < 0 ? qAbs(min) : 0;
    min += diff;

    bool changed = false;

    for (int i = 0; i < sourceData.size() && i < d->m_points.size(); ++i) {
        const qreal startValue = qMax(0.0, sourceData.at(i) + diff - min);
        const qreal percentage = startValue / range;
        QColor color = image.pixelColor(0, qMin(percentage * imgSize, imgSize - 1));
        if (d->setPointConfiguration(i, QXYSeries::PointConfiguration::Color, color))
            changed = true;
    }

    if (changed)
        emit pointsConfigurationChanged(d->m_pointsConfiguration);
}

/*!
   Returns true if point at given \a index is among selected points and false otherwise.
   \note Selected points are drawn using the selected color if it was specified.
   \sa selectedPoints(), setPointSelected(), setSelectedColor()
   \since 6.2
 */
bool QXYSeries::isPointSelected(int index)
{
    Q_D(QXYSeries);
    return d->isPointSelected(index);
}

/*!
  Marks point at \a index as selected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectPoint(int index)
{
    setPointSelected(index, true);
}

/*!
  Deselects point at given \a index.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectPoint(int index)
{
    setPointSelected(index, false);
}

/*!
  Marks point at given \a index as either selected or deselected as specified by \a selected.
  \note Selected points are drawn using the selected color if it was specified. Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected(), setSelectedColor()
  \since 6.2
 */
void QXYSeries::setPointSelected(int index, bool selected)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    d->setPointSelected(index, selected, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks all points in the series as selected,
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectAllPoints()
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (int i = 0; i < d->m_points.size(); ++i)
        d->setPointSelected(i, true, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Deselects all points in the series.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectAllPoints()
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (int i = 0; i < d->m_points.size(); ++i)
        d->setPointSelected(i, false, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks multiple points passed in a \a indexes list as selected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::selectPoints(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, true, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Marks multiple points passed in a \a indexes list as deselected.
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::deselectPoints(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, false, callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Changes selection state of points at given \a indexes to the opposite one. Makes
  \note Emits QXYSeries::selectedPointsChanged
  \sa setPointSelected()
  \since 6.2
 */
void QXYSeries::toggleSelection(const QList<int> &indexes)
{
    Q_D(QXYSeries);

    bool callSignal = false;
    for (const int &index : indexes)
        d->setPointSelected(index, !isPointSelected(index), callSignal);

    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Returns a list of points indexes marked as selected.
  Selected points are visible regardless of points visibility.
  \sa setPointSelected(), pointsVisible()
  \since 6.2
 */
QList<int> QXYSeries::selectedPoints() const
{
    Q_D(const QXYSeries);
    return QList<int>(d->m_selectedPoints.begin(), d->m_selectedPoints.end());
}

/*!
  Removes the point that has the coordinates \a x and \a y from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(qreal x, qreal y)
{
    remove(QPointF(x, y));
}

/*!
  Removes the data point \a point from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(const QPointF &point)
{
    Q_D(QXYSeries);
    int index = d->m_points.indexOf(point);
    if (index == -1)
        return;
    remove(index);
}

/*!
  Removes the point at the position specified by \a index from the series.
  \sa pointRemoved()
*/
void QXYSeries::remove(int index)
{
    Q_D(QXYSeries);
    d->m_points.remove(index);

    bool callSignal = false;
    d->setPointSelected(index, false, callSignal);

    emit pointRemoved(index);
    if (callSignal)
        emit selectedPointsChanged();
}

/*!
  Removes the number of points specified by \a count from the series starting at
  the position specified by \a index.
  \sa pointsRemoved()
*/
void QXYSeries::removePoints(int index, int count)
{
    // This function doesn't overload remove as there is chance for it to get mixed up with
    // remove(qreal, qreal) overload in some implicit casting cases.
    Q_D(QXYSeries);
    if (count > 0) {
        d->m_points.remove(index, count);

        bool callSignal = false;
        if (!d->m_selectedPoints.empty()) {
            QSet<int> selectedAfterRemoving;

            for (const int &selectedPointIndex : std::as_const(d->m_selectedPoints)) {
                if (selectedPointIndex < index) {
                    selectedAfterRemoving << selectedPointIndex;
                } else if (selectedPointIndex >= index + count) {
                    selectedAfterRemoving << selectedPointIndex - count;
                    callSignal = true;
                } else {
                    callSignal = true;
                }
            }

            d->m_selectedPoints = selectedAfterRemoving;
        }

        emit pointsRemoved(index, count);
        if (callSignal)
            emit selectedPointsChanged();
    }
}

/*!
  Inserts the data point \a point in the series at the position specified by
  \a index.
  \sa pointAdded()
*/
void QXYSeries::insert(int index, const QPointF &point)
{
    Q_D(QXYSeries);
    if (isValidValue(point)) {
        index = qMax(0, qMin(index, d->m_points.size()));

        d->m_points.insert(index, point);

        bool callSignal = false;
        if (!d->m_selectedPoints.isEmpty()) {
            // if point was inserted we need to move already selected points by 1
            QSet<int> selectedAfterInsert;
            for (const auto &value : std::as_const(d->m_selectedPoints)) {
                if (value >= index) {
                    selectedAfterInsert << value + 1;
                    callSignal = true;
                } else {
                    selectedAfterInsert << value;
                }
            }
            d->m_selectedPoints = selectedAfterInsert;
        }

        emit pointAdded(index);
        if (callSignal)
            emit selectedPointsChanged();
    }
}

/*!
  Removes all points from the series.
  \sa pointsRemoved()
*/
void QXYSeries::clear()
{
    Q_D(QXYSeries);
    removePoints(0, d->m_points.size());
}

/*!
    Returns the points in the series.
*/
QList<QPointF> QXYSeries::points() const
{
    Q_D(const QXYSeries);
    return d->m_points;
}

#if QT_DEPRECATED_SINCE(6, 0)
/*!
    \deprecated

    Use points() instead.
    Returns the points in the series.

*/
QList<QPointF> QXYSeries::pointsVector() const
{
    Q_D(const QXYSeries);
    return d->m_points;
}
#endif

/*!
    Returns the data point at the position specified by \a index in the internal
    series of points.
*/
const QPointF &QXYSeries::at(int index) const
{
    Q_D(const QXYSeries);
    return d->m_points.at(index);
}

/*!
    Returns the number of data points in a series.
*/
int QXYSeries::count() const
{
    Q_D(const QXYSeries);
    return d->m_points.size();
}


/*!
    Sets the pen used for drawing points on the chart to \a pen. If the pen is
    not defined, the pen from the chart theme is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->seriesUpdated();
        if (emitColorChanged)
            emit colorChanged(pen.color());
        emit penChanged(pen);
    }
}

QPen QXYSeries::pen() const
{
    Q_D(const QXYSeries);
    if (d->m_pen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_pen;
}

/*!
    Sets the brush used for drawing points on the chart to \a brush. If the
    brush is not defined, the brush from the chart theme setting is used.
    \sa QChart::setTheme()
*/
void QXYSeries::setBrush(const QBrush &brush)
{
    Q_D(QXYSeries);
    if (d->m_brush != brush) {
        d->m_brush = brush;
        emit d->seriesUpdated();
    }
}

QBrush QXYSeries::brush() const
{
    Q_D(const QXYSeries);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QXYSeries::setColor(const QColor &color)
{
    QPen p = pen();
    if (p.color() != color) {
        p.setColor(color);
        setPen(p);
    }
}

QColor QXYSeries::color() const
{
    return pen().color();
}

void QXYSeries::setSelectedColor(const QColor &color)
{
    Q_D(QXYSeries);
    if (selectedColor() != color) {
        d->m_selectedColor = color;
        emit selectedColorChanged(color);
    }
}

QColor QXYSeries::selectedColor() const
{
    Q_D(const QXYSeries);
    return d->m_selectedColor;
}

void QXYSeries::setPointsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointsVisible != visible) {
        d->m_pointsVisible = visible;
        emit d->seriesUpdated();
    }
}

bool QXYSeries::pointsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointsVisible;
}

void QXYSeries::setPointLabelsFormat(const QString &format)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsFormat != format) {
        d->m_pointLabelsFormat = format;
        emit pointLabelsFormatChanged(format);
    }
}

QString QXYSeries::pointLabelsFormat() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsFormat;
}

void QXYSeries::setPointLabelsVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsVisible != visible) {
        d->m_pointLabelsVisible = visible;
        emit pointLabelsVisibilityChanged(visible);
    }
}

bool QXYSeries::pointLabelsVisible() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsVisible;
}

void QXYSeries::setPointLabelsFont(const QFont &font)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsFont != font) {
        d->m_pointLabelsFont = font;
        emit pointLabelsFontChanged(font);
    }
}

QFont QXYSeries::pointLabelsFont() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsFont;
}

void QXYSeries::setPointLabelsColor(const QColor &color)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsColor != color) {
        d->m_pointLabelsColor = color;
        emit pointLabelsColorChanged(color);
    }
}

QColor QXYSeries::pointLabelsColor() const
{
    Q_D(const QXYSeries);
    if (d->m_pointLabelsColor == QChartPrivate::defaultPen().color())
        return QPen().color();
    else
        return d->m_pointLabelsColor;
}

void QXYSeries::setPointLabelsClipping(bool enabled)
{
    Q_D(QXYSeries);
    if (d->m_pointLabelsClipping != enabled) {
        d->m_pointLabelsClipping = enabled;
        emit pointLabelsClippingChanged(enabled);
    }
}

bool QXYSeries::pointLabelsClipping() const
{
    Q_D(const QXYSeries);
    return d->m_pointLabelsClipping;
}

/*!
    Sets the image used for drawing markers on each point of the series as
    the value of \a lightMarker.

    The default value is a default-QImage() (QImage::isNull() == true), meaning no light marker
    will be painted.
    You can reset back to default (disabled) by calling this function with a null QImage (QImage()).

    The light markers visualize the data points of this series and as such are an alternative
    to \c setPointsVisible(true).
    If a light marker is set with this method, visible points as set with \c setPointsVisible(true)
    are not displayed.

    Unlike the elements of \l {QScatterSeries}{QScatterSeries} the light markers
    are not represented by QGraphicsItem, but are just painted (no objects created).
    However, the mouse-event-signals of QXYSeries behave the same way,
    meaning that you'll get the exact domain value of the point if you click/press/hover
    the light marker. You'll still get the in between domain value if you click on the line.
    The light markers are above the line in terms of painting as well as events.

    \sa QXYSeries::lightMarker()
    \since 6.2
*/
void QXYSeries::setLightMarker(const QImage &lightMarker)
{
    Q_D(QXYSeries);
    if (d->m_lightMarker == lightMarker)
        return;

    d->m_lightMarker = lightMarker;
    emit d->seriesUpdated();
    emit lightMarkerChanged(d->m_lightMarker);
}

/*!
    Gets the image used for drawing markers on each point of the series.

    The default value is QImage(), meaning no light marker will be painted.

    The light markers visualize the data points of this series and as such are an alternative
    to setPointsVisible(true).
    Both features can be enabled independently from each other.

    Unlike the elements of \l {QScatterSeries}{QScatterSeries} the light markers
    are not represented by QGraphicsItem, but are just painted (no objects created).
    However, the mouse-event-signals of QXYSeries behave the same way,
    meaning that you'll get the exact domain value of the point if you click/press/hover
    the light marker. You'll still get the in between domain value if you click on the line.
    The light markers are above the line in terms of painting as well as events.
    \sa QXYSeries::setLightMarker()
    \since 6.2
*/
const QImage &QXYSeries::lightMarker() const
{
    Q_D(const QXYSeries);
    return d->m_lightMarker;
}

/*!
    Sets the image used for drawing markers on selected series's points to \a selectedLightMarker.

    The default value is QImage(), meaning usual lightMarker() will be painted.

    This is an equivalent for \l{selectedColor} if you prefer light markers over
    normal points, but still want to distinguish selected points.

    \sa lightMarker(), selectedColor, setPointSelected()
    \since 6.2
*/
void QXYSeries::setSelectedLightMarker(const QImage &selectedLightMarker)
{
    Q_D(QXYSeries);
    if (d->m_selectedLightMarker == selectedLightMarker)
        return;

    d->m_selectedLightMarker = selectedLightMarker;
    emit d->seriesUpdated();
    emit selectedLightMarkerChanged(d->m_selectedLightMarker);
}

/*!
    Returns the image used for drawing markers on selected series' points.

    The default value is QImage(), meaning usual lightMarker() will be painted.

    This is equivalent to \l{selectedColor} if you prefer light markers over
    normal points, but still want to distinguish selected points.

    \sa lightMarker(), selectedColor, setPointSelected()
    \since 6.2
*/
const QImage &QXYSeries::selectedLightMarker() const
{
    Q_D(const QXYSeries);
    return d->m_selectedLightMarker;
}

/*!
    Sets the \a size of the marker used to render points in the series.

    The default size is 15.0.
    \sa QScatterSeries::markerSize
    \since 6.2
*/
void QXYSeries::setMarkerSize(qreal size)
{
    Q_D(QXYSeries);

    if (!qFuzzyCompare(d->m_markerSize, size)) {
        d->m_markerSizeDefault = false;
        d->setMarkerSize(size);
        emit d->seriesUpdated();
        emit markerSizeChanged(size);
    }
}

/*!
    Gets the size of the marker used to render points in the series.

    The default size depends on the specific QXYSeries type.
    QScatterSeries has a default of 15.0
    QLineSeries has a default of the series pen size * 1.5
    \sa QScatterSeries::markerSize
    \since 6.2
*/
qreal QXYSeries::markerSize() const
{
    Q_D(const QXYSeries);
    return d->m_markerSize;
}

void QXYSeries::setBestFitLineVisible(bool visible)
{
    Q_D(QXYSeries);
    if (d->m_bestFitLineVisible != visible) {
        d->m_bestFitLineVisible = visible;
        emit bestFitLineVisibilityChanged(visible);
        emit d->seriesUpdated();
    }
}

bool QXYSeries::bestFitLineVisible() const
{
    Q_D(const QXYSeries);
    return d->m_bestFitLineVisible;
}

/*!
    Returns a pair of numbers where the first number is a slope factor
    and the second number is intercept of a linear function for a best fit line.

    Those factors are calculated using Least Squares Method based
    on points passed to the series.

    Parameter \a ok is used to report a failure by setting its value to \c false
    and to report a success by setting its value to \c true.

    \sa QXYSeries::bestFitLineVisible()
    \since 6.2
*/
QPair<qreal, qreal> QXYSeries::bestFitLineEquation(bool &ok) const
{
    Q_D(const QXYSeries);
    return d->bestFitLineEquation(ok);
}

void QXYSeries::setBestFitLinePen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_bestFitLinePen != pen) {
        bool emitColorChanged = d->m_bestFitLinePen.color() != pen.color();
        d->m_bestFitLinePen = pen;
        emit d->seriesUpdated();
        if (emitColorChanged)
            bestFitLineColorChanged(pen.color());
        emit bestFitLinePenChanged(pen);
    }
}

QPen QXYSeries::bestFitLinePen() const
{
    Q_D(const QXYSeries);
    if (d->m_bestFitLinePen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d->m_bestFitLinePen;
}

/*!
    Stream operator for adding the data point \a point to the series.
    \sa append()
*/
QXYSeries &QXYSeries::operator<< (const QPointF &point)
{
    append(point);
    return *this;
}

/*!
    Stream operator for adding the list of data points specified by \a points
    to the series.
    \sa append()
*/

QXYSeries &QXYSeries::operator<< (const QList<QPointF>& points)
{
    append(points);
    return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYSeriesPrivate::QXYSeriesPrivate(QXYSeries *q)
    : QAbstractSeriesPrivate(q),
      m_pen(QChartPrivate::defaultPen()),
      m_brush(QChartPrivate::defaultBrush()),
      m_pointsVisible(false),
      m_pointLabelsFormat(QLatin1String("@xPoint, @yPoint")),
      m_pointLabelsVisible(false),
      m_pointLabelsFont(QChartPrivate::defaultFont()),
      m_pointLabelsColor(QChartPrivate::defaultPen().color()),
      m_pointLabelsClipping(true),
      m_bestFitLinePen(QChartPrivate::defaultPen()),
      m_bestFitLineVisible(false),
      m_markerSize(15.0)
{
}

void QXYSeriesPrivate::initializeDomain()
{
    qreal minX(0);
    qreal minY(0);
    qreal maxX(1);
    qreal maxY(1);

    Q_Q(QXYSeries);

    const QList<QPointF> &points = q->points();

    if (!points.isEmpty()) {
        minX = points[0].x();
        minY = points[0].y();
        maxX = minX;
        maxY = minY;

        for (int i = 0; i < points.size(); i++) {
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

QList<QLegendMarker*> QXYSeriesPrivate::createLegendMarkers(QLegend* legend)
{
    Q_Q(QXYSeries);
    QList<QLegendMarker*> list;
    return list << new QXYLegendMarker(q,legend);
}

void QXYSeriesPrivate::initializeAxes()
{

}

QAbstractAxis::AxisType QXYSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return QAbstractAxis::AxisTypeValue;
}

QAbstractAxis* QXYSeriesPrivate::createDefaultAxis(Qt::Orientation orientation) const
{
    Q_UNUSED(orientation);
    return new QValueAxis;
}

void QXYSeriesPrivate::initializeAnimations(QChart::AnimationOptions options,
                                            int duration, QEasingCurve &curve)
{
    XYChart *item = static_cast<XYChart *>(m_item.get());
    Q_ASSERT(item);
    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        item->setAnimation(new XYAnimation(item, duration, curve));
    else
        item->setAnimation(0);
    QAbstractSeriesPrivate::initializeAnimations(options, duration, curve);
}

void QXYSeriesPrivate::drawPointLabels(QPainter *painter, const QList<QPointF> &allPoints,
                                       const int offset)
{
    if (m_pointLabelsVisible || !m_pointsConfiguration.isEmpty()) {
        if (m_pointLabelsClipping)
            painter->setClipping(true);
        else
            painter->setClipping(false);

        QList<int> pointsToSkip;
        QHash<int, QString> labelFormats;
        QHash<int, int> offsets;

        if (!m_pointsConfiguration.isEmpty()) {
            for (int i = 0; i < allPoints.size(); ++i) {
                bool drawLabel = m_pointLabelsVisible;
                if (m_pointsConfiguration.contains(i)) {
                    const auto &conf = m_pointsConfiguration[i];
                    auto key = QXYSeries::PointConfiguration::LabelVisibility;
                    if (conf.contains(key)) {
                        drawLabel = m_pointsConfiguration[i][key].toBool();
                        key = QXYSeries::PointConfiguration::Size;
                        if (drawLabel && conf.contains(key))
                            offsets[i] = conf[key].toReal();
                    }
                    key = QXYSeries::PointConfiguration::LabelFormat;
                    if (conf.contains(key) && !conf[key].toString().isEmpty())
                        labelFormats[i] = conf[key].toString();
                }

                if (!drawLabel)
                    pointsToSkip << i;
            }
        }

        drawSeriesPointLabels(painter, allPoints, offset, offsets, pointsToSkip, labelFormats);
    }
}

void QXYSeriesPrivate::drawSeriesPointLabels(QPainter *painter, const QList<QPointF> &points,
                                             const int offset, const QHash<int, int> &offsets,
                                             const QList<int> &indexesToSkip,
                                             const QHash<int, QString> &labelFormats)
{
    if (points.size() == 0)
        return;

    static const QString xPointTag(QLatin1String("@xPoint"));
    static const QString yPointTag(QLatin1String("@yPoint"));
    static const QString indexTag(QLatin1String("@index"));

    QFont f(m_pointLabelsFont);
    f.setPixelSize(QFontInfo(m_pointLabelsFont).pixelSize());
    painter->setFont(f);
    painter->setPen(QPen(m_pointLabelsColor));
    QFontMetrics fm(painter->font());
    // m_points is used for the label here as it has the series point information
    // points variable passed is used for positioning because it has the coordinates
    const int pointCount = qMin(points.size(), m_points.size());
    for (int i(0); i < pointCount; i++) {
        if (indexesToSkip.contains(i))
            continue;

        QString pointLabel = labelFormats.contains(i) ? labelFormats[i] : m_pointLabelsFormat;
        pointLabel.replace(xPointTag, presenter()->numberToString(m_points.at(i).x()));
        pointLabel.replace(yPointTag, presenter()->numberToString(m_points.at(i).y()));
        pointLabel.replace(indexTag, presenter()->numberToString(i));

        int currOffset = offset;
        if (offsets.contains(i))
            currOffset = offsets[i];

        const int labelOffset = currOffset + 2;

        // Position text in relation to the point
        int pointLabelWidth = fm.horizontalAdvance(pointLabel);
        QPointF position(points.at(i));
        position.setX(position.x() - pointLabelWidth / 2);
        position.setY(position.y() - labelOffset);

        painter->drawText(position, pointLabel);
    }
}

void QXYSeriesPrivate::drawBestFitLine(QPainter *painter, const QRectF &clipRect)
{
    bool ok = false;
    const auto &bestFitLineParams = bestFitLineEquation(ok);

    if (!ok)
        return;

    auto *domain = this->domain();
    const auto clipOriginX = domain->isReverseX() ? clipRect.right() : clipRect.left();
    const auto clipOriginY = domain->isReverseY() ? clipRect.top() : clipRect.bottom();
    const auto domainOrigin = domain->calculateDomainPoint({clipOriginX, clipOriginY});

    const qreal x1 = domainOrigin.x();
    const qreal y1 = bestFitLineParams.first * x1 + bestFitLineParams.second;
    QPointF p1 = domain->calculateGeometryPoint(QPointF(x1, y1), ok);

    const qreal x2 = domainOrigin.x() + 1;
    const qreal y2 = bestFitLineParams.first * x2 + bestFitLineParams.second;
    QPointF p2 = domain->calculateGeometryPoint(QPointF(x2, y2), ok);

    if (ok) {
        QLineF bestFitLine { p1, p2 };
        // maxLength is length of the diagonal, no line can be longer
        const qreal maxLength = qSqrt(qPow(clipRect.width(), 2) * qPow(clipRect.height(), 2));
        bestFitLine.setLength(maxLength);

        painter->save();
        painter->setPen(m_bestFitLinePen);
        painter->drawLine(bestFitLine);
        painter->restore();
    }
}

void QXYSeries::setBestFitLineColor(const QColor &color)
{
    QPen p = bestFitLinePen();
    if (p.color() != color) {
        p.setColor(color);
        setBestFitLinePen(p);
    }
}

QColor QXYSeries::bestFitLineColor() const
{
    return bestFitLinePen().color();
}

QPair<qreal, qreal> QXYSeriesPrivate::bestFitLineEquation(bool &ok) const
{
    if (m_points.size() <= 1) {
        ok = false;
        return { 0, 0 };
    }

    ok = true;
    qreal xSum = 0.0, x2Sum = 0.0, ySum = 0.0, xySum = 0.0;
    for (const auto &point : m_points) {
        xSum += point.x();
        ySum += point.y();
        x2Sum += qPow(point.x(), 2);
        xySum += point.x() * point.y();
    }

    const qreal divisor = m_points.size() * x2Sum - xSum * xSum;
    // To prevent crashes in unusual cases
    if (divisor == 0.0) {
        ok = false;
        return { 0, 0 };
    }

    qreal a = (m_points.size() * xySum - xSum * ySum) / divisor;
    qreal b = (x2Sum * ySum - xSum * xySum) / divisor;

    return { a, b };
}

void QXYSeriesPrivate::setPointSelected(int index, bool selected, bool &callSignal)
{
    if (index < 0 || index > m_points.size() - 1)
        return;

    if (selected) {
        if (!isPointSelected(index)) {
            m_selectedPoints << index;
            callSignal = true;
        }
    } else {
        if (isPointSelected(index)) {
            m_selectedPoints.remove(index);
            callSignal = true;
        }
    }
}

bool QXYSeriesPrivate::isPointSelected(int index)
{
    return m_selectedPoints.contains(index);
}

bool QXYSeriesPrivate::isMarkerSizeDefault()
{
    return m_markerSizeDefault;
}

void QXYSeriesPrivate::setMarkerSize(qreal markerSize)
{
    m_markerSize = markerSize;
}

QList<qreal> QXYSeriesPrivate::colorByData() const
{
    return m_colorByData;
}

bool QXYSeriesPrivate::setPointConfiguration(const int index,
                                             const QXYSeries::PointConfiguration key,
                                             const QVariant &value)
{
    QHash<QXYSeries::PointConfiguration, QVariant> conf;
    if (m_pointsConfiguration.contains(index))
        conf = m_pointsConfiguration[index];

    bool changed = false;
    if (conf.contains(key)) {
        if (conf[key] != value)
            changed = true;
    } else {
        changed = true;
    }

    conf[key] = value;
    m_pointsConfiguration[index] = conf;

    return changed;
}

QT_END_NAMESPACE

#include "moc_qxyseries.cpp"
#include "moc_qxyseries_p.cpp"
