#include "qchart.h"
#include "qchartseries.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qpieseries.h"
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
#include "qlinechartseries.h"

#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
m_backgroundItem(0),
m_titleItem(0),
m_dataset(new ChartDataSet(this)),
m_presenter(new ChartPresenter(this,m_dataset))
{
}

QChart::~QChart() {}

void QChart::addSeries(QChartSeries* series)
{
    m_dataset->addSeries(series);
}

//TODO on review, is it really needed ??
QChartSeries* QChart::createSeries(QChartSeries::QChartSeriesType type)
{
    // TODO: support also other types; not only scatter and pie

    QChartSeries *series(0);

    switch (type) {
        case QChartSeries::SeriesTypeLine: {
            series = QLineChartSeries::create();
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

    if(!m_backgroundItem) {
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setZValue(-1);
    }

    m_backgroundItem->setBrush(brush);
    m_backgroundItem->update();
}

void QChart::setChartBackgroundPen(const QPen& pen)
{

    if(!m_backgroundItem) {
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
    return m_presenter->margin();
}

void QChart::setMargin(int margin)
{
    m_presenter->setMargin(margin);
}

void QChart::setTheme(QChart::ChartThemeId theme)
{
    m_presenter->setTheme(theme);
}

QChart::ChartThemeId QChart::theme()
{
    return (QChart::ChartThemeId) m_presenter->theme();
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

}
void QChart::setAxisY(const QChartAxis& axis)
{

}

void QChart::setAxisY(const QList<QChartAxis>& axis)
{
    //TODO not implemented
}

void QChart::setAxis(AxisItem *item, const QChartAxis& axis)
{

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
