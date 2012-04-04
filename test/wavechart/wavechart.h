#include <QTimer>
#include <QTime>
#include <QObject>
#include <QLineSeries>
#include <QChartView>

QTCOMMERCIALCHART_USE_NAMESPACE

class WaveChart: public QChartView
{
    Q_OBJECT

public:
    WaveChart(QChart* chart, QWidget* parent);

private slots:
    void update();

private:
    QLineSeries* m_series;
    int m_wave;
    qreal m_step;
    QTimer m_timer;
};
