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

#ifndef QLOGVALUEAXIS_P_H
#define QLOGVALUEAXIS_P_H

#include <QtCharts/qlogvalueaxis.h>
#include <private/qabstractaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT QLogValueAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
    public:
    QLogValueAxisPrivate(QLogValueAxis *q);
    ~QLogValueAxisPrivate();

    public:
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(AbstractDomain *domain) override;

    qreal min() override { return m_min; }
    qreal max() override { return m_max; }
    void setRange(qreal min,qreal max) override;

    void updateTickCount();

    protected:
    void setMin(const QVariant &min) override;
    void setMax(const QVariant &max) override;
    void setRange(const QVariant &min, const QVariant &max) override;

    protected:
    qreal m_min;
    qreal m_max;
    qreal m_base;
    int m_tickCount;
    int m_minorTickCount;
    QString m_labelFormat;
    Q_DECLARE_PUBLIC(QLogValueAxis)
};

QT_END_NAMESPACE

#endif // QLOGVALUEAXIS_P_H
