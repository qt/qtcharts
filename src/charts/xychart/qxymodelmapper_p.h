/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
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

#ifndef QXYMODELMAPPER_P_H
#define QXYMODELMAPPER_P_H

#include <QtCharts/QXYModelMapper>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QObject>

QT_BEGIN_NAMESPACE
class QModelIndex;
class QAbstractItemModel;
class QPointF;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE

class QXYModelMapper;
class QXYSeries;

class Q_CHARTS_PRIVATE_EXPORT QXYModelMapperPrivate : public QObject
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
    void handlePointsRemoved(int pointPos, int count);
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

QT_END_NAMESPACE

#endif // QXYMODELMAPPER_P_H
