/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QAbstractAxis>
#include <private/qabstractaxis_p.h>
#include <private/chartdataset_p.h>
#include <private/charttheme_p.h>
#include <private/qchart_p.h>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAbstractAxis
    \inmodule Qt Charts
    \brief The QAbstractAxis class is used for manipulating chart's axis.
    \mainclass

    Each series can be bound to one or more horizontal and vertical axes, but mixing axis types
    that would result in different domains is not supported, such as specifying
    QValueAxis and QLogValueAxis on the same orientation.

    Properties and visibility of various axis elements such as axis line, title, labels, grid lines,
    and shades can be individually controlled.
*/
/*!
    \qmltype AbstractAxis
    \instantiates QAbstractAxis
    \inqmlmodule QtCharts

    \brief The AbstractAxis is a base element used for specialized axis elements.

    Each series can be bound to only one horizontal and vertical axis.

    Properties and visibility of various axis elements such as axis line, title, labels, grid lines,
    and shades can be individually controlled.
*/

/*!
    \enum QAbstractAxis::AxisType

    The type of the axis object.

    \value AxisTypeNoAxis
    \value AxisTypeValue
    \value AxisTypeBarCategory
    \value AxisTypeCategory
    \value AxisTypeDateTime
    \value AxisTypeLogValue
*/

/*!
 *\fn void QAbstractAxis::type() const
  Returns the type of the axis
*/

/*!
  \property QAbstractAxis::lineVisible
  The visibility of the axis line
*/
/*!
  \qmlproperty bool AbstractAxis::lineVisible
  The visibility of the axis line
*/

/*!
  \property QAbstractAxis::linePen
  The pen of the line.
*/

/*!
  \property QAbstractAxis::labelsVisible
  Defines if axis labels are visible.
*/
/*!
  \qmlproperty bool AbstractAxis::labelsVisible
  Defines if axis labels are visible.
*/

/*!
  \property QAbstractAxis::labelsBrush
  The brush of the labels. Only the color of the brush is relevant.
*/

/*!
  \property QAbstractAxis::visible
  The visibility of the axis.
*/
/*!
  \qmlproperty bool AbstractAxis::visible
  The visibility of the axis.
*/

/*!
  \property QAbstractAxis::gridVisible
  The visibility of the grid lines.
*/
/*!
  \qmlproperty bool AbstractAxis::gridVisible
  The visibility of the grid lines.
*/

/*!
  \property QAbstractAxis::color
  The color of the axis and ticks.
*/
/*!
  \qmlproperty color AbstractAxis::color
  The color of the axis and ticks.
*/

/*!
  \property QAbstractAxis::gridLinePen
  The pen of the grid line.
*/

/*!
  \property QAbstractAxis::labelsFont
  The font of the axis labels.
*/

/*!
  \qmlproperty Font AbstractAxis::labelsFont
  The font of the axis labels.

  See the Qt documentation for more details of Font.
*/

/*!
  \property QAbstractAxis::labelsColor
  The color of the axis labels.
*/
/*!
  \qmlproperty color AbstractAxis::labelsColor
  The color of the axis labels.
*/

/*!
  \property QAbstractAxis::labelsAngle
  The angle of the axis labels in degrees.
*/
/*!
  \qmlproperty int AbstractAxis::labelsAngle
  The angle of the axis labels in degrees.
*/

/*!
  \property QAbstractAxis::shadesVisible
  The visibility of the axis shades.
*/
/*!
  \qmlproperty bool AbstractAxis::shadesVisible
  The visibility of the axis shades.
*/

/*!
  \property QAbstractAxis::shadesColor
  The fill (brush) color of the axis shades.
*/
/*!
  \qmlproperty color AbstractAxis::shadesColor
  The fill (brush) color of the axis shades.
*/

/*!
  \property QAbstractAxis::shadesBorderColor
  The border (pen) color of the axis shades.
*/
/*!
  \qmlproperty color AbstractAxis::shadesBorderColor
  The border (pen) color of the axis shades.
*/

