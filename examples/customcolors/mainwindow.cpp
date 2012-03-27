#include "mainwindow.h"
#include <qchartview.h>
#include <qpieseries.h>
#include <qpieslice.h>
#include <qlineseries.h>
#include <qscatterseries.h>
#include <qchartaxis.h>
#include <QDebug>

QTCOMMERCIALCHART_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Here's the set of company's colors used throughout the example
    m_companyColor1 = "#b90020";
    m_companyColor2 = "#6d0013";
    m_companyColor3 = "#f5d5d5";
    m_companyColor4 = "#fcfcfc";

    resize(400, 300);
    setWindowFlags(Qt::FramelessWindowHint);

    // Create chart view
    //! [4]
    m_chartView = new QChartView(this);
    m_chartView->setChartTheme(QChart::ChartThemeHighContrast);
    //! [4]
    setCentralWidget(m_chartView);
    m_chartView->setChartTitle("Custom colors example");
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // Create line series
    m_line = new QLineSeries();
    m_line->add(0.0, 1.1);
    m_line->add(1.0, 2.3);
    m_line->add(2.0, 2.1);
    m_line->add(3.0, 3.3);
    m_chartView->addSeries(m_line);

    // Create scatter series with the same data
    m_scatter = new QScatterSeries();
    m_scatter->add(m_line->data());
    m_chartView->addSeries(m_scatter);

    // Create pie series with different data
    m_pie = new QPieSeries();
    m_pie->add(1.1, "1");
    m_pie->add(2.1, "2");
    m_pie->add(3.0, "3");
    m_pie->setPiePosition(0.7, 0.7);
    m_pie->setPieSize(0.5);
    m_chartView->addSeries(m_pie);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(customize()));
    m_timer.setInterval(1500);
    m_timer.setSingleShot(false);
    m_timer.start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::customize()
{
    //! [1]
    // Use a gradient from "color 3" to "color 4" for chart background
    QLinearGradient chartGradient(0, 0, 0, 300);
    chartGradient.setColorAt(0.0, m_companyColor3);
    chartGradient.setColorAt(0.5, m_companyColor4);
    chartGradient.setColorAt(1.0, m_companyColor3);
    m_chartView->setChartBackgroundBrush(chartGradient);
    m_chartView->setBackgroundBrush(m_companyColor4);
    m_chartView->setChartTitleBrush(m_companyColor1);
    //! [1]

    //! [2]
    QPen color1Pen(m_companyColor1, 4.0);
    m_chartView->axisX()->setAxisPen(color1Pen);
    m_chartView->axisY()->setAxisPen(color1Pen);
    //! [2]

    //! [3]
    // Customize pen of the line series
    m_line->setPen(color1Pen);

    // Customize pen and brush for the scatter
    m_scatter->setPen(color1Pen);
    m_scatter->setBrush(m_companyColor3);

    // Customize pen and brush for the pie
    for (int i(0); i < m_pie->slices().count(); i++) {
        Qt::BrushStyle style = static_cast<Qt::BrushStyle>(i + 1);
        m_pie->slices().at(i)->setBrush(QBrush(m_companyColor2, style));
        m_pie->slices().at(i)->setPen(color1Pen);
    }
    //! [3]

    // Calculate new colors to be used on the next update for the series
    m_companyColor1.setRed((m_companyColor1.red() + 25) % 255);
    m_companyColor1.setGreen((m_companyColor1.green() + 25) % 255);
    m_companyColor1.setBlue((m_companyColor1.blue() + 25) % 255);
    m_companyColor2.setRed((m_companyColor2.red() + 25) % 255);
    m_companyColor2.setGreen((m_companyColor2.green() + 25) % 255);
    m_companyColor2.setBlue((m_companyColor2.blue() + 25) % 255);
}
