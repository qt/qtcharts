#include <QTimer>
#include <QObject>
#include <cmath>
#include <qxychartseries.h>

QTCOMMERCIALCHART_USE_NAMESPACE

#define PI 3.14159265358979
static const int numPoints =100;

class Updater: public QObject
{
    Q_OBJECT

public:
    Updater(QXYChartSeries* series1, QXYChartSeries* series2) :
        m_series1(series1),
        m_series2(series2)
    {
        QTimer::singleShot(5000, this, SLOT(update()));
    };

public slots:
    void update()
    {
        for (int x = 0; x <= numPoints; ++x) {
            m_series1->set(x, x, fabs(cos(PI / 50 * x)*100));
            m_series2->set(x, x, fabs(sin(PI / 50 * x)*100));
        }
    };

private:
    QXYChartSeries* m_series1;
    QXYChartSeries* m_series2;
};
