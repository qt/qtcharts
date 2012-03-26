#include "declarativescatterseries.h"
#include "declarativechart.h"
#include "qchart.h"
#include "qscatterseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeScatterSeries::DeclarativeScatterSeries(QDeclarativeItem *parent) :
    DeclarativeXySeries(QSeries::SeriesTypeScatter, parent)
{
    setFlag(QGraphicsItem::ItemHasNoContents, false);
}

#include "moc_declarativescatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
