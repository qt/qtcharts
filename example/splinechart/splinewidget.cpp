#include "splinewidget.h"
#include "qchartview.h"
#include "qlineseries.h"
#include <QGridLayout>
#include <QPushButton>

QTCOMMERCIALCHART_USE_NAMESPACE

SplineWidget::SplineWidget(QWidget *parent)
    : QWidget(parent)
{
    //create QSplineSeries
    series = new QSplineSeries(this);
    series->add(QPointF(150, 100));
    series->add(QPointF(200, 130));
    series->add(QPointF(250, 120));
    series->add(QPointF(300, 140));
    series->add(QPointF(350, 100));
    series->add(QPointF(400, 120));
    series->add(QPointF(450, 150));
    //    series->add(QPointF(600, 150));
    series->add(QPointF(500, 145));
    series->add(QPointF(550, 170));
    series->add(QPointF(600, 190));
    series->add(QPointF(650, 210));
    series->add(QPointF(700, 190));
    series->add(QPointF(750, 180));
    series->add(QPointF(800, 170));

//    series->calculateControlPoints();

    QSplineSeries* series2 = new QSplineSeries(this);
    qsrand(time(NULL));
    //    for (int i = 0; i < 100; i++)
    //    {
    //        series2->add(QPointF(i*7, qrand()%600));
    //    }
    int k = 10;
    for (int i = 0; i < 25; i++)
    {
        if (k > 60)
        {
            k = 10;
        }
        series2->add(QPointF(i*50, k));
        k +=10;
    }

//    series2->calculateControlPoints();

    //    QLineSeries* lineSeries = new QLineSeries;
    //    for (int i = 0; i < series->count() - 1; i++)
    //    {
    //        lineSeries->add(series->at(i).x(), series->at(i).y());
    //        lineSeries->add(series->controlPoint(2*i).x(), series->controlPoint(2*i).y());
    //        lineSeries->add(series->controlPoint(2*i + 1).x(), series->controlPoint(2*i + 1).y());
    //    }

    //    QLineChartSeries* lineSeries2 = new QLineChartSeries;
    //    lineSeries2->add(10, 50);
    //    lineSeries2->add(30, 15);
    //    lineSeries2->add(60, 40);
    //    lineSeries2->add(90, 70);
    //    lineSeries2->add(100, 20);

    //create chart view
    QChartView* chart = new QChartView;
    chart->setMinimumSize(800,600);
    //    chart->setGeometry(50, 50, 400, 300);
    chart->addSeries(series);
    chart->addSeries(series2);

    //add new item
    QPushButton* addButton = new QPushButton("Add new point");
    connect(addButton, SIGNAL(clicked()), this, SLOT(addNewPoint()));

    QPushButton* removeButton = new QPushButton("Remove point from the end");
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removePoint()));

    //butttons layout
    QVBoxLayout* buttonsLayout = new QVBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addStretch();

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chart, 1, 0);
    mainLayout->addLayout(buttonsLayout, 1, 1);
    setLayout(mainLayout);
}

void SplineWidget::addNewPoint()
{
    if (series->count() > 0)
        series->add(QPointF(series->x(series->count() - 1) + 50, series->y(series->count() - 1) - 50 + qrand()%100));
    else
        series->add(QPointF(50, 50 + qrand()%50));
}

void SplineWidget::removePoint()
{
    if (series->count() > 0)
        series->remove(QPointF(series->x(series->count() - 1), series->y(series->count() - 1)));
}

SplineWidget::~SplineWidget()
{
    
}
