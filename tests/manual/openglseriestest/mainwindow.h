// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

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


QT_USE_NAMESPACE

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
    void antiAliasCheckBoxClicked(bool checked);
    void handleHovered(const QPointF &point, bool state);
    void handleClicked(const QPointF &point);
    void handlePressed(const QPointF &point);
    void handleReleased(const QPointF &point);
    void handleDoubleClicked(const QPointF &point);

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
