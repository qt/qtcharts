// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef LEGENDWIDGET_H
#define LEGENDWIDGET_H

#include "contentwidget.h"

#include <QBarSeries>
#include <QChart>
#include <QChartView>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QPushButton>

class LegendWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit LegendWidget(QWidget *parent = nullptr);
    void createUi();
    void createSeries();
    void updateLegendSpinbox();

public slots:
    void toggleAttached();
    void toggleInteractive();
    void toggleBold();
    void toggleItalic();
    void addBarset();
    void removeBarset();
    void setLegendAlignment();
    void fontSizeChanged();
    void updateLegendLayout();

protected:
    void resizeEvent(QResizeEvent *) override;

private:
    QChart *m_chart;
    QChartView *m_chartView;
    QBarSeries *m_series;

    QCheckBox *m_toggleAttachedButton;
    QCheckBox *m_interactiveButton;
    QCheckBox *m_boldButton;
    QCheckBox *m_italicButton;
    QPushButton *m_addSetButton;
    QPushButton *m_removeSetButton;
    QPushButton *m_alignmentButton;
    QDoubleSpinBox *m_fontSize;

    QGroupBox *m_geometrySettings;
    QDoubleSpinBox *m_legendPosX;
    QDoubleSpinBox *m_legendPosY;
    QDoubleSpinBox *m_legendWidth;
    QDoubleSpinBox *m_legendHeight;
};

#endif
