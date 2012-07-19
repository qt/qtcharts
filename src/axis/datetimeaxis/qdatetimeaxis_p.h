/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QVALUESAXIS_P_H
#define QVALUESAXIS_P_H

#include "qdatetimeaxis.h"
#include "qabstractaxis_p.h"
#include <QDateTime>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QDateTimeAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
    public:
    QDateTimeAxisPrivate(QDateTimeAxis *q);
    ~QDateTimeAxisPrivate();

    public:
    ChartAxis* createGraphics(ChartPresenter* presenter);
    void intializeDomain(Domain* domain);
    void handleDomainUpdated();
    qreal min(){ return m_min.toMSecsSinceEpoch(); }
    qreal max(){ return m_max.toMSecsSinceEpoch(); }

    protected:
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);
    void setRange(const QVariant &min, const QVariant &max);
    int ticksCount() const;

    protected:
    QDateTime m_min;
    QDateTime m_max;
    int m_tickCount;
    QString m_format;
    Q_DECLARE_PUBLIC(QDateTimeAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVALUESAXIS_P_H
