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
    tableView = new QTableView;
    tableView->setModel(m_model);
    tableView->setMinimumHeight(240);
//    tableView->setMinimumSize(340, 480);
//    tableView->setItemDelegate(new QStyledItemDelegate);
    chartView = new QChartView(this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);

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

    linesCountSpinBox = new QSpinBox;
    linesCountSpinBox->setRange(1, 10);
    linesCountSpinBox->setValue(1);

    // buttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(linesCountSpinBox);
    buttonsLayout->addWidget(addRowAboveButton);
    buttonsLayout->addWidget(addRowBelowButton);
    buttonsLayout->addWidget(removeRowButton);
    buttonsLayout->addStretch();

    // chart type radio buttons
    lineRadioButton = new QRadioButton("Line");
    splineRadioButton = new QRadioButton("Spline");
    scatterRadioButton = new QRadioButton("Scatter");
    pieRadioButton = new QRadioButton("Pie");
    areaRadioButton = new QRadioButton("Area");
    barRadioButton = new QRadioButton("Bar");

    connect(lineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(splineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(scatterRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(pieRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(areaRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(barRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    lineRadioButton->setChecked(true);

    // radio buttons layout
    QVBoxLayout* radioLayout = new QVBoxLayout;
    radioLayout->addWidget(lineRadioButton);
    radioLayout->addWidget(splineRadioButton);
    radioLayout->addWidget(scatterRadioButton);
    radioLayout->addWidget(pieRadioButton);
    radioLayout->addWidget(areaRadioButton);
    radioLayout->addWidget(barRadioButton);
    radioLayout->addStretch();

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonsLayout, 1, 0);
    mainLayout->addLayout(radioLayout, 2, 0);
    mainLayout->addWidget(tableView, 1, 1);
    mainLayout->addWidget(chartView, 2, 1);
    setLayout(mainLayout);    
    lineRadioButton->setFocus();
}

void TableWidget::addRowAbove()
{
//    m_model->insertRow(m_model->rowCount());
//    m_model->insertRow(tableView->currentIndex().row());
    m_model->insertRows(tableView->currentIndex().row(), linesCountSpinBox->value());

}

void TableWidget::addRowBelow()
{
//    m_model->insertRow(m_model->rowCount());
//    m_model->insertRow(tableView->currentIndex().row() + 1);
    m_model->insertRows(tableView->currentIndex().row() + 1, linesCountSpinBox->value());

}

void TableWidget::removeRow()
{
//    m_model->removeRow(m_model->rowCount() - 1);
//    m_model->removeRow(tableView->currentIndex().row());
    m_model->removeRows(tableView->currentIndex().row(), qMin(m_model->rowCount() - tableView->currentIndex().row(), linesCountSpinBox->value()));
}

void TableWidget::updateChartType()
{
    chartView->removeAllSeries();

    if (lineRadioButton->isChecked())
    {
        QPen pen;
        pen.setWidth(2);

        QColor seriesColor("#8FBC8F");

        // series 1
        series = new QLineSeries;
        series->setModel(m_model);
        series->setModelMapping(0,1, Qt::Vertical);
        series->setModelMappingShift(1, 4);
//        series->setModelMapping(0,1, Qt::Horizontal);

        pen.setColor(seriesColor);
        series->setPen(pen);
        chartView->addSeries(series);
        for (int i = 1; i <=4; i++)
        {
            m_model->setData(m_model->index(i, 0), seriesColor  , Qt::BackgroundRole);
            m_model->setData(m_model->index(i, 1), seriesColor  , Qt::BackgroundRole);
        }
//        tableView->setsetStyleSheet("QTableView { border: 2px solid red }");

        seriesColor = QColor("#1E90FF");

        // series 2
        series = new QLineSeries;
        series->setModel(m_model);
        series->setModelMapping(2,3, Qt::Vertical);
//        series->setModelMapping(2,3, Qt::Horizontal);
        pen.setColor(seriesColor);
        series->setPen(pen);
        chartView->addSeries(series);

        chartView->axisX()->setRange(0, 500);

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
    else if (splineRadioButton->isChecked())
    {
        // series 1
        series = new QSplineSeries;
        series->setModel(m_model);        
        series->setModelMapping(0,1, Qt::Vertical);        
        series->setModelMappingShift(1, 4);
//        series->setModelMapping(0,1, Qt::Horizontal);
        chartView->addSeries(series);

        // series 2
        series = new QSplineSeries;
        series->setModel(m_model);
        series->setModelMapping(2,3, Qt::Vertical);
        series->setModelMappingShift(0, 0);
//        series->setModelMapping(2,3, Qt::Horizontal);
        chartView->addSeries(series);

        // series 3
        series = new QSplineSeries;
        series->setModel(m_model);
        series->setModelMapping(4,5, Qt::Vertical);
        series->setModelMappingShift(0, 0);
//        series->setModelMapping(4,5, Qt::Horizontal);
        chartView->addSeries(series);
    }
    else if (scatterRadioButton->isChecked())
    {
        // series 1
        series = new QScatterSeries;
        series->setModel(m_model);
        series->setModelMapping(0,1, Qt::Vertical);
//        series->setModelMapping(0,1, Qt::Horizontal);
        chartView->addSeries(series);

        // series 2
        series = new QScatterSeries;
        series->setModel(m_model);
        series->setModelMapping(2,3, Qt::Vertical);
//        series->setModelMapping(2,3, Qt::Horizontal);
        chartView->addSeries(series);

        // series 3
        series = new QScatterSeries;
        series->setModel(m_model);
        series->setModelMapping(4,5, Qt::Vertical);
//        series->setModelMapping(4,5, Qt::Horizontal);
        chartView->addSeries(series);
    }
    else if (pieRadioButton->isChecked())
    {
        // pie 1
        QPieSeries* pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(0,0, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.2, 0.35);
        chartView->addSeries(pieSeries);

        // pie 2
        pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(1,1, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.8, 0.35);
        chartView->addSeries(pieSeries);

        // pie 3
        pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(2,2, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        pieSeries->setPieSize(0.4);
        pieSeries->setPiePosition(0.5, 0.65);
        chartView->addSeries(pieSeries);
    }
    else if (areaRadioButton->isChecked())
    {
        QLineSeries* upperLineSeries = new QLineSeries;
        upperLineSeries->setModel(m_model);
        upperLineSeries->setModelMapping(0, 1, Qt::Vertical);
        QLineSeries* lowerLineSeries = new QLineSeries;
        lowerLineSeries->setModel(m_model);
        lowerLineSeries->setModelMapping(2, 3, Qt::Vertical);
        QAreaSeries* areaSeries = new QAreaSeries(upperLineSeries, lowerLineSeries);
        chartView->addSeries(areaSeries);
    }
    else if (barRadioButton->isChecked())
    {
        QBarSeries* barSeries = new QBarSeries(QStringList());
        barSeries->setModel(m_model);
        barSeries->setModelMapping(5, 2, 4, Qt::Vertical);
        barSeries->setToolTipEnabled(true);
        chartView->addSeries(barSeries);
    }

//    series->setModel(m_model);
//    series->setModelMapping(0,1, Qt::Vertical);
//    chartView->addSeries(series);
}

TableWidget::~TableWidget()
{
    
}
