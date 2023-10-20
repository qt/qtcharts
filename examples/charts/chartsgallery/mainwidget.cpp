// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause


#include "areawidget.h"
#include "boxplotwidget.h"
#include "barmodelmapperwidget.h"
#include "barwidget.h"
#include "barpercentwidget.h"
#include "barstackedwidget.h"
#include "calloutwidget.h"
#include "candlestickwidget.h"
#include "contentwidget.h"
#include "customchartwidget.h"
#include "datetimeaxiswidget.h"
#include "donutbreakdownwidget.h"
#include "donutwidget.h"
#include "dynamicsplinewidget.h"
#include "horizontalbarwidget.h"
#include "horizontalpercentbarwidget.h"
#include "horizontalstackedbarwidget.h"
#include "interactionswidget.h"
#include "legendwidget.h"
#include "legendmarkerswidget.h"
#include "lightmarkerswidget.h"
#include "lineandbarwidget.h"
#include "linewidget.h"
#include "logaxiswidget.h"
#include "mainwidget.h"
#include "modeldatawidget.h"
#include "multiaxiswidget.h"
#include "nesteddonutswidget.h"
#include "pccwidget.h"
#include "piewidget.h"
#include "piedrilldownwidget.h"
#include "pointconfigurationwidget.h"
#include "polarchartwidget.h"
#include "scatterwidget.h"
#include "scatterinteractionswidget.h"
#include "selectedbarwidget.h"
#include "splinewidget.h"
#include "stackeddrilldownwidget.h"
#include "temperaturerecordswidget.h"
#include "themewidget.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QListView>
#include <QModelIndex>
#include <QStringListModel>
#include <QVBoxLayout>

#include <algorithm>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_listModel(new QStringListModel(this))
    , m_contentArea(new QWidget(this))
{
    m_exampleMap.insert(tr("Area Chart"), AreaChart);
    m_exampleMap.insert(tr("Bar Model Mapper"), BarModelMapper);
    m_exampleMap.insert(tr("Bar Chart"), BarChart);
    m_exampleMap.insert(tr("Bar Chart Percent"), BarChartPercent);
    m_exampleMap.insert(tr("Bar Chart Stacked"), BarChartStacked);
    m_exampleMap.insert(tr("Bar Chart Horizontal"), BarChartHorizontal);
    m_exampleMap.insert(tr("Bar Chart Percent Horizontal"), BarChartHorizontalPercent);
    m_exampleMap.insert(tr("Bar Chart Stacked Horizontal"), BarChartHorizontalStacked);
    m_exampleMap.insert(tr("Box Plot Chart"), BoxPlotChart);
    m_exampleMap.insert(tr("Callout"), Callout);
    m_exampleMap.insert(tr("Candlestick Chart"), CandleStickChart);
    m_exampleMap.insert(tr("Chart Interactions"), ChartInteractions);
    m_exampleMap.insert(tr("Chart Themes"), ChartThemes);
    m_exampleMap.insert(tr("Custom Chart"), CustomChart);
    m_exampleMap.insert(tr("Datetime Axis"), DateTimeAxis);
    m_exampleMap.insert(tr("Donut"), Donut);
    m_exampleMap.insert(tr("Donut Breakdown"), DonutBreakdown);
    m_exampleMap.insert(tr("Drilldown Bar Chart"), StackedDrilldown);
    m_exampleMap.insert(tr("Drilldown Pie Chart"), PieDrilldown);
    m_exampleMap.insert(tr("Dynamic Spline Chart"), DynamicSplineChart);
    m_exampleMap.insert(tr("Legend"), Legend);
    m_exampleMap.insert(tr("Legend Markers"), LegendMarkers);
    m_exampleMap.insert(tr("Light Markers and Point Selection"), LightMarkersPointSelection);
    m_exampleMap.insert(tr("Line and Bar Chart"), LineAndBarChart);
    m_exampleMap.insert(tr("Line Chart"), LineChart);
    m_exampleMap.insert(tr("Log Axis"), LogAxis);
    m_exampleMap.insert(tr("Model Data"), ModelData);
    m_exampleMap.insert(tr("Multiple Axes"), MultiAxis);
    m_exampleMap.insert(tr("Nested Donuts"), NestedDonuts);
    m_exampleMap.insert(tr("Pie Chart Customization"), PieChartCustomization);
    m_exampleMap.insert(tr("Pie Chart"), PieChart);
    m_exampleMap.insert(tr("Point Configuration"), PointConfiguration);
    m_exampleMap.insert(tr("Polar Chart"), PolarChart);
    m_exampleMap.insert(tr("Scatter Interactions"), ScatterInteractions);
    m_exampleMap.insert(tr("Scatter Chart"), ScatterChart);
    m_exampleMap.insert(tr("Selected Bar"), SelectedBar);
    m_exampleMap.insert(tr("Spline Chart"), SplineChart);
    m_exampleMap.insert(tr("Temperature Records"), TemperatureRecords);

    QStringList examples = m_exampleMap.keys();
    std::sort(examples.begin(), examples.end());
    m_listModel->setStringList(examples);

    m_listView->setModel(m_listModel);
    m_listView->setCurrentIndex(m_listModel->index(0));
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_contentArea->installEventFilter(this);

    setMinimumSize(800, 400);
    resize(1200, 600);

    connect(m_listView->selectionModel(), &QItemSelectionModel::currentChanged, this,
            [this](const QModelIndex &index) {
        setActiveExample(m_exampleMap[m_listModel->data(index).toString()]);
    });

    setActiveExample(m_exampleMap[examples[0]]);

    setMouseTracking(true);

    qApp->setApplicationDisplayName(tr("Qt Charts Example Gallery"));
}