/*!
  \property QAbstractAxis::shadesPen
  The pen of the axis shades (area between grid lines).
*/

/*!
  \property QAbstractAxis::shadesBrush
  The brush of the axis shades (area between grid lines).
*/

/*!
  \property QAbstractAxis::titleVisible
  The visibility of the axis title. By default the value is true.
*/
/*!
  \qmlproperty bool AbstractAxis::titleVisible
  The visibility of the axis title. By default the value is true.
*/

/*!
  \property QAbstractAxis::titleText
  The title of the axis. Empty by default. Axis titles support html formatting.
*/
/*!
  \qmlproperty String AbstractAxis::titleText
  The title of the axis. Empty by default. Axis titles support html formatting.
*/

/*!
  \property QAbstractAxis::titleBrush
  The brush of the title text. Only the color of the brush is relevant.
*/

/*!
  \property QAbstractAxis::titleFont
  The font of the title of the axis.
*/
/*!
  \qmlproperty Font AbstractAxis::titleFont
  The font of the title of the axis.
*/

/*!
  \property QAbstractAxis::orientation
  The orientation of the axis. Fixed to either Qt::Horizontal or Qt::Vertical when you add the axis to a chart.
*/
/*!
  \qmlproperty Qt.Orientation AbstractAxis::orientation
  The orientation of the axis. Fixed to either Qt.Horizontal or Qt.Vertical when the axis is set to a series.
*/

/*!
  \property QAbstractAxis::alignment
  The alignment of the axis. Can be Qt::AlignLeft, Qt::AlignRight, Qt::AlignBottom, or Qt::AlignTop.
*/
/*!
  \qmlproperty alignment AbstractAxis::alignment
  The alignment of the axis. Can be Qt.AlignLeft, Qt.AlignRight, Qt.AlignBottom, or Qt.AlignTop.
*/

/*!
  \fn void QAbstractAxis::visibleChanged(bool visible)
  Visibility of the axis has changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onVisibleChanged(bool visible)
  Visibility of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::linePenChanged(const QPen& pen)
  The pen of the line of the axis has changed to \a pen.
*/

/*!
  \fn void QAbstractAxis::lineVisibleChanged(bool visible)
  Visibility of the axis line has changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onLineVisibleChanged(bool visible)
  Visibility of the axis line has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::labelsVisibleChanged(bool visible)
  Visibility of the labels of the axis has changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onLabelsVisibleChanged(bool visible)
  Visibility of the labels of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::labelsFontChanged(const QFont& font)
  The font of the axis labels has changed to \a font.
*/
/*!
  \qmlsignal AbstractAxis::onLabelsFontChanged(Font font)
  The font of the axis labels has changed to \a font.
*/

/*!
  \fn void QAbstractAxis::labelsBrushChanged(const QBrush& brush)
  The brush of the axis labels has changed to \a brush.
*/

/*!
  \fn void QAbstractAxis::labelsAngleChanged(int angle)
  The angle of the axis labels has changed to \a angle.
*/
/*!
  \qmlsignal AbstractAxis::onLabelsAngleChanged(int angle)
  The angle of the axis labels has changed to \a angle.
*/

/*!
  \fn void QAbstractAxis::gridVisibleChanged(bool visible)
  Visibility of the grid lines of the axis has changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onGridVisibleChanged(bool visible)
  Visibility of the grid lines of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::gridLinePenChanged(const QPen& pen)
  The pen of the grid line has changed to \a pen.
*/

/*!
  \fn void QAbstractAxis::colorChanged(QColor color)
  Emitted if the \a color of the axis is changed.
*/
/*!
  \qmlsignal AbstractAxis::onColorChanged(QColor color)
  Emitted if the \a color of the axis is changed.
*/

/*!
  \fn void QAbstractAxis::labelsColorChanged(QColor color)
  Emitted if the \a color of the axis labels is changed.
*/
/*!
  \qmlsignal AbstractAxis::onLabelsColorChanged(QColor color)
  Emitted if the \a color of the axis labels is changed.
*/

