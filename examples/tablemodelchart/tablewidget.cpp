#include "tablewidget.h"
#include <QGridLayout>
#include <QTableView>
#include <QStyledItemDelegate>
#include "qlineseries.h"
#include "qsplineseries.h"
#include "customtablemodel.h"
#include "qpieseries.h"

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{


    // create simple model for storing data
    // user's table data model
    CustomTableModel* model = new CustomTableModel;
    QTableView* tableView = new QTableView;
    tableView->setModel(model);
    tableView->setMinimumSize(340, 480);
//    tableView->setItemDelegate(new QStyledItemDelegate);
    chartView = new QChartView;
    chartView->setMinimumSize(640, 480);

    // create
//    QLineSeries* series = new QLineSeries;
    QSplineSeries* series = new QSplineSeries;
    series->setModel(model);
    series->setModelMapping(0,1, Qt::Vertical);
//    series->setModelMappingY(1);

//    series->add(QPointF(150, 100));
//    series->add(QPointF(200, 130));
//    series->add(QPointF(250, 120));
//    series->add(QPointF(300, 140));
//    series->add(QPointF(350, 160));

//    QPieSeries* pieSeries = new QPieSeries;
//    pieSeries->setModel(model);
//    pieSeries

    chartView->addSeries(series);

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(tableView, 1, 1);
    mainLayout->addWidget(chartView, 1, 2);
    setLayout(mainLayout);
}

TableWidget::~TableWidget()
{
    
}
