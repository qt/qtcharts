#include "qchartglobal.h"
#include "qlegend.h"
#include "qseries.h"
#include "legendmarker_p.h"
#include "qxyseries.h"
#include "qlineseries.h"
#include "qareaseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qbarset.h"
#include "qpieseries.h"
#include "qpieslice.h"
#include <QPainter>
#include <QPen>

#include <QGraphicsSceneEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLegend::QLegend(QGraphicsItem *parent)
    : QGraphicsObject(parent)
    ,mBoundingRect(0,0,1,1)
    ,mBackgroundBrush(Qt::darkGray)     // TODO: from theme?
{
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(mBackgroundBrush);
    painter->drawRect(mBoundingRect);

    foreach(LegendMarker* m, mMarkers) {
        QRectF r = m->boundingRect();
        painter->setBrush(m->brush());
        painter->drawText(r.x() + r.width()*2, r.y() + r.height(), m->name());
    }
}

QRectF QLegend::boundingRect() const
{
    return mBoundingRect;
}

void QLegend::setBackgroundBrush(const QBrush& brush)
{
    mBackgroundBrush = brush;
}

QBrush QLegend::backgroundBrush() const
{
    return mBackgroundBrush;
}

void QLegend::handleSeriesAdded(QSeries* series,Domain* domain)
{
    mSeriesList.append(series);

    switch (series->type())
    {
    case QSeries::SeriesTypeLine: {

        QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
        createMarker(lineSeries);
        break;
    }
    case QSeries::SeriesTypeArea: {

        QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
        createMarker(areaSeries->upperSeries());
        if(areaSeries->lowerSeries())
        createMarker(areaSeries->lowerSeries());
        break;
    }

    case QSeries::SeriesTypeBar: {

        QBarSeries* barSeries = static_cast<QBarSeries*>(series);
        createMarkers(barSeries);
        break;
    }

    case QSeries::SeriesTypeStackedBar: {

        QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
        createMarkers(stackedBarSeries);
        break;
    }

    case QSeries::SeriesTypePercentBar: {

        QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
        createMarkers(percentBarSeries);
        break;
    }

    case QSeries::SeriesTypeScatter: {

        QScatterSeries *scatterSeries = static_cast<QScatterSeries *>(series);
        createMarker(scatterSeries);
        break;
    }

    case QSeries::SeriesTypePie: {

        QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
        createMarkers(pieSeries);
        break;
    }

    case QSeries::SeriesTypeSpline: {

        QSplineSeries* splineSeries = static_cast<QSplineSeries*>(series);
        break;
    }
    default: {
        qDebug()<< "QLegend::handleSeriesAdded" << series->type() << "not implemented.";
        break;
    }
    }

    layoutChanged();
}

void QLegend::handleSeriesRemoved(QSeries* series)
{
    // TODO: delete markers, disconnect.
    mSeriesList.removeOne(series);
    layoutChanged();
}

void QLegend::handleGeometryChanged(const QRectF& size)
{
    mBoundingRect = size;
    layoutChanged();
}

void QLegend::createMarker(QXYSeries* series)
{
    LegendMarker* marker = new LegendMarker(series,this);
    marker->setName(series->name());
    marker->setBrush(series->brush());
    connect(marker,SIGNAL(clicked(QSeries*,Qt::MouseButton)),this,SIGNAL(clicked(QSeries*,Qt::MouseButton)));
    mMarkers.append(marker);
    childItems().append(marker);
}

void QLegend::createMarkers(QBarSeries *series)
{
    foreach(QBarSet* s, series->barSets()) {
        LegendMarker* marker = new LegendMarker(s,this);
        marker->setName(s->name());
        marker->setBrush(s->brush());
        connect(marker,SIGNAL(clicked(QBarSet*,Qt::MouseButton)),this,SIGNAL(clicked(QBarSet*,Qt::MouseButton)));
        mMarkers.append(marker);
        childItems().append(marker);
    }
}

void QLegend::createMarkers(QPieSeries *series)
{
    foreach(QPieSlice* s, series->slices()) {
        LegendMarker* marker = new LegendMarker(s,this);
        marker->setName(s->label());
        marker->setBrush(s->sliceBrush());
        connect(marker,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)),this,SIGNAL(clicked(QPieSlice*,Qt::MouseButton)));
        mMarkers.append(marker);
        childItems().append(marker);
    }
}

void QLegend::layoutChanged()
{
    // Calculate layout for markers and text
    if (mMarkers.count() <= 0) {
        // Nothing to do
        return;
    }

    // TODO: marker defined by series.
    QSizeF markerSize(10,10);

    // TODO: better layout, this is just concept.
    // Leave some space around markers like this: | x x x x |
    qreal steps = mMarkers.count();

    qreal xStep = mBoundingRect.width() / steps;
    qreal yStep = mBoundingRect.height() / steps;
    qreal x = mBoundingRect.x() + 5;
    qreal y = mBoundingRect.y() + (mBoundingRect.height() - markerSize.height())/2;
    foreach (LegendMarker* m, mMarkers) {
        m->setBoundingRect(QRectF(x,y,markerSize.width(),markerSize.height()));
        x += xStep;
    }
}



#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
