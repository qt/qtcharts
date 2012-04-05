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

QTCOMMERCIALCHART_USE_NAMESPACE

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    // create simple model for storing data
    // user's table data model
    CustomTableModel *model = new CustomTableModel;

    // create table view and add model to it
    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->setColumnWidth(0, 56);
    tableView->setColumnWidth(1, 56);
    tableView->setColumnWidth(2, 56);
    tableView->setColumnWidth(3, 56);

    QChart *m_chart = new QChart;
    m_chart->setAnimationOptions(QChart::AllAnimations);
    QChartView *m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setMinimumSize(640, 480);

    // for storing color hex from the series
    QString seriesColorHex = "#000000";

    // series 1
    QLineSeries *m_series = new QLineSeries;
    m_series->setModel(model);
    m_series->setModelMapping(0, 1, Qt::Vertical);
    m_chart->addSeries(m_series);

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(0, 0, 2, model->rowCount()));

    // series 2
    m_series = new QLineSeries;
    m_series->setModel(model);
    m_series->setModelMapping(2,3, Qt::Vertical);
    m_chart->addSeries(m_series);

    // get the color of the series and use it for showing the mapped area
    seriesColorHex = "#" + QString::number(m_series->pen().color().rgb(), 16).right(6).toUpper();
    model->addMapping(seriesColorHex, QRect(2, 0, 2, model->rowCount()));

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 0);
    mainLayout->addWidget(m_chartView, 1, 1);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(0, 0);
    setLayout(mainLayout);
}
