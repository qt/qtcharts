//#include "DeclarativeXySeries.h"
#include "declarativexyseries.h"
#include "qxyseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

void DeclarativeXySeries::classBegin()
{
}

void DeclarativeXySeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                          DeclarativeXyPoint *element)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(list->object);
    if (series)
        series->append(QPointF(element->x(), element->y()));
}

QTCOMMERCIALCHART_END_NAMESPACE
