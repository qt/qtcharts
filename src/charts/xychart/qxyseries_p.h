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

#ifndef QXYSERIES_P_H
#define QXYSERIES_P_H

#include <private/qabstractseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_CHARTS_BEGIN_NAMESPACE

class QXYSeries;
class QAbstractAxis;

class Q_CHARTS_PRIVATE_EXPORT QXYSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QXYSeriesPrivate(QXYSeries *q);

    void initializeDomain();
    void initializeAxes();
    void initializeAnimations(QtCharts::QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve);

    QList<QLegendMarker*> createLegendMarkers(QLegend* legend);

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const;

    void drawSeriesPointLabels(QPainter *painter, const QVector<QPointF> &points,
                               const int offset = 0);

Q_SIGNALS:
    void updated();

protected:
    QVector<QPointF> m_points;
    QPen m_pen;
    QBrush m_brush;
    bool m_pointsVisible;
    QString m_pointLabelsFormat;
    bool m_pointLabelsVisible;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

private:
    Q_DECLARE_PUBLIC(QXYSeries)
    friend class QScatterSeries;
};

QT_CHARTS_END_NAMESPACE

#endif
