/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPolarChart>
#include <QMainWindow>
#include <QFont>
#include <QChart>
#include <QScatterSeries>
#include <QLineSeries>
#include <QSplineSeries>
#include <QAreaSeries>

namespace Ui {
class MainWindow;
}

QTCOMMERCIALCHART_USE_NAMESPACE

class QBrush;
class QPen;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void angularTicksChanged(int value);
    void radialTicksChanged(int value);
    void anglesChanged(int value);
    void angularMinChanged(double value);
    void angularMaxChanged(double value);
    void radialMinChanged(double value);
    void radialMaxChanged(double value);
    void angularShadesIndexChanged(int index);
    void radialShadesIndexChanged(int index);
    void labelFormatEdited(const QString &text);
    void labelFontChanged(const QFont &font);
    void labelFontSizeChanged(int value);
    void animationIndexChanged(int index);
    void labelsIndexChanged(int index);
    void titleIndexChanged(int index);
    void titleFontChanged(const QFont &font);
    void titleFontSizeChanged(int value);
    void gridIndexChanged(int index);
    void arrowIndexChanged(int index);
    void angularRangeChanged(qreal min, qreal max);
    void radialRangeChanged(qreal min, qreal max);
    void angularAxisIndexChanged(int index);
    void radialAxisIndexChanged(int index);
    void logBaseChanged(double value);
    void niceNumbersChecked();
    void dateFormatEdited(const QString &text);
    void moreCategoriesChecked();
    void series1CheckBoxChecked();
    void series2CheckBoxChecked();
    void series3CheckBoxChecked();
    void series4CheckBoxChecked();
    void series5CheckBoxChecked();
    void series6CheckBoxChecked();
    void series7CheckBoxChecked();
    void themeIndexChanged(int index);
    void seriesHovered(QPointF point, bool state);
    void seriesClicked(const QPointF &point);
    void backgroundIndexChanged(int index);
    void plotAreaIndexChanged(int index);

private:
    enum AxisMode {
        AxisModeNone,
        AxisModeValue,
        AxisModeLogValue,
        AxisModeDateTime,
        AxisModeCategory
    };

    void initXYValueChart();
    void setAngularAxis(AxisMode mode);
    void setRadialAxis(AxisMode mode);

    void applyRanges();
    void applyCategories();

    Ui::MainWindow *ui;

    int m_angularTickCount;
    int m_radialTickCount;
    qreal m_labelsAngle;
    qreal m_angularMin;
    qreal m_angularMax;
    qreal m_radialMin;
    qreal m_radialMax;
    bool m_angularShadesVisible;
    bool m_radialShadesVisible;
    bool m_labelsVisible;
    bool m_titleVisible;
    bool m_gridVisible;
    bool m_arrowVisible;
    QBrush *m_angularShadesBrush;
    QBrush *m_radialShadesBrush;
    QBrush *m_labelBrush;
    QBrush *m_titleBrush;
    QBrush *m_backgroundBrush;
    QBrush *m_plotAreaBackgroundBrush;
    QPen *m_angularShadesPen;
    QPen *m_radialShadesPen;
    QPen *m_labelPen;
    QPen *m_titlePen;
    QPen *m_gridPen;
    QPen *m_arrowPen;
    QPen *m_backgroundPen;
    QPen *m_plotAreaBackgroundPen;
    QString m_labelFormat;
    QFont m_currentLabelFont;
    QFont m_currentTitleFont;
    QChart::AnimationOptions m_animationOptions;
    QString m_angularTitle;
    QString m_radialTitle;
    qreal m_base;
    QString m_dateFormat;

    QPolarChart *m_chart;
    QAbstractAxis *m_angularAxis;
    QAbstractAxis *m_radialAxis;
    AxisMode m_angularAxisMode;
    AxisMode m_radialAxisMode;
    bool m_moreCategories;

    QScatterSeries *m_series1;
    QLineSeries *m_series2;
    QLineSeries *m_series3;
    QLineSeries *m_series4;
    QAreaSeries *m_series5;
    QSplineSeries *m_series6;
    QScatterSeries *m_series7;
};

#endif // MAINWINDOW_H
