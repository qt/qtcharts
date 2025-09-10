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

#ifndef QPIESERIES_P_H
#define QPIESERIES_P_H

#include <QtCharts/QPieSeries>
#include <private/qabstractseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE
class QLegendPrivate;

class Q_CHARTS_EXPORT QPieSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QPieSeriesPrivate(QPieSeries *parent);
    ~QPieSeriesPrivate();

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeAnimations(QChart::AnimationOptions options, int duration,
                              QEasingCurve &curve) override;
    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;

    QList<QLegendMarker *> createLegendMarkers(QLegend *legend) override;

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const override;

    void updateDerivativeData();
    void setSizes(qreal innerSize, qreal outerSize);

    static QPieSeriesPrivate *fromSeries(QPieSeries *series);

Q_SIGNALS:
    void calculatedDataChanged();
    void pieSizeChanged();
    void pieStartAngleChanged();
    void pieEndAngleChanged();
    void horizontalPositionChanged();
    void verticalPositionChanged();

public Q_SLOTS:
    void sliceValueChanged();
    void sliceClicked();
    void sliceHovered(bool state);
    void slicePressed();
    void sliceReleased();
    void sliceDoubleClicked();

private:
    QList<QPieSlice *> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_sum;
    qreal m_holeRelativeSize;

public:
    friend class QLegendPrivate;
    Q_DECLARE_PUBLIC(QPieSeries)
};

QT_END_NAMESPACE

#endif // QPIESERIES_P_H
