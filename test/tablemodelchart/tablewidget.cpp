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
#include <QLineSeries>
#include <QSplineSeries>
#include <QScatterSeries>
#include "customtablemodel.h"
#include <QPieSeries>
#include <QPieSlice>
#include <QAreaSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
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
    m_tableView->setMinimumHeight(300);
    //    tableView->setMinimumSize(340, 480);
    //    tableView->setItemDelegate(new QStyledItemDelegate);
    m_chart = new QChart;
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(640, 480);

    // add, remove data buttons
    QPushButton* addRowAboveButton = new QPushButton("Add row above");
    connect(addRowAboveButton, SIGNAL(clicked()), this, SLOT(addRowAbove()));

    QPushButton* addRowBelowButton = new QPushButton("Add row below");
    connect(addRowBelowButton, SIGNAL(clicked()), this, SLOT(addRowBelow()));

    QPushButton* removeRowButton = new QPushButton("Remove row");
    connect(removeRowButton, SIGNAL(clicked()), this, SLOT(removeRow()));

    QLabel *spinBoxLabel = new QLabel("Rows affected:");

    // spin box for setting number of affected items (add, remove)
    m_linesCountSpinBox = new QSpinBox;
    m_linesCountSpinBox->setRange(1, 10);
    m_linesCountSpinBox->setValue(1);

    // buttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(spinBoxLabel);
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

    connect(m_lineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
    connect(m_splineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
    connect(m_scatterRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
    connect(m_pieRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
    connect(m_areaRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
    connect(m_barRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType(bool)));
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
    m_model->insertRows(m_tableView->currentIndex().row(), m_linesCountSpinBox->value());

}

void TableWidget::addRowBelow()
{
    m_model->insertRows(m_tableView->currentIndex().row() + 1, m_linesCountSpinBox->value());

}

void TableWidget::removeRow()
{
    m_model->removeRows(m_tableView->currentIndex().row(), qMin(m_model->rowCount() - m_tableView->currentIndex().row(), m_linesCountSpinBox->value()));
}

void TableWidget::updateChartType(bool toggle)
{
    // this if is needed, so that the function is only called once.
    // For the radioButton that was enabled.
    if (toggle) {
        m_chart->removeAllSeries();

        // renable axes of the chart (pie hides them)
        // x axis
        QChartAxis *axis = m_chart->axisX();
        axis->setAxisVisible(true);
        axis->setGridLineVisible(true);
        axis->setLabelsVisible(true);

        // y axis
        axis = m_chart->axisY();
        axis->setAxisVisible(true);
        axis->setGridLineVisible(true);
        axis->setLabelsVisible(true);

        m_model->clearMapping();

        QString seriesColorHex = "#000000";
        QPen pen;
        pen.setWidth(2);

        if (m_lineRadioButton->isChecked())
        {
            // series 1
            m_series = new QLineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(0,1, Qt::Vertical);
            m_series->setModelMappingRange(1, 4);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(0, 1, 2, 4));

            // series 2
            m_series = new QLineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(2,3, Qt::Vertical);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(2, 0, 2, 1000));

            // series 3
            m_series = new QLineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(4,5, Qt::Vertical);
            m_series->setModelMappingRange(2, 0);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(4, 2, 2, 1000));
        }
        else if (m_splineRadioButton->isChecked())
        {
            // series 1
            m_series = new QSplineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(0,1, Qt::Vertical);
            m_series->setModelMappingRange(1, 4);
            //        series->setModelMapping(0,1, Qt::Horizontal);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(0, 1, 2, 4));

            // series 2
            m_series = new QSplineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(2,3, Qt::Vertical);
            m_series->setModelMappingRange(0, 0);
            //        series->setModelMapping(2,3, Qt::Horizontal);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(2, 0, 2, 1000));

            // series 3
            m_series = new QSplineSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(4,5, Qt::Vertical);
            m_series->setModelMappingRange(2, 0);
            //        series->setModelMapping(4,5, Qt::Horizontal);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(4, 2, 2, 1000));
        }
        else if (m_scatterRadioButton->isChecked())
        {
            // series 1
            m_series = new QScatterSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(0,1, Qt::Vertical);
            m_series->setModelMappingRange(2, 0);
            //        series->setModelMapping(0,1, Qt::Horizontal);
            m_chart->addSeries(m_series);

            seriesColorHex = "#" + QString::number(m_series->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(0, 2, 2, 1000));

            // series 2
            m_series = new QScatterSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(2,3, Qt::Vertical);
            m_series->setModelMappingRange(1, 6);
            //        series->setModelMapping(2,3, Qt::Horizontal);
            m_chart->addSeries(m_series);

            seriesColorHex = "#" + QString::number(m_series->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(2, 1, 2, 6));

            // series 3
            m_series = new QScatterSeries;
            m_series->setModel(m_model);
            m_series->setModelMapping(4,5, Qt::Vertical);
            //        series->setModelMapping(4,5, Qt::Horizontal);
            m_chart->addSeries(m_series);
            seriesColorHex = "#" + QString::number(m_series->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(4, 0, 2, 1000));
        }
        else if (m_pieRadioButton->isChecked())
        {
            // pie 1
            QPieSeries* pieSeries = new QPieSeries;
            pieSeries->setModel(m_model);
            pieSeries->setModelMapping(0,0, Qt::Vertical);
            pieSeries->setLabelsVisible(true);
            pieSeries->setPieSize(0.4);
            pieSeries->setHorizontalPosition(0.2);
            pieSeries->setVerticalPosition(0.35);

            m_chart->addSeries(pieSeries);
            seriesColorHex = "#" + QString::number(pieSeries->slices().at(pieSeries->slices().count()/2)->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(0, 0, 1, 1000));

            // pie 2
            pieSeries = new QPieSeries;
            pieSeries->setModel(m_model);
            pieSeries->setModelMapping(1,1, Qt::Vertical);
            pieSeries->setLabelsVisible(true);
            pieSeries->setPieSize(0.4);
            pieSeries->setHorizontalPosition(0.8);
            pieSeries->setVerticalPosition(0.35);
            m_chart->addSeries(pieSeries);
            seriesColorHex = "#" + QString::number(pieSeries->slices().at(pieSeries->slices().count()/2)->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(1, 0, 1, 1000));

            // pie 3
            pieSeries = new QPieSeries;
            pieSeries->setModel(m_model);
            pieSeries->setModelMapping(2,2, Qt::Vertical);
            pieSeries->setLabelsVisible(true);
            pieSeries->setPieSize(0.4);
            pieSeries->setHorizontalPosition(0.5);
            pieSeries->setVerticalPosition(0.65);
            m_chart->addSeries(pieSeries);
            seriesColorHex = "#" + QString::number(pieSeries->slices().at(pieSeries->slices().count()/2)->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(2, 0, 1, 1000));
        }
        else if (m_areaRadioButton->isChecked())
        {
            QLineSeries* upperLineSeries = new QLineSeries;
            upperLineSeries->setModel(m_model);
            upperLineSeries->setModelMapping(0, 1, Qt::Vertical);
            upperLineSeries->setModelMappingRange(1, 5);
            QLineSeries* lowerLineSeries = new QLineSeries;
            lowerLineSeries->setModel(m_model);
            lowerLineSeries->setModelMapping(2, 3, Qt::Vertical);
            QAreaSeries* areaSeries = new QAreaSeries(upperLineSeries, lowerLineSeries);
            m_chart->addSeries(areaSeries);
            seriesColorHex = "#" + QString::number(areaSeries->brush().color().rgb(), 16).right(6).toUpper();
            m_model->addMapping(seriesColorHex, QRect(0, 1, 2, 5));
            m_model->addMapping(seriesColorHex, QRect(2, 0, 2, 1000));
        }
        else if (m_barRadioButton->isChecked())
        {
            QBarSeries* barSeries = new QBarSeries(QStringList());
            barSeries->setModel(m_model);
            barSeries->setModelMapping(5, 2, 4, Qt::Vertical);
            barSeries->setToolTipEnabled(true);
            m_chart->addSeries(barSeries);
            for (int i = 0; i < barSeries->barsetCount(); i++) {
                seriesColorHex = "#" + QString::number(barSeries->barsetAt(i)->brush().color().rgb(), 16).right(6).toUpper();
                m_model->addMapping(seriesColorHex, QRect(2 + i, 0, 1, 1000));
            }
        }


        m_chart->axisX()->setRange(0, 500);
        m_chart->axisY()->setRange(0, 120);

        // repaint table view colors
        m_tableView->repaint();
        m_tableView->setFocus();
    }
}

TableWidget::~TableWidget()
{
    
}
