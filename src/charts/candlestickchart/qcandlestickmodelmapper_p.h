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

#ifndef QCANDLESTICKMODELMAPPER_P_H
#define QCANDLESTICKMODELMAPPER_P_H

#include <QtCharts/QCandlestickModelMapper>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QCandlestickSet;

class Q_CHARTS_EXPORT QCandlestickModelMapperPrivate : public QObject
{
    Q_OBJECT

public:
    explicit QCandlestickModelMapperPrivate(QCandlestickModelMapper *q);

Q_SIGNALS:
    void timestampChanged();
    void openChanged();
    void highChanged();
    void lowChanged();
    void closeChanged();
    void firstSetSectionChanged();
    void lastSetSectionChanged();

private Q_SLOTS:
    void initializeCandlestickFromModel();

    // for the model
    void modelDataUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelHeaderDataUpdated(Qt::Orientation orientation, int first, int last);
    void modelRowsInserted(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsInserted(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);
    void modelDestroyed();

    // for the series
    void candlestickSetsAdded(const QList<QCandlestickSet *> &sets);
    void candlestickSetsRemoved(const QList<QCandlestickSet *> &sets);
    void candlestickSetChanged();
    void seriesDestroyed();

private:
    QCandlestickSet *candlestickSet(QModelIndex index);
    QModelIndex candlestickModelIndex(int section, int pos);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QAbstractItemModel *m_model;
    QCandlestickSeries *m_series;
    int m_timestamp;
    int m_open;
    int m_high;
    int m_low;
    int m_close;
    int m_firstSetSection;
    int m_lastSetSection;
    QList<QCandlestickSet *> m_sets;
    bool m_modelSignalsBlock;
    bool m_seriesSignalsBlock;

private:
    QCandlestickModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QCandlestickModelMapper)
};

QT_END_NAMESPACE

#endif // QCANDLESTICKMODELMAPPER_P_H
