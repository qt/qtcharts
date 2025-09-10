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

#ifndef QBOXPLOTMODELMAPPER_P_H
#define QBOXPLOTMODELMAPPER_P_H

#include <QtCore/QObject>
#include <QtCharts/QBoxPlotModelMapper>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QBoxSet;

class Q_CHARTS_EXPORT QBoxPlotModelMapperPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QBoxPlotModelMapperPrivate(QBoxPlotModelMapper *q);

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
    void boxSetsAdded(const QList<QBoxSet *> &sets);
    void boxSetsRemoved(const QList<QBoxSet *> &sets);
    void boxValueChanged(int index);
    void handleSeriesDestroyed();

    void initializeBoxFromModel();

private:
    QBoxSet *boxSet(QModelIndex index);
    QModelIndex boxModelIndex(int boxSection, int posInBox);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QBoxPlotSeries *m_series;
    QList<QBoxSet *> m_boxSets;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_firstBoxSetSection;
    int m_lastBoxSetSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QBoxPlotModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QBoxPlotModelMapper)
};

QT_END_NAMESPACE

#endif // QBOXPLOTMODELMAPPER_P_H
