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
    ,mMinimumSize(50,20)                // TODO: magic numbers
{
}

void QLegend::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(mBackgroundBrush);
    painter->drawRect(mBoundingRect);
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

QSizeF QLegend::minimumSize() const
{
    return mMinimumSize;
}

void QLegend::setMinimumSize(const QSizeF size)
{
    mMinimumSize = size;
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
        createMarker(splineSeries);
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
    if (series->type() == QSeries::SeriesTypeArea)
    {
        // This is special case. Area series has upper and lower series, which each have markers
        QAreaSeries* s = static_cast<QAreaSeries*> (series);
        deleteMarkers(s->upperSeries());
        deleteMarkers(s->lowerSeries());
    } else {
        deleteMarkers(series);
    }

    mSeriesList.removeOne(series);
    layoutChanged();
}

void QLegend::handleGeometryChanged(const QRectF& size)
{
    mBoundingRect = size;
    layoutChanged();
}

void QLegend::deleteMarkers(QSeries *series)
{
    // Search all markers that belong to given series and delete them.
    foreach (LegendMarker *m, mMarkers) {
        if (m->series() == series) {
            mMarkers.removeOne(m);
            delete m;
        }
    }
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
        LegendMarker* marker = new LegendMarker(series,s,this);
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
        LegendMarker* marker = new LegendMarker(series,s,this);
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

    qreal steps = mMarkers.count();
    qreal xStep = mBoundingRect.width() / steps;
    qreal x=mBoundingRect.x();
    qreal y = mBoundingRect.y() + (mBoundingRect.height()/4);
    foreach (LegendMarker* m, mMarkers) {
        m->setBoundingRect(QRectF(x,y,xStep,mBoundingRect.height()/2));
        x += xStep;
    }
}

#include "moc_qlegend.cpp"
QTCOMMERCIALCHART_END_NAMESPACE
