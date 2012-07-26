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

#include "chartwindow.h"

#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QPercentBarSeries>
#include <QStackedBarSeries>
#include <QBarSeries>
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
#include <QBarCategoriesAxis>
#include <QGraphicsScene>
#include <QGraphicsGridLayout>
#include <QGraphicsLinearLayout>
#include <QGraphicsProxyWidget>
#include <QGLWidget>
#include <QApplication>
#include <QDebug>

ChartWindow::ChartWindow(QWidget* parent) :
    QMainWindow(parent), m_listCount(3), m_valueMax(10), m_valueCount(7), m_scene(
        new QGraphicsScene(this)), m_view(0), m_dataTable(
        generateRandomData(m_listCount, m_valueMax, m_valueCount)), m_form(0), m_themeComboBox(0), m_antialiasCheckBox(
        0), m_animatedComboBox(0), m_legendComboBox(0), m_openGLCheckBox(0)
{
    createProxyWidgets();
    connectSignals();

    // create layout
    QGraphicsGridLayout* baseLayout = new QGraphicsGridLayout();
    QGraphicsLinearLayout *settingsLayout = new QGraphicsLinearLayout();
    settingsLayout->setOrientation(Qt::Vertical);
    settingsLayout->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    settingsLayout->addItem(m_widgetHash["openGLCheckBox"]);
    settingsLayout->addItem(m_widgetHash["antialiasCheckBox"]);
    settingsLayout->addItem(m_widgetHash["themeLabel"]);
    settingsLayout->addItem(m_widgetHash["themeComboBox"]);
    settingsLayout->addItem(m_widgetHash["animationsLabel"]);
    settingsLayout->addItem(m_widgetHash["animatedComboBox"]);
    settingsLayout->addItem(m_widgetHash["legendLabel"]);
    settingsLayout->addItem(m_widgetHash["legendComboBox"]);
    settingsLayout->addStretch();
    baseLayout->addItem(settingsLayout, 0, 3, 2, 1);
    //create charts

    int i = m_widgetHash.count();
    foreach(QGraphicsProxyWidget* widget , m_widgetHash) {
        widget->setZValue(i--);
        widget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    }

    QChart* chart;

    chart = createAreaChart();
    baseLayout->addItem(chart, 0, 0);
    m_chartList << chart;

    chart = createBarChart(m_valueCount);
    baseLayout->addItem(chart, 0, 1);
    m_chartList << chart;

    chart = createLineChart();
    baseLayout->addItem(chart, 0, 2);
    m_chartList << chart;

    chart = createPieChart();
    baseLayout->addItem(chart, 1, 0);
    m_chartList << chart;

    chart = createSplineChart();
    baseLayout->addItem(chart, 1, 1);
    m_chartList << chart;

    chart = createScatterChart();
    baseLayout->addItem(chart, 1, 2);
    m_chartList << chart;

    // Set defaults
    //m_antialiasCheckBox->setChecked(true);

    m_form = new QGraphicsWidget();
    m_form->setLayout(baseLayout);
    m_scene->addItem(m_form);

    m_view = new GraphicsView(m_scene, m_form);
    m_view->setMinimumSize(m_form->preferredSize().toSize());

    updateUI();
    setCentralWidget(m_view);
}

ChartWindow::~ChartWindow()
{
}

void ChartWindow::connectSignals()
{
    connect(m_themeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_antialiasCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_openGLCheckBox, SIGNAL(toggled(bool)), this, SLOT(updateUI()));
    connect(m_animatedComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
    connect(m_legendComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateUI()));
}

DataTable ChartWindow::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal) (qrand() % valueMax) / (qreal) valueCount;
            QPointF value(
                (j + (qreal) qrand() / (qreal) RAND_MAX)
                    * ((qreal) m_valueMax / (qreal) valueCount), yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

void ChartWindow::createProxyWidgets()
{
    m_themeComboBox = createThemeBox();
    m_antialiasCheckBox = new QCheckBox(tr("Anti-aliasing"));
    m_animatedComboBox = createAnimationBox();
    m_legendComboBox = createLegendBox();
    m_openGLCheckBox = new QCheckBox(tr("OpenGL"));
    m_widgetHash["themeComboBox"] = m_scene->addWidget(m_themeComboBox);
    m_widgetHash["antialiasCheckBox"] = m_scene->addWidget(m_antialiasCheckBox);
    m_widgetHash["animatedComboBox"] = m_scene->addWidget(m_animatedComboBox);
    m_widgetHash["legendComboBox"] = m_scene->addWidget(m_legendComboBox);
    m_widgetHash["openGLCheckBox"] = m_scene->addWidget(m_openGLCheckBox);
    m_widgetHash["themeLabel"] = m_scene->addWidget(new QLabel("Theme"));
    m_widgetHash["animationsLabel"] = m_scene->addWidget(new QLabel("Animations"));
    m_widgetHash["legendLabel"] = m_scene->addWidget(new QLabel("Legend"));
}

QComboBox* ChartWindow::createThemeBox() const
{
    // settings layoutQGLWidget’
    QComboBox* themeComboBox = new QComboBox();
    themeComboBox->addItem("Light", QChart::ChartThemeLight);
    themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    return themeComboBox;
}

QComboBox* ChartWindow::createAnimationBox() const
{
    // settings layout
    QComboBox* animationComboBox = new QComboBox();
    animationComboBox->addItem("No Animations", QChart::NoAnimation);
    animationComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    animationComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    animationComboBox->addItem("All Animations", QChart::AllAnimations);
    return animationComboBox;
}

QComboBox* ChartWindow::createLegendBox() const
{
    QComboBox* legendComboBox = new QComboBox();
    legendComboBox->addItem("No Legend ", 0);
    legendComboBox->addItem("Legend Top", Qt::AlignTop);
    legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    legendComboBox->addItem("Legend Right", Qt::AlignRight);
    return legendComboBox;
}

QChart* ChartWindow::createAreaChart() const
{
    QChart *chart = new QChart();
//    chart->axisX()->setNiceNumbersEnabled(true);
//    chart->axisY()->setNiceNumbersEnabled(true);
    chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = 0;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < m_dataTable.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < m_dataTable[i].count(); j++) {
            Data data = m_dataTable[i].at(j);
            if (lowerSeries) {
                const QList<QPointF>& points = lowerSeries->points();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            }
            else
                upperSeries->append(QPointF(j, data.first.y()));
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        chart->createDefaultAxes();
        lowerSeries = upperSeries;
    }

    return chart;
}

