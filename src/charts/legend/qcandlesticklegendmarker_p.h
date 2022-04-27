/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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
******************************************************************************/

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

class Q_CHARTS_PRIVATE_EXPORT QCandlestickLegendMarkerPrivate : public QLegendMarkerPrivate
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
