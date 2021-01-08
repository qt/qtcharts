/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

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

QT_CHARTS_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT QValueAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    QValueAxisPrivate(QValueAxis *q);
    ~QValueAxisPrivate();

public:
    void initializeGraphics(QGraphicsItem* parent);
    void initializeDomain(AbstractDomain *domain);

    qreal min() { return m_min; }
    qreal max() { return m_max; }
    void setRange(qreal min,qreal max);

    qreal tickInterval() { return m_tickInterval; }
    qreal tickAnchor() { return m_tickAnchor; }

protected:
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);
    void setRange(const QVariant &min, const QVariant &max);

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

QT_CHARTS_END_NAMESPACE

#endif // QVALUEAXIS_P_H
