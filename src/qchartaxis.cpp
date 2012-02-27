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
   \fn QPen QChartAxis::axisPen() const
   \brief  Returns pen used to draw axis and ticks.
    \sa setAxisPen()
*/

/*!
   \fn QPen QChartAxis::gridPen() const
   \brief  Returns pen used to draw grid.
    \sa setGridPen()
*/

/*!
   \fn QPen QChartAxis::labelsPen() const
   \brief  Returns the pen used to labels.
    \sa setLabelsPen()
*/

/*!
   \fn QBrush QChartAxis::labelsBrush() const
   \brief  Returns brush used to draw labels.
    \sa setLabelsBrush()
*/

/*!
   \fn QFont QChartAxis::labelsFont() const
   \brief  Returns font used to draw labels.
    \sa setLabelsFont()
*/

/*!
   \fn QFont QChartAxis::labelsAngle() const
   \brief  Returns angle used to draw labels.
    \sa setLabelsAngle()
*/

/*!
   \fn QPen QChartAxis::shadesPen() const
   \brief  Returns pen used to draw shades.
    \sa setShadesPen()
*/

/*!
   \fn QBrush QChartAxis::shadesBrush() const
   \brief  Returns brush used to draw shades.
    \sa setShadesBrush()
*/

/*!
    \fn void QChartAxis::update(QChartAxis*)
    \brief \internal
*/

/*!
    \fn void QChartAxis::ticksChanged(QChartAxis*)
    \brief \internal
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
    m_axisPen=pen;
    emit update(this);
}

/*!
  Sets if axis and ticks are \a visible.
 */
void QChartAxis::setAxisVisible(bool visible)
{
    m_axisVisible=visible;
    emit update(this);
}

/*!
  Sets if grid is \a visible.
 */
void QChartAxis::setGridVisible(bool visible)
{
    m_gridVisible=visible;
    emit update(this);
}

/*!
  Sets \a pen used to draw grid.
 */
void QChartAxis::setGridPen(const QPen& pen)
{
    m_gridPen=pen;
    emit update(this);
}

/*!
  Sets if axis' labels are \a visible.
 */
void QChartAxis::setLabelsVisible(bool visible)
{
    m_labelsVisible=visible;
    emit update(this);
}

/*!
  Sets \a pen used to draw labels.
 */
void QChartAxis::setLabelsPen(const QPen& pen)
{
    m_labelsPen=pen;
    emit update(this);
}

/*!
  Sets \a brush used to draw labels.
 */
void QChartAxis::setLabelsBrush(const QBrush& brush)
{
    m_labelsBrush=brush;
    emit update(this);
}

/*!
  Sets \a font used to draw labels.
 */
void QChartAxis::setLabelsFont(const QFont& font)
{
    m_labelsFont=font;
    emit update(this);
}

/*!
  Sets \a angle for all the labels on given axis.
 */
void QChartAxis::setLabelsAngle(int angle)
{
	m_labelsAngle=angle;
	 emit update(this);
}

/*!
  Sets if shades are \a visible.
 */
void QChartAxis::setShadesVisible(bool visible)
{
    m_shadesVisible=visible;
    emit update(this);
}

/*!
  Sets \a pen used to draw shades.
 */
void QChartAxis::setShadesPen(const QPen& pen)
{
    m_shadesPen=pen;
    emit update(this);
}

/*!
  Sets \a brush used to draw shades.
 */
void QChartAxis::setShadesBrush(const QBrush& brush)
{
    m_shadesBrush=brush;
    emit update(this);
}

/*!
  Sets \a opacity of the shades.
 */
void QChartAxis::setShadesOpacity(qreal opacity)
{
    m_shadesOpacity=opacity;
    emit update(this);
}

/*!
  Sets \a min value on the axis.
 */
void QChartAxis::setMin(qreal min)
{
	if(m_min!=min){
		m_min=min;
		emit minChanged(m_min);
	}
}

/*!
  Sets \a max value on the axis.
 */
void QChartAxis::setMax(qreal max)
{
	if(m_max!=max){
		m_max=max;
		emit maxChanged(m_max);
	}
}

/*!
  Sets range from \a min to \a max on the axis.
 */
void QChartAxis::setRange(qreal min, qreal max)
{
	setMin(min);
	setMax(max);
}

/*!
  Sets \a count for ticks on the axis.
 */
void QChartAxis::setTicksCount(int count)
{
	m_ticksCount=count;
	emit ticksChanged(this);
}

/*!
  TODO: refactor me. Sets string \a label for \a value on the axis.
 */
void QChartAxis::addAxisTickLabel(qreal value,const QString& label)
{
	m_ticks.insert(value,label);
	emit ticksChanged(this);
}

/*!
  TODO: refactor me. Removes label for \a value on the axis.
 */
void QChartAxis::removeAxisTickLabel(qreal value)
{
	m_ticks.remove(value);
	emit ticksChanged(this);
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
	emit ticksChanged(this);
}

#include "moc_qchartaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
