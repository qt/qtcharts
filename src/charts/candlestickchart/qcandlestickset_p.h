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

#ifndef QCANDLESTICKSET_P_H
#define QCANDLESTICKSET_P_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtGui/QBrush>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE

class QCandlestickSeriesPrivate;
class QCandlestickSet;

class Q_CHARTS_EXPORT QCandlestickSetPrivate : public QObject
{
    Q_OBJECT

public:
    QCandlestickSetPrivate(qreal timestamp, QCandlestickSet *parent);
    ~QCandlestickSetPrivate();

    bool setTimestamp(qreal timestamp);

Q_SIGNALS:
    void updatedLayout();
    void updatedCandlestick();

private:
    QCandlestickSet *q_ptr;
    qreal m_timestamp;
    qreal m_open;
    qreal m_high;
    qreal m_low;
    qreal m_close;
    QBrush m_brush;
    QPen m_pen;
    QCandlestickSeriesPrivate *m_series;

private:
    Q_DECLARE_PUBLIC(QCandlestickSet)
    friend class QCandlestickSeriesPrivate;
};

QT_END_NAMESPACE

#endif // QCANDLESTICKSET_P_H