/*!
  \fn void QAbstractAxis::titleVisibleChanged(bool visible)
  Visibility of the title text of the axis has changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onTitleVisibleChanged(bool visible)
  Visibility of the title text of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::titleTextChanged(const QString& text)
  The text of the axis title has changed to \a text.
*/
/*!
  \qmlsignal AbstractAxis::onTitleTextChanged(String text)
  The text of the axis title has changed to \a text.
*/

/*!
  \fn void QAbstractAxis::titleBrushChanged(const QBrush& brush)
  The brush of the axis title has changed to \a brush.
*/

/*!
  \fn void QAbstractAxis::titleFontChanged(const QFont& font)
  The font of the axis title has changed to \a font.
*/
/*!
  \qmlsignal AbstractAxis::onTitleFontChanged(Font font)
  The font of the axis title has changed to \a font.
*/

/*!
  \fn void QAbstractAxis::shadesVisibleChanged(bool)
  Emitted if the visibility of the axis shades is changed to \a visible.
*/
/*!
  \qmlsignal AbstractAxis::onShadesVisibleChanged(bool visible)
  Emitted if the visibility of the axis shades is changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::shadesColorChanged(QColor color)
  Emitted if the \a color of the axis shades is changed.
*/
/*!
  \qmlsignal AbstractAxis::onShadesColorChanged(QColor color)
  Emitted if the \a color of the axis shades is changed.
*/

/*!
  \fn void QAbstractAxis::shadesBorderColorChanged(QColor)
  Emitted if the border \a color of the axis shades is changed.
*/
/*!
  \qmlsignal AbstractAxis::onBorderColorChanged(QColor color)
  Emitted if the border \a color of the axis shades is changed.
*/

/*!
  \fn void QAbstractAxis::shadesBrushChanged(const QBrush& brush)
  The brush of the axis shades has changed to \a brush.
*/

/*!
  \fn void QAbstractAxis::shadesPenChanged(const QPen& pen)
  The pen of the axis shades has changed to \a pen.
*/

/*!
 \internal
  Constructs new axis object which is a child of \a parent. Ownership is taken by
  QChart when axis added.
*/

QAbstractAxis::QAbstractAxis(QAbstractAxisPrivate &d, QObject *parent)
    : QObject(parent),
      d_ptr(&d)
{
}

/*!
  Destructor of the axis object. When axis is added to chart, chart object takes ownership.
*/

QAbstractAxis::~QAbstractAxis()
{
    if (d_ptr->m_chart)
        qFatal("Still binded axis detected !");
}

/*!
  Sets \a pen used to draw axis line and ticks.
 */
void QAbstractAxis::setLinePen(const QPen &pen)
{
    if (d_ptr->m_axisPen != pen) {
        d_ptr->m_axisPen = pen;
        emit linePenChanged(pen);
    }
}

