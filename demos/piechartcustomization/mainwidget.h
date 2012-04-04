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
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QChartGlobal>

class QLabel;
class QPushButton;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
class PenTool;
class BrushTool;
class CustomSlice;

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QChartView;
class QPieSeries;
class QPieSlice;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget* parent = 0);

public Q_SLOTS:
    void updateChartSettings();
    void updateSerieSettings();
    void updateSliceSettings();
    void handleSliceClicked(QPieSlice* slice, Qt::MouseButtons buttons);
    void showFontDialog();
    void appendSlice();
    void insertSlice();
    void removeSlice();

private:
    QComboBox *m_themeComboBox;
    QCheckBox *m_aaCheckBox;
    QCheckBox *m_animationsCheckBox;

    QChartView* m_chartView;
    QPieSeries* m_series;
    CustomSlice* m_slice;

    QDoubleSpinBox* m_hPosition;
    QDoubleSpinBox* m_vPosition;
    QDoubleSpinBox* m_sizeFactor;
    QDoubleSpinBox* m_startAngle;
    QDoubleSpinBox* m_endAngle;

    QLabel* m_sliceName;
    QDoubleSpinBox* m_sliceValue;
    QCheckBox* m_sliceLabelVisible;
    QDoubleSpinBox* m_sliceLabelArmFactor;
    QCheckBox* m_sliceExploded;
    QDoubleSpinBox* m_sliceExplodedFactor;
    QPushButton *m_brush;
    BrushTool *m_brushTool;
    QPushButton *m_pen;
    PenTool *m_penTool;
    QPushButton *m_font;
    QPushButton *m_labelPen;
    PenTool *m_labelPenTool;
};

#endif // MAINWIDGET_H
