#include "splinewidget.h"
#include "qchartview.h"
#include "qlineseries.h"
#include <QGridLayout>
#include <QPushButton>
#include "qchartaxis.h"
#include <qmath.h>

QTCOMMERCIALCHART_USE_NAMESPACE

SplineWidget::SplineWidget(QWidget *parent)
    : QWidget(parent)
{
//    qsrand(time(NULL));
    //! [1]
    //create QSplineSeries
    series = new QSplineSeries(this);
    //! [1]

    //! [2]
    // customize the series presentation settings
    QPen seriesPen(Qt::blue);
    seriesPen.setWidth(3);
//    series->setPen(seriesPen);
    //! [2]

    //! [add points to series]
    //add data points to the series
    series->add(QPointF(150, 100));
    series->add(QPointF(200, 130));
    series->add(QPointF(250, 120));
    series->add(QPointF(300, 140));
    series->add(QPointF(350, 160));
    //! [add points to series]

    QSplineSeries* series2 = new QSplineSeries;

    series2->add(QPointF(400, 120));
    series2->add(QPointF(450, 150));
    series2->add(QPointF(500, 145));
    series2->add(QPointF(550, 170));

//    series->add(QPointF(600, 190));
//    series->add(QPointF(650, 210));
//    series->add(QPointF(700, 190));
//    series->add(QPointF(750, 180));
//    series->add(QPointF(800, 170));
    QSplineSeries* series3 = new QSplineSeries;
        series3->add(QPointF(600, 190));
        series3->add(QPointF(650, 210));
        series3->add(QPointF(700, 190));
        series3->add(QPointF(750, 180));
        series3->add(QPointF(800, 170));

    //! [3]
    // create chart view
    QChartView* chart = new QChartView;
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->addSeries(series3);

    chart->setChartTitle("Spline chart example");
    chart->axisX()->setMax(1500);
    chart->axisY()->setMax(500);

    chart->setMinimumSize(800,600);
    //! [3]

    //! [4]
    //add new data point button
    QPushButton* addButton = new QPushButton("Add new point");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNewPoint()));

    // remove the last data point in the series
    QPushButton* removeButton = new QPushButton("Remove point");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removePoint()));
    //! [4]

    //! [5]
    //butttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addStretch();

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chart, 1, 0);
    mainLayout->addLayout(buttonsLayout, 1, 1);
    setLayout(mainLayout);
    //! [5]
}

//! [add point]
void SplineWidget::addNewPoint()
{
    if (series->count() > 0)
        series->add(QPointF(series->x(series->count() - 1) + 40 + qrand()%40, qAbs(series->y(series->count() - 1) - 50 + qrand()%100)));
    else
        series->add(QPointF(50, 50 + qrand()%50));
}
//! [add point]

//! [remove point]
void SplineWidget::removePoint()
{
    if (series->count() > 0)
        series->remove(QPointF(series->x(series->count() - 1), series->y(series->count() - 1)));
}
//! [remove point]

SplineWidget::~SplineWidget()
{
    
}
