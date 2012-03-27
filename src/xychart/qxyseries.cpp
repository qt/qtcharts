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
    \fn void QXYSeries::clicked(const QPointF& point)
    \brief Signal is emitted when user clicks the \a point on chart.
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
QXYSeries::QXYSeries(QObject *parent):QSeries(parent)
{
    m_mapX = -1;
    m_mapY = -1;
    m_mapFirst = 0;
    m_mapCount = 0;
    m_mapLimited = false;
    m_mapOrientation = Qt::Vertical;
    //    m_mapYOrientation = Qt::Vertical;
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
void QXYSeries::add(const QPointF &point)
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
    m_x[index] = x;
    m_y[index] = y;
    emit pointReplaced(index);
}

/*!
  This is an overloaded function.
  Replaces current y value of for given \a point x value with \a point y value.
*/
void QXYSeries::replace(const QPointF &point)
{
    replace(point.x(),point.y());
}

/*!
  Removes first \a x value and related y value.
*/
void QXYSeries::remove(qreal x)
{
    int index = m_x.indexOf(x);

    if (index == -1) return;

    m_x.remove(index);
    m_y.remove(index);

    emit pointRemoved(index);
}

/*!
  Removes current \a x and \a y value.
*/
void QXYSeries::remove(qreal x,qreal y)
{
    int index =-1;
    do {
        index = m_x.indexOf(x,index+1);
    } while (index !=-1 && m_y.at(index)!=y);

    if (index==-1) return;

    m_x.remove(index);
    m_y.remove(index);
    emit pointRemoved(index);
}

/*!
  Removes current \a point x value. Note \a point y value is ignored.
*/
void QXYSeries::remove(const QPointF &point)
{
    remove(point.x(),point.y());
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
    if (m_model) {
        if (m_mapOrientation == Qt::Vertical)
            // consecutive data is read from model's column
            return m_model->data(m_model->index(pos + m_mapFirst, m_mapX), Qt::DisplayRole).toDouble();
        else
            // consecutive data is read from model's row
            return m_model->data(m_model->index(m_mapX, pos + m_mapFirst), Qt::DisplayRole).toDouble();
    } else {
        // model is not specified, return the data from series' internal data store
        return m_x.at(pos);
    }
}

/*!
    \internal \a pos
*/
qreal QXYSeries::y(int pos) const
{
    if (m_model) {
        if (m_mapOrientation == Qt::Vertical)
            // consecutive data is read from model's column
            return m_model->data(m_model->index(pos + m_mapFirst, m_mapY), Qt::DisplayRole).toDouble();
        else
            // consecutive data is read from model's row
            return m_model->data(m_model->index(m_mapY, pos + m_mapFirst), Qt::DisplayRole).toDouble();
    } else {
        // model is not specified, return the data from series' internal data store
        return m_y.at(pos);
    }
}

/*!
    Returns number of data points within series.
*/
int QXYSeries::count() const
{
    Q_ASSERT(m_x.size() == m_y.size());

    if (m_model) {
        if (m_mapOrientation == Qt::Vertical) {
            // data is in a column. Return the number of mapped items if the model's column have enough items
            // or the number of items that can be mapped
            if (m_mapLimited)
                return qMin(m_mapCount, qMax(m_model->rowCount() - m_mapFirst, 0));
            else
                return qMax(m_model->rowCount() - m_mapFirst, 0);
        } else {
            // data is in a row. Return the number of mapped items if the model's row have enough items
            // or the number of items that can be mapped
            if (m_mapLimited)
                return qMin(m_mapCount, qMax(m_model->columnCount() - m_mapFirst, 0));
            else
                return qMax(m_model->columnCount() - m_mapFirst, 0);
        }
    }

    // model is not specified, return the number of points in the series internal data store
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
void QXYSeries::setPen(const QPen &pen)
{
    if (pen != m_pen) {
        m_pen = pen;
        emit updated();
    }
}

/*!
    Sets \a brush used for drawing points on the chart. If the brush is not defined, brush
    from chart theme setting is used.
    \sa QChart::setChartTheme()
*/

void QXYSeries::setBrush(const QBrush &brush)
{
    if (brush != m_brush) {
        m_brush = brush;
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
    Q_UNUSED(bottomRight)

    if (m_mapOrientation == Qt::Vertical) {
        if (topLeft.row() >= m_mapFirst && (!m_mapLimited || topLeft.row() < m_mapFirst + m_mapCount))
            emit pointReplaced(topLeft.row() - m_mapFirst);
    } else {
        if (topLeft.column() >= m_mapFirst && (!m_mapLimited || topLeft.column() < m_mapFirst + m_mapCount))
            emit pointReplaced(topLeft.column() - m_mapFirst);
    }
}

void QXYSeries::modelDataAboutToBeAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    //    Q_UNUSED(end)

    if (m_mapLimited) {
        if (start >= m_mapFirst + m_mapCount) {
            // the added data is below mapped area
            // therefore it has no relevance
            return;
        } else {
            // the added data is in the mapped area or before it and update is needed

            // check how many mapped items there is currently (before new items are added)
            // if the number of items currently is equal the m_mapCount then some needs to be removed from xychartitem
            // internal storage before new ones can be added

            int itemsToRemove = qMin(count() - (start - m_mapFirst), end - start + 1);
            if (m_mapCount == count()) {
                for (int i = 0; i < itemsToRemove; i++)
                    emit pointRemoved(count() - 1 - i);
            }
        }
    } else {
        // map is not limited (it includes all the items starting from m_mapFirst till the end of model)
        // nothing to do
        //        emit pointAdded(qMax(start - m_mapFirst, 0));
    }
}

void QXYSeries::modelDataAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    //    Q_UNUSED(end)

    if (m_mapLimited) {
        if (start >= m_mapFirst + m_mapCount) {
            // the added data is below mapped area
            // therefore it has no relevance
            return;
        } else {
            // the added data is in the mapped area or before it
            // update needed
            if (count() > 0) {
                for (int i = 0; i < qMin(m_mapCount - (start - m_mapFirst), end - start + 1); i++)
                    emit pointAdded(qMax(start + i - m_mapFirst, 0));
            }
        }
    } else {
        // map is not limited (it included all the items starting from m_mapFirst till the end of model)
        for (int i = 0; i < end - start + 1; i++)
            emit pointAdded(qMax(start + i - m_mapFirst, 0));
    }
}

