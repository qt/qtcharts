#ifndef QXYMODELMAPPER_P_H
#define QXYMODELMAPPER_P_H

#include "qxymodelmapper.h"
#include <QObject>

class QModelIndex;
class QAbstractItemModel;
class QPointF;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYModelMapper;
class QXYSeries;

class QXYModelMapperPrivate : public QObject
{
    Q_OBJECT

public:
    QXYModelMapperPrivate(QXYModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);

    // for the series
    void handlePointAdded(int pointPos);
    void handlePointRemoved(int pointPos);
    void handlePointReplaced(int pointPos);

    void initializeXYFromModel();

private:
    QModelIndex xModelIndex(int xPos);
    QModelIndex yModelIndex(int yPos);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QXYSeries *m_series;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_xSection;
    int m_ySection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QXYModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QXYModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYMODELMAPPER_P_H
