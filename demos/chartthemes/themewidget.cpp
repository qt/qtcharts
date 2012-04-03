/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#include "themewidget.h"

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QPercentBarSeries>
#include <QStackedBarSeries>
#include <QBarSet>
#include <QLineSeries>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QAreaSeries>
#include <QLegend>
#include <QGridLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QTime>

ThemeWidget::ThemeWidget(QWidget* parent) :
    QWidget(parent),
    m_listCount(3),
    m_valueMax(100),
    m_valueCount(11),
    m_dataTable(generateRandomData(m_listCount,m_valueMax,m_valueCount)),
    m_themeComboBox(createThemeBox()),
    m_antialiasCheckBox(new QCheckBox("Anti aliasing")),
    m_animatedComboBox(createAnimationBox()),
    m_legendComboBox(createLegendBox())

{

    connectSignals();
    // create layout
    QGridLayout* baseLayout = new QGridLayout();
    QHBoxLayout *settingsLayout = new QHBoxLayout();
    settingsLayout->addWidget(new QLabel("Theme:"));
    settingsLayout->addWidget(m_themeComboBox);
    settingsLayout->addWidget(new QLabel("Animation:"));
    settingsLayout->addWidget(m_animatedComboBox);
    settingsLayout->addWidget(m_legendComboBox);
    settingsLayout->addWidget(m_antialiasCheckBox);
    settingsLayout->addStretch();
    baseLayout->addLayout(settingsLayout, 0, 0, 1, 3);

    //create charts

    QChartView *chartView;

    chartView = new QChartView(createAreaChart());
    baseLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;

    chartView = new QChartView(createBarChart(m_valueCount));
    baseLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

    chartView = new QChartView(createLineChart());
    baseLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;

    chartView = new QChartView(createPieChart());
    chartView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored); // funny things happen if the pie slice labels no not fit the screen...
    baseLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart());
    baseLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;

    chartView = new QChartView(createScatterChart());
    baseLayout->addWidget(chartView, 2, 2);
    m_charts << chartView;

    setLayout(baseLayout);
}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::connectSignals()
{
    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
}

