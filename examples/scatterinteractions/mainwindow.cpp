#include "mainwindow.h"
#include <qchartglobal.h>
#include <qchartview.h>
#include <qchartaxis.h>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QChartView *chartView = new QChartView(this);
    chartView->setChartTitle("Click to remove scatter point");
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);

    m_scatter = new QScatterSeries();
    for(qreal x(0.5); x <= 4.0; x += 0.5) {
        for(qreal y(0.5); y <= 4.0; y += 0.5) {
            *m_scatter << QPointF(x, y);
        }
    }

    chartView->addSeries(m_scatter);
    chartView->axisX()->setRange(0,4.5);
    chartView->axisY()->setRange(0,4.5);

    connect(m_scatter, SIGNAL(clicked(const QPointF&)), this, SLOT(handleClickedPoint(const QPointF&)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleClickedPoint(const QPointF& point)
{
    m_scatter->remove(point);
}
