#ifndef CHARTVIEW_H_
#define CHARTVIEW_H_

#include <QChartView>
#include <QTimer>


QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QSplineSeries;
class QLineSeries;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

//![1]
class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QWidget* parent = 0);
    virtual ~ChartView();

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QLineSeries* m_series0;
    QSplineSeries* m_series1;
    QStringList m_titles;
    qreal m_step;
    qreal m_x;
    qreal m_y;
};
//![1]

#endif /* CHARTVIEW_H_ */
