#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
//series
#include "qbarchartseries.h"
#include "qstackedbarchartseries.h"
#include "qpercentbarchartseries.h"
#include "qlinechartseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"
//items
#include "axisitem_p.h"
#include "barpresenter.h"
#include "stackedbarpresenter.h"
#include "linechartitem_p.h"
#include "percentbarpresenter.h"
#include "linechartanimationitem_p.h"
#include "piepresenter.h"
#include "scatterpresenter_p.h"
#include "splinepresenter_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_dataset(dataset),
m_chartTheme(0),
m_marginSize(0),
m_rect(QRectF(QPoint(0,0),m_chart->size()))
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
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QChartSeries*)),this,SLOT(handleSeriesAdded(QChartSeries*)));
    QObject::connect(m_dataset,SIGNAL(seriesRemoved(QChartSeries*)),this,SLOT(handleSeriesRemoved(QChartSeries*)));
    QObject::connect(m_dataset,SIGNAL(axisAdded(QChartAxis*)),this,SLOT(handleAxisAdded(QChartAxis*)));
    QObject::connect(m_dataset,SIGNAL(axisRemoved(QChartAxis*)),this,SLOT(handleAxisRemoved(QChartAxis*)));
    QObject::connect(m_dataset,SIGNAL(seriesDomainChanged(QChartSeries*,const Domain&)),this,SLOT(handleSeriesDomainChanged(QChartSeries*,const Domain&)));
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

    if(axis==m_dataset->axisX()){
    item = new AxisItem(AxisItem::X_AXIS,m_chart);
    }else{
    item = new AxisItem(AxisItem::Y_AXIS,m_chart);
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


void ChartPresenter::handleSeriesAdded(QChartSeries* series)
{
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {
            QLineChartSeries* lineSeries = static_cast<QLineChartSeries*>(series);
            LineChartItem* item = new LineChartAnimationItem(this,lineSeries,m_chart);
            m_chartTheme->decorate(item,lineSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(lineSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QChartSeries::SeriesTypeBar: {
            QBarChartSeries* barSeries = static_cast<QBarChartSeries*>(series);
            BarPresenter* item = new BarPresenter(barSeries,m_chart);
            m_chartTheme->decorate(item,barSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(barSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            // m_axisXItem->setVisible(false);
            break;
        }

        case QChartSeries::SeriesTypeStackedBar: {

            QStackedBarChartSeries* stackedBarSeries = static_cast<QStackedBarChartSeries*>(series);
            StackedBarPresenter* item = new StackedBarPresenter(stackedBarSeries,m_chart);
            m_chartTheme->decorate(item,stackedBarSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(stackedBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QChartSeries::SeriesTypePercentBar: {

            QPercentBarChartSeries* percentBarSeries = static_cast<QPercentBarChartSeries*>(series);
            PercentBarPresenter* item = new PercentBarPresenter(percentBarSeries,m_chart);
            m_chartTheme->decorate(item,percentBarSeries ,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(percentBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }
        case QChartSeries::SeriesTypeScatter: {
            QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
            ScatterPresenter *scatterPresenter = new ScatterPresenter(scatterSeries, m_chart);
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)),
                             scatterPresenter, SLOT(handleGeometryChanged(const QRectF&)));
            m_chartTheme->decorate(scatterPresenter, scatterSeries, m_chartItems.count());
            m_chartItems.insert(scatterSeries, scatterPresenter);
            break;
        }
        case QChartSeries::SeriesTypePie: {
            QPieSeries *s = qobject_cast<QPieSeries *>(series);
            PiePresenter* pie = new PiePresenter(m_chart, s);
            m_chartTheme->decorate(pie, s, m_chartItems.count());
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)), pie, SLOT(handleGeometryChanged(const QRectF&)));
            m_chartItems.insert(series, pie);
            break;
        }
    case QChartSeries::SeriesTypeSpline: {
        QSplineSeries* splineSeries = qobject_cast<QSplineSeries*>(series);
        SplinePresenter* splinePresenter = new SplinePresenter
        break;
    }
        default: {
            qDebug()<< "Series type" << series->type() << "not implemented.";
            break;
        }
    }

    if(m_rect.isValid()) emit geometryChanged(m_rect);
}

void ChartPresenter::handleSeriesRemoved(QChartSeries* series)
{
	ChartItem* item = m_chartItems.take(series);
	delete item;
}

void ChartPresenter::handleSeriesChanged(QChartSeries* series)
{
    //TODO:
}

void ChartPresenter::handleSeriesDomainChanged(QChartSeries* series, const Domain& domain)
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
    QMapIterator<QChartSeries*,ChartItem*> i(m_chartItems);

    int index=0;
    while (i.hasNext()) {
        i.next();
        index++;
        m_chartTheme->decorate(i.value(),i.key(),index);
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


#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
