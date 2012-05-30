#include "qbarmodelmapper.h"
#include "qbarmodelmapper_p.h"
#include "qbarseries.h"
#include "qbarset.h"
#include <QAbstractItemModel>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarModelMapper::QBarModelMapper(QObject *parent) :
    QObject(parent),
    d_ptr(new QBarModelMapperPrivate(this))
{
}

QAbstractItemModel* QBarModelMapper::model() const
{
    Q_D(const QBarModelMapper);
    return d->m_model;
}

void QBarModelMapper::setModel(QAbstractItemModel *model)
{
    if (model == 0)
        return;

    Q_D(QBarModelMapper);
    if (d->m_model) {
        disconnect(d->m_model, 0, d, 0);
    }

    d->m_model = model;
    d->initializeBarFromModel();
    //    connect signals from the model
    connect(d->m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), d, SLOT(modelUpdated(QModelIndex,QModelIndex)));
    connect(d->m_model, SIGNAL(rowsInserted(QModelIndex,int,int)), d, SLOT(modelRowsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(rowsRemoved(QModelIndex,int,int)), d, SLOT(modelRowsRemoved(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsInserted(QModelIndex,int,int)), d, SLOT(modelColumnsAdded(QModelIndex,int,int)));
    connect(d->m_model, SIGNAL(columnsRemoved(QModelIndex,int,int)), d, SLOT(modelColumnsRemoved(QModelIndex,int,int)));
}

QBarSeries* QBarModelMapper::series() const
{
    Q_D(const QBarModelMapper);
    return d->m_series;
}

void QBarModelMapper::setSeries(QBarSeries *series)
{
    Q_D(QBarModelMapper);
    if (d->m_series) {
        disconnect(d->m_series, 0, d, 0);
    }

    if (series == 0)
        return;

    d->m_series = series;
    d->initializeBarFromModel();
    // connect the signals from the series
    //    connect(d->m_series, SIGNAL(pointAdded(int)), d, SLOT(handlePointAdded(int)));
    //    connect(d->m_series, SIGNAL(pointRemoved(int)), d, SLOT(handlePointRemoved(int)));
    //    connect(d->m_series, SIGNAL(pointReplaced(int)), d, SLOT(handlePointReplaced(int)));
}

int QBarModelMapper::first() const
{
    Q_D(const QBarModelMapper);
    return d->m_first;
}

void QBarModelMapper::setFirst(int first)
{
    Q_D(QBarModelMapper);
    d->m_first = qMax(first, 0);
    d->initializeBarFromModel();
}

int QBarModelMapper::count() const
{
    Q_D(const QBarModelMapper);
    return d->m_count;
}

void QBarModelMapper::setCount(int count)
{
    Q_D(QBarModelMapper);
    d->m_count = qMax(count, -1);
    d->initializeBarFromModel();
}

Qt::Orientation QBarModelMapper::orientation() const
{
    Q_D(const QBarModelMapper);
    return d->m_orientation;
}

void QBarModelMapper::setOrientation(Qt::Orientation orientation)
{
    Q_D(QBarModelMapper);
    d->m_orientation = orientation;
    d->initializeBarFromModel();
}

int QBarModelMapper::firstBarSection() const
{
    Q_D(const QBarModelMapper);
    return d->m_firstBarSection;
}

void QBarModelMapper::setFirstBarSection(int firstBarSection)
{
    Q_D(QBarModelMapper);
    d->m_firstBarSection = firstBarSection;
    d->initializeBarFromModel();
}

int QBarModelMapper::lastBarSection() const
{
    Q_D(const QBarModelMapper);
    return d->m_lastBarSection;
}

void QBarModelMapper::setLastBarSection(int lastBarSection)
{
    Q_D(QBarModelMapper);
    d->m_lastBarSection = lastBarSection;
    d->initializeBarFromModel();
}

int QBarModelMapper::categoriesSection() const
{
    Q_D(const QBarModelMapper);
    return d->m_categoriesSection;
}

void QBarModelMapper::setCategoriesSection(int categoriesSection)
{
    Q_D(QBarModelMapper);
    d->m_categoriesSection = categoriesSection;
    d->initializeBarFromModel();
}

void QBarModelMapper::reset()
{
    Q_D(QBarModelMapper);
    d->m_first = 0;
    d->m_count = -1;
    d->m_orientation = Qt::Vertical;
    d->m_firstBarSection = -1;
    d->m_lastBarSection = -1;
    d->m_categoriesSection = -1;
    d->initializeBarFromModel();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarModelMapperPrivate::QBarModelMapperPrivate(QBarModelMapper *q) :
    m_series(0),
    m_model(0),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_firstBarSection(-1),
    m_lastBarSection(-1),
    m_categoriesSection(-1),
    m_seriesSignalsBlock(false),
    m_modelSignalsBlock(false),
    q_ptr(q)
{
}

void QBarModelMapperPrivate::blockModelSignals(bool block)
{
    m_modelSignalsBlock = block;
}

void QBarModelMapperPrivate::blockSeriesSignals(bool block)
{
    m_seriesSignalsBlock = block;
}

QBarSet* QBarModelMapperPrivate::barSet(QModelIndex index)
{
    if (!index.isValid())
        return 0;

    if (m_orientation == Qt::Vertical && index.column() >= m_firstBarSection && index.column() <= m_lastBarSection) {
        if (index.row() >= m_first && (m_count == - 1 || index.row() < m_first + m_count))
            return m_series->barSets().at(index.column() - m_firstBarSection);
    } else if (m_orientation == Qt::Horizontal && index.row() >= m_firstBarSection && index.row() <= m_lastBarSection) {
        if (index.column() >= m_first && (m_count == - 1 || index.column() < m_first + m_count))
            return m_series->barSets().at(index.row() - m_firstBarSection);
    }
    return 0; // This part of model has not been mapped to any slice
}

QModelIndex QBarModelMapperPrivate::barModelIndex(int barSection, int posInBar)
{
    if (m_count != -1 && posInBar >= m_count)
        return QModelIndex(); // invalid

    if (barSection < m_firstBarSection || barSection > m_lastBarSection)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(posInBar + m_first, barSection);
    else
        return m_model->index(barSection, posInBar + m_first);
}

QModelIndex QBarModelMapperPrivate::categoriesModelIndex(int posInCategories)
{
    if (m_count != -1 && posInCategories >= m_count)
        return QModelIndex(); // invalid

    if (m_orientation == Qt::Vertical)
        return m_model->index(posInCategories + m_first, m_categoriesSection);
    else
        return m_model->index(m_categoriesSection, posInCategories + m_first);
}

void QBarModelMapperPrivate::modelUpdated(QModelIndex topLeft, QModelIndex bottomRight)
{
    Q_UNUSED(topLeft)
    Q_UNUSED(bottomRight)

    if (m_model == 0 || m_series == 0)
        return;

    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    QModelIndex index;
    //    QPointF oldPoint;
    //    QPointF newPoint;
    for (int row = topLeft.row(); row <= bottomRight.row(); row++) {
        for (int column = topLeft.column(); column <= bottomRight.column(); column++) {
            index = topLeft.sibling(row, column);
            QBarSet* bar = barSet(index);
            if (bar) {
                if (m_orientation == Qt::Vertical)
                    bar->replace(row - m_first, m_model->data(index).toReal());
                else
                    bar->replace(column - m_first, m_model->data(index).toReal());
            }
        }
    }
    blockSeriesSignals(false);
}

void QBarModelMapperPrivate::modelRowsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(end)
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        //        insertData(start, end);
        initializeBarFromModel();
    else if (start <= m_firstBarSection || start <= m_lastBarSection || start <= m_categoriesSection) // if the changes affect the map - reinitialize
        initializeBarFromModel();
    blockSeriesSignals(false);
}

void QBarModelMapperPrivate::modelRowsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(end)
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Vertical)
        //        removeData(start, end);
        initializeBarFromModel();
    else if (start <= m_firstBarSection || start <= m_lastBarSection || start <= m_categoriesSection) // if the changes affect the map - reinitialize
        initializeBarFromModel();
    blockSeriesSignals(false);
}

