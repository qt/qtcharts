// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QCheckBox;
class QGridLayout;
QT_END_NAMESPACE

QT_USE_NAMESPACE

#define RealList QList<qreal>
class DataSerieDialog;

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);

signals:

private:
    void initBackroundCombo(QGridLayout *grid);
    void initScaleControls(QGridLayout *grid);
    void initThemeCombo(QGridLayout *grid);
    void initCheckboxes(QGridLayout *grid);

private slots:
    void addSeries();
    void addSeries(QString series, int columnCount, int rowCount, QString dataCharacteristics, bool labelsEnabled);
    void backgroundChanged(int itemIndex);
    void autoScaleChanged(int value);
    void xMinChanged(int value);
    void xMaxChanged(int value);
    void yMinChanged(int value);
    void yMaxChanged(int value);
    void antiAliasToggled(bool enabled);
    void openGLToggled(bool enabled);
    void changeChartTheme(int themeIndex);
    QList<RealList> generateTestData(int columnCount, int rowCount, QString dataCharacteristics);
    QStringList generateLabels(int count);

private:
    DataSerieDialog *m_addSerieDialog;
    QChart *m_chart;
    QChartView *m_chartView;
    QCheckBox *m_autoScaleCheck;
    QSpinBox *m_xMinSpin;
    QSpinBox *m_xMaxSpin;
    QSpinBox *m_yMinSpin;
    QSpinBox *m_yMaxSpin;
    QString m_defaultSeriesName;
    QGridLayout *m_scatterLayout;
};

#endif // MAINWIDGET_H
