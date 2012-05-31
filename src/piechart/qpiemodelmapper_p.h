/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QPIEMODELMAPPER_P_H
#define QPIEMODELMAPPER_P_H

#include "qpiemodelmapper.h"
#include <QObject>

class QModelIndex;
class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapper;
class QPieSeries;
class QPieSlice;

class QPieModelMapperPrivate : public QObject
{
    Q_OBJECT

public:
    QPieModelMapperPrivate(QPieModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);

    // for the series
    void slicesAdded(QList<QPieSlice*> slices);
    void slicesRemoved(QList<QPieSlice*> slices);
    void sliceLabelChanged();
    void sliceValueChanged();

    void initializePieFromModel();

private:
    QPieSlice* pieSlice(QModelIndex index) const;
    bool isLabelIndex(QModelIndex index) const;
    bool isValueIndex(QModelIndex index) const;
    QModelIndex valueModelIndex(int slicePos);
    QModelIndex labelModelIndex(int slicePos);
    void insertData(int start, int end);
    void removeData(int start, int end);

    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QPieSeries *m_series;
    QList<QPieSlice*> m_slices;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_valuesSection;
    int m_labelsSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:

    QPieModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QPieModelMapper)
    friend class QPieSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_P_H
