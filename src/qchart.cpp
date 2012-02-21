#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

/*!
    \class QChart
    \brief QtCommercial chart API.

    QChart is a QGraphicsWidget that you can show in a QGraphicsScene. It manages the graphical
    representation of different types of QChartSeries and other chart related objects like
    QChartAxis and QChartLegend. If you simply want to show a chart in a layout, you can use the
    convenience class QChartView instead of QChart.
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a chart object which is a child of parent.
*/
QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    m_backgroundItem(0),
    m_titleItem(0),
    m_dataset(new ChartDataSet(this)),
    m_presenter(new ChartPresenter(this,m_dataset))
{
}

/*!
    Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
*/
QChart::~QChart()
{
}

/*!
    Adds the series and optional y axis onto the chart and takes the ownership of the objects.
    If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
    the y axis).
*/
void QChart::addSeries(QChartSeries* series, QChartAxis* axisY)
{
    m_dataset->addSeries(series, axisY);
}

void QChart::removeSeries(QChartSeries* series)
{
    m_dataset->removeSeries(series);
}

void QChart::removeAllSeries()
{
    m_dataset->removeAllSeries();
}

void QChart::setChartBackgroundBrush(const QBrush& brush)
{
    createChartBackgroundItem();
    m_backgroundItem->setBrush(brush);
    m_backgroundItem->update();
}

void QChart::setChartBackgroundPen(const QPen& pen)
{
    createChartBackgroundItem();
    m_backgroundItem->setPen(pen);
    m_backgroundItem->update();
}

void QChart::setChartTitle(const QString& title)
{
    createChartTitleItem();
    m_titleItem->setPlainText(title);
}

void QChart::setChartTitleFont(const QFont& font)
{
    createChartTitleItem();
    m_titleItem->setFont(font);
}

void QChart::createChartBackgroundItem()
{
    if(!m_backgroundItem) {
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void QChart::createChartTitleItem()
{
    if(!m_titleItem) {
        m_titleItem = new QGraphicsTextItem(this);
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

int QChart::margin() const
{
    return m_presenter->margin();
}

void QChart::setMargin(int margin)
{
    m_presenter->setMargin(margin);
}

void QChart::setChartTheme(QChart::ChartTheme theme)
{
    m_presenter->setChartTheme(theme);
}

QChart::ChartTheme QChart::chartTheme() const
{
    return m_presenter->chartTheme();
}

void QChart::zoomIn()
{
    if (!m_dataset->nextDomain()) {
        QRectF rect = m_presenter->geometry();
        rect.setWidth(rect.width()/2);
        rect.setHeight(rect.height()/2);
        rect.moveCenter(m_presenter->geometry().center());
        zoomIn(rect);
    }
}

void QChart::zoomIn(const QRectF& rect)
{
    if(!rect.isValid()) return;
       QRectF r = rect.normalized();
       int margin = m_presenter->margin();
       r.translate(-margin, -margin);
       m_dataset->addDomain(r,m_presenter->geometry());
}

void QChart::zoomOut()
{
    m_dataset->previousDomain();
}

void QChart::zoomReset()
{
    m_dataset->clearDomains();
}

QChartAxis* QChart::axisX() const
{
    return m_dataset->axisX();
}

QChartAxis* QChart::axisY() const
{
    return m_dataset->axisY();
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
