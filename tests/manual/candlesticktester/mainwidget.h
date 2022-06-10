// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QGridLayout;
QT_END_NAMESPACE

QT_BEGIN_NAMESPACE
class QCandlestickSet;
class QHCandlestickModelMapper;
QT_END_NAMESPACE

QT_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    QGridLayout *createSeriesControlsLayout();
    QGridLayout *createSetsControlsLayout();
    QGridLayout *createCandlestickControlsLayout();
    QGridLayout *createMiscellaneousControlsLayout();
    QGridLayout *createModelMapperControlsLayout();

    qreal randomValue(int min, int max) const;
    QCandlestickSet *randomSet(qreal timestamp);

    void updateAxes();

private slots:
    void addSeries();
    void removeSeries();
    void removeAllSeries();
    void addSet();
    void insertSet();
    void removeSet();
    void removeAllSets();
    void changeMaximumColumnWidth(double width);
    void changeMinimumColumnWidth(double width);
    void bodyOutlineVisibleToggled(bool visible);
    void capsVisibleToggled(bool visible);
    void changeBodyWidth(double width);
    void changeCapsWidth(double width);
    void customIncreasingColorToggled(bool custom);
    void customDecreasingColorToggled(bool custom);
    void antialiasingToggled(bool enabled);
    void animationToggled(bool enabled);
    void legendToggled(bool visible);
    void titleToggled(bool visible);
    void changeChartTheme(int themeIndex);
    void changeAxisX(int axisXIndex);
    void attachModelMapper();
    void detachModelMapper();

private:
    QChart *m_chart;
    QChartView *m_chartView;
    QAbstractAxis *m_axisX;
    QAbstractAxis *m_axisY;
    qreal m_maximumColumnWidth;
    qreal m_minimumColumnWidth;
    bool m_bodyOutlineVisible;
    bool m_capsVisible;
    qreal m_bodyWidth;
    qreal m_capsWidth;
    bool m_customIncreasingColor;
    bool m_customDecreasingColor;
    QHCandlestickModelMapper *m_hModelMapper;
};

#endif // MAINWIDGET_H
