// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QAREASERIES_P_H
#define QAREASERIES_P_H

#include <private/qabstractseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QAreaSeries;
class QLineSeries;

class Q_CHARTS_EXPORT QAreaSeriesPrivate: public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QAreaSeriesPrivate(QLineSeries *upperSeries, QLineSeries *lowerSeries, QAreaSeries *q);

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve) override;

    QList<QLegendMarker *> createLegendMarkers(QLegend *legend) override;

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis* createDefaultAxis(Qt::Orientation) const override;

Q_SIGNALS:
    void updated();

protected:
    QBrush m_brush;
    QPen m_pen;
    QLineSeries *m_upperSeries;
    QLineSeries *m_lowerSeries;
    bool m_pointsVisible;
    QString m_pointLabelsFormat;
    bool m_pointLabelsVisible;
    QFont m_pointLabelsFont;
    QColor m_pointLabelsColor;
    bool m_pointLabelsClipping;

private:
    Q_DECLARE_PUBLIC(QAreaSeries);
};

QT_END_NAMESPACE

#endif
