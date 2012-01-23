#include "qchartview.h"
#include "qchart.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRubberBand>
#include <QResizeEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartView::QChartView(QWidget *parent) :
    QGraphicsView(parent),
    m_scene(new QGraphicsScene()),
    m_chart(new QChart()),
    m_rubberBand(0),
    m_showRubberBand(false)
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_scene);
    m_chart->setMargin(50);
    m_scene->addItem(m_chart);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

QChartView::~QChartView()
{
}

void QChartView::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0,0,size().width(),size().height());
    m_chart->setSize(size());
    QWidget::resizeEvent(event);
}


void QChartView::addSeries(QChartSeries* series)
{
    m_chart->addSeries(series);
}

QChartSeries* QChartView::createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type)
{

    return m_chart->createSeries(x, y, type);
}

void QChartView::mousePressEvent(QMouseEvent *event)
{
    int margin = m_chart->margin();

    QRect rect(margin,margin,width()-2*margin,height()-2*margin);

    m_origin = event->pos();

    if (!rect.contains(m_origin)) return;

    if (!m_rubberBand)
    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    m_rubberBand->setGeometry(QRect(m_origin, QSize()));
    m_showRubberBand=true;
    m_rubberBand->show();

}

 void QChartView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_showRubberBand)
    m_rubberBand->setGeometry(QRect(m_origin, event->pos()).normalized());
}

 void QChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_showRubberBand) {
        m_rubberBand->hide();
        m_showRubberBand=false;
    }
}

QTCOMMERCIALCHART_END_NAMESPACE
