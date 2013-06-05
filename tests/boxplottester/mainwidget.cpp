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

#include "mainwidget.h"
#include "customtablemodel.h"
#include <QVBoxPlotModelMapper>
#include <QTableView>
#include <QHeaderView>
#include <QChartView>
#include <QBoxPlotSeries>
#include <QBoxSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QBrush>
#include <QColor>
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
#include <QLogValueAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

QString addCategories[] = {"Jul", "Aug", "Sep", "Nov", "Dec"};
static const int maxAddCategories = 5;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_chart(0),
    m_axis(0),
    rowPos(0),
    nSeries(0),
    nNewBoxes(0)
{
    m_chart = new QChart();

    // Grid layout for the controls for configuring the chart widget
    QGridLayout *grid = new QGridLayout();

    // Create add a series button
    QPushButton *addSeriesButton = new QPushButton("Add a series");
    connect(addSeriesButton, SIGNAL(clicked()), this, SLOT(addSeries()));
    grid->addWidget(addSeriesButton, rowPos++, 1);

    // Create remove a series button
    QPushButton *removeSeriesButton = new QPushButton("Remove a series");
    connect(removeSeriesButton, SIGNAL(clicked()), this, SLOT(removeSeries()));
    grid->addWidget(removeSeriesButton, rowPos++, 1);

    // Create add a single box button
    QPushButton *addBoxButton = new QPushButton("Add a box");
    connect(addBoxButton, SIGNAL(clicked()), this, SLOT(addBox()));
    grid->addWidget(addBoxButton, rowPos++, 1);

    // Create insert a box button
    QPushButton *insertBoxButton = new QPushButton("Insert a box");
    connect(insertBoxButton, SIGNAL(clicked()), this, SLOT(insertBox()));
    grid->addWidget(insertBoxButton, rowPos++, 1);

    // Create add a single box button
    QPushButton *removeBoxButton = new QPushButton("Remove a box");
    connect(removeBoxButton, SIGNAL(clicked()), this, SLOT(removeBox()));
    grid->addWidget(removeBoxButton, rowPos++, 1);

    // Create clear button
    QPushButton *clearButton = new QPushButton("Clear");
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    grid->addWidget(clearButton, rowPos++, 1);

    // Create clear button
    QPushButton *clearBoxButton = new QPushButton("ClearBox");
    connect(clearBoxButton, SIGNAL(clicked()), this, SLOT(clearBox()));
    grid->addWidget(clearBoxButton, rowPos++, 1);


    // Create set brush button
    QPushButton *setBrushButton = new QPushButton("Set brush");
    connect(setBrushButton, SIGNAL(clicked()), this, SLOT(setBrush()));
    grid->addWidget(setBrushButton, rowPos++, 1);

    initThemeCombo(grid);
    initCheckboxes(grid);

    m_model = new CustomTableModel;
    QTableView *tableView = new QTableView;
    tableView->setModel(m_model);
    tableView->setMaximumWidth(200);
    grid->addWidget(tableView, rowPos++, 0, 3, 2, Qt::AlignLeft);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    // add row with empty label to make all the other rows static
    grid->addWidget(new QLabel(""), grid->rowCount(), 0);
    grid->setRowStretch(grid->rowCount() - 1, 1);

    // Create chart view with the chart
    m_chartView = new QChartView(m_chart, this);

    // Another grid layout as a main layout
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addLayout(grid, 0, 0);
    mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    setLayout(mainLayout);

    legendToggled(false);
    animationToggled(false);
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
    connect(chartTheme, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeChartTheme(int)));
    grid->addWidget(new QLabel("Chart theme:"), rowPos, 0);
    grid->addWidget(chartTheme, rowPos++, 1);
}