void MainWidget::resizeEvent(QResizeEvent *)
{
    bool isHorizontal = width() >= height();
    if (!layout() || isHorizontal != m_isHorizontal)
        relayout(isHorizontal);

    if (m_isHorizontal)
        m_listView->setMaximumHeight(QWIDGETSIZE_MAX);
    else
        m_listView->setMaximumHeight(height() / 3);
}

bool MainWidget::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Resize && object == m_contentArea && m_activeWidget)
        m_activeWidget->resize(m_contentArea->size());
    return QObject::eventFilter(object, event);
}

void MainWidget::setActiveExample(Example example)
{
    // We only keep one example alive at the time to save resources.
    // This also allows resetting the example by switching to another example and back.
    if (m_activeWidget) {
        m_activeWidget->setVisible(false);
        m_activeWidget->deleteLater();
    }

    switch (example) {
    case AreaChart:
        m_activeWidget = new AreaWidget(m_contentArea);
        break;
    case BarModelMapper:
        m_activeWidget = new BarModelMapperWidget(m_contentArea);
        break;
    case BarChart:
        m_activeWidget = new BarWidget(m_contentArea);
        break;
    case BarChartPercent:
        m_activeWidget = new BarPercentWidget(m_contentArea);
        break;
    case BarChartStacked:
        m_activeWidget = new BarStackedWidget(m_contentArea);
        break;
    case BarChartHorizontal:
        m_activeWidget = new HorizontalBarWidget(m_contentArea);
        break;
    case BarChartHorizontalPercent:
        m_activeWidget = new HorizontalPercentBarWidget(m_contentArea);
        break;
    case BarChartHorizontalStacked:
        m_activeWidget = new HorizontalStackedBarWidget(m_contentArea);
        break;
    case BoxPlotChart:
        m_activeWidget = new BoxPlotWidget(m_contentArea);
        break;
    case Callout:
        m_activeWidget = new CalloutWidget(m_contentArea);
        break;
    case CandleStickChart:
        m_activeWidget = new CandleStickWidget(m_contentArea);
        break;
    case ChartInteractions:
        m_activeWidget = new InteractionsWidget(m_contentArea);
        break;
    case ChartThemes:
        m_activeWidget = new ThemeWidget(m_contentArea);
        break;
    case CustomChart:
        m_activeWidget = new CustomChartWidget(m_contentArea);
        break;
    case DateTimeAxis:
        m_activeWidget = new DateTimeAxisWidget(m_contentArea);
        break;
    case Donut:
        m_activeWidget = new DonutWidget(m_contentArea);
        break;
    case DonutBreakdown:
        m_activeWidget = new DonutBreakdownWidget(m_contentArea);
        break;
    case DynamicSplineChart:
        m_activeWidget = new DynamicSplineWidget(m_contentArea);
        break;
    case Legend:
        m_activeWidget = new LegendWidget(m_contentArea);
        break;
    case LegendMarkers:
        m_activeWidget = new LegendMarkersWidget(m_contentArea);
        break;
    case LightMarkersPointSelection:
        m_activeWidget = new LightMarkersWidget(m_contentArea);
        break;
    case LineAndBarChart:
        m_activeWidget = new LineAndBarWidget(m_contentArea);
        break;
    case LineChart:
        m_activeWidget = new LineWidget(m_contentArea);
        break;
    case LogAxis:
        m_activeWidget = new LogAxisWidget(m_contentArea);
        break;
    case ModelData:
        m_activeWidget = new ModelDataWidget(m_contentArea);
        break;
    case MultiAxis:
        m_activeWidget = new MultiAxisWidget(m_contentArea);
        break;
    case NestedDonuts:
        m_activeWidget = new NestedDonutsWidget(m_contentArea);
        break;
    case PieChartCustomization:
        m_activeWidget = new PccWidget(m_contentArea);
        break;
    case PieDrilldown:
        m_activeWidget = new PieDrilldownWidget(m_contentArea);
        break;
    case PieChart:
        m_activeWidget = new PieWidget(m_contentArea);
        break;
    case PointConfiguration:
        m_activeWidget = new PointConfigurationWidget(m_contentArea);
        break;
    case PolarChart:
        m_activeWidget = new PolarChartWidget(m_contentArea);
        break;
    case ScatterInteractions:
        m_activeWidget = new ScatterInteractionsWidget(m_contentArea);
        break;
    case ScatterChart:
        m_activeWidget = new ScatterWidget(m_contentArea);
        break;
    case SelectedBar:
        m_activeWidget = new SelectedBarWidget(m_contentArea);
        break;
    case SplineChart:
        m_activeWidget = new SplineWidget(m_contentArea);
        break;
    case TemperatureRecords:
        m_activeWidget = new TemperatureRecordsWidget(m_contentArea);
        break;
    case StackedDrilldown:
        m_activeWidget = new StackedDrilldownWidget(m_contentArea);
        break;
    }

    m_activeWidget->load();
    m_activeWidget->resize(m_contentArea->size());
    m_activeWidget->setVisible(true);
}

void MainWidget::relayout(bool horizontal)
{
    m_isHorizontal = horizontal;

    delete layout();

    QBoxLayout *layout;
    if (horizontal) {
        layout = new QHBoxLayout(this);
        layout->addWidget(m_listView);
        layout->addWidget(m_contentArea);
        m_listView->setMaximumWidth(220);
    } else {
        layout = new QVBoxLayout(this);
        layout->addWidget(m_contentArea);
        layout->addWidget(m_listView);
        m_listView->setMaximumWidth(QWIDGETSIZE_MAX);
    }
    setLayout(layout);
}
