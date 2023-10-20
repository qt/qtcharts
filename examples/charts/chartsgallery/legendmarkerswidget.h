// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LEGENDMARKERSWIDGET_H
#define LEGENDMARKERSWIDGET_H

#include "contentwidget.h"

QT_FORWARD_DECLARE_CLASS(QChart)
QT_FORWARD_DECLARE_CLASS(QChartView)
QT_FORWARD_DECLARE_CLASS(QGridLayout)
QT_FORWARD_DECLARE_CLASS(QLineSeries)

class LegendMarkersWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LegendMarkersWidget(QWidget *parent = nullptr);

public slots:
    void addSeries();
    void removeSeries();
    void connectMarkers();
    void disconnectMarkers();
    void handleMarkerClicked();

private:
    QChart *m_chart = nullptr;
    QChartView *m_chartView = nullptr;
    QGridLayout *m_mainLayout = nullptr;
    QGridLayout *m_fontLayout = nullptr;
    QList<QLineSeries *> m_series;
};

#endif
