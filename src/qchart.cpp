#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qpieseries.h"
#include "qpieseries_p.h"
#include "qxychartseries.h"
#include "qchartaxis.h"
#include "barchartseries.h"
#include "bargroup.h"
#include "stackedbarchartseries.h"
#include "stackedbargroup.h"
#include "percentbarchartseries.h"
#include "percentbargroup.h"
#include "charttheme_p.h"
#include "chartitem_p.h"

#include "xylinechartitem_p.h"
#include "plotdomain_p.h"
#include "axisitem_p.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    m_backgroundItem(0),
    m_titleItem(0),
    m_axisXItem(new AxisItem(AxisItem::X_AXIS, this)),
    m_plotDataIndex(0),
    m_marginSize(0),
    m_chartTheme(new ChartTheme(this)),
    m_dataset(0),
    //m_dataset(new ChartDataSet(this)),
    m_presenter(0)
    //m_presenter(new ChartPresenter(this,m_dataset))
{
    // TODO: the default theme?
    setTheme(QChart::ChartThemeDefault);

    PlotDomain domain;
    m_plotDomainList << domain;
    m_axisYItem << new AxisItem(AxisItem::Y_AXIS,this);
    m_chartItems << m_axisXItem;
    m_chartItems << m_axisYItem.at(0);
}

QChart::~QChart(){}

void QChart::addSeries(QChartSeries* series)
{
    if(m_dataset) {
        m_dataset->addSeries(series);
        return;
    }

    Q_ASSERT(series);
    Q_ASSERT(series->type() != QChartSeries::SeriesTypeInvalid);

    // TODO: we should check the series not already added


    m_chartSeries << series;

    m_plotDataIndex = 0 ;
    m_plotDomainList.resize(1);
    PlotDomain& domain = m_plotDomainList[m_plotDataIndex];

    switch(series->type())
    {
    case QChartSeries::SeriesTypeLine: {

        QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);

        for (int i = 0 ; i < xyseries->count() ; i++) {
            qreal x = xyseries->x(i);
            qreal y = xyseries->y(i);
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
        }

        //XYLineChartItem* item = new XYLineChartItem(xyseries,0,this);

        //m_chartItems << item;
        // TODO:
        //m_chartTheme->addObserver(xyseries);

        break;
    }
    case QChartSeries::SeriesTypeBar: {

        qDebug() << "barSeries added";
        BarChartSeries* barSeries = static_cast<BarChartSeries*>(series);
        BarGroup* barGroup = new BarGroup(*barSeries,this);

        // Add some fugly colors for 5 fist series...
        barGroup->addColor(QColor(255,0,0,128));
        barGroup->addColor(QColor(255,255,0,128));
        barGroup->addColor(QColor(0,255,0,128));
        barGroup->addColor(QColor(0,0,255,128));
        barGroup->addColor(QColor(255,128,0,128));

        m_chartItems << barGroup;
        childItems().append(barGroup);

        qreal x = barSeries->countColumns();
        qreal y = barSeries->max();
        domain.m_minX = qMin(domain.m_minX,x);
        domain.m_minY = qMin(domain.m_minY,y);
        domain.m_maxX = qMax(domain.m_maxX,x);
        domain.m_maxY = qMax(domain.m_maxY,y);
        m_axisXItem->setVisible(false);
        break;
        }
    case QChartSeries::SeriesTypeStackedBar: {

        qDebug() << "barSeries added";
        StackedBarChartSeries* stackedBarSeries = static_cast<StackedBarChartSeries*>(series);
        StackedBarGroup* stackedBarGroup = new StackedBarGroup(*stackedBarSeries,this);

        // Add some fugly colors for 5 fist series...
        stackedBarGroup->addColor(QColor(255,0,0,128));
        stackedBarGroup->addColor(QColor(255,255,0,128));
        stackedBarGroup->addColor(QColor(0,255,0,128));
        stackedBarGroup->addColor(QColor(0,0,255,128));
        stackedBarGroup->addColor(QColor(255,128,0,128));

        m_chartItems << stackedBarGroup;
        childItems().append(stackedBarGroup);

        qreal x = stackedBarSeries->countColumns();
        qreal y = stackedBarSeries->maxColumnSum();
        domain.m_minX = qMin(domain.m_minX,x);
        domain.m_minY = qMin(domain.m_minY,y);
        domain.m_maxX = qMax(domain.m_maxX,x);
        domain.m_maxY = qMax(domain.m_maxY,y);
        m_axisXItem->setVisible(false);
        break;
        }
    case QChartSeries::SeriesTypePercentBar: {

        qDebug() << "barSeries added";
        PercentBarChartSeries* percentBarSeries = static_cast<PercentBarChartSeries*>(series);
        PercentBarGroup* percentBarGroup = new PercentBarGroup(*percentBarSeries,this);

        // Add some fugly colors for 5 fist series...
        percentBarGroup->addColor(QColor(255,0,0,128));
        percentBarGroup->addColor(QColor(255,255,0,128));
        percentBarGroup->addColor(QColor(0,255,0,128));
        percentBarGroup->addColor(QColor(0,0,255,128));
        percentBarGroup->addColor(QColor(255,128,0,128));

        m_chartItems << percentBarGroup;
        childItems().append(percentBarGroup);

        qreal x = percentBarSeries->countColumns();
        domain.m_minX = qMin(domain.m_minX,x);
        domain.m_minY = 0;
        domain.m_maxX = qMax(domain.m_maxX,x);
        domain.m_maxY = 100;
        m_axisXItem->setVisible(false);
        break;
        }
    case QChartSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
        scatterSeries->d->m_theme = m_chartTheme->themeForSeries();
        scatterSeries->d->setParentItem(this);
        scatterSeries->d->m_boundingRect = m_rect.adjusted(margin(),margin(), -margin(), -margin());
        m_chartItems << scatterSeries->d;
        m_chartTheme->addObserver(scatterSeries->d);

        foreach (qreal x, scatterSeries->d->m_x) {
            domain.m_minX = qMin(domain.m_minX, x);
            domain.m_maxX = qMax(domain.m_maxX, x);
        }
        foreach (qreal y, scatterSeries->d->m_y) {
            domain.m_minY = qMin(domain.m_minY, y);
            domain.m_maxY = qMax(domain.m_maxY, y);
        }

        break;
        }
    case QChartSeries::SeriesTypePie: {
        QPieSeries *pieSeries = qobject_cast<QPieSeries *>(series);
        pieSeries->d->setParentItem(this);
        m_chartItems << pieSeries->d;
        pieSeries->d->m_chartTheme = m_chartTheme;
        m_chartTheme->addObserver(pieSeries->d);
        break;
        }
    default:
        break;
    }

    // Update all the items to match the new visible area of the chart
    foreach(ChartItem* i, m_chartItems)
        i->setPlotDomain(m_plotDomainList.at(m_plotDataIndex));
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

