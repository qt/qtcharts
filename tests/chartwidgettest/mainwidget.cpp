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

#include "mainwidget.h"
#include "dataseriedialog.h"
#include "qchartview.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include "qlineseries.h"
#include <qareaseries.h>
#include <qsplineseries.h>
#include <qbarset.h>
#include <qbarseries.h>
#include <qstackedbarseries.h>
#include <qpercentbarseries.h>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QMessageBox>
#include <cmath>
#include <QDebug>
#include <QStandardItemModel>
#include <QBarCategoryAxis>
#include <QGLWidget>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_addSerieDialog(0),
    m_chart(0)
{
    m_chart = new QChart();

    // Grid layout for the controls for configuring the chart widget
    QGridLayout *grid = new QGridLayout();
    QPushButton *addSeriesButton = new QPushButton("Add series");
    connect(addSeriesButton, SIGNAL(clicked()), this, SLOT(addSeries()));
    grid->addWidget(addSeriesButton, 0, 1);
    initBackroundCombo(grid);
    initScaleControls(grid);
    initThemeCombo(grid);
    initCheckboxes(grid);

    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), grid->rowCount(), 0);
    grid->setRowStretch(grid->rowCount() - 1, 1);

    // Create chart view with the chart
    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRubberBand(QChartView::HorizonalRubberBand);

    // Another grid layout as a main layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(grid, 0, 0);
    mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(mainLayout);
}

// Combo box for selecting the chart's background
void MainWidget::initBackroundCombo(QGridLayout *grid)
{
    QComboBox *backgroundCombo = new QComboBox(this);
    backgroundCombo->addItem("Color");
    backgroundCombo->addItem("Gradient");
    backgroundCombo->addItem("Image");
    connect(backgroundCombo, SIGNAL(currentIndexChanged(int)),
            this, SLOT(backgroundChanged(int)));

    grid->addWidget(new QLabel("Background:"), grid->rowCount(), 0);
    grid->addWidget(backgroundCombo, grid->rowCount() - 1, 1);
}

// Scale related controls (auto-scale vs. manual min-max values)
void MainWidget::initScaleControls(QGridLayout *grid)
{
    m_autoScaleCheck = new QCheckBox("Automatic scaling");
    connect(m_autoScaleCheck, SIGNAL(stateChanged(int)), this, SLOT(autoScaleChanged(int)));
    // Allow setting also non-sense values (like -2147483648 and 2147483647)
    m_xMinSpin = new QSpinBox();
    m_xMinSpin->setMinimum(INT_MIN);
    m_xMinSpin->setMaximum(INT_MAX);
    m_xMinSpin->setValue(0);
    connect(m_xMinSpin, SIGNAL(valueChanged(int)), this, SLOT(xMinChanged(int)));
    m_xMaxSpin = new QSpinBox();
    m_xMaxSpin->setMinimum(INT_MIN);
    m_xMaxSpin->setMaximum(INT_MAX);
    m_xMaxSpin->setValue(10);
    connect(m_xMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(xMaxChanged(int)));
    m_yMinSpin = new QSpinBox();
    m_yMinSpin->setMinimum(INT_MIN);
    m_yMinSpin->setMaximum(INT_MAX);
    m_yMinSpin->setValue(0);
    connect(m_yMinSpin, SIGNAL(valueChanged(int)), this, SLOT(yMinChanged(int)));
    m_yMaxSpin = new QSpinBox();
    m_yMaxSpin->setMinimum(INT_MIN);
    m_yMaxSpin->setMaximum(INT_MAX);
    m_yMaxSpin->setValue(10);
    connect(m_yMaxSpin, SIGNAL(valueChanged(int)), this, SLOT(yMaxChanged(int)));

    grid->addWidget(m_autoScaleCheck, grid->rowCount(), 0);
    grid->addWidget(new QLabel("x min:"), grid->rowCount(), 0);
    grid->addWidget(m_xMinSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("x max:"), grid->rowCount(), 0);
    grid->addWidget(m_xMaxSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("y min:"), grid->rowCount(), 0);
    grid->addWidget(m_yMinSpin, grid->rowCount() - 1, 1);
    grid->addWidget(new QLabel("y max:"), grid->rowCount(), 0);
    grid->addWidget(m_yMaxSpin, grid->rowCount() - 1, 1);

    m_autoScaleCheck->setChecked(true);
}

