/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>

class QSpinBox;
class QCheckBox;
class QGridLayout;

QT_CHARTS_USE_NAMESPACE

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
