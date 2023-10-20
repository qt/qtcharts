// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef PCCWIDGET_H
#define PCCWIDGET_H

#include "contentwidget.h"

#include <QGridLayout>
#include <QScrollArea>

QT_FORWARD_DECLARE_CLASS(QChartView);
QT_FORWARD_DECLARE_CLASS(QCheckBox);
QT_FORWARD_DECLARE_CLASS(QComboBox);
QT_FORWARD_DECLARE_CLASS(QDoubleSpinBox);
QT_FORWARD_DECLARE_CLASS(QLineEdit);
QT_FORWARD_DECLARE_CLASS(QPushButton);
QT_FORWARD_DECLARE_CLASS(QPieSeries);
QT_FORWARD_DECLARE_CLASS(QPieSlice);

class PccPenTool;
class PccBrushTool;
class PccCustomSlice;

class PccWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit PccWidget(QWidget *parent = nullptr);

public slots:
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

    QComboBox *m_themeComboBox = nullptr;
    QCheckBox *m_aaCheckBox = nullptr;
    QCheckBox *m_animationsCheckBox = nullptr;
    QCheckBox *m_legendCheckBox = nullptr;

    QChartView *m_chartView = nullptr;
    QPieSeries *m_series = nullptr;
    PccCustomSlice *m_slice = nullptr;

    QDoubleSpinBox *m_hPosition = nullptr;
    QDoubleSpinBox *m_vPosition = nullptr;
    QDoubleSpinBox *m_sizeFactor = nullptr;
    QDoubleSpinBox *m_startAngle = nullptr;
    QDoubleSpinBox *m_endAngle = nullptr;
    QDoubleSpinBox *m_holeSize = nullptr;

    QLineEdit *m_sliceName = nullptr;
    QDoubleSpinBox *m_sliceValue = nullptr;
    QCheckBox *m_sliceLabelVisible = nullptr;
    QDoubleSpinBox *m_sliceLabelArmFactor = nullptr;
    QCheckBox *m_sliceExploded = nullptr;
    QDoubleSpinBox *m_sliceExplodedFactor = nullptr;
    QPushButton *m_brush = nullptr;
    PccBrushTool *m_brushTool = nullptr;
    QPushButton *m_pen = nullptr;
    PccPenTool *m_penTool = nullptr;
    QPushButton *m_font = nullptr;
    QPushButton *m_labelBrush = nullptr;
    QComboBox *m_labelPosition = nullptr;
    PccBrushTool *m_labelBrushTool = nullptr;
    QGridLayout *m_baseLayout = nullptr;
    QScrollArea *m_settingsScrollBar = nullptr;

    double m_oldAspectRatio = 0.;
};

#endif