// Different check boxes for customizing chart
void MainWidget::initCheckboxes(QGridLayout *grid)
{
    QCheckBox *animationCheckBox = new QCheckBox("Animation");
    connect(animationCheckBox, SIGNAL(toggled(bool)), this, SLOT(animationToggled(bool)));
    animationCheckBox->setChecked(false);
    grid->addWidget(animationCheckBox, rowPos++, 0);

    QCheckBox *legendCheckBox = new QCheckBox("Legend");
    connect(legendCheckBox, SIGNAL(toggled(bool)), this, SLOT(legendToggled(bool)));
    legendCheckBox->setChecked(false);
    grid->addWidget(legendCheckBox, rowPos++, 0);

    QCheckBox *titleCheckBox = new QCheckBox("Title");
    connect(titleCheckBox, SIGNAL(toggled(bool)), this, SLOT(titleToggled(bool)));
    titleCheckBox->setChecked(false);
    grid->addWidget(titleCheckBox, rowPos++, 0);

    QCheckBox *modelMapperCheckBox = new QCheckBox("Use model mapper");
    connect(modelMapperCheckBox, SIGNAL(toggled(bool)), this, SLOT(modelMapperToggled(bool)));
    modelMapperCheckBox->setChecked(false);
    grid->addWidget(modelMapperCheckBox, rowPos++, 0);

}

void MainWidget::addSeries()
{
    qDebug() << "BoxPlotTester::MainWidget::addSeries()";

    if (nSeries > 9)
        return;

    // Initial data
    QBoxSet *set0 = new QBoxSet();
    QBoxSet *set1 = new QBoxSet();
    QBoxSet *set2 = new QBoxSet();
    QBoxSet *set3 = new QBoxSet();
    QBoxSet *set4 = new QBoxSet();
    QBoxSet *set5 = new QBoxSet();

    //      low  bot   med   top  upp
    *set0 << -1 << 2 << 4 << 13 << 15;
    *set1 << 5 << 6 << 7.5 << 8 << 12;
    *set2 << 3 << 5 << 5.7 << 8 << 9;
    *set3 << 5 << 6 << 6.8 << 7 << 8;
    *set4 << 4 << 5 << 5.2 << 6 << 7;
    *set5 << 4 << 7 << 8.2 << 9 << 10;

    m_series[nSeries] = new QBoxPlotSeries();
    m_series[nSeries]->append(set0);
    m_series[nSeries]->append(set1);
    m_series[nSeries]->append(set2);
    m_series[nSeries]->append(set3);
    m_series[nSeries]->append(set4);
    m_series[nSeries]->append(set5);
    m_series[nSeries]->setName("Box & Whiskers");

    connect(m_series[nSeries], SIGNAL(clicked(QBoxSet*)), this, SLOT(boxClicked(QBoxSet*)));
    connect(m_series[nSeries], SIGNAL(hovered(bool, QBoxSet*)), this, SLOT(boxHovered(bool, QBoxSet*)));
    connect(set1, SIGNAL(clicked()), this, SLOT(singleBoxClicked()));
    connect(set2, SIGNAL(hovered(bool)), this, SLOT(singleBoxHovered(bool)));

    m_chart->addSeries(m_series[nSeries]);

    if (!m_axis) {
        QStringList categories;
        categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
        m_axis = new QBarCategoryAxis();
        m_axis->append(categories);
        m_chart->createDefaultAxes();
    }
    m_chart->setAxisX(m_axis, m_series[nSeries]);

    nSeries++;
}

void MainWidget::removeSeries()
{
    qDebug() << "BoxPlotTester::MainWidget::removeSeries()";

    if (nSeries > 0) {
        nSeries--;
        m_chart->removeSeries(m_series[nSeries]);
        delete m_series[nSeries];
    } else {
        qDebug() << "Create a series first";
    }
}

void MainWidget::addBox()
{
    qDebug() << "BoxPlotTester::MainWidget::addBox()";

    if (nSeries > 0 && nNewBoxes < maxAddCategories) {
        QBoxSet *newSet = new QBoxSet();
        newSet->setValue(QBoxSet::LowerExtreme, 5.0);
        newSet->setValue(QBoxSet::LowerQuartile, 6.0);
        newSet->setValue(QBoxSet::Median, 6.8);
        newSet->setValue(QBoxSet::UpperQuartile, 7.0);
        newSet->setValue(QBoxSet::UpperExtreme, 8.0);

        m_series[0]->append(newSet);

        m_axis->append(addCategories[nNewBoxes]);

        nNewBoxes++;
    }
}

void MainWidget::insertBox()
{
    qDebug() << "BoxPlotTester::MainWidget::insertBox()";

    if (nSeries > 0) {
        QBoxSet *newSet = new QBoxSet();
        *newSet << 2 << 6 << 6.8 << 7 << 10;

        for (int i = 0; i < nSeries; i++)
            m_series[i]->insert(1, newSet);

        m_axis->append(addCategories[nNewBoxes]);

        nNewBoxes++;
    }
}

