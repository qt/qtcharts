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

#include "qvalueaxis.h"
#include "qabstractaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QValueAxisPrivate : public QAbstractAxisPrivate
{
    Q_OBJECT
public:
    QValueAxisPrivate(QValueAxis *q);
    ~QValueAxisPrivate();

public:
    ChartAxis* createGraphics(ChartPresenter* presenter);
    void intializeDomain(Domain* domain);
    void handleDomainUpdated();
    qreal min(){ return m_min; };
    qreal max(){ return m_max; };
    int count() const { return m_tickCount;}

protected:
    void setMin(const QVariant &min);
    void setMax(const QVariant &max);
    void setRange(const QVariant &min, const QVariant &max);

private:
    void looseNiceNumbers(qreal &min, qreal &max, int &ticksCount) const;
    qreal niceNumber(qreal x,bool ceiling) const;

private:
    qreal m_min;
    qreal m_max;
    int m_tickCount;
    bool m_niceNumbers;
    Q_DECLARE_PUBLIC(QValueAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVALUESAXIS_P_H
