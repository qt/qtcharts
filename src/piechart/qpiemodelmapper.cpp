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

QAbstractItemModel* QPieModelMapper::model() const
{
    Q_D(const QPieModelMapper);
    return d->m_model;
}

void QPieModelMapper::setModel(QAbstractItemModel *model)
{
    if (model == 0)
        return;

    Q_D(QPieModelMapper);
    if (d->m_model) {
        disconnect(d->m_model, 0, d, 0);
    }

    d->m_model = model;
    d->initializePieFromModel();
    //    connect signals from the model
    connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelRowsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelColumnsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelColumnsRemoved(QModelIndex,int,int)));
}

QPieSeries* QPieModelMapper::series() const
{
    Q_D(const QPieModelMapper);
    return d->m_series;
}

void QPieModelMapper::setSeries(QPieSeries *series)
{
    if (series == 0)
        return;

    Q_D(QPieModelMapper);
    if (d->m_series) {
        disconnect(d->m_series, 0, d, 0);
    }

    d->m_series = series;
    d->initializePieFromModel();
    // connect the signals from the series
    connect(d->m_series, SIGNAL(added(QList<QPieSlice*>)), d, SLOT(slicesAdded(QList<QPieSlice*>)));
    connect(d->m_series, SIGNAL(removed(QList<QPieSlice*>)), d, SLOT(slicesRemoved(QList<QPieSlice*>)));
    //        connect(d->m_model, SIGNAL(), d, SLOT());
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
    d->initializePieFromModel();
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
    d->initializePieFromModel();
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
    d->initializePieFromModel();
}

int QPieModelMapper::valuesIndex() const
{
    Q_D(const QPieModelMapper);
    return d->m_valuesIndex;
}

void QPieModelMapper::setValuesIndex(int valuesIndex)
{
    Q_D(QPieModelMapper);
    d->m_valuesIndex = qMax(-1, valuesIndex);
    d->initializePieFromModel();
}

int QPieModelMapper::labelsIndex() const
{
    Q_D(const QPieModelMapper);
    return d->m_labelsIndex;
}

void QPieModelMapper::setLabelsIndex(int labelsIndex)
{
    Q_D(QPieModelMapper);
    d->m_labelsIndex = qMax(-1, labelsIndex);
    d->initializePieFromModel();
}

