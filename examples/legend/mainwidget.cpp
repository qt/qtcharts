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
    m_setCount = 0;
    m_chart = new QChart();

//![1]
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
//![1]

    // Create chart view with the chart
    m_chartView = new QChartView(m_chart, this);
    m_chartView->setRubberBand(QChartView::HorizonalRubberBand);

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
}

void MainWidget::detachLegend()
{
//![3]
    // Detach legend from chart
    QLegend *legend = m_chart->legend();
    legend->detachFromChart();

    // Put legend to our custom scene
    m_customScene->addItem(legend);
//![3]

    // This causes redraw
    QSize size(1,1);
    this->resize(this->size() + size);
    this->resize(this->size() - size);
}


void MainWidget::attachLegend()
{
//![4]
    QLegend *legend = m_chart->legend();

    if (m_customScene->items().contains(legend)) {
        // Remove legend from custom scene and put it back to chartview scene.
        // Attach legend back to chart, so that layout works.
        m_customScene->removeItem(legend);
        legend->setParent(m_chart);
        m_chartView->scene()->addItem(legend);
        legend->attachToChart();
    }
//![4]

    // This causes redraw
    QSize size(1,1);
    this->resize(this->size() + size);
    this->resize(this->size() - size);
}

void MainWidget::addBarset()
{
    QBarSet *barSet = new QBarSet(QString("set ") + QString::number(m_setCount));
    m_setCount++;
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
