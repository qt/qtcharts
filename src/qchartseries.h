#ifndef QCHARTSERIES_H
#define QCHARTSERIES_H

#include "qchartconfig.h"
#include <QObject>

QCHART_BEGIN_NAMESPACE

class QCHART_EXPORT QChartSeries : public QObject
{

public:
    enum QChartSeriesType {LINE,PIE,BAR};

protected:
    QChartSeries(QObject *parent = 0):QObject(parent){};

public:
    virtual ~QChartSeries(){};

    //factory method
    static QChartSeries* create(QObject* parent = 0 ){ return 0;}
    //pure virtual
    virtual QChartSeriesType type() const = 0;

};

QCHART_END_NAMESPACE

#endif

