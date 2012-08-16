#include "qhorizontalpercentbarseries.h"
#include "qhorizontalpercentbarseries_p.h"
#include "horizontalpercentbarchartitem_p.h"
#include "horizontalpercentbaranimation_p.h"

#include "chartdataset_p.h"
#include "charttheme_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHorizontalPercentBarSeries
    \brief Series for creating horizontal percent bar chart
    \mainclass

    QHorizontalPercentBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars
    as groups, where bars in same category are grouped next to each other. QHorizontalPercentBarSeries groups the data
    from sets to categories, which are defined by a QStringList.

    See the \l {HorizontalPercentBarChart Example} {horizontal percent bar chart example} to learn how to create a horizontal percent bar chart.
    \image examples_horizontalpercentbarchart.png

    \sa QBarSet, QBarSeries, QPercentBarSeries, QAbstractBarSeries, QStackedBarSeries, QHorizontalStackedBarSeries, QHorizontalBarSeries
*/

/*!
    Constructs empty QHorizontalPercentBarSeries.
    QHorizontalPercentBarSeries is QObject which is a child of a \a parent.
*/
QHorizontalPercentBarSeries::QHorizontalPercentBarSeries(QObject *parent) :
    QAbstractBarSeries(*new QHorizontalPercentBarSeriesPrivate(this), parent)
{
}

/*!
    Returns QChartSeries::SeriesTypeHorizontalPercentBar.
*/
QAbstractSeries::SeriesType QHorizontalPercentBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeHorizontalPercentBar;
}

/*!
    Destructor
    Removes series from chart.
*/
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

ChartElement* QHorizontalPercentBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QHorizontalPercentBarSeries);

    HorizontalPercentBarChartItem* bar = new HorizontalPercentBarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        bar->setAnimation(new HorizontalPercentBarAnimation(bar));
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;
}

#include "moc_qhorizontalpercentbarseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
