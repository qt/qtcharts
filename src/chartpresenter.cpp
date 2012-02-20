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
//items
#include "axisitem_p.h"
#include "barpresenter.h"
#include "stackedbarpresenter.h"
#include "linechartitem_p.h"
#include "percentbarpresenter.h"
#include "linechartanimationitem_p.h"
#include "piepresenter.h"
#include "scatterpresenter_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_dataset(dataset),
m_chartTheme(0),
m_axisXItem(new AxisItem(AxisItem::X_AXIS,m_chart)),
m_axisYItem(new AxisItem(AxisItem::Y_AXIS,m_chart)),
m_domainIndex(0),
m_marginSize(0),
m_rect(QRectF(QPoint(0,0),m_chart->size()))
{
    setChartTheme(QChart::ChartThemeDefault);
    createConnections();
}

ChartPresenter::~ChartPresenter()
{
}

void ChartPresenter::createConnections()
{
    QObject::connect(m_chart,SIGNAL(geometryChanged()),this,SLOT(handleGeometryChanged()));
    QObject::connect(m_dataset,SIGNAL(seriesAdded(QChartSeries*)),this,SLOT(handleSeriesAdded(QChartSeries*)));
    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),m_axisXItem,SLOT(handleGeometryChanged(const QRectF&)));
    QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),m_axisXItem,SLOT(handleDomainChanged(const Domain&)));
    QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),m_axisYItem,SLOT(handleGeometryChanged(const QRectF&)));
    QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),m_axisYItem,SLOT(handleDomainChanged(const Domain&)));
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

void ChartPresenter::handleSeriesAdded(QChartSeries* series)
{
    qDebug() << " ChartPresenter::handleSeriesAdded";
    switch(series->type())
    {
        case QChartSeries::SeriesTypeLine: {
            QLineChartSeries* lineSeries = static_cast<QLineChartSeries*>(series);
            LineChartItem* item = new LineChartAnimationItem(this,lineSeries,m_chart);
            m_chartTheme->decorate(item,lineSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),item,SLOT(handleDomainChanged(const Domain&)));
            QObject::connect(lineSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QChartSeries::SeriesTypeBar: {
            QBarChartSeries* barSeries = static_cast<QBarChartSeries*>(series);
            BarPresenter* item = new BarPresenter(barSeries->model(),m_chart);
            m_chartTheme->decorate(item,barSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),item,SLOT(handleDomainChanged(const Domain&)));
            QObject::connect(barSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            // m_axisXItem->setVisible(false);
            break;
        }

        case QChartSeries::SeriesTypeStackedBar: {

            QStackedBarChartSeries* stackedBarSeries = static_cast<QStackedBarChartSeries*>(series);
            StackedBarPresenter* item = new StackedBarPresenter(stackedBarSeries->model(),m_chart);
            m_chartTheme->decorate(item,stackedBarSeries,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),item,SLOT(handleDomainChanged(const Domain&)));
            QObject::connect(stackedBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }

        case QChartSeries::SeriesTypePercentBar: {

            QPercentBarChartSeries* percentBarSeries = static_cast<QPercentBarChartSeries*>(series);
            PercentBarPresenter* item = new PercentBarPresenter(percentBarSeries->model(),m_chart);
            m_chartTheme->decorate(item,percentBarSeries ,m_chartItems.count());
            QObject::connect(this,SIGNAL(geometryChanged(const QRectF&)),item,SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset,SIGNAL(domainChanged(const Domain&)),item,SLOT(handleDomainChanged(const Domain&)));
            QObject::connect(percentBarSeries,SIGNAL(changed(int)),item,SLOT(handleModelChanged(int)));
            m_chartItems.insert(series,item);
            break;
        }
        case QChartSeries::SeriesTypeScatter: {
            QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
            ScatterPresenter *scatterPresenter = new ScatterPresenter(scatterSeries, m_chart);
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)),
                             scatterPresenter, SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset, SIGNAL(domainChanged(const Domain&)),
                             scatterPresenter, SLOT(handleDomainChanged(const Domain&)));
            m_chartTheme->decorate(scatterPresenter, scatterSeries, m_chartItems.count());
            m_chartItems.insert(scatterSeries, scatterPresenter);
            break;
        }
        case QChartSeries::SeriesTypePie: {
            QPieSeries *s = qobject_cast<QPieSeries *>(series);
            PiePresenter* pie = new PiePresenter(m_chart, s);
            m_chartTheme->decorate(pie, s, m_chartItems.count());
            QObject::connect(this, SIGNAL(geometryChanged(const QRectF&)), pie, SLOT(handleGeometryChanged(const QRectF&)));
            QObject::connect(m_dataset, SIGNAL(domainChanged(const Domain&)), pie, SLOT(handleDomainChanged(const Domain&)));
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

void ChartPresenter::handleSeriesChanged(QChartSeries* series)
{
    //TODO:
}

void ChartPresenter::zoomInToRect(const QRectF& rect)
{
    if(!rect.isValid()) return;
    QRectF r = rect.normalized();
    r.translate(-m_marginSize, -m_marginSize);
    Domain domain (m_dataset->domain().subDomain(r,m_rect.width(),m_rect.height()));
    m_dataset->addDomain(domain);
}

void ChartPresenter::zoomIn()
{
    if (!m_dataset->nextDomain()) {
        QRectF rect = m_rect;
        rect.setWidth(rect.width()/2);
        rect.setHeight(rect.height()/2);
        rect.moveCenter(m_rect.center());
        Domain domain (m_dataset->domain().subDomain(rect,m_rect.width(),m_rect.height()));
        m_dataset->addDomain(domain);
    }
}

void ChartPresenter::zoomOut()
{
    m_dataset->previousDomain();
}

void ChartPresenter::zoomReset()
{
    m_dataset->clearDomains();
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

    m_chartTheme->decorate(m_axisX, m_axisXItem);
    m_chartTheme->decorate(m_axisY, m_axisYItem);

}


QChart::ChartTheme ChartPresenter::chartTheme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setDefaultAxisX(const QChartAxis& axis)
{
    //if(m_axisX != axis) {
        m_axisX = axis;
        m_axisXItem->handleAxisChanged(m_axisX);
    //}
}

void ChartPresenter::setDefaultAxisY(const QChartAxis& axis)
{
    // if(m_axisY != axis) {
        m_axisY = axis;
        m_axisYItem->handleAxisChanged(m_axisY);
    //}
}

QChartAxis ChartPresenter::defaultAxisX() const
{
    return m_axisX;
}

QChartAxis ChartPresenter::defaultAxisY() const
{
    return m_axisY;
}

QChartAxis ChartPresenter::axisY(int id) const
{
    return m_axis.value(id);
}

int ChartPresenter::addAxisY(const QChartAxis& axis)
{
    int key =0 ;

    while(m_axis.contains(key)){
        key++;
        //TODO overflow
    }

    m_axis.insert(key,axis);
    m_axisItems.insert(key,new AxisItem(AxisItem::Y_AXIS,m_chart));

    return key;
}


void ChartPresenter::removeAxisY(int id)
{
    m_axis.remove(id);
    delete m_axisItems.take(id);
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
