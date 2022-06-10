// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>

QT_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void createUi();
    void createSeries();
    void updateLegendSpinbox();

public Q_SLOTS:
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

#endif // MAINWIDGET_H