void QChart::setBackground(const QColor& startColor, const QColor& endColor, GradientOrientation orientation)
{

    if(!m_backgroundItem){
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setZValue(-1);
    }

    m_bacgroundOrinetation = orientation;
    m_backgroundGradient.setColorAt(0.0, startColor);
    m_backgroundGradient.setColorAt(1.0, endColor);
    m_backgroundGradient.setCoordinateMode(QGradient::ObjectBoundingMode);

    if(orientation == VerticalGradientOrientation){
        m_backgroundGradient.setFinalStop(0,1);
    }else{
        m_backgroundGradient.setFinalStop(1,0);
    }

    m_backgroundItem->setBrush(m_backgroundGradient);
    m_backgroundItem->setPen(Qt::NoPen);
    m_backgroundItem->update();
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
    return m_marginSize;
}

void QChart::setMargin(int margin)
{
    m_marginSize = margin;
}

void QChart::setTheme(QChart::ChartThemeId theme)
{
    m_chartTheme->setTheme(theme);
    setBackground(m_chartTheme->d->m_gradientStartColor,
                  m_chartTheme->d->m_gradientEndColor,
                  m_bacgroundOrinetation);

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

    if(!rectangle.isValid()) return;

    qreal margin = this->margin();

    QRectF rect = rectangle.normalized();
    rect.translate(-margin, -margin);

    PlotDomain& oldDomain = m_plotDomainList[m_plotDataIndex];

    PlotDomain domain = oldDomain.subDomain(rect,m_rect.width() - 2 * margin,m_rect.height() - 2 * margin);

    m_plotDomainList.resize(m_plotDataIndex + 1);
    m_plotDomainList<<domain;
    m_plotDataIndex++;

    foreach (ChartItem* item, m_chartItems)
        item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
    update();
}

void QChart::zoomIn()
{
    if (m_plotDataIndex < m_plotDomainList.count() - 1) {
        m_plotDataIndex++;
        foreach (ChartItem* item, m_chartItems)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    } else {
        QRectF rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());
        rect.setWidth(rect.width()/2);
        rect.setHeight(rect.height()/2);
        rect.moveCenter(m_rect.center());
        zoomInToRect(rect);
    }
}

void QChart::zoomOut()
{
    if (m_plotDataIndex > 0) {
        m_plotDataIndex--;
        foreach (ChartItem* item, m_chartItems)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    }
}

void QChart::zoomReset()
{
    if (m_plotDataIndex > 0) {
        m_plotDataIndex = 0;
        foreach (ChartItem* item, m_chartItems)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    }
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

    // resize and reposition childs
    foreach (ChartItem *item, m_chartItems) {
        item->setPos(rect.topLeft());
        item->setSize(rect.size());
    }

    QGraphicsWidget::resizeEvent(event);
    update();
}



#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
