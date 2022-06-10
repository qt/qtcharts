// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef TST_QABSTRACTAXIS_H
#define TST_QABSTRACTAXIS_H

#include <QtTest/QtTest>
#include <tst_definitions.h>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QChartView>

QT_USE_NAMESPACE

class tst_QAbstractAxis : public QObject
{
    Q_OBJECT

public slots:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    virtual void cleanup();

protected:
    void initAxes(QAbstractAxis *axis, QAbstractSeries *series);

private slots:
    void axisPen_data();
    void axisPen();
    void axisPenColor_data();
    void axisPenColor();
    void gridLinePen_data();
    void gridLinePen();
    void minorGridLinePen_data();
    void minorGridLinePen();
    void lineVisible_data();
    void lineVisible();
    void gridLineVisible_data();
    void gridLineVisible();
    void minorGridLineVisible_data();
    void minorGridLineVisible();
    void gridLineColor_data();
    void gridLineColor();
    void minorGridLineColor_data();
    void minorGridLineColor();
    void visible_data();
    void visible();
    void labelsAngle_data();
    void labelsAngle();
    void labelsBrush_data();
    void labelsBrush();
    void labelsColor_data();
    void labelsColor();
    void labelsFont_data();
    void labelsFont();
    void labelsVisible_data();
    void labelsVisible();
    void orientation_data();
    void orientation();
    void setMax_data();
    void setMax();
    void setMin_data();
    void setMin();
    void setRange_data();
    void setRange();
    void shadesBorderColor_data();
    void shadesBorderColor();
    void shadesBrush_data();
    void shadesBrush();
    void shadesColor_data();
    void shadesColor();
    void shadesPen_data();
    void shadesPen();
    void shadesVisible_data();
    void shadesVisible();
    void show_data();
    void show();
    void hide_data();
    void hide();

protected:
    void qabstractaxis();
protected:
    QChartView* m_view;
    QChart* m_chart;
    QAbstractAxis* m_axis;
    QAbstractSeries* m_series;
};

#endif
