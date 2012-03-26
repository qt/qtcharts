#ifndef DECLARATIVELINESERIES_H
#define DECLARATIVELINESERIES_H

#include "qchartglobal.h"
#include "declarativexyseries.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeLineSeries : public DeclarativeXySeries
{
    Q_OBJECT

public:
    explicit DeclarativeLineSeries(QDeclarativeItem *parent = 0);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVELINESERIES_H
