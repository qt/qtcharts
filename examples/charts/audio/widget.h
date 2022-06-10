// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class XYSeriesIODevice;

QT_BEGIN_NAMESPACE
class QAudioInput;
class QAudioDevice;
class QAudioSource;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(const QAudioDevice &deviceInfo, QWidget *parent = nullptr);
    ~Widget();

private:
    XYSeriesIODevice *m_device = nullptr;
    QChart *m_chart;
    QLineSeries *m_series ;
    QAudioInput *m_audioInput = nullptr;
    QAudioSource *m_audioSource = nullptr;
};

#endif // WIDGET_H