void QPieModelMapper::reset()
{
    Q_D(QPieModelMapper);
    d->m_first = 0;
    d->m_count = -1;
    d->m_orientation = Qt::Vertical;
    d->m_valuesIndex = -1;
    d->m_labelsIndex = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPieModelMapperPrivate::QPieModelMapperPrivate(QPieModelMapper *q) :
    m_series(0),
    m_model(0),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_valuesIndex(-1),
    m_labelsIndex(-1),
    m_seriesSignalsBlock(false),
    m_modelSignalsBlock(false),
    q_ptr(q)
{
}

void QPieModelMapperPrivate::blockModelSignals(bool block)
{
    m_modelSignalsBlock = block;
}

void QPieModelMapperPrivate::blockSeriesSignals(bool block)
{
    m_seriesSignalsBlock = block;
}


QPieSlice* QPieModelMapperPrivate::pieSlice(QModelIndex index) const
{
    if (m_orientation == Qt::Vertical && (index.column() == m_valuesIndex || index.column() == m_labelsIndex)) {
        if (index.row() >= m_first && (m_count == - 1 || index.row() < m_first + m_count))
            return m_series->slices().at(index.row() - m_first);
    } else if (m_orientation == Qt::Horizontal && (index.row() == m_valuesIndex || index.row() == m_labelsIndex)) {
        if (index.column() >= m_first && (m_count == - 1 || index.column() < m_first + m_count))
            return m_series->slices().at(index.column() - m_first);
    }
    return 0; // This part of model has not been mapped to any slice
}

QModelIndex QPieModelMapperPrivate::valueModelIndex(int slicePos)
{
    if (m_count != -1 && slicePos >= m_count)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(slicePos + m_first, m_valuesIndex);
    else
        return m_model->index(m_valuesIndex, slicePos + m_first);
}

QModelIndex QPieModelMapperPrivate::labelModelIndex(int slicePos)
{
    if (m_count != -1 && slicePos >= m_count)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(slicePos + m_first, m_labelsIndex);
    else
        return m_model->index(m_labelsIndex, slicePos + m_first);
}

void QPieModelMapperPrivate::slicesAdded(QList<QPieSlice*> slices)
{
    if (m_seriesSignalsBlock)
        return;

    if (slices.count() == 0)
        return;

    int firstIndex = m_series->slices().indexOf(slices.at(0));
    if (firstIndex == -1)
        return;

    if (m_count != -1)
        m_count += slices.count();

    for (int i = firstIndex; i < firstIndex + slices.count(); i++) {
        m_slices.insert(i, slices.at(i - firstIndex));
        connect(slices.at(i - firstIndex), SIGNAL(labelChanged()), this, SLOT(sliceLabelChanged()));
        connect(slices.at(i - firstIndex), SIGNAL(valueChanged()), this, SLOT(sliceValueChanged()));
    }

    blockModelSignals();
    if (m_orientation == Qt::Vertical)
        m_model->insertRows(firstIndex + m_first, slices.count());
    else
        m_model->insertColumns(firstIndex + m_first, slices.count());

    for(int i = firstIndex; i < firstIndex + slices.count(); i++) {
        m_model->setData(valueModelIndex(i), slices.at(i - firstIndex)->value());
        m_model->setData(labelModelIndex(i), slices.at(i - firstIndex)->label());
    }
    blockModelSignals(false);
}

void QPieModelMapperPrivate::slicesRemoved(QList<QPieSlice*> slices)
{
    if (m_seriesSignalsBlock)
        return;

    if (slices.count() == 0)
        return;

    int firstIndex = m_slices.indexOf(slices.at(0));
    if (firstIndex == -1)
        return;

    if (m_count != -1)
        m_count -= slices.count();

    for (int i = firstIndex + slices.count() - 1; i >= firstIndex; i--)
        m_slices.removeAt(i);

    blockModelSignals();
    if (m_orientation == Qt::Vertical)
        m_model->removeRows(firstIndex + m_first, slices.count());
    else
        m_model->removeColumns(firstIndex + m_first, slices.count());
    blockModelSignals(false);
}

void QPieModelMapperPrivate::sliceLabelChanged()
{
    if (m_seriesSignalsBlock)
        return;

    blockModelSignals();
    QPieSlice *slice = qobject_cast<QPieSlice *>(QObject::sender());
    m_model->setData(labelModelIndex(m_series->slices().indexOf(slice)), slice->label());
    blockModelSignals(false);
}

void QPieModelMapperPrivate::sliceValueChanged()
{
    if (m_seriesSignalsBlock)
        return;

    blockModelSignals();
    QPieSlice *slice = qobject_cast<QPieSlice *>(QObject::sender());
    m_model->setData(valueModelIndex(m_series->slices().indexOf(slice)), slice->value());
    blockModelSignals(false);
}

void QPieModelMapperPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    QModelIndex index;
    QPieSlice *slice;
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            index = topLeft.sibling(row, column);
            slice = pieSlice(index);
            if (slice) {
                slice->setValue(m_model->data(index, Qt::DisplayRole).toReal());
                slice->setLabel(m_model->data(index, Qt::DisplayRole).toString());
            }
        }
    }
    blockSeriesSignals(false);
}


void QPieModelMapperPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        insertData(start, end);
    else if (start <= m_valuesIndex || start <= m_labelsIndex) // if the changes affect the map - reinitialize the pie
        initializePieFromModel();
    blockSeriesSignals(false);
}

void QPieModelMapperPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        removeData(start, end);
    else if (start <= m_valuesIndex || start <= m_labelsIndex) // if the changes affect the map - reinitialize the pie
        initializePieFromModel();
    blockSeriesSignals(false);
}

void QPieModelMapperPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        insertData(start, end);
    else if (start <= m_valuesIndex || start <= m_labelsIndex) // if the changes affect the map - reinitialize the pie
        initializePieFromModel();
    blockSeriesSignals(false);
}

void QPieModelMapperPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        removeData(start, end);
    else if (start <= m_valuesIndex || start <= m_labelsIndex) // if the changes affect the map - reinitialize the pie
        initializePieFromModel();
    blockSeriesSignals(false);
}