void QBarModelMapperPrivate::modelColumnsAdded(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(end)
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        //        insertData(start, end);
        initializeBarFromModel();
    else if (start <= m_firstBarSection || start <= m_lastBarSection || start <= m_categoriesSection) // if the changes affect the map - reinitialize
        initializeBarFromModel();
    blockSeriesSignals(false);
}

void QBarModelMapperPrivate::modelColumnsRemoved(QModelIndex parent, int start, int end)
{
    Q_UNUSED(parent);
    Q_UNUSED(end)
    if (m_modelSignalsBlock)
        return;

    blockSeriesSignals();
    if (m_orientation == Qt::Horizontal)
        //        removeData(start, end);
        initializeBarFromModel();
    else if (start <= m_firstBarSection || start <= m_lastBarSection || start <= m_categoriesSection) // if the changes affect the map - reinitialize
        initializeBarFromModel();
    blockSeriesSignals(false);
}

void QBarModelMapperPrivate::insertData(int start, int end)
{
    Q_UNUSED(end)
    if (m_model == 0 || m_series == 0)
        return;

    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } /*else {
        int addedCount = end - start + 1;
        if (m_count != -1 && addedCount > m_count)
            addedCount = m_count;
        int first = qMax(start, m_first);
        int last = qMin(first + addedCount - 1, m_orientation == Qt::Vertical ? m_model->rowCount() - 1 : m_model->columnCount() - 1);
        for (int k = 0; k < m_series->barSets().count(); k++) {
            for (int i = first; i <= last; i++) {
                QBar point;
                point.setX(m_model->data(xModelIndex(i - m_first), Qt::DisplayRole).toDouble());
                point.setY(m_model->data(yModelIndex(i - m_first), Qt::DisplayRole).toDouble());
                m_series->insert(i - m_first, point);
            }
        }

        // remove excess of slices (abouve m_count)
        if (m_count != -1 && m_series->points().size() > m_count)
            for (int i = m_series->points().size() - 1; i >= m_count; i--) {
                m_series->remove(m_series->points().at(i));
            }
    }*/
}

