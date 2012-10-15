#ifndef XYSERIESIODEVICE_H
#define XYSERIESIODEVICE_H

#include <QIODevice>
#include <QChartGlobal>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QXYSeries;
QTCOMMERCIALCHART_END_NAMESPACE

QTCOMMERCIALCHART_USE_NAMESPACE

class XYSeriesIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit XYSeriesIODevice(QXYSeries * series, QObject *parent = 0);
        
protected:
    qint64 readData(char * data, qint64 maxSize);
    qint64 writeData(const char * data, qint64 maxSize);
    
private:
    QXYSeries *m_series;
};

#endif // XYSERIESIODEVICE_H
