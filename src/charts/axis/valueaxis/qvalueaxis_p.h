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

#ifndef QVALUEAXIS_P_H
#define QVALUEAXIS_P_H

#include <QtCharts/QValueAxis>
#include <private/qabstractaxis_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT QValueAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    QValueAxisPrivate(QValueAxis *q);
    ~QValueAxisPrivate();

public:
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(AbstractDomain *domain) override;

    qreal min() override { return m_min; }
    qreal max() override { return m_max; }
    void setRange(qreal min,qreal max) override;

    qreal tickInterval() { return m_tickInterval; }
    qreal tickAnchor() { return m_tickAnchor; }

protected:
    void setMin(const QVariant &min) override;
    void setMax(const QVariant &max) override;
    void setRange(const QVariant &min, const QVariant &max) override;

private:
    qreal m_min;
    qreal m_max;
    int m_tickCount;
    int m_minorTickCount;
    QString m_format;
    bool m_applying;
    qreal m_tickInterval;
    qreal m_tickAnchor;
    QValueAxis::TickType m_tickType;
    Q_DECLARE_PUBLIC(QValueAxis)
};

QT_END_NAMESPACE

#endif // QVALUEAXIS_P_H
