// Copyright (C) 2022 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QChartView>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QXYSeries>

typedef QHash<QXYSeries::PointConfiguration, QVariant> PointConfigurations;

//![1]
class ChartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow() {};

private:
    QChart *m_chart = nullptr;
    QXYSeries *m_series = nullptr;

    QMetaObject::Connection m_selectInitialPointConnection;
    int m_selectedPointIndex = -1;
    PointConfigurations m_selectedPointConfig;

    QLineEdit *m_selectedPointIndexLineEdit = nullptr;
    QComboBox *m_colorCombobox = nullptr;
    QComboBox *m_sizeCombobox = nullptr;
    QCheckBox *m_labelVisibilityCheckbox = nullptr;
    QLineEdit *m_customLabelLineEdit = nullptr;
};
//![1]

#endif // CHARTWINDOW_H
