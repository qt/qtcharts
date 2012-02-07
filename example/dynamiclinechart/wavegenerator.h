#include <QTimer>
#include <QTime>
#include <QObject>
#include <cmath>
#include <qxychartseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979
static const int numPoints =100;

class WaveGenerator: public QObject
{
    Q_OBJECT

public:
    WaveGenerator(QXYChartSeries* series1, QXYChartSeries* series2) :
        m_series1(series1),
        m_series2(series2),
        m_wave(0),
        m_step(2*PI/numPoints)
    {

        QTime now = QTime::currentTime();
        qsrand((uint)now.msec());

        int fluctuate = 100;

        for (qreal x = 0; x <= 2*PI; x+=m_step) {
              series1->add(x, fabs(sin(x)*fluctuate));
              series2->add(x, fabs(cos(x)*fluctuate));
        }

        QObject::connect(&m_timer,SIGNAL(timeout()),this,SLOT(update()));
        m_timer.setInterval(5000);
        m_timer.start();

    };

public slots:
    void update()
    {
        int fluctuate;

        for (qreal i = 0, x = 0; x <= 2*PI; x+=m_step, i++) {
            fluctuate = qrand() % 100;
            m_series1->set(i, x, fabs(sin(x)*fluctuate));
            fluctuate = qrand() % 100;
            m_series2->set(i, x, fabs(cos(x)*fluctuate));
        }

    }

private:
    QXYChartSeries* m_series1;
    QXYChartSeries* m_series2;
    int m_wave;
    qreal m_step;
    QTimer m_timer;
};
