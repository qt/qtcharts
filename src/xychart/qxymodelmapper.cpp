#include "qxymodelmapper.h"
#include "qxymodelmapper_p.h"
#include "qxyseries.h"
#include <QAbstractItemModel>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QXYModelMapper::QXYModelMapper(QObject *parent):
    QObject(parent),
    d_ptr(new QXYModelMapperPrivate(this))
{
}

QAbstractItemModel* QXYModelMapper::model() const
{
    Q_D(const QXYModelMapper);
    return d->m_model;
}

void QXYModelMapper::setModel(QAbstractItemModel *model)
{
    if (model == 0)
        return;

    Q_D(QXYModelMapper);
    if (d->m_model) {
        disconnect(d->m_model, 0, d, 0);
    }

    d->m_model = model;
    d->initializeXYFromModel();
    //    connect signals from the model
    connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelRowsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelColumnsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelColumnsRemoved(QModelIndex,int,int)));
}

QXYSeries* QXYModelMapper::series() const
{
    Q_D(const QXYModelMapper);
    return d->m_series;
}

void QXYModelMapper::setSeries(QXYSeries *series)
{
    Q_D(QXYModelMapper);
    if (d->m_series) {
        disconnect(d->m_series, 0, d, 0);
    }

    if (series == 0)
        return;

    d->m_series = series;
    d->initializeXYFromModel();
    // connect the signals from the series
    connect(d->m_series, SIGNAL(pointAdded(int)), d, SLOT(handlePointAdded(int)));
    connect(d->m_series, SIGNAL(pointRemoved(int)), d, SLOT(handlePointRemoved(int)));
    connect(d->m_series, SIGNAL(pointReplaced(int)), d, SLOT(pointReplaced(int)));
}

int QXYModelMapper::first() const
{
    Q_D(const QXYModelMapper);
    return d->m_first;
}

void QXYModelMapper::setFirst(int first)
{
    Q_D(QXYModelMapper);
    d->m_first = qMax(first, 0);
    d->initializeXYFromModel();
}

int QXYModelMapper::count() const
{
    Q_D(const QXYModelMapper);
    return d->m_count;
}

void QXYModelMapper::setCount(int count)
{
    Q_D(QXYModelMapper);
    d->m_count = qMax(count, -1);
    d->initializeXYFromModel();
}

Qt::Orientation QXYModelMapper::orientation() const
{
    Q_D(const QXYModelMapper);
    return d->m_orientation;
}

void QXYModelMapper::setOrientation(Qt::Orientation orientation)
{
    Q_D(QXYModelMapper);
    d->m_orientation = orientation;
    d->initializeXYFromModel();
}

int QXYModelMapper::xSection() const
{
    Q_D(const QXYModelMapper);
    return d->m_xSection;
}

void QXYModelMapper::setXSection(int xSection)
{
    Q_D(QXYModelMapper);
    d->m_xSection = xSection;
    d->initializeXYFromModel();
}

int QXYModelMapper::ySection() const
{
    Q_D(const QXYModelMapper);
    return d->m_ySection;
}

void QXYModelMapper::setYSection(int ySection)
{
    Q_D(QXYModelMapper);
    d->m_ySection = ySection;
    d->initializeXYFromModel();
}

void QXYModelMapper::reset()
{
    Q_D(QXYModelMapper);
    d->m_first = 0;
    d->m_count = -1;
    d->m_orientation = Qt::Vertical;
    d->m_xSection = -1;
    d->m_ySection = -1;
    d->initializeXYFromModel();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYModelMapperPrivate::QXYModelMapperPrivate(QXYModelMapper *q) :
    m_series(0),
    m_model(0),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_xSection(-1),
    m_ySection(-1),
    m_seriesSignalsBlock(false),
    m_modelSignalsBlock(false),
    q_ptr(q)
{
}

void QXYModelMapperPrivate::blockModelSignals(bool block)
{
    m_modelSignalsBlock = block;
}

void QXYModelMapperPrivate::blockSeriesSignals(bool block)
{
    m_seriesSignalsBlock = block;
}

QModelIndex QXYModelMapperPrivate::xModelIndex(int xPos)
{
    if (m_count != -1 && xPos >= m_count)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(xPos + m_first, m_xSection);
    else
        return m_model->index(m_xSection, xPos + m_first);
}

QModelIndex QXYModelMapperPrivate::yModelIndex(int yPos)
{
    if (m_count != -1 && yPos >= m_count)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(yPos + m_first, m_ySection);
    else
        return m_model->index(m_ySection, yPos + m_first);
}

void QXYModelMapperPrivate::handlePointAdded(int pointPos)
{
    Q_UNUSED(pointPos)
}

void QXYModelMapperPrivate::handlePointRemoved(int pointPos)
{
    Q_UNUSED(pointPos)
}

void QXYModelMapperPrivate::handlePointReplaced(int pointPos)
{
    Q_UNUSED(pointPos)
}

void QXYModelMapperPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    QModelIndex index;
    QPointF oldPoint;
    QPointF newPoint;
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            index = topLeft.sibling(row, column);
            if (m_orientation == Qt::Vertical && (index.column() == m_xSection|| index.column() == m_ySection)) {
                if (index.row() >= m_first && (m_count == - 1 || index.row() < m_first + m_count)) {
                    oldPoint = m_series->points().at(index.row() - m_first);
                    newPoint.setX(m_model->data(m_model->index(index.row(), m_xSection)).toReal());
                    newPoint.setY(m_model->data(m_model->index(index.row(), m_ySection)).toReal());
                }
            } else if (m_orientation == Qt::Horizontal && (index.row() == m_xSection || index.row() == m_ySection)) {
                if (index.column() >= m_first && (m_count == - 1 || index.column() < m_first + m_count)) {
                    oldPoint = m_series->points().at(index.column() - m_first);
                    newPoint.setX(m_model->data(m_model->index(m_xSection, index.column())).toReal());
                    newPoint.setY(m_model->data(m_model->index(m_ySection, index.column())).toReal());
                }
            } else {
                continue;
            }
            m_series->replace(oldPoint, newPoint);
        }
        blockSeriesSignals(false);
    }
}

void QXYModelMapperPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        insertData(start, end);
    else if (start <= m_xSection || start <= m_ySection) // if the changes affect the map - reinitialize the xy
        initializeXYFromModel();
    blockSeriesSignals(false);
}

void QXYModelMapperPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        removeData(start, end);
    else if (start <= m_xSection || start <= m_ySection) // if the changes affect the map - reinitialize the xy
        initializeXYFromModel();
    blockSeriesSignals(false);
}

void QXYModelMapperPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        insertData(start, end);
    else if (start <= m_xSection || start <= m_ySection) // if the changes affect the map - reinitialize the xy
        initializeXYFromModel();
    blockSeriesSignals(false);
}

void QXYModelMapperPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        removeData(start, end);
    else if (start <= m_xSection || start <= m_ySection) // if the changes affect the map - reinitialize the xy
        initializeXYFromModel();
    blockSeriesSignals(false);
}

void QXYModelMapperPrivate::insertData(int start, int end)
{
    if (m_model == 0 || m_series == 0)
        return;

    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } else {
        int addedCount = end - start + 1;
        if (m_count != -1 && addedCount > m_count)
            addedCount = m_count;
        int first = qMax(start, m_first);
        int last = qMin(first + addedCount - 1, m_orientation == Qt::Vertical ? m_model->rowCount() - 1 : m_model->columnCount() - 1);
        for (int i = first; i <= last; i++) {
            QPointF point;
            point.setX(m_model->data(xModelIndex(i - m_first), Qt::DisplayRole).toDouble());
            point.setY(m_model->data(yModelIndex(i - m_first), Qt::DisplayRole).toDouble());
            m_series->insert(i - m_first, point);
        }

        // remove excess of slices (abouve m_count)
        if (m_count != -1 && m_series->points().size() > m_count)
            for (int i = m_series->points().size() - 1; i >= m_count; i--) {
                m_series->remove(m_series->points().at(i));
            }
    }
}

void QXYModelMapperPrivate::removeData(int start, int end)
{
    if (m_model == 0 || m_series == 0)
        return;

    int removedCount = end - start + 1;
    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } else {
        int toRemove = qMin(m_series->points().size(), removedCount);     // first find how many items can actually be removed
        int first = qMax(start, m_first);    // get the index of the first item that will be removed.
        int last = qMin(first + toRemove - 1, m_series->points().size() + m_first - 1);    // get the index of the last item that will be removed.
        for (int i = last; i >= first; i--) {
            m_series->remove(m_series->points().at(i - m_first));
        }

        if (m_count != -1) {
            int itemsAvailable;     // check how many are available to be added
            if (m_orientation == Qt::Vertical)
                itemsAvailable = m_model->rowCount() - m_first - m_series->points().size();
            else
                itemsAvailable = m_model->columnCount() - m_first - m_series->points().size();
            int toBeAdded = qMin(itemsAvailable, m_count - m_series->points().size());     // add not more items than there is space left to be filled.
            int currentSize = m_series->points().size();
            if (toBeAdded > 0)
                for (int i = m_series->points().size(); i < currentSize + toBeAdded; i++) {
                    QPointF point;
                    point.setX(m_model->data(xModelIndex(i), Qt::DisplayRole).toDouble());
                    point.setY(m_model->data(yModelIndex(i), Qt::DisplayRole).toDouble());
                    m_series->insert(i, point);
                }
        }
    }
}

void QXYModelMapperPrivate::initializeXYFromModel()
{
    if (m_model == 0 || m_series == 0)
        return;

    blockSeriesSignals();
    // clear current content
    m_series->clear();

    // create the initial slices set
    int pointPos = 0;
    QModelIndex xIndex = xModelIndex(pointPos);
    QModelIndex yIndex = yModelIndex(pointPos);
    while (xIndex.isValid() && yIndex.isValid()) {
        QPointF point;
        point.setX(m_model->data(xIndex, Qt::DisplayRole).toDouble());
        point.setY(m_model->data(yIndex, Qt::DisplayRole).toDouble());
        m_series->append(point);
        pointPos++;
        xIndex = xModelIndex(pointPos);
        yIndex = yModelIndex(pointPos);
    }
    blockSeriesSignals(false);
}

#include "moc_qxymodelmapper.cpp"
#include "moc_qxymodelmapper_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
