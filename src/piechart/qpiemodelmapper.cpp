#include "qpiemodelmapper_p.h"
#include "qpiemodelmapper.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include <QAbstractItemModel>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieModelMapper::QPieModelMapper(QObject *parent) :
    QObject(parent),
    d_ptr(new QPieModelMapperPrivate(this))
{
}

int QPieModelMapper::first() const
{
    Q_D(const QPieModelMapper);
    return d->m_first;
}

void QPieModelMapper::setFirst(int first)
{
    Q_D(QPieModelMapper);
    d->m_first = qMax(first, 0);
    //    emit updated();
}

int QPieModelMapper::count() const
{
    Q_D(const QPieModelMapper);
    return d->m_count;
}

void QPieModelMapper::setCount(int count)
{
    Q_D(QPieModelMapper);
    d->m_count = qMax(count, -1);
    //    emit updated();
}

Qt::Orientation QPieModelMapper::orientation() const
{
    Q_D(const QPieModelMapper);
    return d->m_orientation;
}

void QPieModelMapper::setOrientation(Qt::Orientation orientation)
{
    Q_D(QPieModelMapper);
    d->m_orientation = orientation;
    //    emit updated();
}

int QPieModelMapper::mapValues() const
{
    Q_D(const QPieModelMapper);
    return d->m_mapValues;
}

void QPieModelMapper::setMapValues(int mapValues)
{
    Q_D(QPieModelMapper);
    d->m_mapValues = mapValues;
    //    emit updated();
}

int QPieModelMapper::mapLabels() const
{
    Q_D(const QPieModelMapper);
    return d->m_mapLabels;
}

void QPieModelMapper::setMapLabels(int mapLabels)
{
    Q_D(QPieModelMapper);
    d->m_mapLabels = mapLabels;
    //    emit updated();
}

void QPieModelMapper::reset()
{
    Q_D(QPieModelMapper);
    d->m_first = 0;
    d->m_count = -1;
    d->m_orientation = Qt::Vertical;
    d->m_mapValues = -1;
    d->m_mapLabels = -1;
    //    emit updated();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPieModelMapperPrivate::QPieModelMapperPrivate(QPieModelMapper *q) :
    q_ptr(q)
{
    m_first = 0;
    m_count = -1;
    m_orientation = Qt::Vertical;
    m_mapValues = -1;
    m_mapLabels = -1;
}

int QPieModelMapperPrivate::getSliceIndex()
{

    // invalid
    return -1;
}

void QPieModelMapperPrivate::setModel(QAbstractItemModel *model)
{
    if (model == 0)
        return;

    if(m_model)
    {
        // disconnect signals from old model
        disconnect(m_model, 0, this, 0);
    }

    m_model = model;
    //    connect signals from the model
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    connect(m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(modelRowsAdded(QModelIndex,int,int)));
    connect(m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    connect(m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), this, SLOT(modelColumnsAdded(QModelIndex,int,int)));
    connect(m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), this, SLOT(modelColumnsRemoved(QModelIndex,int,int)));
}

void QPieModelMapperPrivate::slicesAdded()
{
    //
}

void QPieModelMapperPrivate::slicesRemoved()
{
    //
}

void QPieModelMapperPrivate::sliceChanged()
{
    //
}

void QPieModelMapperPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            if (m_orientation == Qt::Vertical)
            {
                if ( topLeft.row() >= m_first && (m_count == - 1 || topLeft.row() < m_first + m_count)) {
                    if (topLeft.column() == m_mapValues)
                        m_series->slices().at(topLeft.row() - m_first)->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    if (topLeft.column() == m_mapLabels)
                        m_series->slices().at(topLeft.row() - m_first)->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
                }
            }
            else
            {
                if (topLeft.column() >= m_first && (m_count == - 1 || topLeft.column() < m_first + m_count)) {
                    if (topLeft.row() == m_mapValues)
                        m_series->slices().at(topLeft.column() - m_first)->setValue(m_model->data(topLeft, Qt::DisplayRole).toDouble());
                    if (topLeft.row() == m_mapLabels)
                        m_series->slices().at(topLeft.column() - m_first)->setLabel(m_model->data(topLeft, Qt::DisplayRole).toString());
                }
            }
        }
    }
}


//void QPieModelMapperPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
//{
//    Q_UNUSED(parent);
//        if (m_mapper->orientation() == Qt::Vertical)
//            insertData(start, end);
//        else if (start <= m_mapValues || start <= m_mapLabels) // if the changes affect the map - reinitialize the pie
//            initializePieFromModel();
//}

//void QPieModelMapperPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
//{
//    Q_UNUSED(parent);
//        if (m_mapper->orientation() == Qt::Vertical)
//            removeData(start, end);
//        else if (start <= m_mapValues || start <= m_mapLabels) // if the changes affect the map - reinitialize the pie
//            initializePieFromModel();
//}

//void QPieModelMapperPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
//{
//    Q_UNUSED(parent);
//        if (m_mapper->orientation() == Qt::Horizontal)
//            insertData(start, end);
//        else if (start <= m_mapValues || start <= m_mapLabels) // if the changes affect the map - reinitialize the pie
//            initializePieFromModel();
//}

//void QPieModelMapperPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
//{
//    Q_UNUSED(parent);
//        if (m_mapper->orientation() == Qt::Horizontal)
//            removeData(start, end);
//        else if (start <= m_mapValues || start <= m_mapLabels) // if the changes affect the map - reinitialize the pie
//            initializePieFromModel();
//}