DataTable ThemeWidget::generateRandomData(int listCount,int valueMax,int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(j + (qreal) rand() / (qreal) RAND_MAX, qrand() % valueMax);
            QString label = "Item " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

QComboBox* ThemeWidget::createThemeBox() const
{
    // settings layout
    QComboBox* themeComboBox = new QComboBox();
    themeComboBox->addItem("Default", QChart::ChartThemeDefault);
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    return themeComboBox;
}

QComboBox* ThemeWidget::createAnimationBox() const
{
    // settings layout
    QComboBox* animationComboBox = new QComboBox();
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox* ThemeWidget::createLegendBox() const
{
    QComboBox* legendComboBox = new QComboBox();
    legendComboBox->addItem("Legend Top", QLegend::AlignmentTop);
    legendComboBox->addItem("Legend Bottom", QLegend::AlignmentBottom);
    legendComboBox->addItem("Legend Left", QLegend::AlignmentLeft);
    legendComboBox->addItem("Legend Right", QLegend::AlignmentRight);
    return legendComboBox;
}

QChart* ThemeWidget::createAreaChart() const
{
    // area chart
    QChart *chart = new QChart();
    chart->setTitle("Area chart");
    {
        QString name("Series ");
        int nameIndex = 0;
        for (int i(0); i < m_dataTable.count(); i++) {
            QLineSeries *series1 = new QLineSeries(chart);
            QLineSeries *series2 = new QLineSeries(chart);
            foreach (Data data, m_dataTable[i]) {
                series1->append(data.first);
                series2->append(QPointF(data.first.x(), 0.0));
            }
            QAreaSeries *area = new QAreaSeries(series1, series2);
            area->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(area);
        }
    }
    return chart;
}

QChart* ThemeWidget::createBarChart(int valueCount) const
{
    // bar chart
    QChart* chart = new QChart();
    chart->setTitle("Bar chart");
    {
        QBarCategories categories;
        // TODO: categories
        for (int i(0); i < valueCount; i++)
            categories << QString::number(i);
//            QBarSeries* series = new QBarSeries(categories, chart);
//            QPercentBarSeries* series = new QPercentBarSeries(categories, chart);
        QStackedBarSeries* series = new QStackedBarSeries(categories, chart);
        for (int i(0); i < m_dataTable.count(); i++) {
            QBarSet *set = new QBarSet("Set" + QString::number(i));
            foreach (Data data, m_dataTable[i])
                *set << data.first.y();
            series->appendBarSet(set);
        }
        chart->addSeries(series);
    }
    return chart;
}

QChart* ThemeWidget::createLineChart() const
{
    // line chart
    QChart* chart = new QChart();
    chart->setTitle("Line chart");
    QString name("Series ");
    int nameIndex = 0;
    foreach (DataList list, m_dataTable) {
        QLineSeries *series = new QLineSeries(chart);
        foreach (Data data, list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    return chart;
}

QChart* ThemeWidget::createPieChart() const
{
    // pie chart
    QChart* chart = new QChart();
    chart->setTitle("Pie chart");
    qreal pieSize = 1.0 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        foreach (Data data, m_dataTable[i]) {
            QPieSlice *slice = series->append(data.first.y(), data.second);
            if (data == m_dataTable[i].first()) {
                slice->setLabelVisible();
                slice->setExploded();
            }
        }
        qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
        series->setPieSize(pieSize);
        series->setPiePosition(hPos, 0.5);
        chart->addSeries(series);
    }

    return chart;
}

QChart* ThemeWidget::createSplineChart() const
{ // spine chart
    QChart* chart = new QChart();
    chart->setTitle("Spline chart");
    QString name("Series ");
    int nameIndex = 0;
    foreach (DataList list, m_dataTable) {
        QSplineSeries *series = new QSplineSeries(chart);
        foreach (Data data, list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    return chart;
}

QChart* ThemeWidget::createScatterChart() const
{ // scatter chart
    QChart* chart = new QChart();
    chart->setTitle("Scatter chart");
    QString name("Series ");
    int nameIndex = 0;
    foreach (DataList list, m_dataTable) {
        QScatterSeries *series = new QScatterSeries(chart);
        foreach (Data data, list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    return chart;
}

void ThemeWidget::updateUI()
{
    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(m_themeComboBox->currentIndex()).toInt();

    if (m_charts.at(0)->chart()->theme() != theme) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->setTheme(theme);

        QPalette pal = window()->palette();
        if (theme == QChart::ChartThemeLight) {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeDark) {
            pal.setColor(QPalette::Window, QRgb(0x121218));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBlueCerulean) {
            pal.setColor(QPalette::Window, QRgb(0x40434a));
            pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
        } else if (theme == QChart::ChartThemeBrownSand) {
            pal.setColor(QPalette::Window, QRgb(0x9e8965));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeBlueNcs) {
            pal.setColor(QPalette::Window, QRgb(0x018bba));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else if (theme == QChart::ChartThemeHighContrast) {
            pal.setColor(QPalette::Window, QRgb(0xffab03));
            pal.setColor(QPalette::WindowText, QRgb(0x181818));
        } else if (theme == QChart::ChartThemeBlueIcy) {
            pal.setColor(QPalette::Window, QRgb(0xcee7f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        } else {
            pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
            pal.setColor(QPalette::WindowText, QRgb(0x404044));
        }
        window()->setPalette(pal);
    }

    bool checked = m_antialiasCheckBox->isChecked();
    foreach (QChartView *chart, m_charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);

    QChart::AnimationOptions options(m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
    if (m_charts.at(0)->chart()->animationOptions() != options) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->setAnimationOptions(options);
    }

    QLegend::Alignments alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());
    foreach (QChartView *chartView, m_charts) {
        chartView->chart()->legend()->setAlignmnent(alignment);
    }
}

