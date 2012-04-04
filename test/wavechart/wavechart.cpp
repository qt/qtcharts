#include "wavechart.h"
#include <cmath>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979
static const int numPoints =100;

WaveChart::WaveChart(QChart* chart, QWidget* parent) :
    QChartView(chart, parent),
    m_series(new QLineSeries()),
    m_wave(0),
    m_step(2 * PI / numPoints)
{
    QPen blue(Qt::blue);
    blue.setWidth(3);
    m_series->setPen(blue);

    QTime now = QTime::currentTime();
    qsrand((uint) now.msec());

    int fluctuate = 100;

    for (qreal x = 0; x <= 2 * PI; x += m_step) {
        m_series->append(x, fabs(sin(x) * fluctuate));
    }

    chart->addSeries(m_series);

    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer.setInterval(5000);
    m_timer.start();

}
;

void WaveChart::update()
{

    int fluctuate;

    for (qreal i = 0, x = 0; x <= 2 * PI; x += m_step, i++) {
        fluctuate = qrand() % 100;
        m_series->replace(x, fabs(sin(x) * fluctuate));

    }

}
