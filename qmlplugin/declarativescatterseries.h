#ifndef DECLARATIVESCATTERSERIES_H
#define DECLARATIVESCATTERSERIES_H

#include "qchartglobal.h"
#include "declarativexyseries.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeScatterSeries : public DeclarativeXySeries
{
    Q_OBJECT

public:
    explicit DeclarativeScatterSeries(QDeclarativeItem *parent = 0);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESCATTERSERIES_H
