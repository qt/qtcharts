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

#include "qaxis.h"
#include "qaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAxis
    \brief The QAxis class is used for manipulating chart's axis
    and for adding optional axes to the chart.
    \mainclass

    There is only one x Axis, however there can be multiple y axes.
    Each chart series can be bound to exactly one Y axis and the shared common X axis.
    Axis can be setup to show axis line with tick marks, grid lines and shades.
*/

/*!
    \qmlclass Axis QAxis
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
  \property QAxis::labelsVisible
  Defines if axis labels are visible.
*/
/*!
  \qmlproperty bool Axis::labelsVisible
  Defines if axis labels are visible.
*/

/*!
  \property QAxis::min
  Defines the minimum value on the axis.
*/
/*!
  \qmlproperty real Axis::min
  Defines the minimum value on the axis.
*/

/*!
  \property QAxis::max
  Defines the maximum value on the axis.
*/
/*!
  \qmlproperty real Axis::max
  Defines the maximum value on the axis.
*/

/*!
  \property QAxis::visible
  The visibility of the axis.
*/
/*!
  \qmlproperty bool Axis::visible
  The visibility of the axis.
*/

/*!
  \property QAxis::gridVisible
  The visibility of the grid lines.
*/
/*!
  \qmlproperty bool Axis::gridVisible
  The visibility of the grid lines.
*/

/*!
  \property QAxis::color
  The color of the axis and ticks.
*/
/*!
  \qmlproperty color Axis::color
  The color of the axis and ticks.
*/

/*!
  \property QAxis::labelsColor
  The color of the axis labels.
*/
/*!
  \qmlproperty color Axis::labelsColor
  The color of the axis labels.
*/

/*!
  \property QAxis::labelsAngle
  The angle of the axis labels in degrees.
*/
/*!
  \qmlproperty int Axis::labelsAngle
  The angle of the axis labels in degrees.
*/

/*!
  \property QAxis::shadesVisible
  The visibility of the axis shades.
*/
/*!
  \qmlproperty bool Axis::shadesVisible
  The visibility of the axis shades.
*/

/*!
  \property QAxis::shadesColor
  The fill (brush) color of the axis shades.
*/
/*!
  \qmlproperty color Axis::shadesColor
  The fill (brush) color of the axis shades.
*/

/*!
  \property QAxis::shadesBorderColor
  The border (pen) color of the axis shades.
*/
/*!
  \qmlproperty color Axis::shadesBorderColor
  The border (pen) color of the axis shades.
*/

/*!
  \property QAxis::ticksCount
  The number of tick marks for the axis.
*/
/*!
  \qmlproperty int Axis::ticksCount
  The number of tick marks for the axis.
*/

/*!
  \property QAxis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/
/*!
  \qmlproperty bool Axis::niceNumbersEnabled
  Whether the nice numbers algorithm is enabled or not for the axis.
*/

/*!
  \fn void QAxis::visibleChanged(bool)
  Visiblity of the axis has changed to \a visible.
*/

/*!
  \fn void QAxis::labelsVisibleChanged(bool)
  Visiblity of the labels of the axis has changed to \a visible.
*/

/*!
  \fn void QAxis::gridVisibleChanged(bool)
  Visiblity of the grid lines of the axis has changed to \a visible.
*/

/*!
  \fn void QAxis::minChanged(qreal min)
  Axis emits signal when \a min of axis has changed.
*/

/*!
  \fn void QAxis::maxChanged(qreal max)
  Axis emits signal when \a max of axis has changed.
*/

/*!
  \fn void QAxis::rangeChanged(qreal min, qreal max)
  Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
  \fn QChartAxisCategories* QAxis::categories()
  Returns pointer to the list of categories which correspond to the values on the axis.
*/

/*!
  \fn void QAxis::colorChanged(QColor)
  Emitted if the \a color of the axis is changed.
*/

/*!
  \fn void QAxis::labelsColorChanged(QColor)
  Emitted if the \a color of the axis labels is changed.
*/

/*!
  \fn void QAxis::labelsAngleChanged(int)
  Emitted if the \a angle of the axis labels is changed.
*/

/*!
  \fn void QAxis::shadesVisibleChanged(bool)
  Emitted if the visibility of the axis shades is changed to \a visible.
*/

/*!
  \fn void QAxis::shadesColorChanged(QColor)
  Emitted if the \a color of the axis shades is changed.
*/

/*!
  \fn void QAxis::shadesBorderColorChanged(QColor)
  Emitted if the border \a color of the axis shades is changed.
*/

/*!
  \fn void QAxis::ticksCountChanged(int count)
  \brief Emits the new \a count of ticks on the axis
  Signal is emitted when the number of the ticks on the axis has been changed to a different value.
  Parementer count\a count is the new number of ticks on the axis.
*/

