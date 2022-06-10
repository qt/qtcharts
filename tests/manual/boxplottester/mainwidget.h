// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtCharts/QBoxPlotSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBoxSet>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE

class CustomTableModel;
class PenTool;

QT_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

private:
    void initThemeCombo(QGridLayout *grid);
    void initCheckboxes(QGridLayout *grid);
    void updateAxis(int categoryCount);

private slots:
    void addSeries();
    void removeSeries();
    void addBox();
    void insertBox();
    void removeBox();
    void clear();
    void clearBox();
    void setBrush();
    void animationToggled(bool enabled);
    void legendToggled(bool enabled);
    void titleToggled(bool enabled);
    void modelMapperToggled(bool enabled);
    void changeChartTheme(int themeIndex);
    void boxClicked(QBoxSet *set);
    void boxHovered(bool state, QBoxSet *set);
    void boxPressed(QBoxSet *set);
    void boxReleased(QBoxSet *set);
    void boxDoubleClicked(QBoxSet *set);
    void singleBoxClicked();
    void singleBoxHovered(bool state);
    void singleBoxPressed();
    void singleBoxReleased();
    void singleBoxDoubleClicked();
    void changePen();
    void antialiasingToggled(bool);
    void boxOutlineToggled(bool);
    void setBoxWidth(double width);

private:
    QChart *m_chart;
    QChartView *m_chartView;
    QGridLayout *m_scatterLayout;
    QBarCategoryAxis *m_axis;
    CustomTableModel *m_model;
    PenTool *m_penTool;
    int m_rowPos;
    int m_seriesCount;
    QBoxPlotSeries *m_series[10];
    QCheckBox *m_boxOutlined;
    QDoubleSpinBox *m_boxWidthSB;
};

#endif // MAINWIDGET_H
