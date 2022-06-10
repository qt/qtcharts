// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCore/QTimer>

QT_USE_NAMESPACE

//![1]
class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    virtual ~ChartView();

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QList<QAbstractSeries *> m_series;
    QStringList m_titles;
    int m_index;
    QChart *m_chart;
};
//![1]

#endif /* CHARTVIEW_H */