/*!
  Returns pen used to draw axis and ticks.
*/
QPen QAbstractAxis::linePen() const
{
    if (d_ptr->m_axisPen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d_ptr->m_axisPen;
}

void QAbstractAxis::setLinePenColor(QColor color)
{
    QPen p = d_ptr->m_axisPen;
    if (p.color() != color) {
        p.setColor(color);
        setLinePen(p);
        emit colorChanged(color);
    }
}

QColor QAbstractAxis::linePenColor() const
{
    return linePen().color();
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QAbstractAxis::setLineVisible(bool visible)
{
    if (d_ptr->m_arrowVisible != visible) {
        d_ptr->m_arrowVisible = visible;
        emit lineVisibleChanged(visible);
    }
}

bool QAbstractAxis::isLineVisible() const
{
    return d_ptr->m_arrowVisible;
}

void QAbstractAxis::setGridLineVisible(bool visible)
{
    if (d_ptr->m_gridLineVisible != visible) {
        d_ptr->m_gridLineVisible = visible;
        emit gridVisibleChanged(visible);
    }
}

bool QAbstractAxis::isGridLineVisible() const
{
    return d_ptr->m_gridLineVisible;
}

/*!
  Sets \a pen used to draw grid line.
*/
void QAbstractAxis::setGridLinePen(const QPen &pen)
{
    if (d_ptr->m_gridLinePen != pen) {
        d_ptr->m_gridLinePen = pen;
        emit gridLinePenChanged(pen);
    }
}

/*!
  Returns pen used to draw grid.
*/
QPen QAbstractAxis::gridLinePen() const
{
    if (d_ptr->m_gridLinePen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d_ptr->m_gridLinePen;
}

void QAbstractAxis::setLabelsVisible(bool visible)
{
    if (d_ptr->m_labelsVisible != visible) {
        d_ptr->m_labelsVisible = visible;
        emit labelsVisibleChanged(visible);
    }
}

bool QAbstractAxis::labelsVisible() const
{
    return d_ptr->m_labelsVisible;
}

/*!
  Sets \a brush used to draw labels.
 */
void QAbstractAxis::setLabelsBrush(const QBrush &brush)
{
    if (d_ptr->m_labelsBrush != brush) {
        d_ptr->m_labelsBrush = brush;
        emit labelsBrushChanged(brush);
    }
}

/*!
  Returns brush used to draw labels.
*/
QBrush  QAbstractAxis::labelsBrush() const
{
    if (d_ptr->m_labelsBrush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_labelsBrush;
}

/*!
  Sets \a font used to draw labels.
*/
void QAbstractAxis::setLabelsFont(const QFont &font)
{
    if (d_ptr->m_labelsFont != font) {
        d_ptr->m_labelsFont = font;
        emit labelsFontChanged(font);
    }
}

/*!
  Returns font used to draw labels.
*/
QFont QAbstractAxis::labelsFont() const
{
    if (d_ptr->m_labelsFont == QChartPrivate::defaultFont())
        return QFont();
    else
        return d_ptr->m_labelsFont;
}

void QAbstractAxis::setLabelsAngle(int angle)
{
    if (d_ptr->m_labelsAngle != angle) {
        d_ptr->m_labelsAngle = angle;
        emit labelsAngleChanged(angle);
    }
}

int QAbstractAxis::labelsAngle() const
{
    return d_ptr->m_labelsAngle;
}
void QAbstractAxis::setLabelsColor(QColor color)
{
    QBrush b = d_ptr->m_labelsBrush;
    if (b.color() != color) {
        b.setColor(color);
        setLabelsBrush(b);
        emit labelsColorChanged(color);
    }
}

QColor QAbstractAxis::labelsColor() const
{
    return labelsBrush().color();
}

void QAbstractAxis::setTitleVisible(bool visible)
{
    if (d_ptr->m_titleVisible != visible) {
        d_ptr->m_titleVisible = visible;
        emit titleVisibleChanged(visible);
    }
}

bool QAbstractAxis::isTitleVisible() const
{
    return d_ptr->m_titleVisible;
}

/*!
  Sets \a brush used to draw title.
 */
void QAbstractAxis::setTitleBrush(const QBrush &brush)
{
    if (d_ptr->m_titleBrush != brush) {
        d_ptr->m_titleBrush = brush;
        emit titleBrushChanged(brush);
    }
}

/*!
  Returns brush used to draw title.
*/
QBrush QAbstractAxis::titleBrush() const
{
    if (d_ptr->m_titleBrush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d_ptr->m_titleBrush;
}

/*!
  Sets \a font used to draw title.
*/
void QAbstractAxis::setTitleFont(const QFont &font)
{
    if (d_ptr->m_titleFont != font) {
        d_ptr->m_titleFont = font;
        emit titleFontChanged(font);
    }
}

/*!
  Returns font used to draw title.
*/
QFont QAbstractAxis::titleFont() const
{
    if (d_ptr->m_titleFont == QChartPrivate::defaultFont())
        return QFont();
    else
        return d_ptr->m_titleFont;
}

void QAbstractAxis::setTitleText(const QString &title)
{
    if (d_ptr->m_title != title) {
        d_ptr->m_title = title;
        emit titleTextChanged(title);
    }
}

QString QAbstractAxis::titleText() const
{
    return d_ptr->m_title;
}


void QAbstractAxis::setShadesVisible(bool visible)
{
    if (d_ptr->m_shadesVisible != visible) {
        d_ptr->m_shadesVisible = visible;
        emit shadesVisibleChanged(visible);
    }
}

bool QAbstractAxis::shadesVisible() const
{
    return d_ptr->m_shadesVisible;
}

/*!
  Sets \a pen used to draw shades.
*/
void QAbstractAxis::setShadesPen(const QPen &pen)
{
    if (d_ptr->m_shadesPen != pen) {
        d_ptr->m_shadesPen = pen;
        emit shadesPenChanged(pen);
    }
}

/*!
  Returns pen used to draw shades.
*/
QPen QAbstractAxis::shadesPen() const
{
    if (d_ptr->m_shadesPen == QChartPrivate::defaultPen())
        return QPen();
    else
        return d_ptr->m_shadesPen;
}

/*!
  Sets \a brush used to draw shades.
*/
void QAbstractAxis::setShadesBrush(const QBrush &brush)
{
    if (d_ptr->m_shadesBrush != brush) {
        d_ptr->m_shadesBrush = brush;
        emit shadesBrushChanged(brush);
    }
}

/*!
   Returns brush used to draw shades.
*/
QBrush QAbstractAxis::shadesBrush() const
{
    if (d_ptr->m_shadesBrush == QChartPrivate::defaultBrush())
        return QBrush(Qt::SolidPattern);
    else
        return d_ptr->m_shadesBrush;
}

void QAbstractAxis::setShadesColor(QColor color)
{
    QBrush b = d_ptr->m_shadesBrush;
    if (b.color() != color) {
        b.setColor(color);
        setShadesBrush(b);
        emit shadesColorChanged(color);
    }
}

QColor QAbstractAxis::shadesColor() const
{
    return shadesBrush().color();
}

void QAbstractAxis::setShadesBorderColor(QColor color)
{
    QPen p = d_ptr->m_shadesPen;
    if (p.color() != color) {
        p.setColor(color);
        setShadesPen(p);
        emit shadesColorChanged(color);
    }
}

QColor QAbstractAxis::shadesBorderColor() const
{
    return shadesPen().color();
}


bool QAbstractAxis::isVisible() const
{
    return d_ptr->m_visible;
}

/*!
  Sets axis, shades, labels and grid lines to be visible.
*/
void QAbstractAxis::setVisible(bool visible)
{
    if (d_ptr->m_visible != visible) {
        d_ptr->m_visible = visible;
        emit visibleChanged(visible);
    }
}


/*!
  Sets axis, shades, labels and grid lines to be visible.
*/
void QAbstractAxis::show()
{
    setVisible(true);
}

/*!
  Sets axis, shades, labels and grid lines to not be visible.
*/
void QAbstractAxis::hide()
{
    setVisible(false);
}

/*!
  Sets the minimum value shown on the axis.
  Depending on the actual axis type the \a min parameter is converted to appropriate type.
  If the conversion is impossible then the function call does nothing
*/
void QAbstractAxis::setMin(const QVariant &min)
{
    d_ptr->setMin(min);
}

/*!
  Sets the maximum value shown on the axis.
  Depending on the actual axis type the \a max parameter is converted to appropriate type.
  If the conversion is impossible then the function call does nothing
*/
void QAbstractAxis::setMax(const QVariant &max)
{
    d_ptr->setMax(max);
}

/*!
  Sets the range shown on the axis.
  Depending on the actual axis type the \a min and \a max parameters are converted to appropriate types.
  If the conversion is impossible then the function call does nothing.
*/
void QAbstractAxis::setRange(const QVariant &min, const QVariant &max)
{
    d_ptr->setRange(min, max);
}


/*!
  Returns the orientation in which the axis is being used (Vertical or Horizontal)
*/
Qt::Orientation QAbstractAxis::orientation() const
{
    return d_ptr->orientation();
}

Qt::Alignment QAbstractAxis::alignment() const
{
    return d_ptr->alignment();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractAxisPrivate::QAbstractAxisPrivate(QAbstractAxis *q)
    : q_ptr(q),
      m_chart(0),
      m_alignment(0),
      m_orientation(Qt::Orientation(0)),
      m_visible(true),
      m_arrowVisible(true),
      m_axisPen(QChartPrivate::defaultPen()),
      m_axisBrush(QChartPrivate::defaultBrush()),
      m_gridLineVisible(true),
      m_gridLinePen(QChartPrivate::defaultPen()),
      m_labelsVisible(true),
      m_labelsBrush(QChartPrivate::defaultBrush()),
      m_labelsFont(QChartPrivate::defaultFont()),
      m_labelsAngle(0),
      m_titleVisible(true),
      m_titleBrush(QChartPrivate::defaultBrush()),
      m_titleFont(QChartPrivate::defaultFont()),
      m_shadesVisible(false),
      m_shadesPen(QChartPrivate::defaultPen()),
      m_shadesBrush(QChartPrivate::defaultBrush()),
      m_shadesOpacity(1.0),
      m_dirty(false)
{
}

QAbstractAxisPrivate::~QAbstractAxisPrivate()
{
}

void QAbstractAxisPrivate::setAlignment( Qt::Alignment alignment)
{
    switch(alignment) {
        case Qt::AlignTop:
        case Qt::AlignBottom:
        m_orientation = Qt::Horizontal;
        break;
        case Qt::AlignLeft:
        case Qt::AlignRight:
        m_orientation = Qt::Vertical;
        break;
        default:
        qWarning()<<"No alignment specified !";
        break;
    };
    m_alignment=alignment;
}

void QAbstractAxisPrivate::initializeTheme(ChartTheme* theme, bool forced)
{
    if (forced || QChartPrivate::defaultPen() == m_axisPen)
        q_ptr->setLinePen(theme->axisLinePen());

    if (forced || QChartPrivate::defaultPen() == m_gridLinePen)
        q_ptr->setGridLinePen(theme->girdLinePen());

    if (forced || QChartPrivate::defaultBrush() == m_labelsBrush)
        q_ptr->setLabelsBrush(theme->labelBrush());
    if (forced || QChartPrivate::defaultFont() == m_labelsFont)
        q_ptr->setLabelsFont(theme->labelFont());

    if (forced || QChartPrivate::defaultBrush() == m_titleBrush)
        q_ptr->setTitleBrush(theme->labelBrush());
    if (forced || QChartPrivate::defaultFont() == m_titleFont) {
        QFont font(m_labelsFont);
        font.setBold(true);
        q_ptr->setTitleFont(font);
    }

    if (forced || QChartPrivate::defaultBrush() == m_shadesBrush)
        q_ptr->setShadesBrush(theme->backgroundShadesBrush());
    if (forced || QChartPrivate::defaultPen() == m_shadesPen)
        q_ptr->setShadesPen(theme->backgroundShadesPen());

    bool axisX = m_orientation == Qt::Horizontal;
    if (forced && (theme->backgroundShades() == ChartTheme::BackgroundShadesBoth
            || (theme->backgroundShades() == ChartTheme::BackgroundShadesVertical && axisX)
            || (theme->backgroundShades() == ChartTheme::BackgroundShadesHorizontal && !axisX))) {
         q_ptr->setShadesVisible(true);
    } else if (forced) {
        q_ptr->setShadesVisible(false);
    }
}

void QAbstractAxisPrivate::handleRangeChanged(qreal min, qreal max)
{
    setRange(min,max);
}

void QAbstractAxisPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_UNUSED(parent);
}

void QAbstractAxisPrivate::initializeAnimations(QChart::AnimationOptions options)
{
    ChartAxisElement *axis = m_item.data();
    Q_ASSERT(axis);
    if (axis->animation())
        axis->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::GridAxisAnimations))
        axis->setAnimation(new AxisAnimation(axis));
    else
        axis->setAnimation(0);
}



#include "moc_qabstractaxis.cpp"
#include "moc_qabstractaxis_p.cpp"

QT_CHARTS_END_NAMESPACE
