/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
