#include "qhorizontalpercentbarseries.h"
#include "qhorizontalpercentbarseries_p.h"
#include "horizontalpercentbarchartitem_p.h"
#include "horizontalpercentbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHorizontalPercentBarSeries::QHorizontalPercentBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalPercentBarSeriesPrivate(this), parent)
{
}

QAbstractSeries::SeriesType QHorizontalPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalPercentBar;
}

QHorizontalPercentBarSeries::~QHorizontalPercentBarSeries()
{
    Q_D(QHorizontalPercentBarSeries);
    if(d->m_dataset) {
        d->m_dataset->removeSeries(this);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QHorizontalPercentBarSeriesPrivate::QHorizontalPercentBarSeriesPrivate(QHorizontalPercentBarSeries *q) : QAbstractBarSeriesPrivate(q)
{

}

void QHorizontalPercentBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    qreal y = categoryCount();
    minX = 0;
    maxX = 100;
    minY = qMin(minY, - (qreal)0.5);
    maxY = qMax(maxY, y - (qreal)0.5);

    domain.setRange(minX,maxX,minY,maxY);
}

Chart* QHorizontalPercentBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalPercentBarSeries);

    HorizontalPercentBarChartItem* bar = new HorizontalPercentBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimator(presenter->animator());
        bar->setAnimation(new HorizontalPercentBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qhorizontalpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
