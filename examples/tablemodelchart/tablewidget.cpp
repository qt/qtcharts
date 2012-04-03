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

#include "tablewidget.h"
#include <QGridLayout>
#include <QTableView>
#include <QStyledItemDelegate>
#include "qlineseries.h"
#include "qsplineseries.h"
#include "qscatterseries.h"
#include "customtablemodel.h"
#include "qpieseries.h"
#include "qareaseries.h"
#include "qbarseries.h"
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTime>

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(100, 100, 1000, 600);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    // create simple model for storing data
    // user's table data model
    m_model = new CustomTableModel;
    m_tableView = new QTableView;
    m_tableView->setModel(m_model);
    m_tableView->setMinimumHeight(240);
//    tableView->setMinimumSize(340, 480);
//    tableView->setItemDelegate(new QStyledItemDelegate);
    m_chart = new QChart;
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(640, 480);

    // create
//    QLineSeries* series = new QLineSeries;
//    QSplineSeries* series = new QSplineSeries;
//    QScatterSeries* series = new QScatterSeries;
//    series->setModel(m_model);
//    series->setModelMapping(0,1, Qt::Vertical);

//    QPieSeries* pieSeries = new QPieSeries;
//    pieSeries->setModel(model);
//    pieSeries

//    chartView->addSeries(series);

    // add, remove data buttons
    QPushButton* addRowAboveButton = new QPushButton("Add row above");
    connect(addRowAboveButton, SIGNAL(clicked()), this, SLOT(addRowAbove()));

    QPushButton* addRowBelowButton = new QPushButton("Add row below");
    connect(addRowBelowButton, SIGNAL(clicked()), this, SLOT(addRowBelow()));

    QPushButton* removeRowButton = new QPushButton("Remove row");
    connect(removeRowButton, SIGNAL(clicked()), this, SLOT(removeRow()));

    m_linesCountSpinBox = new QSpinBox;
    m_linesCountSpinBox->setRange(1, 10);
    m_linesCountSpinBox->setValue(1);

    // buttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(m_linesCountSpinBox);
    buttonsLayout->addWidget(addRowAboveButton);
    buttonsLayout->addWidget(addRowBelowButton);
    buttonsLayout->addWidget(removeRowButton);
    buttonsLayout->addStretch();

    // chart type radio buttons
    m_lineRadioButton = new QRadioButton("Line");
    m_splineRadioButton = new QRadioButton("Spline");
    m_scatterRadioButton = new QRadioButton("Scatter");
    m_pieRadioButton = new QRadioButton("Pie");
    m_areaRadioButton = new QRadioButton("Area");
    m_barRadioButton = new QRadioButton("Bar");

    connect(m_lineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(m_splineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(m_scatterRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(m_pieRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(m_areaRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(m_barRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    m_lineRadioButton->setChecked(true);

    // radio buttons layout
    QVBoxLayout* radioLayout = new QVBoxLayout;
    radioLayout->addWidget(m_lineRadioButton);
    radioLayout->addWidget(m_splineRadioButton);
    radioLayout->addWidget(m_scatterRadioButton);
    radioLayout->addWidget(m_pieRadioButton);
    radioLayout->addWidget(m_areaRadioButton);
    radioLayout->addWidget(m_barRadioButton);
    radioLayout->addStretch();

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonsLayout, 1, 1);
    mainLayout->addLayout(radioLayout, 2, 1);
    mainLayout->addWidget(m_tableView, 1, 0);
    mainLayout->addWidget(m_chartView, 2, 0);
    setLayout(mainLayout);    
    m_lineRadioButton->setFocus();
}

void TableWidget::addRowAbove()
{
//    m_model->insertRow(m_model->rowCount());
//    m_model->insertRow(tableView->currentIndex().row());
    m_model->insertRows(m_tableView->currentIndex().row(), m_linesCountSpinBox->value());

}

void TableWidget::addRowBelow()
{
//    m_model->insertRow(m_model->rowCount());
//    m_model->insertRow(tableView->currentIndex().row() + 1);
    m_model->insertRows(m_tableView->currentIndex().row() + 1, m_linesCountSpinBox->value());

}

void TableWidget::removeRow()
{
//    m_model->removeRow(m_model->rowCount() - 1);
//    m_model->removeRow(tableView->currentIndex().row());
    m_model->removeRows(m_tableView->currentIndex().row(), qMin(m_model->rowCount() - m_tableView->currentIndex().row(), m_linesCountSpinBox->value()));
}

void TableWidget::updateChartType()
{
    m_chart->removeAllSeries();

    if (m_lineRadioButton->isChecked())
    {
        QPen pen;
        pen.setWidth(2);

        QColor seriesColor("#8FBC8F");

        // series 1
        m_series = new QLineSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(0,1, Qt::Vertical);
        m_series->setModelMappingShift(3, 3);
//        series->setModelMapping(0,1, Qt::Horizontal);

        pen.setColor(seriesColor);
        m_series->setPen(pen);
        m_chart->addSeries(m_series);
        for (int i = 1; i <=4; i++)
        {
            m_model->setData(m_model->index(i, 0), seriesColor  , Qt::BackgroundRole);
            m_model->setData(m_model->index(i, 1), seriesColor  , Qt::BackgroundRole);
        }
//        tableView->setsetStyleSheet("QTableView { border: 2px solid red }");

        seriesColor = QColor("#1E90FF");

        // series 2
        m_series = new QLineSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(2,3, Qt::Vertical);
//        series->setModelMapping(2,3, Qt::Horizontal);
        pen.setColor(seriesColor);
        m_series->setPen(pen);
//        m_chart->addSeries(m_series);

        m_chart->axisX()->setRange(0, 500);
        m_chart->axisY()->setRange(0, 120);

        for (int i = 0; i < m_model->rowCount(); i++)
        {
            m_model->setData(m_model->index(i, 2), seriesColor  , Qt::BackgroundRole);
            m_model->setData(m_model->index(i, 3), seriesColor  , Qt::BackgroundRole);
        }
//        // series 3
//        series = new QLineSeries;
//        series->setModel(m_model);
//        series->setModelMapping(4,5, Qt::Vertical);
////        series->setModelMapping(4,5, Qt::Horizontal);
//        chartView->addSeries(series);
    }
    else if (m_splineRadioButton->isChecked())
    {
        // series 1
        m_series = new QSplineSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(0,1, Qt::Vertical);
        m_series->setModelMappingShift(1, 4);
//        series->setModelMapping(0,1, Qt::Horizontal);
        m_chart->addSeries(m_series);

        // series 2
        m_series = new QSplineSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(2,3, Qt::Vertical);
        m_series->setModelMappingShift(0, 0);
//        series->setModelMapping(2,3, Qt::Horizontal);
        m_chart->addSeries(m_series);

        // series 3
        m_series = new QSplineSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(4,5, Qt::Vertical);
        m_series->setModelMappingShift(0, 0);
//        series->setModelMapping(4,5, Qt::Horizontal);
        m_chart->addSeries(m_series);
    }
    else if (m_scatterRadioButton->isChecked())
    {
        // series 1
        m_series = new QScatterSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(0,1, Qt::Vertical);
//        series->setModelMapping(0,1, Qt::Horizontal);
        m_chart->addSeries(m_series);

        // series 2
        m_series = new QScatterSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(2,3, Qt::Vertical);
//        series->setModelMapping(2,3, Qt::Horizontal);
        m_chart->addSeries(m_series);

        // series 3
        m_series = new QScatterSeries;
        m_series->setModel(m_model);
        m_series->setModelMapping(4,5, Qt::Vertical);
//        series->setModelMapping(4,5, Qt::Horizontal);
        m_chart->addSeries(m_series);
    }
    else if (m_pieRadioButton->isChecked())
    {
        // pie 1
        QPieSeries* pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(0,0, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.2, 0.35);
        m_chart->addSeries(pieSeries);

        // pie 2
        pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(1,1, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.8, 0.35);
        m_chart->addSeries(pieSeries);

        // pie 3
        pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(2,2, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.5, 0.65);
        m_chart->addSeries(pieSeries);
    }
    else if (m_areaRadioButton->isChecked())
    {
        QLineSeries* upperLineSeries = new QLineSeries;
        upperLineSeries->setModel(m_model);
        upperLineSeries->setModelMapping(0, 1, Qt::Vertical);
        QLineSeries* lowerLineSeries = new QLineSeries;
        lowerLineSeries->setModel(m_model);
        lowerLineSeries->setModelMapping(2, 3, Qt::Vertical);
        QAreaSeries* areaSeries = new QAreaSeries(upperLineSeries, lowerLineSeries);
        m_chart->addSeries(areaSeries);
    }
    else if (m_barRadioButton->isChecked())
    {
        QBarSeries* barSeries = new QBarSeries(QStringList());
        barSeries->setModel(m_model);
        barSeries->setModelMapping(5, 2, 4, Qt::Vertical);
        barSeries->setToolTipEnabled(true);
        m_chart->addSeries(barSeries);
    }

//    series->setModel(m_model);
//    series->setModelMapping(0,1, Qt::Vertical);
//    chartView->addSeries(series);
}

TableWidget::~TableWidget()
{
    
}
