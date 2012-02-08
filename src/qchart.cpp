#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qpieseries.h"
#include "qpieseries_p.h"
#include "qchartaxis.h"
#include "charttheme_p.h"
#include "chartitem_p.h"
#include "plotdomain_p.h"
#include "axisitem_p.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"

//series
#include "barchartseries.h"
#include "stackedbarchartseries.h"
#include "percentbarchartseries.h"
#include "qxychartseries.h"


#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    m_backgroundItem(0),
    m_titleItem(0),
    m_axisXItem(0),
    m_plotDataIndex(0),
    m_chartTheme(new ChartTheme(this)),
    //m_dataset(0),
    m_dataset(new ChartDataSet(this)),
    //m_presenter(0)
    m_presenter(new ChartPresenter(this,m_dataset))
{
    // TODO: the default theme?
    setTheme(QChart::ChartThemeDefault);

    PlotDomain domain;
    m_plotDomainList << domain;

    //m_chartItems << m_axisXItem;
    //m_chartItems << m_axisYItem.at(0);
}

QChart::~QChart(){}

void QChart::addSeries(QChartSeries* series)
{
   m_dataset->addSeries(series);
}

QChartSeries* QChart::createSeries(QChartSeries::QChartSeriesType type)
{
    // TODO: support also other types; not only scatter and pie

    QChartSeries *series(0);

    switch (type) {
    case QChartSeries::SeriesTypeLine: {
        series = QXYChartSeries::create();
        break;
    }
    case QChartSeries::SeriesTypeBar: {
        series = new BarChartSeries(this);
        break;
    }
    case QChartSeries::SeriesTypeStackedBar: {
        series = new StackedBarChartSeries(this);
        break;
    }
    case QChartSeries::SeriesTypePercentBar: {
        series = new PercentBarChartSeries(this);
        break;
    }
    case QChartSeries::SeriesTypeScatter: {
        series = new QScatterSeries(this);
        break;
    }
    case QChartSeries::SeriesTypePie: {
        series = new QPieSeries(this);
        break;
    }
    default:
        Q_ASSERT(false);
        break;
    }

    addSeries(series);
    return series;
}

void QChart::setChartBackgroundBrush(const QBrush& brush)
{

    if(!m_backgroundItem){
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setZValue(-1);
    }

    m_backgroundItem->setBrush(brush);
    m_backgroundItem->update();
}

void QChart::setChartBackgroundPen(const QPen& pen)
{

    if(!m_backgroundItem){
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setZValue(-1);
    }

    m_backgroundItem->setPen(pen);
    m_backgroundItem->update();
}

void QChart::setTitle(const QString& title,const QFont& font)
{
    if(!m_titleItem) m_titleItem = new QGraphicsTextItem(this);
    m_titleItem->setPlainText(title);
    m_titleItem->setFont(font);
}

int QChart::margin() const
{
    m_presenter->margin();
}

void QChart::setMargin(int margin)
{
   m_presenter->setMargin(margin);
}

void QChart::setTheme(QChart::ChartThemeId theme)
{
    m_chartTheme->setTheme(theme);

    QLinearGradient backgroundGradient;
    backgroundGradient.setColorAt(0.0, m_chartTheme->d->m_gradientStartColor);
    backgroundGradient.setColorAt(1.0, m_chartTheme->d->m_gradientEndColor);
    backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    setChartBackgroundBrush(backgroundGradient);

    // TODO: Move the controlling of the series presentations into private implementation of the
    // series instead of QChart controlling themes for each
    // In other words, the following should be used when creating xy series:
    // m_chartTheme->addObserver(xyseries)
    foreach (QChartSeries *series, m_chartSeries) {
        if (series->type() == QChartSeries::SeriesTypeLine) {
            QXYChartSeries *xyseries = static_cast<QXYChartSeries *>(series);
            SeriesTheme seriesTheme = m_chartTheme->themeForSeries();
            xyseries->setPen(seriesTheme.linePen);
        }
    }

    update();
}

QChart::ChartThemeId QChart::theme()
{
    return (QChart::ChartThemeId) m_chartTheme->d->m_currentTheme;
}

void QChart::zoomInToRect(const QRectF& rectangle)
{
    m_presenter->zoomInToRect(rectangle);
}

void QChart::zoomIn()
{
    m_presenter->zoomIn();
}

void QChart::zoomOut()
{
    m_presenter->zoomOut();
}

void QChart::zoomReset()
{
    m_presenter->zoomReset();
}

void QChart::setAxisX(const QChartAxis& axis)
{
    setAxis(m_axisXItem,axis);
}
void QChart::setAxisY(const QChartAxis& axis)
{
    setAxis(m_axisYItem.at(0),axis);
}

void QChart::setAxisY(const QList<QChartAxis>& axis)
{
    //TODO not implemented
}

void QChart::setAxis(AxisItem *item, const QChartAxis& axis)
{
    item->setVisible(axis.isAxisVisible());
}

void QChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{

    m_rect = QRectF(QPoint(0,0),event->newSize());
    QRectF rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());

    // recalculate title position
    if (m_titleItem) {
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),m_rect.top()/2 + margin()/2);
    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(rect);
    }

    QGraphicsWidget::resizeEvent(event);
    update();
}



#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
