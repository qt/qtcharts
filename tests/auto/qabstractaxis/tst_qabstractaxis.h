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

#ifndef TST_QABSTRACTAXIS_H
#define TST_QABSTRACTAXIS_H

#include <QtTest/QtTest>
#include <tst_definitions.h>
#include <qabstractaxis.h>
#include <qchartview.h>

QTCOMMERCIALCHART_USE_NAMESPACE

class tst_QAbstractAxis : public QObject
{
    Q_OBJECT

public slots:
    virtual void initTestCase();
    virtual void cleanupTestCase();
    virtual void init(QAbstractAxis* axis,QAbstractSeries* series);
    virtual void cleanup();

private slots:
    void axisPen_data();
    void axisPen();
    void axisPenColor_data();
    void axisPenColor();
    void gridLinePen_data();
    void gridLinePen();
    void lineVisible_data();
    void lineVisible();
    void gridLineVisible_data();
    void gridLineVisible();
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
    void labelsPen_data();
    void labelsPen();
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
