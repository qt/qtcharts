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

QHorizontalStackedBarSeries::~QHorizontalStackedBarSeries()
{
    Q_D(QHorizontalStackedBarSeries);
    if(d->m_dataset) {
        d->m_dataset->removeSeries(this);
    }
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

    qreal y = categoryCount();
    qreal x = maxCategorySum();
    minX = qMin(minX, x);
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y - (qreal)0.5);

    domain.setRange(minX,maxX,minY,maxY);
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

#include "moc_qhorizontalstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
