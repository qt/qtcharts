#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include "qchartglobal.h"
#include "qlineseries.h"
#include "declarativexyseries.h"
#include <QDeclarativeParserStatus>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeLineSeries : public QLineSeries, public DeclarativeXySeries
{
    Q_OBJECT
    Q_PROPERTY(QDeclarativeListProperty<DeclarativeXyPoint> points READ points)

public:
    explicit DeclarativeLineSeries(QObject *parent = 0);

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

#endif // DECLARATIVELINESERIES_H
