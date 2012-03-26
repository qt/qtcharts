#ifndef DECLARATIVESPLINESERIES_H
#define DECLARATIVESPLINESERIES_H

#include "qchartglobal.h"
#include "declarativexyseries.h"
#include <QDeclarativeItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeSplineSeries : public DeclarativeXySeries
{
    Q_OBJECT

public:
    explicit DeclarativeSplineSeries(QDeclarativeItem *parent = 0) :
        DeclarativeXySeries(QSeries::SeriesTypeSpline, parent) {}
};

#include "moc_declarativesplineseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVESPLINESERIES_H
