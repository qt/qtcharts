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

#ifndef QPIELEGENDMARKER_P_H
#define QPIELEGENDMARKER_P_H

#include <QtCharts/QChartGlobal>
#include <private/qlegendmarker_p.h>
#include <private/legendmarkeritem_p.h>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QPieLegendMarker;

class Q_CHARTS_PRIVATE_EXPORT QPieLegendMarkerPrivate : public QLegendMarkerPrivate
{
    Q_OBJECT
public:
    explicit QPieLegendMarkerPrivate(QPieLegendMarker *q, QPieSeries *series, QPieSlice *slice, QLegend *legend);
    virtual ~QPieLegendMarkerPrivate();

    // internal
    QPieSeries* series() override;
    QObject* relatedObject() override;

public Q_SLOTS:
    void updated() override;

private:
    QPieLegendMarker *q_ptr;

    QPieSeries *m_series;
    QPieSlice *m_slice;

    Q_DECLARE_PUBLIC(QPieLegendMarker)
};

QT_END_NAMESPACE

#endif // QPIELEGENDMARKER_P_H
