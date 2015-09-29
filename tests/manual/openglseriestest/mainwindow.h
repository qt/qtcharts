/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "datasource.h"
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
class QBrush;
class QPen;

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void xMinChanged(double value);
    void xMaxChanged(double value);
    void yMinChanged(double value);
    void yMaxChanged(double value);
    void animationIndexChanged(int index);
    void xRangeChanged(qreal min, qreal max);
    void yRangeChanged(qreal min, qreal max);
    void xAxisIndexChanged(int index);
    void yAxisIndexChanged(int index);
    void backgroundIndexChanged(int index);
    void plotAreaIndexChanged(int index);
    void themeIndexChanged(int index);
    void addSeriesClicked();
    void removeSeriesClicked();
    void addGLSeriesClicked();
    void countIndexChanged(int index);
    void colorIndexChanged(int index);
    void widthIndexChanged(int index);

private:
    enum AxisMode {
        AxisModeNone,
        AxisModeValue,
        AxisModeLogValue,
        AxisModeDateTime,
        AxisModeCategory
    };

    void initXYValueChart();
    void setXAxis(AxisMode mode);
    void setYAxis(AxisMode mode);

    void applyRanges();
    void applyCategories();
    void addSeries(bool gl);

    Ui::MainWindow *ui;

    qreal m_xMin;
    qreal m_xMax;
    qreal m_yMin;
    qreal m_yMax;
    QBrush *m_backgroundBrush;
    QBrush *m_plotAreaBackgroundBrush;
    QPen *m_backgroundPen;
    QPen *m_plotAreaBackgroundPen;
    QChart::AnimationOptions m_animationOptions;

    QChart *m_chart;
    QAbstractAxis *m_xAxis;
    QAbstractAxis *m_yAxis;
    AxisMode m_xAxisMode;
    AxisMode m_yAxisMode;

    QList<QXYSeries *> m_seriesList;
    DataSource m_dataSource;
    int m_pointCount;
};

#endif // MAINWINDOW_H
