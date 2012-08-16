#include "qhorizontalstackedbarseries.h"
#include "qhorizontalstackedbarseries_p.h"
#include "horizontalstackedbarchartitem_p.h"
#include "horizontalstackedbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QHorizontalStackedBarSeries
    \brief Series for creating horizontal stacked bar chart
    \mainclass

    QHorizontalStackedBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalStackedBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalStackedBarChart Example} {horizontal stacked bar chart example} to learn how to create a horizontal stacked bar chart.
    \image examples_horizontalstackedbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalPercentBarSeries, QHorizontalBarSeries
*/

/*!
    Constructs empty QHorizontalStackedBarSeries.
    QHorizontalStackedBarSeries is QObject which is a child of a \a parent.
*/
QHorizontalStackedBarSeries::QHorizontalStackedBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalStackedBarSeriesPrivate(this), parent)
{
}

/*!
    Destructor
    Removes series from chart.
*/
QHorizontalStackedBarSeries::~QHorizontalStackedBarSeries()
{
    Q_D(QHorizontalStackedBarSeries);
    if(d->m_dataset) {
        d->m_dataset->removeSeries(this);
    }
}

/*!
    Returns QChartSeries::SeriesTypeHorizontalStackedBar.
*/
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

ChartElement* QHorizontalStackedBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalStackedBarSeries);

    HorizontalStackedBarChartItem* bar = new HorizontalStackedBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimation(new HorizontalStackedBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qhorizontalstackedbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
