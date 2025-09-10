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

#ifndef QDATETIMEAXIS_P_H
#define QDATETIMEAXIS_P_H

#include <QtCharts/QDateTimeAxis>
#include <QtCharts/private/qchartglobal_p.h>
#include <private/qabstractaxis_p.h>
#include <QtCore/QDateTime>

QT_BEGIN_NAMESPACE

class Q_CHARTS_EXPORT QDateTimeAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    QDateTimeAxisPrivate(QDateTimeAxis *q);
    ~QDateTimeAxisPrivate();

public:
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeDomain(AbstractDomain *domain) override;

    //interface for manipulating range form base class
    void setMin(const QVariant &min) override;
    void setMax(const QVariant &max) override;
    void setRange(const QVariant &min, const QVariant &max) override;

    //interface manipulating range form domain
    qreal min() override { return m_min; }
    qreal max() override { return m_max; }
    void setRange(qreal min,qreal max) override;

protected:
    int tickCount() const;

protected:
    qreal m_min;
    qreal m_max;
    int m_tickCount;
    QString m_format;
    Q_DECLARE_PUBLIC(QDateTimeAxis)
};

QT_END_NAMESPACE

#endif // QDATETIMEAXIS_P_H
