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

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAbstractAxis
    \brief The QAbstractAxis class is used for manipulating chart's axis.
    \mainclass

    There is only one x Axis, however there can be multiple y axes.
    Each chart series can be bound to exactly one Y axis and the shared common X axis.
    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QAbstractAxis
    \brief The Axis element is used for manipulating chart's axes

    There is only one x Axis, however there can be multiple y axes on a ChartView.
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
  \property QAbstractAxis::labelsVisible
  Defines if axis labels are visible.
*/
/*!
  \qmlproperty bool Axis::labelsVisible
  Defines if axis labels are visible.
*/

/*!
  \property QAbstractAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty real Axis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QAbstractAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty real Axis::max
  Defines the maximum value on the axis.
*/

/*!
  \property QAbstractAxis::visible
  The visibility of the axis.
*/
/*!
  \qmlproperty bool Axis::visible
  The visibility of the axis.
*/

/*!
  \property QAbstractAxis::gridVisible
  The visibility of the grid lines.
*/
/*!
  \qmlproperty bool Axis::gridVisible
  The visibility of the grid lines.
*/

/*!
  \property QAbstractAxis::color
  The color of the axis and ticks.
*/
/*!
  \qmlproperty color Axis::color
  The color of the axis and ticks.
*/

/*!
  \property QAxis::labelsFont
  The font of the axis labels.
*/
/*!
  \qmlproperty Font Axis::labelsFont
  The font of the axis labels.

  See the \l {Font} {QML Font Element} for detailed documentation.
*/

/*!
  \property QAbstractAxis::labelsColor
  The color of the axis labels.
*/
/*!
  \qmlproperty color Axis::labelsColor
  The color of the axis labels.
*/

/*!
  \property QAbstractAxis::labelsAngle
  The angle of the axis labels in degrees.
*/
/*!
  \qmlproperty int Axis::labelsAngle
  The angle of the axis labels in degrees.
*/

/*!
  \property QAbstractAxis::shadesVisible
  The visibility of the axis shades.
*/
/*!
  \qmlproperty bool Axis::shadesVisible
  The visibility of the axis shades.
*/

/*!
  \property QAbstractAxis::shadesColor
  The fill (brush) color of the axis shades.
*/
/*!
  \qmlproperty color Axis::shadesColor
  The fill (brush) color of the axis shades.
*/

/*!
  \property QAbstractAxis::shadesBorderColor
  The border (pen) color of the axis shades.
*/
/*!
  \qmlproperty color Axis::shadesBorderColor
  The border (pen) color of the axis shades.
*/

/*!
  \property QAbstractAxis::ticksCount
  The number of tick marks for the axis.
*/
/*!
  \qmlproperty int Axis::ticksCount
  The number of tick marks for the axis.
*/

/*!
  \property QAbstractAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/
/*!
  \qmlproperty bool Axis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
  \fn void QAbstractAxis::visibleChanged(bool)
  Visiblity of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::labelsVisibleChanged(bool)
  Visiblity of the labels of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::gridVisibleChanged(bool)
  Visiblity of the grid lines of the axis has changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QAbstractAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QAbstractAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \fn QChartAxisCategories* QAbstractAxis::categories()
  Returns pointer to the list of categories which correspond to the values on the axis.
*/

/*!
  \fn void QAbstractAxis::colorChanged(QColor)
  Emitted if the \a color of the axis is changed.
*/

/*!
  \fn void QAbstractAxis::labelsColorChanged(QColor)
  Emitted if the \a color of the axis labels is changed.
*/

/*!
  \fn void QAbstractAxis::shadesVisibleChanged(bool)
  Emitted if the visibility of the axis shades is changed to \a visible.
*/

/*!
  \fn void QAbstractAxis::shadesColorChanged(QColor)
  Emitted if the \a color of the axis shades is changed.
*/

/*!
  \fn void QAbstractAxis::shadesBorderColorChanged(QColor)
  Emitted if the border \a color of the axis shades is changed.
*/

/*!
  Constructs new axis object which is a child of \a parent. Ownership is taken by
  QChart when axis added.
*/

