#include "qlineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QLineSeries
    \brief The QLineSeries class is used for making line charts.

    \mainclass

	A line chart is used to show information as a series of data points
	connected by straight lines.

	\image linechart.png

	Creating basic line chart is simple:
	\code
	QLineSeries* series = new QLineSeries();
	series->add(0, 6);
	series->add(2, 4);
	...
	chartView->addSeries(series);
    \endcode
*/

/*!
    \fn virtual QSeriesType QLineSeries::type() const
    \brief Returns type of series.
    \sa QSeries, QSeriesType
*/

/*!
   \fn QPen QLineSeries::pen() const
   \brief  Returns the pen used to draw line for this series.
    \sa setPen()
*/

/*!
   \fn bool  QLineSeries::pointsVisible() const
   \brief  Returns if the points are drawn for this series.
    \sa setPointsVisible()
*/


/*!
    \fn void QLineSeries::changed(int index)
    \brief \internal \a index
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transfered.
*/
QLineSeries::QLineSeries(QObject* parent):QSeries(parent),
m_pointsVisible(false)
{
}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QLineSeries::~QLineSeries()
{
}

/*!
    Adds data point \a x \a y to the series. Points are connected with lines on the chart.
 */
void QLineSeries::add(qreal x,qreal y)
{
    m_x<<x;
    m_y<<y;
}

/*!
   This is an overloaded function.
   Adds data \a point to the series. Points are connected with lines on the chart.
 */
void QLineSeries::add(const QPointF& point)
{
    m_x<<point.x();
    m_y<<point.y();
}

/*!
  Modifies \a y value for given \a x a value.
*/
void QLineSeries::replace(qreal x,qreal y)
{
    int index = m_x.indexOf(x);
    m_x[index]=x;
    m_y[index]=y;
    emit changed(index);
}

/*!
  This is an overloaded function.
  Replaces current y value of for given \a point x value with \a point y value.
*/
void QLineSeries::replace(const QPointF& point)
{
    int index = m_x.indexOf(point.x());
    m_x[index]=point.x();
    m_y[index]=point.y();
    emit changed(index);
}

/*!
  Removes current \a x and y value.
*/
void QLineSeries::remove(qreal x)
{

}

/*!
  Removes current \a point x value. Note \a point y value is ignored.
*/
void QLineSeries::remove(const QPointF& point)
{

}

/*!
  Clears all the data.
*/
void QLineSeries::clear()
{
    m_x.clear();
    m_y.clear();
}

/*!
    \internal \a pos
*/
qreal QLineSeries::x(int pos) const
{
   return m_x.at(pos);
}

/*!
    \internal \a pos
*/
qreal QLineSeries::y(int pos) const
{
   return m_y.at(pos);
}

/*!
    Returns number of data points within series.
*/
int QLineSeries::count() const
{
	Q_ASSERT(m_x.size() == m_y.size());

	return m_x.size();

}

/*!
    Sets \a pen used for drawing given series..
*/
void QLineSeries::setPen(const QPen& pen)
{
    m_pen=pen;
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QLineSeries::setPointsVisible(bool visible)
{
    m_pointsVisible=visible;
}

QDebug operator<< (QDebug debug, const QLineSeries series)
{
	Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}


#include "moc_qlineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
