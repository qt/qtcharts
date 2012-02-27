#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
//series
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qlineseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"
//items
#include "axisitem_p.h"
#include "axisanimationitem_p.h"
#include "barpresenter.h"
#include "stackedbarpresenter.h"
#include "linechartitem_p.h"
#include "percentbarpresenter.h"
#include "linechartanimationitem_p.h"
#include "piepresenter_p.h"
#include "scatterpresenter_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_dataset(dataset),
m_chartTheme(0),
m_marginSize(0),
m_rect(QRectF(QPoint(0,0),m_chart->size())),
m_options(0)
{
	createConnections();
    setChartTheme(QChart::ChartThemeDefault);

}

ChartPresenter::~ChartPresenter()
{
}

void ChartPresenter::createConnections()
{
    QObject::connect(m_chart,SIGNAL(geometryChanged()),this,SLOT(handleGeometryChanged()));
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QSeries*)),this,SLOT(handleSeriesAdded(QSeries*)));
    QObject::connect(m_dataset,SIGNAL(seriesRemoved(QSeries*)),this,SLOT(handleSeriesRemoved(QSeries*)));
    QObject::connect(m_dataset,SIGNAL(axisAdded(QChartAxis*)),this,SLOT(handleAxisAdded(QChartAxis*)));
    QObject::connect(m_dataset,SIGNAL(axisRemoved(QChartAxis*)),this,SLOT(handleAxisRemoved(QChartAxis*)));
    QObject::connect(m_dataset,SIGNAL(seriesDomainChanged(QSeries*,const Domain&)),this,SLOT(handleSeriesDomainChanged(QSeries*,const Domain&)));
    QObject::connect(m_dataset,SIGNAL(axisLabelsChanged(QChartAxis*,const QStringList&)),this,SLOT(handleAxisLabelsChanged(QChartAxis*,const QStringList&)));
}


QRectF ChartPresenter::geometry() const
{
    return m_rect;
}

void ChartPresenter::handleGeometryChanged()
{
    m_rect = QRectF(QPoint(0,0),m_chart->size());
    m_rect.adjust(m_marginSize,m_marginSize, -m_marginSize, -m_marginSize);
    Q_ASSERT(m_rect.isValid());
    emit geometryChanged(m_rect);
}

int ChartPresenter::margin() const
{
    return m_marginSize;
}

void ChartPresenter::setMargin(int margin)
{
    m_marginSize = margin;
}

void ChartPresenter::handleAxisAdded(QChartAxis* axis)
{

    AxisItem* item ;

    if(!m_options.testFlag(QChart::GridAxisAnimations))
    {
        item = new AxisItem(axis==m_dataset->axisX()?AxisItem::X_AXIS : AxisItem::Y_AXIS,m_chart);
    }else{
        item = new AxisAnimationItem(axis==m_dataset->axisX()?AxisItem::X_AXIS : AxisItem::Y_AXIS,m_chart);
    }

    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
    QObject::connect(axis,SIGNAL(update(QChartAxis*)),item,SLOT(handleAxisUpdate(QChartAxis*)));

    item->handleAxisUpdate(axis);
    item->handleGeometryChanged(m_rect);
    m_chartTheme->decorate(axis,item);
    m_axisItems.insert(axis,item);
}

