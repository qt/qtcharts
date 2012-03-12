#include "mainwindow.h"
#include <qchartglobal.h>
#include <qchartview.h>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QChartView *chartView = new QChartView(this);
    chartView->setChartTitle("Click to play with points");
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);

    m_scatter = new QScatterSeries();
    for(qreal x(0.5); x <= 4.0; x += 0.5) {
        for(qreal y(0.5); y <= 4.0; y += 0.5) {
            *m_scatter << QPointF(x, y);
        }
    }
    chartView->addSeries(m_scatter);

    // Add two more series
    m_scatter2 = new QScatterSeries();
    chartView->addSeries(m_scatter2);
    m_scatter3 = new QScatterSeries();
    chartView->addSeries(m_scatter3);

    connect(m_scatter, SIGNAL(clicked(QPointF)), this, SLOT(clickPoint(QPointF)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::clickPoint(QPointF coordinate)
{
    // Remove the clicked point from the series and add points to the two other series we have
    //TODO: fix me
    /*
    int index = m_scatter->closestPoint(coordinate);
    QPointF point = m_scatter->data().at(index);
    Q_ASSERT(m_scatter->removeAt(index));
    point.rx() += 0.25;
    point.ry() += 0.25;
    *m_scatter2 << point;
    point.ry() -= 0.25;
    *m_scatter3 << point;
    */
}
