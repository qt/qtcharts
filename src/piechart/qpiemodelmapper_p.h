#ifndef QPIEMODELMAPPER_P_H
#define QPIEMODELMAPPER_P_H

#include "qpiemodelmapper.h"
#include <QObject>

class QModelIndex;
class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapper;
class QPieSeries;

class QPieModelMapperPrivate : public QObject
{
    Q_OBJECT

public:
    QPieModelMapperPrivate(QPieModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
//    void modelRowsAdded(QModelIndex parent, int start, int end);
//    void modelRowsRemoved(QModelIndex parent, int start, int end);
//    void modelColumnsAdded(QModelIndex parent, int start, int end);
//    void modelColumnsRemoved(QModelIndex parent, int start, int end);

    // for the series
    void slicesAdded();
    void slicesRemoved();
    void sliceChanged();

private:
    void setModel(QAbstractItemModel *model);

private:
    int getSliceIndex();

private:
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_mapValues;
    int m_mapLabels;

private:
    QPieSeries *m_series;
    QAbstractItemModel *m_model;
    QPieModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QPieModelMapper)
    friend class QPieSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_P_H
