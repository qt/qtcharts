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

#ifndef POLARCHARTVALUEAXISRADIAL_P_H
#define POLARCHARTVALUEAXISRADIAL_P_H

#include <private/polarchartaxisradial_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QValueAxis;

class Q_CHARTS_EXPORT PolarChartValueAxisRadial : public PolarChartAxisRadial
{
    Q_OBJECT
public:
    PolarChartValueAxisRadial(QValueAxis *axis, QGraphicsItem *item);
    ~PolarChartValueAxisRadial();

    QList<qreal> calculateLayout() const override;
    void createAxisLabels(const QList<qreal> &layout) override;

private Q_SLOTS:
    void handleTickCountChanged(int tick);
    void handleMinorTickCountChanged(int tick);
    void handleLabelFormatChanged(const QString &format);
};

QT_END_NAMESPACE

#endif // POLARCHARTVALUEAXISRADIAL_P_H
