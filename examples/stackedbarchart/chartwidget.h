#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <qchartview.h>

QTCOMMERCIALCHART_USE_NAMESPACE


class ChartWidget : public QChartView
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // CHARTWIDGET_H