//void QPieModelMapperPrivate::insertData(int start, int end)
//{
//    Q_Q(QPieSeries);
//        if (m_count != -1 && start >= m_first + m_count) {
//            return;
//        } else {
//            int addedCount = end - start + 1;
//            if (m_count != -1 && addedCount > m_count)
//                addedCount = m_count;
//            int first = qMax(start, m_first);
//            int last = qMin(first + addedCount - 1, m_mapper->orientation() == Qt::Vertical ? m_model->rowCount() - 1 : m_model->columnCount() - 1);
//            for (int i = first; i <= last; i++) {
//                QPieSlice *slice = new QPieSlice;
//                if (m_mapper->orientation() == Qt::Vertical) {
//                    slice->setValue(m_model->data(m_model->index(i, m_mapValues), Qt::DisplayRole).toDouble());
//                    slice->setLabel(m_model->data(m_model->index(i, m_mapLabels), Qt::DisplayRole).toString());
//                } else {
//                    slice->setValue(m_model->data(m_model->index(m_mapValues, i), Qt::DisplayRole).toDouble());
//                    slice->setLabel(m_model->data(m_model->index(m_mapLabels, i), Qt::DisplayRole).toString());
//                }
//                slice->setLabelVisible();
//                q->insert(i - m_first, slice);
//            }
//            if (m_count != -1 && m_series->slices().size() > m_count)
//                for (int i = m_series->slices().size() - 1; i >= m_count; i--)
//                    q->remove(q->slices().at(i));
//        }
//}

//void QPieModelMapperPrivate::removeData(int start, int end)
//{
//    Q_Q(QPieSeries);
//        int removedCount = end - start + 1;
//        if (m_count != -1 && start >= m_first + m_count) {
//            return;
//        } else {
//            int toRemove = qMin(m_series->slices().size(), removedCount);     // first find how many items can actually be removed
//            int first = qMax(start, m_first);    // get the index of the first item that will be removed.
//            int last = qMin(first + toRemove - 1, m_series->slices().size() + m_first - 1);    // get the index of the last item that will be removed.
//            for (int i = last; i >= first; i--)
//                q->remove(q->slices().at(i - m_first));

//            if (m_count != -1) {
//                int itemsAvailable;     // check how many are available to be added
//                if (m_mapper->orientation() == Qt::Vertical)
//                    itemsAvailable = m_model->rowCount() - m_first - m_series->slices().size();
//                else
//                    itemsAvailable = m_model->columnCount() - m_first - m_series->slices().size();
//                int toBeAdded = qMin(itemsAvailable, m_count - m_series->slices().size());     // add not more items than there is space left to be filled.
//                int currentSize = m_series->slices().size();
//                if (toBeAdded > 0)
//                    for (int i = m_series->slices().size(); i < currentSize + toBeAdded; i++) {
//                        QPieSlice *slice = new QPieSlice;
//                        if (m_mapper->orientation() == Qt::Vertical) {
//                            slice->setValue(m_model->data(m_model->index(i + m_first, m_mapValues), Qt::DisplayRole).toDouble());
//                            slice->setLabel(m_model->data(m_model->index(i + m_first, m_mapLabels), Qt::DisplayRole).toString());
//                        } else {
//                            slice->setValue(m_model->data(m_model->index(m_mapValues, i + m_first), Qt::DisplayRole).toDouble());
//                            slice->setLabel(m_model->data(m_model->index(m_mapLabels, i + m_first), Qt::DisplayRole).toString());
//                        }
//                        slice->setLabelVisible();
//                        q->insert(i, slice);
//                    }
//            }
//        }
//}

//void QPieModelMapperPrivate::initializePieFromModel()
//{
//    Q_Q(QPieSeries);

//    // clear current content
//    q->clear();

//    if (m_model == 0 || m_mapper == 0)
//        return;

//    // check if mappings are set
//    if (m_mapValues == -1 || m_mapLabels == -1)
//        return;

//    // create the initial slices set
//    if (m_mapper->orientation() == Qt::Vertical) {
//        if (m_mapValues >= m_model->columnCount() || m_mapLabels >= m_model->columnCount())
//            return;   // mapped columns are not existing

//        int sliceCount = 0;
//        if(m_count == -1)
//            sliceCount = m_model->rowCount() - m_first;
//        else
//            sliceCount = qMin(m_count, m_model->rowCount() - m_first);
//        for (int i = m_first; i < m_first + sliceCount; i++)
//            q->append(m_model->data(m_model->index(i, m_mapValues), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(i, m_mapLabels), Qt::DisplayRole).toString());
//    } else {
//        if (m_mapValues >= m_model->rowCount() || m_mapLabels >= m_model->rowCount())
//            return;   // mapped columns are not existing

//        int sliceCount = 0;
//        if(m_count == -1)
//            sliceCount = m_model->columnCount() - m_first;
//        else
//            sliceCount = qMin(m_count, m_model->columnCount() - m_first);
//        for (int i = m_first; i < m_first + sliceCount; i++)
//            q->append(m_model->data(m_model->index(m_mapValues, i), Qt::DisplayRole).toDouble(), m_model->data(m_model->index(m_mapLabels, i), Qt::DisplayRole).toString());
//    }
//    q->setLabelsVisible(true);
//}

#include "moc_qpiemodelmapper_p.cpp"
#include "moc_qpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
