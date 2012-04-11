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

#include "qchartaxis.h"
#include "qchartaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QChartAxis
    \brief The QChartAxis class is used for manipulating chart's axis
    and for adding optional axes to the chart.
    \mainclass

    There is only one x Axis, however there can be multiple y axes.
    Each chart series can be bound to exactly one Y axis and the share common X axis.
    Axis can be setup to show axis line with ticks, gird lines and shades.

*/

/*!
   \fn bool QChartAxis::isAxisVisible() const
   \brief Returns if axis is visible
   \sa setAxisVisible()
*/

/*!
   \fn QPen QChartAxis::axisPen() const
   \brief  Returns pen used to draw axis and ticks.
    \sa setAxisPen()
*/


/*!
   \fn bool QChartAxis::isGridLineVisible() const
   \brief Returns if grid is visible
   \sa setGridLineVisible()
*/

/*!
   \fn QPen QChartAxis::gridLinePen() const
   \brief  Returns pen used to draw grid.
    \sa setGridLinePen()
*/

/*!
   \fn  bool QChartAxis::labelsVisible() const
   \brief Returns if grid is visible
   \sa setLabelsVisible()
*/

/*!
   \fn QPen QChartAxis::labelsPen() const
   \brief Returns the pen used to labels.
    \sa setLabelsPen()
*/

/*!
   \fn QBrush QChartAxis::labelsBrush() const
   \brief Returns brush used to draw labels.
    \sa setLabelsBrush()
*/

/*!
   \fn QFont QChartAxis::labelsFont() const
   \brief Returns font used to draw labels.
    \sa setLabelsFont()
*/

/*!
   \fn QFont QChartAxis::labelsAngle() const
   \brief Returns angle used to draw labels.
    \sa setLabelsAngle()
*/

/*!
   \fn bool QChartAxis::shadesVisible() const
   \brief Returns if shades are visible.
   \sa setShadesVisible()
*/

/*!
  \fn  qreal QChartAxis::shadesOpacity() const
  \brief Returns opacity of shades.
 */

/*!
   \fn QPen QChartAxis::shadesPen() const
   \brief Returns pen used to draw shades.
    \sa setShadesPen()
*/

/*!
   \fn QBrush QChartAxis::shadesBrush() const
   \brief Returns brush used to draw shades.
    \sa setShadesBrush()
*/

/*!
   \fn qreal QChartAxis::min() const
   \brief Returns minimum value on the axis.
   \sa setMin()
*/

/*!
   \fn qreal QChartAxis::max() const
   \brief Returns maximim value on the axis.
   \sa setMax()
*/

/*!
   \fn void QChartAxis::minChanged(qreal min)
   \brief Axis emits signal when \a min of axis has changed.
*/

/*!
   \fn void QChartAxis::maxChanged(qreal max)
   \brief Axis emits signal when \a max of axis has changed.
*/

/*!
   \fn void QChartAxis::rangeChanged(qreal min, qreal max)
   \brief Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
   \fn int QChartAxis::ticksCount() const
   \brief Return number of ticks on the axis
   \sa setTicksCount()
*/

/*!
    \fn bool QChartAxis::niceNumbers() const
    \brief Returns whether nice numbers are enabled or not.
*/

/*!
    \fn QChartAxisCategories* QChartAxis::categories()
    \brief Returns pointer to the list of categories which correspond to the values on the axis.
*/

/*!
    \fn void QChartAxis::ticksCountChanged(int count)
    \brief Emits the new \a count of ticks on the axis
    Signal is emitted when the number of the ticks on the axis has been changed to a different value.
    Parementer count\a count is the new number of ticks on the axis.
*/

/*!
    Constructs new axis object which is a child of \a parent. Ownership is taken by
    QChatView or QChart when axis added.
*/

QChartAxis::QChartAxis(QObject *parent) : QObject(parent),
d_ptr(new QChartAxisPrivate(this))
{

}

/*!
    Destructor of the axis object. When axis is added to chart, chart object takes ownership.
*/

QChartAxis::~QChartAxis()
{
}

/*!
  Sets \a pen used to draw axis line and ticks.
 */
void QChartAxis::setAxisPen(const QPen &pen)
{
	if (d_ptr->m_axisPen!=pen) {
	    d_ptr->m_axisPen = pen;
        emit d_ptr->updated();
	}
}

