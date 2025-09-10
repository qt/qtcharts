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

#ifndef QCANDLESTICKLEGENDMARKER_P_H
#define QCANDLESTICKLEGENDMARKER_P_H

#include <private/qlegendmarker_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QCandlestickLegendMarker;
class QCandlestickSeries;

class Q_CHARTS_EXPORT QCandlestickLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QCandlestickLegendMarkerPrivate(QCandlestickLegendMarker *q,
                                             QCandlestickSeries *series, QLegend *legend);
    virtual ~QCandlestickLegendMarkerPrivate();

    QAbstractSeries *series() override;
    QObject *relatedObject() override;

public Q_SLOTS:
    void updated() override;

private:
    QCandlestickLegendMarker *q_ptr;
    QCandlestickSeries *m_series;

    Q_DECLARE_PUBLIC(QCandlestickLegendMarker)
};

QT_END_NAMESPACE

#endif // QCANDLESTICKLEGENDMARKER_P_H
