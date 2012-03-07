#include "chartview.h"
#include <qlineseries.h>
#include <qscatterseries.h>
#include <qsplineseries.h>
#include <QTime>

ChartView::ChartView(QWidget* parent):QChartView(parent),
m_index(0)
{
    QTime now = QTime::currentTime();
    qsrand((uint)now.msec());
    setChartTitle("Three random line charts");

    QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(handleTimeout()));
    m_timer.setInterval(3000);

//![1]
    QLineSeries* series0 = new QLineSeries(this);
    QPen blue(Qt::blue);
    blue.setWidth(3);
    series0->setPen(blue);

    QScatterSeries* series1 = new QScatterSeries(this);
    QPen red(Qt::red);
    red.setWidth(3);
    series1->setPen(red);
    series1->setBrush(Qt::white);

    QSplineSeries* series2 = new QSplineSeries(this);
    QPen green(Qt::green);
    green.setWidth(3);
    series2->setPen(green);
//![1]

//![2]
    int numPoints = 10;

    for (int x = 0; x <= numPoints; ++x) {
        qreal y = qrand() % 100;
        series0->add(x,y);
        series1->add(x,y);
        series2->add(x,y);
    }
//![2]

//![3]
    m_series<<series0;
    m_titles<<chartTitle()+": LineChart";
    m_series<<series1;
    m_titles<<chartTitle()+": ScatterChart";
    m_series<<series2;
    m_titles<<chartTitle()+": SplineChart";
//![3]
    addSeries(series0);
    setChartTitle(m_titles.at(0));

    m_timer.start();
}

ChartView::~ChartView()
{
    if(m_series.size()==0) return;
    removeSeries(m_series.at(m_index));
    qDeleteAll(m_series);
}

//![4]
void ChartView::handleTimeout()
{
    if(m_series.size()==0) return;
    removeSeries(m_series.at(m_index));
    m_index++;
    m_index=m_index%m_series.size();
    addSeries(m_series.at(m_index));
    setChartTitle(m_titles.at(m_index));
}
//![4]