void MainWidget::removeBox()
{
    qDebug() << "BoxPlotTester::MainWidget::removeBox";

    if (nSeries > 0) {
        for (int i = 0; i < nSeries; i++) {
            qDebug() << "m_series[i]->count() = " << m_series[i]->count();
            if (m_series[i]->count() > 3) {
                QList<QBoxSet *> sets = m_series[i]->boxSets();
                m_series[i]->remove(sets.at(m_series[i]->count() - 3));
            }
        }

        if (m_axis->count() > 3)
            m_axis->remove(m_axis->at(1));
    } else {
        qDebug() << "Create a series first";
    }
}

void MainWidget::clear()
{
    qDebug() << "BoxPlotTester::MainWidget::clear";

    if (nSeries > 0)
        m_series[0]->clear();
    else
        qDebug() << "Create a series first";
}

void MainWidget::clearBox()
{
    qDebug() << "BoxPlotTester::MainWidget::clearBox";

    if (nSeries > 0) {
        QList<QBoxSet *> sets = m_series[0]->boxSets();
        sets.at(1)->clear();
    } else {
        qDebug() << "Create a series first";
    }
}

void MainWidget::setBrush()
{
    qDebug() << "BoxPlotTester::MainWidget::setBrush";

    if (nSeries > 0) {
        QList<QBoxSet *> sets = m_series[0]->boxSets();
        sets.at(1)->setBrush(QBrush(QColor(Qt::yellow)));
    } else {
        qDebug() << "Create a series first";
    }
}

void MainWidget::animationToggled(bool enabled)
{
    qDebug() << "BoxPlotTester::Animation toggled to " << enabled;
    if (enabled)
        m_chart->setAnimationOptions(QChart::SeriesAnimations);
    else
        m_chart->setAnimationOptions(QChart::NoAnimation);
}

void MainWidget::legendToggled(bool enabled)
{
    qDebug() << "BoxPlotTester::Legend toggled to " << enabled;
    m_chart->legend()->setVisible(enabled);
    if (enabled)
        m_chart->legend()->setAlignment(Qt::AlignBottom);
}

void MainWidget::titleToggled(bool enabled)
{
    qDebug() << "BoxPlotTester::Title toggled to " << enabled;
    if (enabled)
        m_chart->setTitle("Simple boxplotchart example");
    else
        m_chart->setTitle("");
}

void MainWidget::modelMapperToggled(bool enabled)
{
    if (enabled) {
        m_series[nSeries] = new QBoxPlotSeries();

        int first = 0;
        int count = 5;
        QVBoxPlotModelMapper *mapper = new QVBoxPlotModelMapper(this);
        mapper->setFirstBoxSetColumn(0);
        mapper->setLastBoxSetColumn(5);
        mapper->setFirstRow(first);
        mapper->setRowCount(count);
        mapper->setSeries(m_series[nSeries]);
        mapper->setModel(m_model);
        m_chart->addSeries(m_series[nSeries]);

        nSeries++;
    } else {
        removeSeries();
    }
}

void MainWidget::changeChartTheme(int themeIndex)
{
    qDebug() << "BoxPlotTester::changeChartTheme: " << themeIndex;
    if (themeIndex == 0)
        m_chart->setTheme(QChart::ChartThemeLight);
    else
        m_chart->setTheme((QChart::ChartTheme) (themeIndex - 1));
}

void MainWidget::boxClicked(QBoxSet *set)
{
    qDebug() << "boxClicked, median = " << set->at(QBoxSet::Median);
}

void MainWidget::boxHovered(bool state, QBoxSet *set)
{
    if (state)
        qDebug() << "box median " << set->at(QBoxSet::Median) << " hover started";
    else
        qDebug() << "box median " << set->at(QBoxSet::Median) << " hover ended";
}

void MainWidget::singleBoxClicked()
{
    qDebug() << "singleBoxClicked";
}

void MainWidget::singleBoxHovered(bool state)
{
    if (state)
        qDebug() << "single box hover started";
    else
        qDebug() << "single box hover ended";
}
