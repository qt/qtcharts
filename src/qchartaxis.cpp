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
   \fn bool QChartAxis::isGridVisible() const
   \brief Returns if grid is visible
   \sa setGridVisible()
*/

/*!
   \fn QPen QChartAxis::gridPen() const
   \brief  Returns pen used to draw grid.
    \sa setGridPen()
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
    \fn void QChartAxis::update()
    \brief \internal
*/

/*!
    \fn void QChartAxis::handleAxisRangeChanged(qreal min, qreal max)
    \brief \internal \a min \a max
*/

/*!
    Constructs new axis object which is a child of \a parent. Ownership is taken by
    QChatView or QChart when axis added.
*/

QChartAxis::QChartAxis(QObject* parent):QObject(parent),
m_axisVisible(true),
m_gridVisible(true),
m_labelsVisible(true),
m_labelsAngle(0),
m_shadesVisible(true),
m_shadesOpacity(1.0),
m_min(0),
m_max(0),
m_ticksCount(5)
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
void QChartAxis::setAxisPen(const QPen& pen)
{
	if (pen != m_axisPen) {
    m_axisPen=pen;
    emit updated();
	}
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QChartAxis::setAxisVisible(bool visible)
{
	if (m_axisVisible!=visible) {
    m_axisVisible=visible;
    emit updated();
	}
}

/*!
  Sets if grid is \a visible.
 */
void QChartAxis::setGridVisible(bool visible)
{
	if (m_gridVisible!=visible) {
    m_gridVisible=visible;
    emit updated();
	}
}

/*!
  Sets \a pen used to draw grid.
 */
void QChartAxis::setGridPen(const QPen& pen)
{
	if (m_gridPen!=pen) {
    m_gridPen=pen;
    emit updated();
	}
}

/*!
  Sets if axis' labels are \a visible.
 */
void QChartAxis::setLabelsVisible(bool visible)
{
	if(m_labelsVisible!=visible) {
    m_labelsVisible=visible;
    emit updated();
	}
}

/*!
  Sets \a pen used to draw labels.
 */
void QChartAxis::setLabelsPen(const QPen& pen)
{
	if(m_labelsPen!=pen) {
    m_labelsPen=pen;
    emit updated();
	}
}

/*!
  Sets \a brush used to draw labels.
 */
void QChartAxis::setLabelsBrush(const QBrush& brush)
{
	if(m_labelsBrush!=brush) {
    m_labelsBrush=brush;
    emit updated();
	}
}

/*!
  Sets \a font used to draw labels.
 */
void QChartAxis::setLabelsFont(const QFont& font)
{
	if(m_labelsFont!=font) {
    m_labelsFont=font;
    emit updated();
	}
}

/*!
  Sets \a angle for all the labels on given axis.
 */
void QChartAxis::setLabelsAngle(int angle)
{
	if(m_labelsAngle!=angle) {
	m_labelsAngle=angle;
	emit updated();
	}
}

/*!
  Sets if shades are \a visible.
 */
void QChartAxis::setShadesVisible(bool visible)
{
	if(m_shadesVisible!=visible) {
    m_shadesVisible=visible;
    emit updated();
	}
}

/*!
  Sets \a pen used to draw shades.
 */
void QChartAxis::setShadesPen(const QPen& pen)
{
	if(m_shadesPen!=pen) {
	m_shadesPen=pen;
	emit updated();
	}
}

/*!
  Sets \a brush used to draw shades.
 */
void QChartAxis::setShadesBrush(const QBrush& brush)
{
	if(m_shadesBrush!=brush) {
    m_shadesBrush=brush;
    emit updated();
	}
}

/*!
  Sets \a opacity of the shades.
 */
void QChartAxis::setShadesOpacity(qreal opacity)
{
	if(m_shadesOpacity!=opacity) {
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
    if(m_min!=min) {
        m_min=min;
        emit minChanged(min);
    }

    if(m_max!=max) {
        m_max=max;
        emit maxChanged(max);
    }

    if(changed) emit rangeChanged(m_min,m_max);
}

void QChartAxis::handleAxisRangeChanged(qreal min, qreal max)
{
   setRange(min,max);
}

/*!
  Sets \a count for ticks on the axis.
 */
void QChartAxis::setTicksCount(int count)
{
	if(m_ticksCount!=count) {
	m_ticksCount=count;
	emit updated();
	}
}

/*!
  TODO: refactor me. Sets string \a label for \a value on the axis.
 */
void QChartAxis::addAxisTickLabel(qreal value,const QString& label)
{
	m_ticks.insert(value,label);
	emit updated();
}

/*!
  TODO: refactor me. Removes label for \a value on the axis.
 */
void QChartAxis::removeAxisTickLabel(qreal value)
{
	m_ticks.remove(value);
	emit updated();
}

/*!
  TODO: refactor me. Returns label for \a value on the axis.
 */
QString QChartAxis::axisTickLabel(qreal value) const
{
	return m_ticks.value(value);
}

/*!
  TODO: refactor me. Removes all the string labels for on the axis.
 */
void QChartAxis::clearAxisTickLabels()
{
	m_ticks.clear();
	emit updated();
}

#include "moc_qchartaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