void QPieModelMapperPrivate::insertData(int start, int end)
{
    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } else {
        int addedCount = end - start + 1;
        if (m_count != -1 && addedCount > m_count)
            addedCount = m_count;
        int first = qMax(start, m_first);
        int last = qMin(first + addedCount - 1, m_orientation == Qt::Vertical ? m_model->rowCount() - 1 : m_model->columnCount() - 1);
        for (int i = first; i <= last; i++) {
            QPieSlice *slice = new QPieSlice;
            slice->setValue(m_model->data(valueModelIndex(i - m_first), Qt::DisplayRole).toDouble());
            slice->setLabel(m_model->data(labelModelIndex(i - m_first), Qt::DisplayRole).toString());
            slice->setLabelVisible();
            connect(slice, SIGNAL(labelChanged()), this, SLOT(sliceLabelChanged()));
            connect(slice, SIGNAL(valueChanged()), this, SLOT(sliceValueChanged()));
            m_series->insert(i - m_first, slice);
            m_slices.insert(i - m_first, slice);
        }

        // remove excess of slices (abouve m_count)
        if (m_count != -1 && m_series->slices().size() > m_count)
            for (int i = m_series->slices().size() - 1; i >= m_count; i--) {
                m_series->remove(m_series->slices().at(i));
                m_slices.removeAt(i);
            }
    }
}

void QPieModelMapperPrivate::removeData(int start, int end)
{
    int removedCount = end - start + 1;
    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } else {
        int toRemove = qMin(m_series->slices().size(), removedCount);     // first find how many items can actually be removed
        int first = qMax(start, m_first);    // get the index of the first item that will be removed.
        int last = qMin(first + toRemove - 1, m_series->slices().size() + m_first - 1);    // get the index of the last item that will be removed.
        for (int i = last; i >= first; i--) {
            m_series->remove(m_series->slices().at(i - m_first));
            m_slices.removeAt(i - m_first);
        }

        if (m_count != -1) {
            int itemsAvailable;     // check how many are available to be added
            if (m_orientation == Qt::Vertical)
                itemsAvailable = m_model->rowCount() - m_first - m_series->slices().size();
            else
                itemsAvailable = m_model->columnCount() - m_first - m_series->slices().size();
            int toBeAdded = qMin(itemsAvailable, m_count - m_series->slices().size());     // add not more items than there is space left to be filled.
            int currentSize = m_series->slices().size();
            if (toBeAdded > 0)
                for (int i = m_series->slices().size(); i < currentSize + toBeAdded; i++) {
                    QPieSlice *slice = new QPieSlice;
                    if (m_orientation == Qt::Vertical) {
                        slice->setValue(m_model->data(m_model->index(i + m_first, m_valuesIndex), Qt::DisplayRole).toDouble());
                        slice->setLabel(m_model->data(m_model->index(i + m_first, m_labelsIndex), Qt::DisplayRole).toString());
                    } else {
                        slice->setValue(m_model->data(m_model->index(m_valuesIndex, i + m_first), Qt::DisplayRole).toDouble());
                        slice->setLabel(m_model->data(m_model->index(m_labelsIndex, i + m_first), Qt::DisplayRole).toString());
                    }
                    slice->setLabelVisible();
                    m_series->insert(i, slice);
                    m_slices.insert(i, slice);
                }
        }
    }
}

void QPieModelMapperPrivate::initializePieFromModel()
{
    if (m_model == 0 || m_series == 0)
        return;

    blockSeriesSignals();
    // clear current content
    m_series->clear();
    m_slices.clear();

    // create the initial slices set
    int slicePos = 0;
    QModelIndex valueIndex = valueModelIndex(slicePos);
    QModelIndex labelIndex = labelModelIndex(slicePos);
    while (valueIndex.isValid() && labelIndex.isValid()) {
        QPieSlice *slice = new QPieSlice;
        slice->setLabel(m_model->data(labelIndex, Qt::DisplayRole).toString());
        slice->setValue(m_model->data(valueIndex, Qt::DisplayRole).toDouble());
        connect(slice, SIGNAL(labelChanged()), this, SLOT(sliceLabelChanged()));
        connect(slice, SIGNAL(valueChanged()), this, SLOT(sliceValueChanged()));
        m_series->append(slice);
        m_slices.append(slice);
//        m_series->append(m_model->data(labelIndex, Qt::DisplayRole).toString(), m_model->data(valueIndex, Qt::DisplayRole).toDouble());
        slicePos++;
        valueIndex = valueModelIndex(slicePos);
        labelIndex = labelModelIndex(slicePos);
    }
    m_series->setLabelsVisible(true);
    blockSeriesSignals(false);
}

#include "moc_qpiemodelmapper_p.cpp"
#include "moc_qpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
