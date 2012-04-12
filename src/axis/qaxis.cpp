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
    \brief The QChartAxis class is used for manipulating chart's axis
    and for adding optional axes to the chart.
    \mainclass

    There is only one x Axis, however there can be multiple y axes.
    Each chart series can be bound to exactly one Y axis and the share common X axis.
    Axis can be setup to show axis line with ticks, gird lines and shades.

*/

/*!
   \fn bool QAxis::isAxisVisible() const
   \brief Returns if axis is visible
   \sa setAxisVisible()
*/

/*!
   \fn QPen QAxis::axisPen() const
   \brief  Returns pen used to draw axis and ticks.
    \sa setAxisPen()
*/


/*!
   \fn bool QAxis::isGridLineVisible() const
   \brief Returns if grid is visible
   \sa setGridLineVisible()
*/

/*!
   \fn QPen QAxis::gridLinePen() const
   \brief  Returns pen used to draw grid.
    \sa setGridLinePen()
*/

/*!
   \fn  bool QAxis::labelsVisible() const
   \brief Returns if grid is visible
   \sa setLabelsVisible()
*/

/*!
   \fn QPen QAxis::labelsPen() const
   \brief Returns the pen used to labels.
    \sa setLabelsPen()
*/

/*!
   \fn QBrush QAxis::labelsBrush() const
   \brief Returns brush used to draw labels.
    \sa setLabelsBrush()
*/

/*!
   \fn QFont QAxis::labelsFont() const
   \brief Returns font used to draw labels.
    \sa setLabelsFont()
*/

/*!
   \fn QFont QAxis::labelsAngle() const
   \brief Returns angle used to draw labels.
    \sa setLabelsAngle()
*/

/*!
   \fn bool QAxis::shadesVisible() const
   \brief Returns if shades are visible.
   \sa setShadesVisible()
*/

/*!
  \fn  qreal QAxis::shadesOpacity() const
  \brief Returns opacity of shades.
 */

/*!
   \fn QPen QAxis::shadesPen() const
   \brief Returns pen used to draw shades.
    \sa setShadesPen()
*/

/*!
   \fn QBrush QAxis::shadesBrush() const
   \brief Returns brush used to draw shades.
    \sa setShadesBrush()
*/

/*!
   \fn qreal QAxis::min() const
   \brief Returns minimum value on the axis.
   \sa setMin()
*/

/*!
   \fn qreal QAxis::max() const
   \brief Returns maximim value on the axis.
   \sa setMax()
*/

/*!
   \fn void QAxis::minChanged(qreal min)
   \brief Axis emits signal when \a min of axis has changed.
*/

/*!
   \fn void QAxis::maxChanged(qreal max)
   \brief Axis emits signal when \a max of axis has changed.
*/

/*!
   \fn void QAxis::rangeChanged(qreal min, qreal max)
   \brief Axis emits signal when \a min or \a max of axis has changed.
*/

/*!
   \fn int QAxis::ticksCount() const
   \brief Return number of ticks on the axis
   \sa setTicksCount()
*/

/*!
    \fn QChartAxisCategories* QAxis::categories()
    \brief Returns pointer to the list of categories which correspond to the values on the axis.
*/

/*!
    \fn void QAxis::ticksCountChanged(int count)
    \brief Emits the new \a count of ticks on the axis
    Signal is emitted when the number of the ticks on the axis has been changed to a different value.
    Parementer count\a count is the new number of ticks on the axis.
*/

/*!
    Constructs new axis object which is a child of \a parent. Ownership is taken by
    QChatView or QChart when axis added.
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

QPen QAxis::axisPen() const
{
    return d_ptr->m_axisPen;
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QAxis::setAxisVisible(bool visible)
{
    if (d_ptr->m_axisVisible != visible) {
        d_ptr->m_axisVisible = visible;
        emit d_ptr->updated();
	}
}

bool QAxis::isAxisVisible() const
{
    return d_ptr->m_axisVisible;
}

/*!
  Sets if grid line is \a visible.
 */
void QAxis::setGridLineVisible(bool visible)
{
    if (d_ptr->m_gridLineVisible != visible) {
        d_ptr->m_gridLineVisible = visible;
        emit d_ptr->updated();
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

QPen QAxis::gridLinePen() const
{
    return d_ptr->m_gridLinePen;
}

/*!
  Sets if axis' labels are \a visible.
 */
void QAxis::setLabelsVisible(bool visible)
{
    if (d_ptr->m_labelsVisible != visible) {
        d_ptr->m_labelsVisible = visible;
        emit d_ptr->updated();
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

QFont QAxis::labelsFont() const
{
    return d_ptr->m_labelsFont;
}

/*!
  Sets \a angle for all the labels on given axis.
 */
void QAxis::setLabelsAngle(int angle)
{
    if (d_ptr->m_labelsAngle != angle) {
        d_ptr->m_labelsAngle = angle;
        emit d_ptr->updated();
	}
}

int QAxis::labelsAngle() const
{
    return d_ptr->m_labelsAngle;
}

/*!
  Sets if shades are \a visible.
 */
void QAxis::setShadesVisible(bool visible)
{
    if (d_ptr->m_shadesVisible != visible) {
        d_ptr->m_shadesVisible = visible;
        emit d_ptr->updated();
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
	}
}

QBrush QAxis::shadesBrush() const
{
    return d_ptr->m_shadesBrush;
}

/*!
  Sets \a opacity of the shades.
 */
void QAxis::setShadesOpacity(qreal opacity)
{
    if (d_ptr->m_shadesOpacity != opacity) {
        d_ptr->m_shadesOpacity=opacity;
        emit d_ptr->updated();
	}
}

qreal QAxis::shadesOpacity() const
{
    return d_ptr->m_shadesOpacity;
}

/*!
 Sets \a min value on the axis.
 */
void QAxis::setMin(qreal min)
{
	setRange(min,d_ptr->m_max);
}

qreal QAxis::min() const
{
    return d_ptr->m_min;
}

/*!
 Sets \a max value on the axis.
 */
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

/*!
    Sets the nice numbers state to \a enable
*/
void QAxis::setNiceNumbersEnabled(bool enable)
{
    if (d_ptr->m_niceNumbers != enable){
        d_ptr->m_niceNumbers = enable;
        emit d_ptr->changed(d_ptr->m_min, d_ptr->m_max, d_ptr->m_ticksCount, d_ptr->m_niceNumbers);
    }
}

/*!
    Returns whether nice numbers are enabled or not.
*/
bool  QAxis::niceNumbersEnabled() const
{
    return d_ptr->m_niceNumbers;
}

QChartAxisCategories* QAxis::categories()
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

#include "moc_qaxis.cpp"
#include "moc_qaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
