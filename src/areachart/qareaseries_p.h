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

#ifndef QAREASERIES_P_H
#define QAREASERIES_P_H

#include "qabstractseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAreaSeries;

class QAreaSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QAreaSeriesPrivate(QLineSeries *upperSeries, QLineSeries *lowerSeries,QAreaSeries* q);

    void scaleDomain(Domain& domain);
    Chart* createGraphics(ChartPresenter* presenter);
    QList<LegendMarker*> createLegendMarker(QLegend* legend);
    QAbstractAxis* createAxisX();
    QAbstractAxis* createAxisY();

Q_SIGNALS:
    void updated();

protected:
    QBrush m_brush;
    QPen m_pen;
    QLineSeries* m_upperSeries;
    QLineSeries* m_lowerSeries;
    bool m_pointsVisible;
private:
    Q_DECLARE_PUBLIC(QAreaSeries);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
