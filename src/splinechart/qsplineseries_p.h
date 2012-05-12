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

#ifndef QSPLINESERIES_P_H
#define QSPLINESERIES_P_H

#include "qlineseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE


class QSplineSeriesPrivate: public QLineSeriesPrivate
{
    Q_OBJECT
public:
    Chart* createGraphics(ChartPresenter* presenter);
    QSplineSeriesPrivate(QSplineSeries* q);

    QPointF controlPoint(int index) const;

public Q_SLOTS:
    void updateControlPoints();

protected Q_SLOTS:
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);

private:
    void calculateControlPoints();
    QVector<qreal> firstControlPoints(const QVector<qreal>& vector);

public:
    QVector<QPointF> m_controlPoints;
private:
    Q_DECLARE_PUBLIC(QSplineSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