void QBarModelMapperPrivate::removeData(int start, int end)
{
    Q_UNUSED(end)
    if (m_model == 0 || m_series == 0)
        return;

    //    int removedCount = end - start + 1;
    if (m_count != -1 && start >= m_first + m_count) {
        return;
    } /*else {
        int toRemove = qMin(m_series->count(), removedCount);     // first find how many items can actually be removed
        int first = qMax(start, m_first);    // get the index of the first item that will be removed.
        int last = qMin(first + toRemove - 1, m_series->count() + m_first - 1);    // get the index of the last item that will be removed.
        for (int i = last; i >= first; i--) {
            m_series->remove(m_series->points().at(i - m_first));
        }

        if (m_count != -1) {
            int itemsAvailable;     // check how many are available to be added
            if (m_orientation == Qt::Vertical)
                itemsAvailable = m_model->rowCount() - m_first - m_series->count();
            else
                itemsAvailable = m_model->columnCount() - m_first - m_series->count();
            int toBeAdded = qMin(itemsAvailable, m_count - m_series->count());     // add not more items than there is space left to be filled.
            int currentSize = m_series->count();
            if (toBeAdded > 0)
                for (int i = m_series->count(); i < currentSize + toBeAdded; i++) {
                    QPointF point;
                    point.setX(m_model->data(xModelIndex(i), Qt::DisplayRole).toDouble());
                    point.setY(m_model->data(yModelIndex(i), Qt::DisplayRole).toDouble());
                    m_series->insert(i, point);
                }
        }
    }*/
}

void QBarModelMapperPrivate::initializeBarFromModel()
{
    if (m_model == 0 || m_series == 0)
        return;

    blockSeriesSignals();
    // clear current content
    m_series->clear();

    // create the initial bar sets
    for (int i = m_firstBarSection; i <= m_lastBarSection; i++) {
        int posInBar = 0;
        QModelIndex barIndex = barModelIndex(i, posInBar);
        QBarSet *barSet = new QBarSet(m_model->headerData(i, Qt::Horizontal).toString());
        //    QModelIndex yIndex = yModelIndex(pointPos);
        while (barIndex.isValid()) {
            barSet->append(m_model->data(barIndex, Qt::DisplayRole).toDouble());
            posInBar++;
            barIndex = barModelIndex(i, posInBar);
        }
        m_series->append(barSet);
    }

    if (m_categoriesSection != -1) {
        int posInCategories = 0;
        QStringList categories;
        QModelIndex categoriesIndex = categoriesModelIndex(posInCategories);
        while (categoriesIndex.isValid()) {
            categories.append(m_model->data(categoriesIndex, Qt::DisplayRole).toString());
            posInCategories++;
            categoriesIndex = categoriesModelIndex(posInCategories);
        }
        m_series->setCategories(categories);
    }
    blockSeriesSignals(false);
}

#include "moc_qbarmodelmapper.cpp"
#include "moc_qbarmodelmapper_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
