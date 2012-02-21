#ifndef CHARTVIEW_H_
#define CHARTVIEW_H_

#include <qchartview.h>
#include <QTimer>

QTCOMMERCIALCHART_USE_NAMESPACE

class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QWidget* parent=0);
    virtual ~ChartView();

public slots:
    void handleTimeout();

private:
    QTimer m_timer;
    QList<QChartSeries*> m_series;
    int m_index;
};

#endif /* CHARTVIEW_H_ */
