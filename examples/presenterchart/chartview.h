#ifndef CHARTVIEW_H_
#define CHARTVIEW_H_

#include <qchartview.h>
#include <QTimer>

QTCOMMERCIALCHART_USE_NAMESPACE

//![1]
class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QWidget* parent=0);
    virtual ~ChartView();

public slots:
    void handleTimeout();
    void handlePointClicked(const QPointF& point);

private:
    QTimer m_timer;
    QList<QSeries*> m_series;
    QStringList m_titles;
    int m_index;
};
//![1]

#endif /* CHARTVIEW_H_ */
