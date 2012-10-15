#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChartGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class XYSeriesIODevice;
class QAudioInput;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    XYSeriesIODevice *m_device;
    QChart *m_chart;
    QLineSeries *m_series;
    QAudioInput *m_audioInput;
};

#endif // WIDGET_H
