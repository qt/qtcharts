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

#ifndef QIntervalsAxis_P_H
#define QIntervalsAxis_P_H

#include "qintervalsaxis.h"
#include "qvalueaxis_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QPair<qreal, qreal> Range;

class QIntervalsAxisPrivate : public QValueAxisPrivate
{
    Q_OBJECT

public:
    QIntervalsAxisPrivate(QIntervalsAxis *q);
    ~QIntervalsAxisPrivate();


public:
    ChartAxis* createGraphics(ChartPresenter* presenter);
    int ticksCount() const;

Q_SIGNALS:
    void changed(qreal min, qreal max, int tickCount,bool niceNumbers);

public Q_SLOTS:
    void handleAxisRangeChanged(qreal min, qreal max,int count);

private:
    QMap<QString , Range> m_intervalsMap;
    QStringList m_intervals;
    qreal m_categoryMinimum;

private:
    Q_DECLARE_PUBLIC(QIntervalsAxis)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCATEGORIESAXIS_P_H
