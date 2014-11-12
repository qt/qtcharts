/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QXYMODELMAPPER_P_H
#define QXYMODELMAPPER_P_H

#include <QtCharts/QXYModelMapper>
#include <QtCore/QObject>

class QModelIndex;
class QAbstractItemModel;
class QPointF;

QT_CHARTS_BEGIN_NAMESPACE

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
    void handleModelDestroyed();

    // for the series
    void handlePointAdded(int pointPos);
    void handlePointRemoved(int pointPos);
    void handlePointReplaced(int pointPos);
    void handleSeriesDestroyed();

    void initializeXYFromModel();

private:
    QModelIndex xModelIndex(int xPos);
    QModelIndex yModelIndex(int yPos);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);
    qreal valueFromModel(QModelIndex index);
    void setValueToModel(QModelIndex index, qreal value);

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

QT_CHARTS_END_NAMESPACE

#endif // QXYMODELMAPPER_P_H
