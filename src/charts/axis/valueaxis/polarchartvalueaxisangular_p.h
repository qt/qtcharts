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

#ifndef POLARCHARTVALUEAXISANGULAR_P_H
#define POLARCHARTVALUEAXISANGULAR_P_H

#include <private/polarchartaxisangular_p.h>
#include <QtCharts/QValueAxis>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QValueAxis;

class Q_CHARTS_EXPORT PolarChartValueAxisAngular : public PolarChartAxisAngular
{
    Q_OBJECT
public:
    PolarChartValueAxisAngular(QValueAxis *axis, QGraphicsItem *item);
    ~PolarChartValueAxisAngular();

    QList<qreal> calculateLayout() const override;
    void createAxisLabels(const QList<qreal> &layout) override;

private Q_SLOTS:
    void handleTickCountChanged(int tick);
    void handleMinorTickCountChanged(int tick);
    void handleLabelFormatChanged(const QString &format);
};

QT_END_NAMESPACE

#endif // POLARCHARTVALUEAXISANGULAR_P_H
