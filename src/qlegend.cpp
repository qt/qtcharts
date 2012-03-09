#include "qchartglobal.h"
#include "qlegend.h"
#include "qseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
QLegend::QLegend(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,0,0)
{
}


void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // TODO:
    qDebug() << "QLegend::paint";
    foreach(QSeries* s, mSeriesList) {
        for (int i=0; i<s->legendEntries().count(); i++) {
            // Paint it...
            //qDebug() << s->legendEntries().at(i).mName;
        }
    }
}

QRectF QLegend::boundingRect() const
{
    return mBoundingRect;
}

void QLegend::handleSeriesAdded(QSeries* series,Domain* domain)
{
    // TODO: append entries
    mSeriesList.append(series);
}

void QLegend::handleSeriesRemoved(QSeries* series)
{
    // TODO: remove entries
    mSeriesList.removeOne(series);
}


#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
