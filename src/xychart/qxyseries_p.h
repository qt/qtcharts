/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
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
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QXYSERIES_P_H
#define QXYSERIES_P_H

#include "qabstractseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QXYSeries;
class QAbstractAxis;

class QXYSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QXYSeriesPrivate(QXYSeries *q);

    void initializeDomain();
    void initializeAxes();
    void initializeAnimations(QtCommercialChart::QChart::AnimationOptions options);

    QList<QLegendMarker*> createLegendMarkers(QLegend* legend);

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const;

Q_SIGNALS:
    void updated();

protected:
    QVector<QPointF> m_points;
    QPen m_pen;
    QBrush m_brush;
    bool m_pointsVisible;

private:
    Q_DECLARE_PUBLIC(QXYSeries)
    friend class QScatterSeries;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
