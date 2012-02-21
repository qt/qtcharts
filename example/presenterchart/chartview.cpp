#include "chartview.h"
#include <qlinechartseries.h>
#include <QTime>

ChartView::ChartView(QWidget* parent):QChartView(parent),
m_index(0)
{
    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    m_timer.setInterval(3000);

    QTime now = QTime::currentTime();
    qsrand((uint)now.msec());

    QLineChartSeries* series0 = new QLineChartSeries();
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);
    QLineChartSeries* series1 = new QLineChartSeries();
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);
    QLineChartSeries* series2 = new QLineChartSeries();
    QPen green(Qt::green);
    green.setWidth(3);
    series2->setPen(green);

    int numPoints = 10;

    for (int x = 0; x <= numPoints; ++x) {
        series0->add(x,  qrand() % 100);
        series1->add(x,  qrand() % 100);
        series2->add(x,  qrand() % 100);
    }

    addSeries(series0);

    m_series<<series0;
    m_series<<series1;
    m_series<<series2;

    m_timer.start();
}

ChartView::~ChartView()
{

}

void ChartView::handleTimeout()
{
    if(m_series.size()==0) return;

    removeSeries(m_series.at(m_index));
    m_index++;
    m_index=m_index%m_series.size();
    addSeries(m_series.at(m_index));
}
