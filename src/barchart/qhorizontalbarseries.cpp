#include "qhorizontalbarseries.h"
#include "qhorizontalbarseries_p.h"
#include "horizontalbarchartitem_p.h"
#include "horizontalbaranimation_p.h"
#include "qbarcategoriesaxis.h"

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
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());

    qreal y = categoryCount();
    qreal x = max();
    minX = qMin(minX, x);
    minY = qMin(minY, - (qreal)0.5);
    maxX = qMax(maxX, x);
    maxY = qMax(maxY, y - (qreal)0.5);

    domain.setRange(minX,maxX,minY,maxY);
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

void QHorizontalBarSeriesPrivate::initializeAxis(QAbstractAxis* axis)
{

    if(axis->type()==QAbstractAxis::AxisTypeCategories && axis->orientation()==Qt::Vertical)
    {
        QBarCategoriesAxis* cataxis = qobject_cast<QBarCategoriesAxis*>(axis);
        Q_ASSERT(cataxis);
        QStringList categories;
        for (int i(1); i < categoryCount()+1; i++)
        categories << QString::number(i);
        cataxis->append(categories);
    }
}

QAbstractAxis::AxisType QHorizontalBarSeriesPrivate::defaultAxisType(Qt::Orientation orientation) const
{
    if(orientation==Qt::Vertical)
        return QAbstractAxis::AxisTypeCategories;
    else
        return QAbstractAxis::AxisTypeValues;
}

#include "moc_qhorizontalbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
