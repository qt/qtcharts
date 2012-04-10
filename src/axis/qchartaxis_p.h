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

#ifndef QCHARTAXIS_P_H_
#define QCHARTAXIS_P_H_

#include "qchartaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartAxisPrivate : public QObject
{
    Q_OBJECT
public:
    QChartAxisPrivate(QChartAxis *q);
    ~QChartAxisPrivate();

Q_SIGNALS:
    void updated();
    void changed(qreal min, qreal max, int tickCount,bool niceNumbers);

public Q_SLOTS:
    void handleAxisRangeChanged(qreal min, qreal max,int count);

private:
    QChartAxis *q_ptr;

    bool m_axisVisible;
    QPen m_axisPen;
    QBrush m_axisBrush;

    bool m_gridLineVisible;
    QPen m_gridLinePen;

    bool m_labelsVisible;
    QPen m_labelsPen;
    QBrush m_labelsBrush;
    QFont m_labelsFont;
    int m_labelsAngle;

    bool m_shadesVisible;
    QPen m_shadesPen;
    QBrush m_shadesBrush;
    qreal m_shadesOpacity;

    qreal m_min;
    qreal m_max;

    int m_ticksCount;
    QChartAxisCategories m_category;

    bool m_niceNumbers;

    friend class QChartAxis;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
