/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
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

#ifndef QLOGVALUEAXIS_P_H
#define QLOGVALUEAXIS_P_H

#include <QtCharts/QLogValueAxis>
#include <private/qabstractaxis_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QLogValueAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
    public:
    QLogValueAxisPrivate(QLogValueAxis *q);
    ~QLogValueAxisPrivate();

    public:
    void initializeGraphics(QGraphicsItem* parent);
    void initializeDomain(AbstractDomain *domain);

    qreal min() { return m_min; }
    qreal max() { return m_max; }
    void setRange(qreal min,qreal max);

    protected:
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);
    void setRange(const QVariant &min, const QVariant &max);
    int tickCount() const;

    protected:
    qreal m_min;
    qreal m_max;
    qreal m_base;
    QString m_format;
    Q_DECLARE_PUBLIC(QLogValueAxis)
};

QT_CHARTS_END_NAMESPACE

#endif // QLOGVALUEAXIS_P_H
