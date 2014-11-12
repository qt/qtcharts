/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
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