void QXYSeries::modelDataAboutToBeRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    //    Q_UNUSED(end)

    if (m_mapLimited) {
        if (start >= m_mapFirst + m_mapCount) {
            // the removed data is below mapped area
            // therefore it has no relevance
            return;
        } else {
            // the removed data is in the mapped area or before it
            // update needed

            // check how many items need to be removed from the xychartitem storage
            // the number equals the number of items that are removed and that lay before
            // or in the mapped area. Items that lay beyond the map do not count
            // the max is the current number of items in storage (count())
            int itemsToRemove = qMin(count(), qMin(end, m_mapFirst + m_mapCount - 1) - start + 1);
            for (int i = 0; i < itemsToRemove; i++)
                emit pointRemoved(qMax(start - m_mapFirst, 0));
        }
    } else {
        // map is not limited (it included all the items starting from m_mapFirst till the end of model)
        for (int i = 0; i < end - start + 1; i++)
            emit pointRemoved(qMax(start - m_mapFirst, 0));
    }
}

void QXYSeries::modelDataRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(end)

    // how many items there were before data was removed
    //    int oldCount = count() - 1;

    if (m_mapLimited) {
        if (start >= m_mapFirst + m_mapCount) {
            // the removed data is below mapped area
            // therefore it has no relevance
            return;
        } else {
            // if the current items count in the whole model is bigger than the index of the last item
            // that was removed than it means there are some extra items available
            int extraItemsAvailable = 0;
            if (m_mapOrientation == Qt::Vertical) {
                extraItemsAvailable = qMax(m_model->rowCount() - end, 0);
            } else {
                extraItemsAvailable = qMax(m_model->columnCount() - end, 0);
            }

            // if there are excess items available (below the mapped area) use them to repopulate mapped area
            int removedItemsCount = qMin(count(), qMin(end, m_mapFirst + m_mapCount - 1) - qMax(start, m_mapFirst) + 1);
            int toBeAdded = qMin(extraItemsAvailable, removedItemsCount);
            for (int k = 0; k < toBeAdded; k++)
                emit pointAdded(qMax(start - m_mapFirst, m_mapFirst) + k);
        }
    } else {
        // data was removed from XYSeries interal storage. Nothing more to do
    }
}

bool QXYSeries::setModel(QAbstractItemModel *model) {

    // disconnect signals from old model
    if (m_model) {
        disconnect(m_model, 0, this, 0);
        m_mapX = -1;
        m_mapY = -1;
        m_mapFirst = 0;
        m_mapCount = 0;
        m_mapLimited = false;
        m_mapOrientation = Qt::Vertical;
    }

    // set new model
    if (model) {
        m_model = model;
        return true;
    } else {
        m_model = 0;
        return false;
    }
}

void QXYSeries::setModelMapping(int modelX, int modelY, Qt::Orientation orientation)
{
    if (m_model == 0)
        return;
    m_mapX = modelX;
    m_mapY = modelY;
    m_mapFirst = 0;
    m_mapOrientation = orientation;
    if (m_mapOrientation == Qt::Vertical) {
        //        m_mapCount = m_model->rowCount();
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(rowsAboutToBeInserted(QModelIndex, int, int)), this, SLOT(modelDataAboutToBeAdded(QModelIndex,int,int)));
        connect(m_model,SIGNAL(rowsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(modelDataAboutToBeRemoved(QModelIndex,int,int)));
        connect(m_model, SIGNAL(rowsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    } else {
        //        m_mapCount = m_model->columnCount();
        connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex, QModelIndex)));
        connect(m_model,SIGNAL(columnsAboutToBeInserted(QModelIndex, int, int)), this, SLOT(modelDataAboutToBeAdded(QModelIndex,int,int)));
        connect(m_model,SIGNAL(columnsInserted(QModelIndex, int, int)), this, SLOT(modelDataAdded(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsAboutToBeRemoved(QModelIndex, int, int)), this, SLOT(modelDataAboutToBeRemoved(QModelIndex,int,int)));
        connect(m_model, SIGNAL(columnsRemoved(QModelIndex, int, int)), this, SLOT(modelDataRemoved(QModelIndex,int,int)));
    }
}

void QXYSeries::setModelMappingShift(int first, int count)
{
    m_mapFirst = first;
    if (count == 0) {
        m_mapLimited = false;
    } else {
        m_mapCount = count;
        m_mapLimited = true;
    }
}

#include "moc_qxyseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
