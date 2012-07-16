/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef TST_QABSTRACTSERIES_H
#define TST_QABSTRACTSERIES_H

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
    virtual void init(QAbstractAxis* axis);
    virtual void cleanup();

private slots:
    void axisPen_data();
    void axisPen();
    void axisPenColor_data();
    void axisPenColor();
    void gridLinePen_data();
    void gridLinePen();
    void hide_data();
    void hide();
    void isArrowVisible_data();
    void isArrowVisible();
    void isGridLineVisible_data();
    void isGridLineVisible();
    void isVisible_data();
    void isVisible();
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
    void setArrowVisible_data();
    void setArrowVisible();
    void setAxisPen_data();
    void setAxisPen();
    void setAxisPenColor_data();
    void setAxisPenColor();
    void setGridLinePen_data();
    void setGridLinePen();
    void setGridLineVisible_data();
    void setGridLineVisible();
    void setLabelsAngle_data();
    void setLabelsAngle();
    void setLabelsBrush_data();
    void setLabelsBrush();
    void setLabelsColor_data();
    void setLabelsColor();
    void setLabelsFont_data();
    void setLabelsFont();
    void setLabelsPen_data();
    void setLabelsPen();
    void setLabelsVisible_data();
    void setLabelsVisible();
    void setMax_data();
    void setMax();
    void setMin_data();
    void setMin();
    void setRange_data();
    void setRange();
    void setShadesBorderColor_data();
    void setShadesBorderColor();
    void setShadesBrush_data();
    void setShadesBrush();
    void setShadesColor_data();
    void setShadesColor();
    void setShadesPen_data();
    void setShadesPen();
    void setShadesVisible_data();
    void setShadesVisible();
    void setVisible_data();
    void setVisible();
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
    void type_data();
    void type();
    void arrowVisibleChanged_data();
    void arrowVisibleChanged();
    void colorChanged_data();
    void colorChanged();
    void gridVisibleChanged_data();
    void gridVisibleChanged();
    void labelsColorChanged_data();
    void labelsColorChanged();
    void labelsVisibleChanged_data();
    void labelsVisibleChanged();
    void shadesBorderColorChanged_data();
    void shadesBorderColorChanged();
    void shadesColorChanged_data();
    void shadesColorChanged();
    void shadesVisibleChanged_data();
    void shadesVisibleChanged();
    void visibleChanged_data();
    void visibleChanged();

protected:
    void qabstractaxis();
protected:
    QChartView* m_view;
    QChart* m_chart;
    QAbstractAxis* m_axis;
};

#endif