QChart* ChartWindow::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount);
    QChart* chart = new QChart();
    //TODO: chart->axisX()->setNiceNumbersEnabled(true);
    //TODO: chart->axisY()->setNiceNumbersEnabled(true);
    chart->setTitle("Bar chart");

    QStackedBarSeries* series = new QStackedBarSeries(chart);
    for (int i(0); i < m_dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        foreach (Data data, m_dataTable[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);
    chart->createDefaultAxes();

    return chart;
}

QChart* ChartWindow::createLineChart() const
{
    QChart* chart = new QChart();
    //TODO: chart->axisX()->setNiceNumbersEnabled(true);
    //TODO: chart->axisY()->setNiceNumbersEnabled(true);
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
    chart->createDefaultAxes();

    return chart;
}

QChart* ChartWindow::createPieChart() const
{
    QChart* chart = new QChart();
    chart->setTitle("Pie chart");

    qreal pieSize = 1.0 / m_dataTable.count();
    for (int i = 0; i < m_dataTable.count(); i++) {
        QPieSeries *series = new QPieSeries(chart);
        foreach (Data data, m_dataTable[i]) {
            QPieSlice *slice = series->append(data.second, data.first.y());
            if (data == m_dataTable[i].first()) {
                slice->setLabelVisible();
                slice->setExploded();
            }
        }
        qreal hPos = (pieSize / 2) + (i / (qreal) m_dataTable.count());
        series->setPieSize(pieSize);
        series->setHorizontalPosition(hPos);
        series->setVerticalPosition(0.5);
        chart->addSeries(series);
    }

    return chart;
}

QChart* ChartWindow::createSplineChart() const
{
    QChart* chart = new QChart();
    //TODO: chart->axisX()->setNiceNumbersEnabled(true);
    //TODO: chart->axisY()->setNiceNumbersEnabled(true);
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
    chart->createDefaultAxes();
    return chart;
}

QChart* ChartWindow::createScatterChart() const
{
    QChart* chart = new QChart();
    //TODO: chart->axisX()->setNiceNumbersEnabled(true);
    //TODO: chart->axisY()->setNiceNumbersEnabled(true);
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
    chart->createDefaultAxes();
    return chart;
}

void ChartWindow::updateUI()
{
    bool opengl = m_openGLCheckBox->isChecked();
    bool isOpengl = qobject_cast<QGLWidget*>(m_view->viewport());
    if ((isOpengl && !opengl) || (!isOpengl && opengl)) {
        m_view->deleteLater();
        m_view = new GraphicsView(m_scene, m_form);
        m_view->setViewport(!opengl ? new QWidget() : new QGLWidget());
        setCentralWidget(m_view);
    }

    QChart::ChartTheme theme = (QChart::ChartTheme) m_themeComboBox->itemData(
        m_themeComboBox->currentIndex()).toInt();

    foreach (QChart *chart, m_chartList)
        chart->setTheme(theme);

    QPalette pal = window()->palette();
    if (theme == QChart::ChartThemeLight) {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeDark) {
        pal.setColor(QPalette::Window, QRgb(0x121218));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    }
    else if (theme == QChart::ChartThemeBlueCerulean) {
        pal.setColor(QPalette::Window, QRgb(0x40434a));
        pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    }
    else if (theme == QChart::ChartThemeBrownSand) {
        pal.setColor(QPalette::Window, QRgb(0x9e8965));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeBlueNcs) {
        pal.setColor(QPalette::Window, QRgb(0x018bba));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else if (theme == QChart::ChartThemeHighContrast) {
        pal.setColor(QPalette::Window, QRgb(0xffab03));
        pal.setColor(QPalette::WindowText, QRgb(0x181818));
    }
    else if (theme == QChart::ChartThemeBlueIcy) {
        pal.setColor(QPalette::Window, QRgb(0xcee7f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    else {
        pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));
    }
    foreach(QGraphicsProxyWidget* widget , m_widgetHash) {
        widget->setPalette(pal);
    }
    m_view->setBackgroundBrush(pal.color((QPalette::Window)));

    QChart::AnimationOptions options(
        m_animatedComboBox->itemData(m_animatedComboBox->currentIndex()).toInt());
    if (m_chartList.at(0)->animationOptions() != options) {
        foreach (QChart *chart, m_chartList)
            chart->setAnimationOptions(options);
    }

    Qt::Alignment alignment(m_legendComboBox->itemData(m_legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        foreach (QChart *chart, m_chartList) {
            chart->legend()->hide();
        }
    }
    else {
        foreach (QChart *chart, m_chartList) {
            chart->legend()->setAlignment(alignment);
            chart->legend()->show();
        }
    }

    bool checked = m_antialiasCheckBox->isChecked();
    if (opengl)
        m_view->setRenderHint(QPainter::HighQualityAntialiasing, checked);
    else
        m_view->setRenderHint(QPainter::Antialiasing, checked);
}

