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
    int m_firstBarSetSection;
    int m_lastBarSetSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QBarModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QBarModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARMODELMAPPER_P_H