/*!
  \fn void QAxis::niceNumbersEnabledChanged(bool)
  Nice numbers algorithm was \a enabled or disabled.
*/

/*!
  Constructs new axis object which is a child of \a parent. Ownership is taken by
  QChart when axis added.
*/
QAxis::QAxis(QObject *parent) : QObject(parent),
d_ptr(new QAxisPrivate(this))
{

}

/*!
  Destructor of the axis object. When axis is added to chart, chart object takes ownership.
*/

QAxis::~QAxis()
{
}

/*!
  Sets \a pen used to draw axis line and ticks.
 */
void QAxis::setAxisPen(const QPen &pen)
{
	if (d_ptr->m_axisPen!=pen) {
	    d_ptr->m_axisPen = pen;
        emit d_ptr->updated();
	}
}

/*!
  Returns pen used to draw axis and ticks.
*/
QPen QAxis::axisPen() const
{
    return d_ptr->m_axisPen;
}

void QAxis::setAxisPenColor(QColor color)
{
    QPen p = d_ptr->m_axisPen;
    if (p.color() != color) {
        p.setColor(color);
        setAxisPen(p);
        emit colorChanged(color);
    }
}

QColor QAxis::axisPenColor() const
{
    return d_ptr->m_axisPen.color();
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QAxis::setAxisVisible(bool visible)
{
    if (d_ptr->m_axisVisible != visible) {
        d_ptr->m_axisVisible = visible;
        emit d_ptr->updated();
        emit visibleChanged(visible);
	}
}

bool QAxis::isAxisVisible() const
{
    return d_ptr->m_axisVisible;
}

void QAxis::setGridLineVisible(bool visible)
{
    if (d_ptr->m_gridLineVisible != visible) {
        d_ptr->m_gridLineVisible = visible;
        emit d_ptr->updated();
        emit gridVisibleChanged(visible);
	}
}

bool QAxis::isGridLineVisible() const
{
    return d_ptr->m_gridLineVisible;
}

/*!
  Sets \a pen used to draw grid line.
*/
void QAxis::setGridLinePen(const QPen &pen)
{
    if (d_ptr->m_gridLinePen != pen) {
        d_ptr->m_gridLinePen = pen;
        emit d_ptr->updated();
	}
}

/*!
  Returns pen used to draw grid.
*/
QPen QAxis::gridLinePen() const
{
    return d_ptr->m_gridLinePen;
}

void QAxis::setLabelsVisible(bool visible)
{
    if (d_ptr->m_labelsVisible != visible) {
        d_ptr->m_labelsVisible = visible;
        emit d_ptr->updated();
        emit labelsVisibleChanged(visible);
	}
}

bool QAxis::labelsVisible() const
{
    return d_ptr->m_labelsVisible;
}

/*!
  Sets \a pen used to draw labels.
*/
void QAxis::setLabelsPen(const QPen &pen)
{
    if (d_ptr->m_labelsPen != pen) {
        d_ptr->m_labelsPen = pen;
        emit d_ptr->updated();
	}
}

/*!
  Returns the pen used to labels.
*/
QPen QAxis::labelsPen() const
{
    return d_ptr->m_labelsPen;
}

/*!
  Sets \a brush used to draw labels.
 */
void QAxis::setLabelsBrush(const QBrush &brush)
{
    if (d_ptr->m_labelsBrush != brush) {
        d_ptr->m_labelsBrush = brush;
        emit d_ptr->updated();
	}
}

/*!
  Returns brush used to draw labels.
*/
QBrush  QAxis::labelsBrush() const
{
    return d_ptr->m_labelsBrush;
}

/*!
  Sets \a font used to draw labels.
*/
void QAxis::setLabelsFont(const QFont &font)
{
    if (d_ptr->m_labelsFont != font) {
        d_ptr->m_labelsFont = font;
        emit d_ptr->updated();
	}
}

/*!
  Returns font used to draw labels.
*/
QFont QAxis::labelsFont() const
{
    return d_ptr->m_labelsFont;
}

void QAxis::setLabelsAngle(int angle)
{
    if (d_ptr->m_labelsAngle != angle) {
        d_ptr->m_labelsAngle = angle;
        emit d_ptr->updated();
        emit labelsAngleChanged(angle);
	}
}

int QAxis::labelsAngle() const
{
    return d_ptr->m_labelsAngle;
}

void QAxis::setLabelsColor(QColor color)
{
    QBrush b = d_ptr->m_labelsBrush;
    if (b.color() != color) {
        b.setColor(color);
        setLabelsBrush(b);
        emit labelsColorChanged(color);
    }
}

QColor QAxis::labelsColor() const
{
    return d_ptr->m_labelsBrush.color();
}

void QAxis::setShadesVisible(bool visible)
{
    if (d_ptr->m_shadesVisible != visible) {
        d_ptr->m_shadesVisible = visible;
        emit d_ptr->updated();
        emit shadesVisibleChanged(visible);
	}
}

bool QAxis::shadesVisible() const
{
    return d_ptr->m_shadesVisible;
}

/*!
  Sets \a pen used to draw shades.
*/
void QAxis::setShadesPen(const QPen &pen)
{
    if (d_ptr->m_shadesPen != pen) {
        d_ptr->m_shadesPen = pen;
        emit d_ptr->updated();
	}
}

/*!
  Returns pen used to draw shades.
*/
QPen QAxis::shadesPen() const
{
    return d_ptr->m_shadesPen;
}

/*!
  Sets \a brush used to draw shades.
*/
void QAxis::setShadesBrush(const QBrush &brush)
{
    if (d_ptr->m_shadesBrush != brush) {
        d_ptr->m_shadesBrush = brush;
        emit d_ptr->updated();
        emit shadesColorChanged(brush.color());
    }
}

/*!
   \brief Returns brush used to draw shades.
*/
QBrush QAxis::shadesBrush() const
{
    return d_ptr->m_shadesBrush;
}

void QAxis::setShadesColor(QColor color)
{
    QBrush b = d_ptr->m_shadesBrush;
    b.setColor(color);
    setShadesBrush(b);
}

QColor QAxis::shadesColor() const
{
    return d_ptr->m_shadesBrush.color();
}

void QAxis::setShadesBorderColor(QColor color)
{
    QPen p = d_ptr->m_shadesPen;
    p.setColor(color);
    setShadesPen(p);
}

QColor QAxis::shadesBorderColor() const
{
    return d_ptr->m_shadesPen.color();
}

void QAxis::setMin(qreal min)
{
	setRange(min,d_ptr->m_max);
}

qreal QAxis::min() const
{
    return d_ptr->m_min;
}

void QAxis::setMax(qreal max)
{
    setRange(d_ptr->m_min,max);
}

qreal QAxis::max() const
{
    return d_ptr->m_max;
}

/*!
  Sets range from \a min to \a max on the axis.
*/
void QAxis::setRange(qreal min, qreal max)
{
	bool changed = false;
    if (!qFuzzyIsNull(d_ptr->m_min - min)) {
        d_ptr->m_min = min;
        changed = true;
        emit minChanged(min);
    }

    if (!qFuzzyIsNull(d_ptr->m_max - max)) {
        d_ptr->m_max = max;
        changed = true;
        emit maxChanged(max);
    }

    if (changed) {
        emit rangeChanged(d_ptr->m_min,d_ptr->m_max);
        emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
    }
}

/*!
  Sets \a count for ticks on the axis.
*/
void QAxis::setTicksCount(int count)
{
    if (d_ptr->m_ticksCount != count) {
        d_ptr->m_ticksCount = count;
		emit ticksCountChanged(count);
		emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
	}
}

/*!
  \fn int QAxis::ticksCount() const
  Return number of ticks on the axis
*/
int QAxis::ticksCount() const
{
    return d_ptr->m_ticksCount;
}

/*!
  Sets axis, shades, labels and grid lines to be visible.
*/
void QAxis::show()
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
void QAxis::hide()
{
    d_ptr->m_axisVisible = false;
    d_ptr->m_gridLineVisible = false;
    d_ptr->m_labelsVisible = false;
    d_ptr->m_shadesVisible = false;
    emit d_ptr->updated();
}

void QAxis::setNiceNumbersEnabled(bool enable)
{
    if (d_ptr->m_niceNumbers != enable){
        d_ptr->m_niceNumbers = enable;
        emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
        emit niceNumbersEnabledChanged(enable);
    }
}

bool  QAxis::niceNumbersEnabled() const
{
    return d_ptr->m_niceNumbers;
}

QAxisCategories* QAxis::categories()
{
    return &d_ptr->m_category;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAxisPrivate::QAxisPrivate(QAxis* q):
    q_ptr(q),
    m_axisVisible(true),
    m_gridLineVisible(true),
    m_labelsVisible(true),
    m_labelsAngle(0),
    m_shadesVisible(false),
    m_shadesBrush(Qt::SolidPattern),
    m_shadesOpacity(1.0),
    m_min(0),
    m_max(0),
    m_ticksCount(5),
    m_niceNumbers(false)
{

}

QAxisPrivate::~QAxisPrivate()
{

}

void QAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
   q_ptr->setRange(min,max);
   q_ptr->setTicksCount(count);
}

QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

#include "moc_qaxis.cpp"
#include "moc_qaxis_p.cpp"
