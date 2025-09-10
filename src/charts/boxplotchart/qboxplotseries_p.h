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

#ifndef QBOXPLOTSERIES_P_H
#define QBOXPLOTSERIES_P_H

#include <QtCharts/QBoxPlotSeries>
#include <private/qabstractbarseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QBarSet>
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class BoxPlotAnimation;

class Q_CHARTS_EXPORT QBoxPlotSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QBoxPlotSeriesPrivate(QBoxPlotSeries *q);
    ~QBoxPlotSeriesPrivate();

    void initializeGraphics(QGraphicsItem *parent) override;
    void initializeDomain() override;
    void initializeAxes() override;
    void initializeAnimations(QChart::AnimationOptions options, int duration, QEasingCurve &curve) override;
    void initializeTheme(int index, ChartTheme *theme, bool forced = false) override;

    QList<QLegendMarker*> createLegendMarkers(QLegend *legend) override;

    QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const override;
    QAbstractAxis *createDefaultAxis(Qt::Orientation orientation) const override;

    bool append(QBoxSet *set);
    bool remove(QBoxSet *set);
    bool append(const QList<QBoxSet *> &sets);
    bool remove(const QList<QBoxSet *> &sets);
    bool insert(int index, QBoxSet *set);
    QBoxSet *boxSetAt(int index);

    qreal max();
    qreal min();

private:
    void populateCategories(QBarCategoryAxis *axis);

Q_SIGNALS:
    void updated();
    void clicked(int index, QBoxSet *barset);
    void pressed(int index, QBoxSet *barset);
    void released(int index, QBoxSet *barset);
    void doubleClicked(int index, QBoxSet *barset);
    void updatedBoxes();
    void updatedLayout();
    void restructuredBoxes();

private Q_SLOTS:
    void handleSeriesChange(QAbstractSeries *series);
    void handleSeriesRemove(QAbstractSeries *series);

protected:
    QList<QBoxSet *> m_boxSets;
    QPen m_pen;
    QBrush m_brush;
    bool m_boxOutlineVisible;
    int m_index;
    BoxPlotAnimation *m_animation;
    qreal m_boxWidth;

private:
    Q_DECLARE_PUBLIC(QBoxPlotSeries)
};

QT_END_NAMESPACE

#endif
