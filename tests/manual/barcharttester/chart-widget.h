// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QtWidgets/QHBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCore/QTimer>
#include <QtCore/QElapsedTimer>

QT_USE_NAMESPACE


class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();

public slots:
    void handleTimeout();

private:
    void createChart();
    void addSeriesToChart(QAbstractBarSeries *series);

private:
    QChart *m_chart;
    QChartView *m_chartView;
    QAbstractAxis *m_barAxis;
    QAbstractAxis *m_valueAxis;
    QList<QAbstractBarSeries *> m_series;
    QMap<const QAbstractBarSeries *, QList<QBarSet *>> m_sets;
    QTimer m_timer;
    QElapsedTimer m_elapsedTimer;
    QHBoxLayout *m_horizontalLayout;
    int m_setCount;
    int m_seriesCount;
    qreal m_extraScroll;
};

#endif // CHARTWIDGET_H
