// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QCOLORAXIS_P_H
#define QCOLORAXIS_P_H

#include <QtCharts/QColorAxis>
#include <private/qabstractaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT QColorAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    explicit QColorAxisPrivate(QColorAxis *q);
    ~QColorAxisPrivate();

    void initializeGraphics(QGraphicsItem *parent) override;
    void initializeDomain(AbstractDomain *domain) override;

    qreal min() override { return m_min; }
    qreal max() override { return m_max; }
    void setRange(qreal min,qreal max) override;

    void updateSeries();

protected:
    void setMin(const QVariant &min) override;
    void setMax(const QVariant &max) override;
    void setRange(const QVariant &min, const QVariant &max) override;

private:
    qreal m_min;
    qreal m_max;
    int m_tickCount;
    qreal m_size;
    bool m_autoRange;
    QLinearGradient m_gradient;
    Q_DECLARE_PUBLIC(QColorAxis)
};

QT_END_NAMESPACE

#endif // QCOLORAXIS_P_H
