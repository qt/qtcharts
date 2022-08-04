// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "qgridlayout.h"
#include "qscrollarea.h"
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
QT_END_NAMESPACE

class PenTool;
class BrushTool;
class CustomSlice;

QT_BEGIN_NAMESPACE
class QChartView;
class QPieSeries;
class QPieSlice;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);

public Q_SLOTS:
    void updateChartSettings();
    void updateSerieSettings();
    void updateSliceSettings();
    void handleSliceClicked(QPieSlice *slice);
    void showFontDialog();
    void appendSlice();
    void insertSlice();
    void removeSlice();

private:
    void resizeEvent(QResizeEvent *e);

    QComboBox *m_themeComboBox;
    QCheckBox *m_aaCheckBox;
    QCheckBox *m_animationsCheckBox;
    QCheckBox *m_legendCheckBox;

    QChartView *m_chartView;
    QPieSeries *m_series;
    CustomSlice *m_slice;

    QDoubleSpinBox *m_hPosition;
    QDoubleSpinBox *m_vPosition;
    QDoubleSpinBox *m_sizeFactor;
    QDoubleSpinBox *m_startAngle;
    QDoubleSpinBox *m_endAngle;
    QDoubleSpinBox *m_holeSize;

    QLineEdit *m_sliceName;
    QDoubleSpinBox *m_sliceValue;
    QCheckBox *m_sliceLabelVisible;
    QDoubleSpinBox *m_sliceLabelArmFactor;
    QCheckBox *m_sliceExploded;
    QDoubleSpinBox *m_sliceExplodedFactor;
    QPushButton *m_brush;
    BrushTool *m_brushTool;
    QPushButton *m_pen;
    PenTool *m_penTool;
    QPushButton *m_font;
    QPushButton *m_labelBrush;
    QComboBox *m_labelPosition;
    BrushTool *m_labelBrushTool;
    QGridLayout *baseLayout;
    QScrollArea *settingsScrollBar;

    double oldAspectRatio;
};

#endif // MAINWIDGET_H