QAbstractAxis::QAbstractAxis(QAbstractAxisPrivate &d, QObject *parent) :
QObject(parent),
d_ptr(&d)
{
}

/*!
  Destructor of the axis object. When axis is added to chart, chart object takes ownership.
*/

QAbstractAxis::~QAbstractAxis()
{
}

/*!
  Sets \a pen used to draw axis line and ticks.
 */
void QAbstractAxis::setAxisPen(const QPen &pen)
{
	if (d_ptr->m_axisPen!=pen) {
	    d_ptr->m_axisPen = pen;
        emit d_ptr->updated();
	}
}

/*!
  Returns pen used to draw axis and ticks.
*/
QPen QAbstractAxis::axisPen() const
{
    return d_ptr->m_axisPen;
}

void QAbstractAxis::setAxisPenColor(QColor color)
{
    QPen p = d_ptr->m_axisPen;
    if (p.color() != color) {
        p.setColor(color);
        setAxisPen(p);
        emit colorChanged(color);
    }
}

QColor QAbstractAxis::axisPenColor() const
{
    return d_ptr->m_axisPen.color();
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QAbstractAxis::setAxisVisible(bool visible)
{
    if (d_ptr->m_axisVisible != visible) {
        d_ptr->m_axisVisible = visible;
        emit d_ptr->updated();
        emit visibleChanged(visible);
	}
}

bool QAbstractAxis::isAxisVisible() const
{
    return d_ptr->m_axisVisible;
}

void QAbstractAxis::setGridLineVisible(bool visible)
{
    if (d_ptr->m_gridLineVisible != visible) {
        d_ptr->m_gridLineVisible = visible;
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
    return d_ptr->m_labelsBrush.color();
}

void QAbstractAxis::setShadesVisible(bool visible)
{
    if (d_ptr->m_shadesVisible != visible) {
        d_ptr->m_shadesVisible = visible;
        emit d_ptr->updated();
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
        emit d_ptr->updated();
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
        emit d_ptr->updated();
        emit shadesColorChanged(brush.color());
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
    b.setColor(color);
    setShadesBrush(b);
}

QColor QAbstractAxis::shadesColor() const
{
    return d_ptr->m_shadesBrush.color();
}

void QAbstractAxis::setShadesBorderColor(QColor color)
{
    QPen p = d_ptr->m_shadesPen;
    p.setColor(color);
    setShadesPen(p);
}

QColor QAbstractAxis::shadesBorderColor() const
{
    return d_ptr->m_shadesPen.color();
}


/*!
  Sets axis, shades, labels and grid lines to be visible.
*/
void QAbstractAxis::show()
{
    d_ptr->m_axisVisible=true;
    d_ptr->m_gridLineVisible=true;
    d_ptr->m_labelsVisible=true;
    d_ptr->m_shadesVisible=true;
    emit d_ptr->updated();
}

/*!
  Sets axis, shades, labels and grid lines to not be visible.
*/
void QAbstractAxis::hide()
{
    d_ptr->m_axisVisible = false;
    d_ptr->m_gridLineVisible = false;
    d_ptr->m_labelsVisible = false;
    d_ptr->m_shadesVisible = false;
    emit d_ptr->updated();
}


void QAbstractAxis::setMin(const QVariant& min)
{
    d_ptr->setMin(min);
}
void QAbstractAxis::setMax(const QVariant& max)
{
    d_ptr->setMax(max);
}
void QAbstractAxis::setRange(const QVariant& min, const QVariant& max)
{
    d_ptr->setRange(min,max);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAbstractAxisPrivate::QAbstractAxisPrivate(QAbstractAxis* q):
    q_ptr(q),
    m_axisVisible(true),
    m_gridLineVisible(true),
    m_labelsVisible(true),
    m_labelsAngle(0),
    m_shadesVisible(false),
    m_shadesBrush(Qt::SolidPattern),
    m_shadesOpacity(1.0),
    m_orientation(Qt::Orientation(0))
{

}

QAbstractAxisPrivate::~QAbstractAxisPrivate()
{

}

#include "moc_qabstractaxis.cpp"
#include "moc_qabstractaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
