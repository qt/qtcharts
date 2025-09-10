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

#ifndef QCANDLESTICKSERIES_P_H
#define QCANDLESTICKSERIES_P_H

#include <private/qabstractseries_p.h>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class CandlestickAnimation;
class QBarCategoryAxis;
class QCandlestickSeries;
class QCandlestickSet;
class QDateTimeAxis;

class Q_CHARTS_EXPORT QCandlestickSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QCandlestickSeriesPrivate(QCandlestickSeries *q);
    ~QCandlestickSeriesPrivate();

    void initializeDomain() override;
    void initializeAxes() override;
    void initializeTheme(int index, ChartTheme* theme, bool forced = false) override;
    void initializeGraphics(QGraphicsItem* parent) override;
    void initializeAnimations(QChart::AnimationOptions options, int duration, QEasingCurve &curve) override;

    QList<QLegendMarker *> createLegendMarkers(QLegend *legend) override;

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis *createDefaultAxis(Qt::Orientation orientation) const override;

    bool append(const QList<QCandlestickSet *> &sets);
    bool remove(const QList<QCandlestickSet *> &sets);
    bool insert(int index, QCandlestickSet *set);

Q_SIGNALS:
    void clicked(int index, QCandlestickSet *set);
    void pressed(int index, QCandlestickSet *set);
    void released(int index, QCandlestickSet *set);
    void doubleClicked(int index, QCandlestickSet *set);
    void updated();
    void updatedLayout();
    void updatedCandlesticks();

private Q_SLOTS:
    void handleSeriesChange(QAbstractSeries *series);
    void handleSeriesRemove(QAbstractSeries *series);

private:
    void populateBarCategories(QBarCategoryAxis *axis);

protected:
    QList<QCandlestickSet *> m_sets;
    qreal m_maximumColumnWidth;
    qreal m_minimumColumnWidth;
    qreal m_bodyWidth;
    bool m_bodyOutlineVisible;
    qreal m_capsWidth;
    bool m_capsVisible;
    QColor m_increasingColor;
    QColor m_decreasingColor;
    bool m_customIncreasingColor;
    bool m_customDecreasingColor;
    QBrush m_brush;
    QPen m_pen;
    CandlestickAnimation *m_animation;

private:
    Q_DECLARE_PUBLIC(QCandlestickSeries)
};

QT_END_NAMESPACE

#endif // QCANDLESTICKSERIES_P_H
