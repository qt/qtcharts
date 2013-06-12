/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TST_QXYSERIES_H
#define TST_QXYSERIES_H

#include <QtTest/QtTest>
#include <qxyseries.h>
#include <qchartview.h>
#include <QStandardItemModel>
#include <tst_definitions.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QXYSeries : public QObject
{
    Q_OBJECT

public slots:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    virtual void init();
    virtual void cleanup();

private slots:
    void seriesName();
    void seriesVisible();
    void seriesOpacity();
    void oper_data();
    void oper();
    void pen_data();
    void pen();
    void pointsVisible_raw_data();
    void pointsVisible_raw();
    void append_raw_data();
    void append_raw();
    void append_chart_data();
    void append_chart();
    void append_chart_animation_data();
    void append_chart_animation();
    void chart_append_data();
    void chart_append();
    void count_raw_data();
    void count_raw();
    void remove_raw_data();
    void remove_raw();
    void remove_chart_data();
    void remove_chart();
    void remove_chart_animation_data();
    void remove_chart_animation();
    void clear_raw_data();
    void clear_raw();
    void clear_chart_data();
    void clear_chart();
    void clear_chart_animation_data();
    void clear_chart_animation();
    void replace_raw_data();
    void replace_raw();
    void replace_chart_data();
    void replace_chart();
    void replace_chart_animation_data();
    void replace_chart_animation();
    void insert_data();
    void insert();
    void changedSignals();
protected:
    void append_data();
    void count_data();
    void pointsVisible_data();

protected:
    QChartView* m_view;
    QChart* m_chart;
    QXYSeries* m_series;
};

#endif
