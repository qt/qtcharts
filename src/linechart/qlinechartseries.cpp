#include "qlinechartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLineChartSeries
    \brief The QLineChartSeries class is used for making line charts.

    \mainclass

	A line chart is used to show information as a series of data points
	connected by straight lines.

	\image linechart.png

    To create line charts, users need to first QLineChartSeries object.

    \snippet ../example/linechart/main.cpp 1

    Populate with the data

    \snippet ../example/linechart/main.cpp 2

    Add created series objects to QChartView or QChart instance.

    \snippet ../example/linechart/main.cpp 3

*/

/*!
    \fn virtual QChartSeriesType QLineChartSeries::type() const
    \brief Returns type of series.
    \sa QChartSeries, QChartSeriesType
*/

/*!
   \fn QPen QLineChartSeries::pen() const
   \brief  Returns the pen used to draw line for this series.
    \sa setPen()
*/

/*!
   \fn bool isPointsVisible() const
   \brief  Returns if the points are drawn for this series.
    \sa setPointsVisible()
*/


/*!
    \fn void QLineChartSeries::changed(int index)
    \brief \internal \a index
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transfered.
*/
QLineChartSeries::QLineChartSeries(QObject* parent):QChartSeries(parent),
m_pointsVisible(false)
{
}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QLineChartSeries::~QLineChartSeries()
{
}

/*!
    Adds data point \a x \a y to the series. Points are connected with lines on the chart.
    Function returns index, which can be used to modify data.
 */
int QLineChartSeries::add(qreal x,qreal y)
{
    m_x<<x;
    m_y<<y;
    return m_x.size()-1;
}

/*!
   This is an overloaded function.
   Adds data \a point to the series. Points are connected with lines on the chart.
   Function returns index, which can be used to modify data.
 */
int QLineChartSeries::add(const QPointF& point)
{
    m_x<<point.x();
    m_y<<point.y();
    return m_x.size()-1;
}

/*!
  Modifies data within \a index, sets new \a x and \a y values.
*/
void QLineChartSeries::set(int index,qreal x,qreal y)
{
    m_x[index]=x;
    m_y[index]=y;
    emit changed(index);
}

/*!
  This is an overloaded function.
  Modifies data within \a index, sets new \a point value.
*/
void QLineChartSeries::set(int index,const QPointF& point)
{
    m_x[index]=point.x();
    m_y[index]=point.y();
    emit changed(index);
}


/*!
  Clears all the data.
*/
void QLineChartSeries::clear()
{
    m_x.clear();
    m_y.clear();
}

/*!
    \internal \a pos
*/
qreal QLineChartSeries::x(int pos) const
{
   return m_x.at(pos);
}

/*!
    \internal \a pos
*/
qreal QLineChartSeries::y(int pos) const
{
   return m_y.at(pos);
}

/*!
    Returns number of data points within series.
*/
int QLineChartSeries::count() const
{
	Q_ASSERT(m_x.size() == m_y.size());

	return m_x.size();

}

/*!
    Sets \a pen used for drawing given series..
*/
void QLineChartSeries::setPen(const QPen& pen)
{
    m_pen=pen;
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QLineChartSeries::setPointsVisible(bool visible)
{
    m_pointsVisible=visible;
}

QDebug operator<< (QDebug debug, const QLineChartSeries series)
{
	Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}


#include "moc_qlinechartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