QPen QChartAxis::axisPen() const
{
    return d_ptr->m_axisPen;
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QChartAxis::setAxisVisible(bool visible)
{
    if (d_ptr->m_axisVisible != visible) {
        d_ptr->m_axisVisible = visible;
        emit d_ptr->updated();
	}
}

bool QChartAxis::isAxisVisible() const
{
    return d_ptr->m_axisVisible;
}

/*!
  Sets if grid line is \a visible.
 */
void QChartAxis::setGridLineVisible(bool visible)
{
    if (d_ptr->m_gridLineVisible != visible) {
        d_ptr->m_gridLineVisible = visible;
        emit d_ptr->updated();
	}
}

bool QChartAxis::isGridLineVisible() const
{
    return d_ptr->m_gridLineVisible;
}
/*!
  Sets \a pen used to draw grid line.
 */
void QChartAxis::setGridLinePen(const QPen &pen)
{
    if (d_ptr->m_gridLinePen != pen) {
        d_ptr->m_gridLinePen = pen;
        emit d_ptr->updated();
	}
}

QPen QChartAxis::gridLinePen() const
{
    return d_ptr->m_gridLinePen;
}

/*!
  Sets if axis' labels are \a visible.
 */
void QChartAxis::setLabelsVisible(bool visible)
{
    if (d_ptr->m_labelsVisible != visible) {
        d_ptr->m_labelsVisible = visible;
        emit d_ptr->updated();
	}
}

bool QChartAxis::labelsVisible() const
{
    return d_ptr->m_labelsVisible;
}
/*!
  Sets \a pen used to draw labels.
 */
void QChartAxis::setLabelsPen(const QPen &pen)
{
    if (d_ptr->m_labelsPen != pen) {
        d_ptr->m_labelsPen = pen;
        emit d_ptr->updated();
	}
}

QPen QChartAxis::labelsPen() const
{
    return d_ptr->m_labelsPen;
}

/*!
  Sets \a brush used to draw labels.
 */
void QChartAxis::setLabelsBrush(const QBrush &brush)
{
    if (d_ptr->m_labelsBrush != brush) {
        d_ptr->m_labelsBrush = brush;
        emit d_ptr->updated();
	}
}

QBrush  QChartAxis::labelsBrush() const
{
    return d_ptr->m_labelsBrush;
}

/*!
  Sets \a font used to draw labels.
 */
void QChartAxis::setLabelsFont(const QFont &font)
{
    if (d_ptr->m_labelsFont != font) {
        d_ptr->m_labelsFont = font;
        emit d_ptr->updated();
	}
}

QFont QChartAxis::labelsFont() const
{
    return d_ptr->m_labelsFont;
}

/*!
  Sets \a angle for all the labels on given axis.
 */
void QChartAxis::setLabelsAngle(int angle)
{
    if (d_ptr->m_labelsAngle != angle) {
        d_ptr->m_labelsAngle = angle;
        emit d_ptr->updated();
	}
}

int QChartAxis::labelsAngle() const
{
    return d_ptr->m_labelsAngle;
}

/*!
  Sets if shades are \a visible.
 */
void QChartAxis::setShadesVisible(bool visible)
{
    if (d_ptr->m_shadesVisible != visible) {
        d_ptr->m_shadesVisible = visible;
        emit d_ptr->updated();
	}
}

bool QChartAxis::shadesVisible() const
{
    return d_ptr->m_shadesVisible;
}

/*!
  Sets \a pen used to draw shades.
 */
void QChartAxis::setShadesPen(const QPen &pen)
{
    if (d_ptr->m_shadesPen != pen) {
        d_ptr->m_shadesPen = pen;
        emit d_ptr->updated();
	}
}

QPen QChartAxis::shadesPen() const
{
    return d_ptr->m_shadesPen;
}

/*!
  Sets \a brush used to draw shades.
 */
void QChartAxis::setShadesBrush(const QBrush &brush)
{
    if (d_ptr->m_shadesBrush != brush) {
        d_ptr->m_shadesBrush = brush;
        emit d_ptr->updated();
	}
}

QBrush QChartAxis::shadesBrush() const
{
    return d_ptr->m_shadesBrush;
}

/*!
  Sets \a opacity of the shades.
 */
void QChartAxis::setShadesOpacity(qreal opacity)
{
    if (d_ptr->m_shadesOpacity != opacity) {
        d_ptr->m_shadesOpacity=opacity;
        emit d_ptr->updated();
	}
}

qreal QChartAxis::shadesOpacity() const
{
    return d_ptr->m_shadesOpacity;
}

/*!
 Sets \a min value on the axis.
 */
void QChartAxis::setMin(qreal min)
{
	setRange(min,d_ptr->m_max);
}

qreal QChartAxis::min() const
{
    return d_ptr->m_min;
}

/*!
 Sets \a max value on the axis.
 */
void QChartAxis::setMax(qreal max)
{
    setRange(d_ptr->m_min,max);
}

qreal QChartAxis::max() const
{
    return d_ptr->m_max;
}

/*!
  Sets range from \a min to \a max on the axis.
 */
void QChartAxis::setRange(qreal min, qreal max)
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
void QChartAxis::setTicksCount(int count)
{
    if (d_ptr->m_ticksCount != count) {
        d_ptr->m_ticksCount = count;
		emit ticksCountChanged(count);
		emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
	}
}

int QChartAxis::ticksCount() const
{
    return d_ptr->m_ticksCount;
}

/*!
  Sets axis, shades, labels and grid lines to be visible.
 */
void QChartAxis::show()
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
void QChartAxis::hide()
{
    d_ptr->m_axisVisible = false;
    d_ptr->m_gridLineVisible = false;
    d_ptr->m_labelsVisible = false;
    d_ptr->m_shadesVisible = false;
    emit d_ptr->updated();
}

/*!
    Sets the nice numbers state to \a enable
*/
void QChartAxis::setNiceNumbers(bool enable)
{
    if (d_ptr->m_niceNumbers != enable){
        d_ptr->m_niceNumbers = enable;
        emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
    }
}

bool  QChartAxis::niceNumbers() const
{
    return d_ptr->m_niceNumbers;
}

QChartAxisCategories* QChartAxis::categories()
{
    return &d_ptr->m_category;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QChartAxisPrivate::QChartAxisPrivate(QChartAxis* q):
q_ptr(q),
m_axisVisible(true),
m_gridLineVisible(true),
m_labelsVisible(true),
m_labelsAngle(0),
m_shadesVisible(false),
m_shadesOpacity(1.0),
m_min(0),
m_max(0),
m_ticksCount(5),
m_niceNumbers(false)
{

}

QChartAxisPrivate::~QChartAxisPrivate()
{

}

void QChartAxisPrivate::handleAxisRangeChanged(qreal min, qreal max,int count)
{
   q_ptr->setRange(min,max);
   q_ptr->setTicksCount(count);
}

#include "moc_qchartaxis.cpp"
#include "moc_qchartaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
