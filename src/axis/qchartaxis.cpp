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
    \fn void QChartAxis::updated()
    \brief \internal
*/

/*!
    \fn void changed(qreal min, qreal max, int tickCount,bool niceNumbers)
    \brief \internal
*/

/*!
    \fn bool QChartAxis::niceNumbers() const
    \brief Returns whether nice numbers are enabled or not.
*/

/*!
    \fn QChartAxisCategories* categories()
    \brief Returns pointer to the list of categories which correspond to the values on the axis.
*/

/*!
    \fn void ticksCountChanged(int count)
    \brief Emits the new \a count of ticks on the axis
    Signal is emitted when the number of the ticks on the axis has been changed to a different value.
    Parementer count\a count is the new number of ticks on the axis.
*/

/*!
    Constructs new axis object which is a child of \a parent. Ownership is taken by
    QChatView or QChart when axis added.
*/

QChartAxis::QChartAxis(QObject *parent) : QObject(parent),
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
	if (pen != m_axisPen) {
        m_axisPen = pen;
        emit updated();
	}
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QChartAxis::setAxisVisible(bool visible)
{
    if (m_axisVisible != visible) {
        m_axisVisible = visible;
        emit updated();
	}
}

/*!
  Sets if grid line is \a visible.
 */
void QChartAxis::setGridLineVisible(bool visible)
{
    if (m_gridLineVisible != visible) {
        m_gridLineVisible = visible;
        emit updated();
	}
}

/*!
  Sets \a pen used to draw grid line.
 */
void QChartAxis::setGridLinePen(const QPen &pen)
{
    if (m_gridLinePen != pen) {
        m_gridLinePen = pen;
        emit updated();
	}
}

/*!
  Sets if axis' labels are \a visible.
 */
void QChartAxis::setLabelsVisible(bool visible)
{
    if (m_labelsVisible != visible) {
        m_labelsVisible = visible;
        emit updated();
	}
}

/*!
  Sets \a pen used to draw labels.
 */
void QChartAxis::setLabelsPen(const QPen &pen)
{
    if (m_labelsPen != pen) {
        m_labelsPen = pen;
        emit updated();
	}
}

/*!
  Sets \a brush used to draw labels.
 */
void QChartAxis::setLabelsBrush(const QBrush &brush)
{
    if (m_labelsBrush != brush) {
        m_labelsBrush = brush;
        emit updated();
	}
}

/*!
  Sets \a font used to draw labels.
 */
void QChartAxis::setLabelsFont(const QFont &font)
{
    if (m_labelsFont != font) {
        m_labelsFont = font;
        emit updated();
	}
}

/*!
  Sets \a angle for all the labels on given axis.
 */
void QChartAxis::setLabelsAngle(int angle)
{
    if (m_labelsAngle != angle) {
        m_labelsAngle = angle;
        emit updated();
	}
}

/*!
  Sets if shades are \a visible.
 */
void QChartAxis::setShadesVisible(bool visible)
{
    if (m_shadesVisible != visible) {
        m_shadesVisible = visible;
        emit updated();
	}
}

/*!
  Sets \a pen used to draw shades.
 */
void QChartAxis::setShadesPen(const QPen &pen)
{
    if (m_shadesPen != pen) {
        m_shadesPen = pen;
        emit updated();
	}
}

/*!
  Sets \a brush used to draw shades.
 */
void QChartAxis::setShadesBrush(const QBrush &brush)
{
    if (m_shadesBrush != brush) {
        m_shadesBrush = brush;
        emit updated();
	}
}

/*!
  Sets \a opacity of the shades.
 */
void QChartAxis::setShadesOpacity(qreal opacity)
{
    if (m_shadesOpacity != opacity) {
    m_shadesOpacity=opacity;
    emit updated();
	}
}

/*!
 Sets \a min value on the axis.
 */
void QChartAxis::setMin(qreal min)
{
	setRange(min,m_max);
}

/*!
 Sets \a max value on the axis.
 */
void QChartAxis::setMax(qreal max)
{
    setRange(m_min,max);
}

/*!
  Sets range from \a min to \a max on the axis.
 */
void QChartAxis::setRange(qreal min, qreal max)
{
	bool changed = false;
    if (!qFuzzyIsNull(m_min - min)) {
        m_min = min;
        changed = true;
        emit minChanged(min);
    }

    if (!qFuzzyIsNull(m_max - max)) {
        m_max = max;
        changed = true;
        emit maxChanged(max);
    }

    if (changed) {
        emit rangeChanged(m_min,m_max);
        emit this->changed(m_min, m_max, m_ticksCount, m_niceNumbers);
    }
}

/*!
  Sets \a count for ticks on the axis.
 */
void QChartAxis::setTicksCount(int count)
{
    if (m_ticksCount != count) {
        m_ticksCount = count;
		emit ticksCountChanged(count);
		emit changed(m_min, m_max, m_ticksCount, m_niceNumbers);
	}
}

/*!
  Sets axis, shades, labels and grid lines to be visible.
 */
void QChartAxis::show()
{
   m_axisVisible=true;
   m_gridLineVisible=true;
   m_labelsVisible=true;
   m_shadesVisible=true;
   emit updated();
}

/*!
  Sets axis, shades, labels and grid lines to not be visible.
 */
void QChartAxis::hide()
{
    m_axisVisible = false;
    m_gridLineVisible = false;
    m_labelsVisible = false;
    m_shadesVisible = false;
    emit updated();
}

/*!
    \internal
 */
void QChartAxis::handleAxisRangeChanged(qreal min, qreal max,int count)
{
   setRange(min,max);
   setTicksCount(count);
}

/*!
    Sets the nice numbers state to \a enable
*/
void QChartAxis::setNiceNumbers(bool enable)
{
    if (m_niceNumbers != enable){
        m_niceNumbers = enable;
        emit changed(m_min, m_max, m_ticksCount, m_niceNumbers);
    }
}

#include "moc_qchartaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
