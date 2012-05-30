#include "mainwidget.h"
#include <QChart>
#include <QChartView>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QBarSet>
#include <QBarSeries>
#include <QLegend>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();
    QPushButton *detachLegendButton = new QPushButton("detach legend");
    connect(detachLegendButton, SIGNAL(clicked()), this, SLOT(detachLegend()));
    m_buttonLayout->addWidget(detachLegendButton, 0, 0);
    QPushButton *attachLegendButton = new QPushButton("attach legend");
    connect(attachLegendButton, SIGNAL(clicked()), this, SLOT(attachLegend()));
    m_buttonLayout->addWidget(attachLegendButton, 1, 0);

    QPushButton *addSetButton = new QPushButton("add barset");
    connect(addSetButton, SIGNAL(clicked()), this, SLOT(addBarset()));
    m_buttonLayout->addWidget(addSetButton, 2, 0);
    QPushButton *removeBarsetButton = new QPushButton("remove barset");
    connect(removeBarsetButton, SIGNAL(clicked()), this, SLOT(removeBarset()));
    m_buttonLayout->addWidget(removeBarsetButton, 3, 0);

    // Create chart view with the chart
//![1]
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRubberBand(QChartView::HorizonalRubberBand);
//![1]

    // Create custom scene and view, where detached legend will be drawn
//![2]
    m_customView = new QGraphicsView(this);
    m_customScene = new QGraphicsScene(this);
    m_customView->setScene(m_customScene);
//![2]

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0);
    m_mainLayout->addWidget(m_chartView, 0, 1, 3, 1);
    m_mainLayout->addWidget(m_customView, 0, 2, 3, 1);
    setLayout(m_mainLayout);

    createSeries();
}

void MainWidget::createSeries()
{
//![3]
    m_series = new QBarSeries();
    addBarset();
    addBarset();
    addBarset();
    addBarset();

    m_chart->addSeries(m_series);
    m_chart->setTitle("Legend detach example");

    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(QLegend::AlignmentBottom);
    m_chart->axisY()->setNiceNumbersEnabled(true);

    m_chartView->setRenderHint(QPainter::Antialiasing);
//![3]
}

void MainWidget::detachLegend()
{
    // Detach legend from chart and
    // put legend to our custom scene
//![4]
    QLegend *legend = m_chart->legend();
    legend->detachFromChart();
    legend->setGeometry(m_customView->rect());
    m_customScene->addItem(legend);
//![4]

    // This forces redraw
    QSize delta(1,1);
    resize(size() + delta);
    resize(size() - delta);
}


void MainWidget::attachLegend()
{
    // Remove legend from custom scene and put it back to chartview scene.
    // Attach legend back to chart, so that layout works.

//![5]
    QLegend *legend = m_chart->legend();

    if (m_customScene->items().contains(legend)) {
        m_customScene->removeItem(legend);
        m_chartView->scene()->addItem(legend);
        legend->attachToChart();
    }
//![5]

    // This forces redraw
    QSize delta(1,1);
    resize(size() + delta);
    resize(size() - delta);
}

void MainWidget::addBarset()
{
    QBarSet *barSet = new QBarSet(QString("set ") + QString::number(m_series->barsetCount()));
    qreal delta = m_series->barsetCount() * 0.1;
    *barSet << QPointF(0.0 + delta, 1 + delta) << QPointF(1.0 + delta, 2 + delta) << QPointF(2.0 + delta, 3 + delta) << QPointF(3.0 + delta, 4 + delta);
    m_series->append(barSet);
}

void MainWidget::removeBarset()
{
    QList<QBarSet*> sets = m_series->barSets();
    if (sets.count() > 0) {
        m_series->remove(sets.at(sets.count()-1));
    }
}
