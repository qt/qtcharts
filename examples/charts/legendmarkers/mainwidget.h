// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QLineSeries>

QT_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

public slots:
    void addSeries();
    void removeSeries();
    void connectMarkers();
    void disconnectMarkers();

    void handleMarkerClicked();

private:

    QChart *m_chart;
    QList<QLineSeries *> m_series;

    QChartView *m_chartView;
    QGridLayout *m_mainLayout;
    QGridLayout *m_fontLayout;

};

#endif // MAINWIDGET_H
