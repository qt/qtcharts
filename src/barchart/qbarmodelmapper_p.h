#ifndef QBARMODELMAPPER_P_H
#define QBARMODELMAPPER_P_H

#include "qchartglobal.h"
#include <QObject>
#include "qbarmodelmapper.h"

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSet;

class QBarModelMapperPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QBarModelMapperPrivate(QBarModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);

//    // for the series
//    void handlePointAdded(int pointPos);
//    void handlePointRemoved(int pointPos);
//    void handlePointReplaced(int pointPos);

    void initializeBarFromModel();

private:
    QBarSet* barSet(QModelIndex index);
    QModelIndex barModelIndex(int barSection, int posInBar);
    QModelIndex categoriesModelIndex(int posInCategories);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QBarSeries *m_series;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_firstBarSection;
    int m_lastBarSection;
    int m_categoriesSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QBarModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QBarModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARMODELMAPPER_P_H