void ChartPresenter::handleAxisRemoved(QChartAxis* axis)
{
    AxisItem* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QSeries* series)
{
    switch(series->type())
    {
        case QSeries::SeriesTypeLine: {
            QLineSeries* lineSeries = static_cast<QLineSeries*>(series);
            LineChartItem* item;
            if(m_options.testFlag(QChart::SeriesAnimations)){
                item = new LineChartAnimationItem(this,lineSeries,m_chart);
            }else{
                item = new LineChartItem(this,lineSeries,m_chart);
            }
            m_chartTheme->decorate(item,lineSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(lineSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QSeries::SeriesTypeBar: {
            QBarSeries* barSeries = static_cast<QBarSeries*>(series);
            BarPresenter* item = new BarPresenter(barSeries,m_chart);
            m_chartTheme->decorate(item,barSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(barSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            // m_axisXItem->setVisible(false);
            break;
        }

        case QSeries::SeriesTypeStackedBar: {

            QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
            StackedBarPresenter* item = new StackedBarPresenter(stackedBarSeries,m_chart);
            m_chartTheme->decorate(item,stackedBarSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(stackedBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QSeries::SeriesTypePercentBar: {

            QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
            PercentBarPresenter* item = new PercentBarPresenter(percentBarSeries,m_chart);
            m_chartTheme->decorate(item,percentBarSeries ,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(percentBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }
        case QSeries::SeriesTypeScatter: {
            QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
            ScatterPresenter *scatterPresenter = new ScatterPresenter(scatterSeries, m_chart);
            QObject::connect(scatterPresenter, SIGNAL(clicked()), scatterSeries, SIGNAL(clicked()));
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)),
                             scatterPresenter, SLOT(handleGeometryChanged(const QRectF&)));
            m_chartTheme->decorate(scatterPresenter, scatterSeries, m_chartItems.count());
            m_chartItems.insert(scatterSeries, scatterPresenter);
            break;
        }
        case QSeries::SeriesTypePie: {
            QPieSeries *s = qobject_cast<QPieSeries *>(series);
            PiePresenter* pie = new PiePresenter(m_chart, s);
            m_chartTheme->decorate(pie, s, m_chartItems.count());
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)), pie, SLOT(handleGeometryChanged(const QRectF&)));

            // Hide all from background when there is only piechart
            // TODO: refactor this ugly code... should be one setting for this
            if (m_chartItems.count() == 0) {
                m_chart->axisX()->setAxisVisible(false);
                m_chart->axisY()->setAxisVisible(false);
                m_chart->axisX()->setGridVisible(false);
                m_chart->axisY()->setGridVisible(false);
                m_chart->axisX()->setLabelsVisible(false);
                m_chart->axisY()->setLabelsVisible(false);
                m_chart->axisX()->setShadesVisible(false);
                m_chart->axisY()->setShadesVisible(false);
                m_chart->setChartBackgroundBrush(Qt::transparent);
            }

            m_chartItems.insert(series, pie);
            break;
        }
        default: {
            qDebug()<< "Series type" << series->type() << "not implemented.";
            break;
        }
    }

    if(m_rect.isValid()) emit geometryChanged(m_rect);
}

void ChartPresenter::handleSeriesRemoved(QSeries* series)
{
	ChartItem* item = m_chartItems.take(series);
	delete item;
}

void ChartPresenter::handleSeriesChanged(QSeries* series)
{
    //TODO:
}

void ChartPresenter::handleSeriesDomainChanged(QSeries* series, const Domain& domain)
{
    m_chartItems.value(series)->handleDomainChanged(domain);
}

void ChartPresenter::handleAxisLabelsChanged(QChartAxis* axis,const QStringList& labels)
{
    m_axisItems.value(axis)->handleLabelsChanged(axis,labels);
}

void ChartPresenter::setChartTheme(QChart::ChartTheme theme)
{
    delete m_chartTheme;

    m_chartTheme = ChartTheme::createTheme(theme);

    m_chartTheme->decorate(m_chart);
    QMapIterator<QSeries*,ChartItem*> i(m_chartItems);

    int index=0;
    while (i.hasNext()) {
        i.next();
        m_chartTheme->decorate(i.value(),i.key(),index);
        index++;
    }

    QMapIterator<QChartAxis*,AxisItem*> j(m_axisItems);
    while (j.hasNext()) {
            j.next();
            m_chartTheme->decorate(j.key(),j.value());
    }
}

QChart::ChartTheme ChartPresenter::chartTheme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if(m_options!=options) {

        m_options=options;

        //recreate elements

        QList<QChartAxis*> axisList = m_axisItems.uniqueKeys();
        QList<QSeries*> seriesList = m_chartItems.uniqueKeys();

        foreach(QChartAxis* axis, axisList) {
            handleAxisRemoved(axis);
            handleAxisAdded(axis);
        }
        foreach(QSeries* series, seriesList) {
            handleSeriesRemoved(series);
            handleSeriesAdded(series);
        }

        //now reintialize view data
        //TODO: make it more nice
        m_dataset->setDomain(m_dataset->domainIndex());
    }
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}


#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
