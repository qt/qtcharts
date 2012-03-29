#ifndef DECLARATIVESPLINESERIES_H
#define DECLARATIVESPLINESERIES_H

#include "qchartglobal.h"
#include "qsplineseries.h"
#include "declarativexyseries.h"
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeSplineSeries : public QSplineSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)

public:
    explicit DeclarativeSplineSeries(QObject *parent = 0);

public:
    void seriesComplete();
    QObject *seriesObject();

public:
    QDeclarativeListProperty<DeclarativeXyPoint> points();

public slots:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESPLINESERIES_H
