#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QChartView>

QTCOMMERCIALCHART_USE_NAMESPACE

class ChartView : public QChartView
{
    Q_OBJECT
public:
    explicit ChartView(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CHARTVIEW_H
