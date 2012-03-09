#include "qxyseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QXYSeries
    \brief The QXYSeries class is a base class for line, spline and scatter series.
*/

/*!
   \fn QPen QXYSeries::pen() const
   \brief  Returns pen used to draw points for series.
    \sa setPen()
*/

/*!
   \fn QBrush QXYSeries::brush() const
   \brief  Returns brush used to draw points for series.
    \sa setBrush()
*/

/*!
    \fn void QXYSeries::pointReplaced(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeries::pointAdded(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeries::pointRemoved(int index)
    \brief \internal \a index
*/

/*!
    \fn void QXYSeries::updated()
    \brief \internal
*/

/*!
    Constructs empty series object which is a child of \a parent.
    When series object is added to QChartView or QChart instance ownerships is transfered.
*/
QXYSeries::QXYSeries(QObject* parent):QSeries(parent)
{
    m_model = 0;
    m_mapX = 0;
    m_mapY = 1;
}
/*!
    Destroys the object. Series added to QChartView or QChart instances are owned by those,
    and are deleted when mentioned object are destroyed.
*/
QXYSeries::~QXYSeries()
{
}

/*!
    Adds data point \a x \a y to the series. Points are connected with lines on the chart.
 */
void QXYSeries::add(qreal x,qreal y)
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
void QXYSeries::add(const QPointF& point)
{
    add(point.x(),point.y());
}

/*!
   This is an overloaded function.
   Adds list of data \a points to the series. Points are connected with lines on the chart.
 */
void QXYSeries::add(const QList<QPointF> points)
{
    foreach(const QPointF& point , points) {
        add(point.x(),point.y());
    }
}

/*!
  Modifies \a y value for given \a x a value.
*/
void QXYSeries::replace(qreal x,qreal y)
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
void QXYSeries::replace(const QPointF& point)
{
    replace(point.x(),point.y());
}

/*!
  Removes current \a x and y value.
*/
void QXYSeries::remove(qreal x)
{
    int index = m_x.indexOf(x);
    emit pointRemoved(index);
    m_x.remove(index);
    m_y.remove(index);
}

/*!
  Removes current \a point x value. Note \a point y value is ignored.
*/
void QXYSeries::remove(const QPointF& point)
{
    remove(point.x());
}

/*!
   Removes all data points from the series.
*/
void QXYSeries::removeAll()
{
    m_x.clear();
    m_y.clear();
}

/*!
    \internal \a pos
*/
qreal QXYSeries::x(int pos) const
{
    if (m_model)
        return m_model->data(m_model->index(pos, m_mapX), Qt::DisplayRole).toDouble();
    else
        return m_x.at(pos);
}

/*!
    \internal \a pos
*/
qreal QXYSeries::y(int pos) const
{
    if (m_model)
        return m_model->data(m_model->index(pos, m_mapY), Qt::DisplayRole).toDouble();
    else
        return m_y.at(pos);
}

/*!
    Returns number of data points within series.
*/
int QXYSeries::count() const
{
    Q_ASSERT(m_x.size() == m_y.size());

//    int k = m_model->rowCount();
    if (m_model)
        return m_model->rowCount();
    else
        return m_x.size();
}

/*!
    Returns the data points of the series.
*/
QList<QPointF> QXYSeries::data()
{
    QList<QPointF> data;
    for (int i(0); i < m_x.count() && i < m_y.count(); i++)
        data.append(QPointF(m_x.at(i), m_y.at(i)));
    return data;
}


/*!
    Sets \a pen used for drawing points on the chart. If the pen is not defined, the
    pen from chart theme is used.
    \sa QChart::setChartTheme()
*/
void QXYSeries::setPen(const QPen& pen)
{
    if(pen!=m_pen){
        m_pen=pen;
        emit updated();
    }
}

/*!
    Sets \a brush used for drawing points on the chart. If the brush is not defined, brush
    from chart theme setting is used.
    \sa QChart::setChartTheme()
*/

void QXYSeries::setBrush(const QBrush& brush)
{
    if(brush!=m_brush){
        m_brush=brush;
        emit updated();
    }
}


/*!
    Stream operator for adding a data \a point to the series.
    \sa add()
*/

QXYSeries& QXYSeries::operator<< (const QPointF &point)
{
    add(point);
    return *this;
}


/*!
    Stream operator for adding a list of \a points to the series.
    \sa add()
*/

QXYSeries& QXYSeries::operator<< (const QList<QPointF> points)
{
    add(points);
    return *this;
}


void QXYSeries::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    emit pointReplaced(topLeft.row());
}

bool QXYSeries::setModel(QAbstractItemModel* model) {
    m_model = model;
    for (int i = 0; i < m_model->rowCount(); i++)
        emit pointAdded(i);
    connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
//        connect(m_model,SIGNAL(), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
}

#include "moc_qxyseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
