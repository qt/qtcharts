/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

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

QT_CHARTS_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT QBoxSet;

class QBoxPlotModelMapperPrivate : public QObject
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
    void boxSetsAdded(QList<QBoxSet *> sets);
    void boxSetsRemoved(QList<QBoxSet *> sets);
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

QT_CHARTS_END_NAMESPACE

#endif // QBOXPLOTMODELMAPPER_P_H
