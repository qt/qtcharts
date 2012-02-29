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
    \fn void QLineSeries::pointReplaced(int index)
    \brief \internal \a index
*/

/*!
    \fn void QLineSeries::pointAdded(int index)
    \brief \internal \a index
*/

/*!
    \fn void QLineSeries::pointRemoved(int index)
    \brief \internal \a index
*/

/*!
    \fn void QLineSeries::updated()
    \brief \internal
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
    Q_ASSERT(m_x.size() == m_y.size());
    m_x<<x;
    m_y<<y;
    emit pointAdded(m_x.size()-1);
}

/*!
   This is an overloaded function.
   Adds data \a point to the series. Points are connected with lines on the chart.
 */
void QLineSeries::add(const QPointF& point)
{
    add(point.x(),point.y());
}

/*!
  Modifies \a y value for given \a x a value.
*/
void QLineSeries::replace(qreal x,qreal y)
{
    int index = m_x.indexOf(x);
    m_x[index]=x;
    m_y[index]=y;
    emit pointReplaced(index);
}

/*!
  This is an overloaded function.
  Replaces current y value of for given \a point x value with \a point y value.
*/
void QLineSeries::replace(const QPointF& point)
{
   replace(point.x(),point.y());
}

/*!
  Removes current \a x and y value.
*/
void QLineSeries::remove(qreal x)
{
    int index = m_x.indexOf(x);
    m_x.remove(index);
    m_y.remove(index);
    emit pointRemoved(index);
}

/*!
  Removes current \a point x value. Note \a point y value is ignored.
*/
void QLineSeries::remove(const QPointF& point)
{
    remove(point.x());
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
    if(pen!=m_pen){
    m_pen=pen;
    emit updated();
    }
}

/*!
    Sets if data points are \a visible and should be drawn on line.
*/
void QLineSeries::setPointsVisible(bool visible)
{
    if(m_pointsVisible!=visible){
    m_pointsVisible=visible;
    emit updated();
    }
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

/*!
    Stream operator for adding a data \a point to the series.
    \sa add()
*/

QLineSeries& QLineSeries::operator<< (const QPointF &point)
{
    add(point);
    return *this;
}


#include "moc_qlineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
