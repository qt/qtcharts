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
#include "customtablemodel.h"
#include <QGridLayout>
#include <QTableView>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QVXYModelMapper>
#include <QHeaderView>
#include <QDoubleSpinBox>
#include <QLogValueAxis>
#include <QLineEdit>
#include <QDateTimeAxis>

QTCOMMERCIALCHART_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent),
      m_logBaseSpinBox(0),
      m_axis(0)
{
    // create simple model for storing data
    // user's table data model
    //! [1]
    CustomTableModel *model = new CustomTableModel;
    //! [1]

    //! [2]
    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#else
    tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
    //! [2]

    //! [3]
    QChart *chart = new QChart;
    chart->setAnimationOptions(QChart::AllAnimations);
    //! [3]

    // series 1
    //! [4]
    QLineSeries *series = new QLineSeries;
    series->setName("Line 1");
    QVXYModelMapper *mapper = new QVXYModelMapper(this);
    mapper->setXColumn(0);
    mapper->setYColumn(1);
    mapper->setSeries(series);
    mapper->setModel(model);
    chart->addSeries(series);
    //! [4]

    //! [5]
    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));
    //! [5]


    // series 2
    //! [6]
    QLineSeries *series2 = new QLineSeries;
    series2->setName("Line 2");

    mapper = new QVXYModelMapper(this);
    mapper->setXColumn(2);
    mapper->setYColumn(3);
    mapper->setSeries(series2);
    mapper->setModel(model);
    chart->addSeries(series2);
    //! [6]

    //! [7]
    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(series2->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 2, model->rowCount()));
    //! [7]

    //! [8]
    chart->createDefaultAxes();

    m_axis = new QLogValueAxis;
    chart->addAxis(m_axis, Qt::AlignRight);
    chart->setAxisY(m_axis, series);
    chart->setAxisY(m_axis, series2);
//    series->attachAxis(m_axis);
//    series2->attachAxis(m_axis);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(640, 480);
    //! [8]

    m_logBaseSpinBox = new QDoubleSpinBox;
    m_logBaseSpinBox->setRange(0.01, 100.0);

    connect(m_logBaseSpinBox, SIGNAL(valueChanged(double)), this, SLOT(logBaseChanged(double)));

    QLineEdit *format = new QLineEdit;
    connect(format, SIGNAL(textEdited(QString)), this, SLOT(formatChanged(QString)));

    //! [9]
    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(chartView, 1, 1);
    mainLayout->addWidget(m_logBaseSpinBox, 1, 2);
    mainLayout->addWidget(format, 1, 3);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
    //! [9]
}

void TableWidget::logBaseChanged(double base)
{
    m_axis->setBase(base);
}

void TableWidget::formatChanged(const QString& format)
{
    m_axis->setLabelFormat(format);
//    m_axis->setFormat(format);
}
