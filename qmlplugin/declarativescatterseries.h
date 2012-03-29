#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "qscatterseries.h"
#include "declarativexyseries.h"
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeScatterSeries : public QScatterSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)

public:
    explicit DeclarativeScatterSeries(QObject *parent = 0);

public:
    void componentComplete();
    QDeclarativeListProperty<DeclarativeXyPoint> points();

public Q_SLOTS:
    static void appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                             DeclarativeXyPoint *element);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
