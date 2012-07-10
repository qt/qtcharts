#include "qhorizontalbarseries.h"
#include "qhorizontalbarseries_p.h"
QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHorizontalBarSeries::QHorizontalBarSeries(QObject *parent) :
    QAbstractBarSeries(parent)
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
    Q_UNUSED(domain);
    /*
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = categoryCount();
    qreal y = max();
    minX = qMin(minX, -0.5);
    minY = qMin(minY, y);
    maxX = qMax(maxX, x - 0.5);
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
    */
}


Chart* QHorizontalBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    // TODO:
    Q_UNUSED(presenter);
    return 0;
/*
    Q_Q(QHorizontalBarSeries);

    GroupedBarChartItem* bar = new GroupedBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
*/
}


#include "moc_qhorizontalbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
