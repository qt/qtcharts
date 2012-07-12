#include "qhorizontalstackedbarseries.h"
#include "qhorizontalstackedbarseries_p.h"
#include "horizontalstackedbarchartitem_p.h"
#include "horizontalstackedbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHorizontalStackedBarSeries::QHorizontalStackedBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalStackedBarSeriesPrivate(this), parent)
{
}

QAbstractSeries::SeriesType QHorizontalStackedBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalStackedBar;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalStackedBarSeriesPrivate::QHorizontalStackedBarSeriesPrivate(QHorizontalStackedBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalStackedBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal y = categoryCount();
    qreal x = maxCategorySum();
    minX = qMin(minX, x);
    minY = qMin(minY, -0.5);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y -0.5);
    tickYCount = y+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}

Chart* QHorizontalStackedBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalStackedBarSeries);

    HorizontalStackedBarChartItem* bar = new HorizontalStackedBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimator(presenter->animator());
        bar->setAnimation(new HorizontalStackedBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

QAbstractAxis::AxisType QHorizontalStackedBarSeriesPrivate::defaultAxisXType() const
{
    return QAbstractAxis::AxisTypeValues;
}

QAbstractAxis::AxisType QHorizontalStackedBarSeriesPrivate::defaultAxisYType() const
{
    return QAbstractAxis::AxisTypeCategories;
}


#include "moc_qhorizontalstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
