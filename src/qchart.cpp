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
#include "chartitemcontrol.h"

#include "xylinechartitem_p.h"
#include "plotdomain_p.h"
#include "axisitem_p.h"
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsObject* parent) : QGraphicsObject(parent),
    m_backgroundItem(0),
    m_titleItem(0),
    m_axisXItem(new AxisItem(AxisItem::X_AXIS,this)),
    m_plotDataIndex(0),
    m_marginSize(0),
    m_chartTheme(new ChartTheme())
{
    // TODO: the default theme?
    setTheme(QChart::ChartThemeDefault);

    PlotDomain domain;
    m_plotDomainList << domain;
    m_axisYItem << new AxisItem(AxisItem::Y_AXIS,this);
    m_chartItemControls << m_axisXItem;
    m_chartItemControls << m_axisYItem.at(0);
}

QChart::~QChart(){}

QRectF QChart::boundingRect() const
{
    return m_rect;
}

void QChart::addSeries(QChartSeries* series)
{
    // TODO: we should check the series not already added

    m_chartSeries << series;

    switch(series->type())
    {
    case QChartSeries::SeriesTypeLine: {

        QXYChartSeries* xyseries = static_cast<QXYChartSeries*>(series);
        m_plotDataIndex = 0 ;
        m_plotDomainList.resize(1);

        PlotDomain& domain = m_plotDomainList[m_plotDataIndex];

        for (int i = 0 ; i < xyseries->count() ; i++)
        {
            qreal x = xyseries->x(i);
            qreal y = xyseries->y(i);
            domain.m_minX = qMin(domain.m_minX,x);
            domain.m_minY = qMin(domain.m_minY,y);
            domain.m_maxX = qMax(domain.m_maxX,x);
            domain.m_maxY = qMax(domain.m_maxY,y);
        }

        XYLineChartItem* item = new XYLineChartItem(xyseries,this);

        // TODO: combine ChartItemControl and ChartItem apis
        m_chartItemControls << item;
        item->setTheme(m_chartTheme);

        foreach(ChartItemControl* i, m_chartItemControls)
            i->setPlotDomain(m_plotDomainList.at(m_plotDataIndex));

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

        m_chartItemControls << barGroup;
        childItems().append(barGroup);
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

        m_chartItemControls << stackedBarGroup;
        childItems().append(stackedBarGroup);
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

        m_chartItemControls << percentBarGroup;
        childItems().append(percentBarGroup);
        break;
        }
    case QChartSeries::SeriesTypeScatter: {
        QScatterSeries *scatterSeries = qobject_cast<QScatterSeries *>(series);
        scatterSeries->d->m_theme  = m_chartTheme->themeForSeries();
        scatterSeries->d->setParentItem(this);
        m_chartItemControls << scatterSeries->d;
        //TODO:? scatterSeries->d->m_themeIndex = m_chartSeries.count() - 1;
        break;
        }
    case QChartSeries::SeriesTypePie: {
        QPieSeries *pieSeries = qobject_cast<QPieSeries *>(series);
//        for (int i(0); i < pieSeries->sliceCount(); i++) {
//            if (!pieSeries->sliceColor(i).isValid())
//                pieSeries->setSliceColor(i, nextColor());
//        }
        pieSeries->d->setTheme(m_chartTheme);
        m_chartItemControls << pieSeries->d;

        // Set pre-defined colors in case the series has no colors defined
        // TODO: how to define the color for all the slices of a pie?
//        for (int (i); i < pieSeries.sliceCount(); i++)
        break;
        }
    }
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

void QChart::setSize(const QSize& size)
{
    m_rect = QRect(QPoint(0,0),size);
    QRect rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());

    //recaculate title
    if(m_titleItem){
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),m_rect.top()/2 + margin()/2);

    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(rect);
        if (m_bacgroundOrinetation == HorizonatlGradientOrientation)
            m_backgroundGradient.setFinalStop(m_backgroundItem->rect().width(), 0);
        else
            m_backgroundGradient.setFinalStop(0, m_backgroundItem->rect().height());
        m_backgroundItem->setBrush(m_backgroundGradient);
    }

    foreach (ChartItemControl *ctrl, m_chartItemControls) {
        ctrl->setPos(rect.topLeft());
        ctrl->resize(rect.size());
    }

    update();
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
    m_backgroundGradient.setStart(0,0);

    if(orientation == VerticalGradientOrientation){
        m_backgroundGradient.setFinalStop(0,m_rect.height());
    }else{
        m_backgroundGradient.setFinalStop(m_rect.width(),0);
    }

    m_backgroundItem->setBrush(m_backgroundGradient);
    m_backgroundItem->setPen(Qt::NoPen);
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
    if (theme != m_chartTheme->d->m_currentTheme) {
        m_chartTheme->d->setTheme(theme);
        setBackground(m_chartTheme->d->m_gradientStartColor,
                      m_chartTheme->d->m_gradientEndColor,
                      m_bacgroundOrinetation);
        foreach (ChartItemControl *ctrl, m_chartItemControls)
            ctrl->setTheme(m_chartTheme);
        update();
    }
}

void QChart::zoomInToRect(const QRect& rectangle)
{

    if(!rectangle.isValid()) return;

    qreal margin = this->margin();

    QRect rect = rectangle.normalized();
    rect.translate(-margin, -margin);

    PlotDomain& oldDomain = m_plotDomainList[m_plotDataIndex];

    PlotDomain domain = oldDomain.subDomain(rect,m_rect.width() - 2 * margin,m_rect.height() - 2 * margin);

    m_plotDomainList.resize(m_plotDataIndex + 1);
    m_plotDomainList<<domain;
    m_plotDataIndex++;

    foreach (ChartItemControl* ctrl, m_chartItemControls)
        ctrl->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
    update();
}

void QChart::zoomIn()
{
    if (m_plotDataIndex < m_plotDomainList.count() - 1) {
        m_plotDataIndex++;
        foreach (ChartItemControl* item, m_chartItemControls)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    } else {
        QRect rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());
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
        foreach (ChartItemControl* item, m_chartItemControls)
            item->setPlotDomain(m_plotDomainList[m_plotDataIndex]);
        update();
    }
}

void QChart::zoomReset()
{
    if (m_plotDataIndex > 0) {
        m_plotDataIndex = 0;
        foreach (ChartItemControl* item, m_chartItemControls)
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

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
