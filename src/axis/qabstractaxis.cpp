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

#include "qabstractaxis.h"
#include "qabstractaxis_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAbstractAxis
    \brief The QAbstractAxis class is used for manipulating chart's axis.
    \mainclass

    There is only one x Axis visible at the time, however there can be multiple y axes.
    Each chart series can be bound to exactly one Y axis and the shared common X axis.
    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass AbstractAxis QAbstractAxis
    \brief The Axis element is used for manipulating chart's axes

    There is only one x Axis visible at the time, however there can be multiple y axes on a ChartView.
    Each chart series can be bound to exactly one Y axis and the shared common X axis.
    Axis can be setup to show axis line with tick marks, grid lines and shades.

    To access Axes you can use ChartView API. For example:
    \code
        ChartView {
            axisX.min: 0
            axisX.max: 3
            axisX.ticksCount: 4
            axisY.min: 0
            axisY.max: 4
            // Add a few series...
        }
    \endcode
*/

/*!
    \enum QAbstractAxis::AxisType

    The type of the series object.

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
  \property QAbstractAxis::labelsPen
  The pen of the labels.
*/

/*!
  \property QAbstractAxis::labelsBrush
  The brush of the labels.
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

  See the \l {Font} {QML Font Element} for detailed documentation.
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
  The title of the axis. Empty by default.
*/
/*!
  \qmlproperty String AbstractAxis::titleText
  The title of the axis. Empty by default.
*/

/*!
  \property QAbstractAxis::titlePen
  The pen of the title text.
*/

/*!
  \property QAbstractAxis::titleBrush
  The brush of the title text.
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
  The orientation of the axis. Fixed to either Qt.Horizontal or Qt.Vertical when the axis is set to a Chart/Series.
*/

/*!
  \property QAbstractAxis::alignment
  The alignment of the axis. Either Qt::AlignLeft or Qt::AlignBottom.
*/
/*!
  \qmlproperty alignment AbstractAxis::alignment
  The alignment of the axis. Either Qt.AlignLeft or Qt.AlignBottom.
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
  \fn void QAbstractAxis::labelsPenChanged(const QPen& pen)
  The pen of the axis labels has changed to \a pen.
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
  \fn void QAbstractAxis::titlePenChanged(const QPen& pen)
  The pen of the axis shades has changed to \a pen.
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
    return d_ptr->m_axisPen;
}

//TODO: remove me
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
    return d_ptr->m_axisPen.color();
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
  Sets \a pen used to draw labels.
*/
void QAbstractAxis::setLabelsPen(const QPen &pen)
{
    if (d_ptr->m_labelsPen != pen) {
        d_ptr->m_labelsPen = pen;
        emit labelsPenChanged(pen);
    }
}

/*!
  Returns the pen used to labels.
*/
QPen QAbstractAxis::labelsPen() const
{
    return d_ptr->m_labelsPen;
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
//TODO: remove me
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
    return d_ptr->m_labelsBrush.color();
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
  Sets \a pen used to draw title.
*/
void QAbstractAxis::setTitlePen(const QPen &pen)
{
    if (d_ptr->m_titlePen != pen) {
        d_ptr->m_titlePen = pen;
        emit titlePenChanged(pen);
    }
}

/*!
  Returns the pen used to title.
*/
QPen QAbstractAxis::titlePen() const
{
    return d_ptr->m_titlePen;
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
QBrush  QAbstractAxis::titleBrush() const
{
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
    return d_ptr->m_shadesBrush.color();
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
    return d_ptr->m_shadesPen.color();
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
// NOTE: should have const but it breaks BC:
// http://techbase.kde.org/Policies/Binary_Compatibility_Examples#Change_the_CV-qualifiers_of_a_member_function
Qt::Orientation QAbstractAxis::orientation()
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
      m_gridLineVisible(true),
      m_labelsVisible(true),
      m_labelsAngle(0),
      m_titleVisible(true),
      m_shadesVisible(false),
      m_shadesBrush(Qt::SolidPattern),
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
    QPen pen;
    QBrush brush;
    QFont font;

    bool axisX = m_orientation == Qt::Horizontal;

    if (m_arrowVisible) {

        if (forced || brush == m_labelsBrush){
            q_ptr->setLabelsBrush(theme->labelBrush());
        }
        //TODO: introduce axis brush
        if (forced || brush == m_titleBrush){
            q_ptr->setTitleBrush(theme->labelBrush());
        }
        if (forced || pen == m_labelsPen){
            q_ptr->setLabelsPen(Qt::NoPen);// NoPen for performance reasons
        }
        if (forced || pen == m_titlePen){
            q_ptr->setTitlePen(Qt::NoPen);// Noen for performance reasons
        }
        if (forced || m_shadesVisible) {

            if (forced || brush == m_shadesBrush){
                q_ptr->setShadesBrush(theme->backgroundShadesBrush());
            }
            if (forced || pen == m_shadesPen){
                q_ptr->setShadesPen(theme->backgroundShadesPen());
            }
            if (forced && (theme->backgroundShades() == ChartTheme::BackgroundShadesBoth
                    || (theme->backgroundShades() == ChartTheme::BackgroundShadesVertical && axisX)
                    || (theme->backgroundShades() == ChartTheme::BackgroundShadesHorizontal && !axisX))) {
            	 q_ptr->setShadesVisible(true);
            }
        }

		if (forced || pen == m_axisPen) {
			q_ptr->setLinePen(theme->axisLinePen());
		}

		if (forced || pen == m_gridLinePen) {
			q_ptr->setGridLinePen(theme->girdLinePen());
		}

        if (forced || font == m_labelsFont){
        	q_ptr->setLabelsFont(theme->labelFont());
        }
        //TODO: discuss with Tero
        if (forced || font == m_titleFont){
            QFont font(m_labelsFont);
            font.setBold(true);
            q_ptr->setTitleFont(font);
        }
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
    ChartAxis* axis = m_item.data();
    Q_ASSERT(axis);
    if(options.testFlag(QChart::GridAxisAnimations)) {
        axis->setAnimation(new AxisAnimation(axis));
    }else{
        axis->setAnimation(0);
    }
}



#include "moc_qabstractaxis.cpp"
#include "moc_qabstractaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
