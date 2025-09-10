// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBARMODELMAPPER_P_H
#define QBARMODELMAPPER_P_H

#include <QtCore/QObject>
#include <QtCharts/QBarModelMapper>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QBarSet;

class Q_CHARTS_EXPORT QBarModelMapperPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QBarModelMapperPrivate(QBarModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelHeaderDataUpdated(Qt::Orientation orientation, int first, int last);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);
    void handleModelDestroyed();

    // for the series
    void barSetsAdded(const QList<QBarSet *> &sets);
    void barSetsRemoved(const QList<QBarSet *> &sets);
    void valuesAdded(int index, int count);
    void valuesRemoved(int index, int count);
    void barLabelChanged();
    void barValueChanged(int index);
    void handleSeriesDestroyed();

    void initializeBarFromModel();

private:
    QBarSet *barSet(QModelIndex index);
    QModelIndex barModelIndex(int barSection, int posInBar);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QAbstractBarSeries *m_series;
    QList<QBarSet *> m_barSets;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_firstBarSetSection;
    int m_lastBarSetSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QBarModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QBarModelMapper)
};

QT_END_NAMESPACE

#endif // QBARMODELMAPPER_P_H
