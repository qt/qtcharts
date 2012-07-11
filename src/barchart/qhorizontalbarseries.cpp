#include "qhorizontalbarseries.h"
#include "qhorizontalbarseries_p.h"
#include "horizontalbarchartitem_p.h"
#include "horizontalbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHorizontalBarSeries::QHorizontalBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalBarSeriesPrivate(this), parent)
{
}

QAbstractSeries::SeriesType QHorizontalBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalBar;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalBarSeriesPrivate::QHorizontalBarSeriesPrivate(QHorizontalBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalBarSeriesPrivate::scaleDomain(Domain& domain)
{
    // TODO:
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal y = categoryCount();
    qreal x = max();
    minX = qMin(minX, x);
    minY = qMin(minY, -0.5);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y -0.5);
    tickYCount = y+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}


Chart* QHorizontalBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalBarSeries);

    HorizontalBarChartItem* bar = new HorizontalBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimator(presenter->animator());
        bar->setAnimation(new HorizontalBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

QAbstractAxis::AxisType QHorizontalBarSeriesPrivate::defaultAxisXType() const
{
    return QAbstractAxis::AxisTypeValues;
}

QAbstractAxis::AxisType QHorizontalBarSeriesPrivate::defaultAxisYType() const
{
    return QAbstractAxis::AxisTypeValues;
}


#include "moc_qhorizontalbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