// Combo box for selecting theme
void MainWidget::initThemeCombo(QGridLayout *grid)
{
    QComboBox *chartTheme = new QComboBox();
    chartTheme->addItem("Default");
    chartTheme->addItem("Light");
    chartTheme->addItem("Blue Cerulean");
    chartTheme->addItem("Dark");
    chartTheme->addItem("Brown Sand");
    chartTheme->addItem("Blue NCS");
    chartTheme->addItem("High Contrast");
    chartTheme->addItem("Blue Icy");
    chartTheme->addItem("Qt");
    connect(chartTheme, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeChartTheme(int)));
    grid->addWidget(new QLabel("Chart theme:"), 8, 0);
    grid->addWidget(chartTheme, 8, 1);
}

// Different check boxes for customizing chart
void MainWidget::initCheckboxes(QGridLayout *grid)
{
    // TODO: setZoomEnabled slot has been removed from QChartView -> Re-implement zoom on/off
    QCheckBox *zoomCheckBox = new QCheckBox("Drag'n drop Zoom");
//    connect(zoomCheckBox, SIGNAL(toggled(bool)), m_chartView, SLOT(setZoomEnabled(bool)));
    zoomCheckBox->setChecked(true);
    grid->addWidget(zoomCheckBox, grid->rowCount(), 0);

    QCheckBox *aliasCheckBox = new QCheckBox("Anti-alias");
    connect(aliasCheckBox, SIGNAL(toggled(bool)), this, SLOT(antiAliasToggled(bool)));
    aliasCheckBox->setChecked(false);
    grid->addWidget(aliasCheckBox, grid->rowCount(), 0);

    QCheckBox *openGLCheckBox = new QCheckBox("Use QGLWidget");
    connect(openGLCheckBox, SIGNAL(toggled(bool)), this, SLOT(openGLToggled(bool)));
    openGLCheckBox->setChecked(false);
    grid->addWidget(openGLCheckBox, grid->rowCount(), 0);
}

void MainWidget::antiAliasToggled(bool enabled)
{
    m_chartView->setRenderHint(QPainter::Antialiasing, enabled);
}

void MainWidget::openGLToggled(bool enabled)
{
    if (enabled) {
        QGLFormat f = QGLFormat::defaultFormat();
        f.setSampleBuffers(true);
        f.setSamples(4);
        QGLFormat::setDefaultFormat(f);
        QGLWidget *g = new QGLWidget();
        m_chartView->setViewport(g);
    } else {
        m_chartView->setViewport(0);
    }
}

void MainWidget::addSeries()
{
    if (!m_addSerieDialog) {
        m_addSerieDialog = new DataSerieDialog(this);
        connect(m_addSerieDialog, SIGNAL(accepted(QString,int,int,QString,bool)),
                this, SLOT(addSeries(QString,int,int,QString,bool)));
    }
    m_addSerieDialog->exec();
}

QList<RealList> MainWidget::generateTestData(int columnCount, int rowCount, QString dataCharacteristics)
{
    QList<RealList> testData;
    for (int j(0); j < columnCount; j++) {
        QList <qreal> newColumn;
        for (int i(0); i < rowCount; i++) {
            if (dataCharacteristics == "Sin") {
                newColumn.append(abs(sin(3.14159265358979 / 50 * i) * 100));
            } else if (dataCharacteristics == "Sin + random") {
                newColumn.append(abs(sin(3.14159265358979 / 50 * i) * 100) + (rand() % 5));
            } else if (dataCharacteristics == "Random") {
                newColumn.append(rand() % 10 + (qreal) rand() / (qreal) RAND_MAX);
            } else if (dataCharacteristics == "Linear") {
                //newColumn.append(i * (j + 1.0));
                // TODO: temporary hack to make pie work; prevent zero values:
                newColumn.append(i * (j + 1.0) + 0.1);
            } else { // "constant"
                newColumn.append((j + 1.0));
            }
        }
        testData.append(newColumn);
    }
    return testData;
}

QStringList MainWidget::generateLabels(int count)
{
    QStringList result;
    for (int i(0); i < count; i++)
        result.append("label" + QString::number(i));
    return result;
}

