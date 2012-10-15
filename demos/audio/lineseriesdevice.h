#ifndef LINESERIESDEVICE_H
#define LINESERIESDEVICE_H

#include <QLineSeries>
#include <QIODevice>

QTCOMMERCIALCHART_USE_NAMESPACE

class LineSeriesDevice : public QIODevice, public QLineSeries
{
    Q_OBJECT
public:
    explicit LineSeriesDevice(QObject *parent = 0);
    
signals:
    
public slots:
    
;

#endif // LINESERIESDEVICE_H
