// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QCANDLESTICKLEGENDMARKER_H
#define QCANDLESTICKLEGENDMARKER_H

#include <QtCharts/QCandlestickSeries>
#include <QtCharts/QLegendMarker>

QT_BEGIN_NAMESPACE

class QCandlestickLegendMarkerPrivate;

class Q_CHARTS_EXPORT QCandlestickLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QCandlestickLegendMarker(QCandlestickSeries *series, QLegend *legend,
                                      QObject *parent = nullptr);
    virtual ~QCandlestickLegendMarker();

    LegendMarkerType type() override;

    // Related series
    QCandlestickSeries* series() override;

private:
    Q_DECLARE_PRIVATE(QCandlestickLegendMarker)
    Q_DISABLE_COPY(QCandlestickLegendMarker)
};

QT_END_NAMESPACE

#endif // QCANDLESTICKLEGENDMARKER_H