void MainWidget::addSeries(QString seriesName, int columnCount, int rowCount, QString dataCharacteristics, bool labelsEnabled)
{
    qDebug() << "addSeries: " << seriesName
             << " columnCount: " << columnCount
             << " rowCount: " << rowCount
             << " dataCharacteristics: " << dataCharacteristics
             << " labels enabled: " << labelsEnabled;
    m_defaultSeriesName = seriesName;

    QList<RealList> data = generateTestData(columnCount, rowCount, dataCharacteristics);

    // Line series and scatter series use similar data
    if (seriesName == "Line") {
        for (int j(0); j < data.count(); j ++) {
            QList<qreal> column = data.at(j);
            QLineSeries *series = new QLineSeries();
            series->setName("line" + QString::number(j));
            for (int i(0); i < column.count(); i++)
                series->append(i, column.at(i));
            m_chart->addSeries(series);
        }
    } else if (seriesName == "Area") {
        // TODO: lower series for the area?
        for (int j(0); j < data.count(); j ++) {
            QList<qreal> column = data.at(j);
            QLineSeries *lineSeries = new QLineSeries();
            for (int i(0); i < column.count(); i++)
                lineSeries->append(i, column.at(i));
            QAreaSeries *areaSeries = new QAreaSeries(lineSeries);
            areaSeries->setName("area" + QString::number(j));
            m_chart->addSeries(areaSeries);
        }
    } else if (seriesName == "Scatter") {
        for (int j(0); j < data.count(); j++) {
            QList<qreal> column = data.at(j);
            QScatterSeries *series = new QScatterSeries();
            series->setName("scatter" + QString::number(j));
            for (int i(0); i < column.count(); i++)
                series->append(i, column.at(i));
            m_chart->addSeries(series);
        }
    } else if (seriesName == "Pie") {
        QStringList labels = generateLabels(rowCount);
        for (int j(0); j < data.count(); j++) {
            QPieSeries *series = new QPieSeries();
            QList<qreal> column = data.at(j);
            for (int i(0); i < column.count(); i++)
                series->append(labels.at(i), column.at(i));
            m_chart->addSeries(series);
        }
    } else if (seriesName == "Bar"
               || seriesName == "Stacked bar"
               || seriesName == "Percent bar") {
        QStringList category;
        QStringList labels = generateLabels(rowCount);
        foreach (QString label, labels)
            category << label;
        QAbstractBarSeries* series = 0;
        if (seriesName == "Bar") {
            series = new QBarSeries(this);
            QBarCategoryAxis* axis = new QBarCategoryAxis();
            axis->append(category);
            m_chart->setAxisX(axis,series);
        } else if (seriesName == "Stacked bar") {
            series = new QStackedBarSeries(this);
            QBarCategoryAxis* axis = new QBarCategoryAxis();
            axis->append(category);
            m_chart->setAxisX(axis,series);
        } else {
            series = new QPercentBarSeries(this);
            QBarCategoryAxis* axis = new QBarCategoryAxis();
            axis->append(category);
            m_chart->setAxisX(axis,series);
        }

        for (int j(0); j < data.count(); j++) {
            QList<qreal> column = data.at(j);
            QBarSet *set = new QBarSet("set" + QString::number(j));
            for (int i(0); i < column.count(); i++)
                *set << column.at(i);
            series->append(set);
        }

        m_chart->addSeries(series);
    } else if (seriesName == "Spline") {
        for (int j(0); j < data.count(); j ++) {
            QList<qreal> column = data.at(j);
            QSplineSeries *series = new QSplineSeries();
            for (int i(0); i < column.count(); i++)
                series->append(i, column.at(i));
            m_chart->addSeries(series);
        }
    }
    m_chart->createDefaultAxes();
}

void MainWidget::backgroundChanged(int itemIndex)
{
    qDebug() << "backgroundChanged: " << itemIndex;
}

void MainWidget::autoScaleChanged(int value)
{
    if (value) {
        // TODO: enable auto scaling
    } else {
        // TODO: set scaling manually (and disable auto scaling)
    }

    m_xMinSpin->setEnabled(!value);
    m_xMaxSpin->setEnabled(!value);
    m_yMinSpin->setEnabled(!value);
    m_yMaxSpin->setEnabled(!value);
}

void MainWidget::xMinChanged(int value)
{
    qDebug() << "xMinChanged: " << value;
}

void MainWidget::xMaxChanged(int value)
{
    qDebug() << "xMaxChanged: " << value;
}

void MainWidget::yMinChanged(int value)
{
    qDebug() << "yMinChanged: " << value;
}

void MainWidget::yMaxChanged(int value)
{
    qDebug() << "yMaxChanged: " << value;
}

void MainWidget::changeChartTheme(int themeIndex)
{
    qDebug() << "changeChartTheme: " << themeIndex;
    if (themeIndex == 0)
        m_chart->setTheme(QChart::ChartThemeLight);
    else
        m_chart->setTheme((QChart::ChartTheme) (themeIndex - 1));
}
