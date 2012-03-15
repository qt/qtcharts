#include "tablewidget.h"
#include <QGridLayout>
#include <QTableView>
#include <QStyledItemDelegate>
#include "qlineseries.h"
#include "qsplineseries.h"
#include "qscatterseries.h"
#include "customtablemodel.h"
#include "qpieseries.h"
#include <QPushButton>
#include <QRadioButton>

TableWidget::TableWidget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(100, 100, 1000, 600);
    // create simple model for storing data
    // user's table data model
    m_model = new CustomTableModel;
    tableView = new QTableView;
    tableView->setModel(m_model);
    tableView->setMinimumSize(340, 480);
//    tableView->setItemDelegate(new QStyledItemDelegate);
    chartView = new QChartView(this);
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

    // buttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(addRowAboveButton);
    buttonsLayout->addWidget(addRowBelowButton);
    buttonsLayout->addWidget(removeRowButton);
    buttonsLayout->addStretch();

    // chart type radio buttons
    lineRadioButton = new QRadioButton("Line");
    splineRadioButton = new QRadioButton("Spline");
    scatterRadioButton = new QRadioButton("Scatter");
    pieRadioButton = new QRadioButton("Pie");

    connect(lineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(splineRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(scatterRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    connect(pieRadioButton, SIGNAL(toggled(bool)), this, SLOT(updateChartType()));
    lineRadioButton->setChecked(true);

    // radio buttons layout
    QHBoxLayout* radioLayout = new QHBoxLayout;
    radioLayout->addWidget(lineRadioButton);
    radioLayout->addWidget(splineRadioButton);
    radioLayout->addWidget(scatterRadioButton);
    radioLayout->addWidget(pieRadioButton);

    // create main layout
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonsLayout, 0, 1);
    mainLayout->addLayout(radioLayout, 0, 2);
    mainLayout->addWidget(tableView, 1, 1);
    mainLayout->addWidget(chartView, 1, 2);
    setLayout(mainLayout);    
}

void TableWidget::addRowAbove()
{
//    m_model->insertRow(m_model->rowCount());
    m_model->insertRow(tableView->currentIndex().row());

}

void TableWidget::addRowBelow()
{
//    m_model->insertRow(m_model->rowCount());
    m_model->insertRow(tableView->currentIndex().row() + 1);

}

void TableWidget::removeRow()
{
//    m_model->removeRow(m_model->rowCount() - 1);
    m_model->removeRow(tableView->currentIndex().row());
}

void TableWidget::updateChartType()
{
    chartView->removeAllSeries();

    if (lineRadioButton->isChecked())
        series = new QLineSeries;
    else if (splineRadioButton->isChecked())
        series = new QSplineSeries;
    else if (scatterRadioButton->isChecked())
        series = new QScatterSeries;
    else if (pieRadioButton->isChecked())
    {
        QPieSeries* pieSeries = new QPieSeries;
        pieSeries->setModel(m_model);
        pieSeries->setModelMapping(0,2, Qt::Vertical);
        pieSeries->setLabelsVisible(true);
        chartView->addSeries(pieSeries);
        return;
    }

    series->setModel(m_model);
    series->setModelMapping(0,1, Qt::Vertical);
    chartView->addSeries(series);
}

TableWidget::~TableWidget()
{
    
}
