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
    m_chart(new QChart())
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

QChartSeries* QChartView::createSeries(QChartSeries::QChartSeriesType type)
{

    return m_chart->createSeries(type);
}

void QChartView::zoomInToRect(const QRect& rectangle)
{
    m_chart->zoomInToRect(rectangle);
}

void QChartView::zoomIn()
{
    m_chart->zoomIn();
}

void QChartView::zoomOut()
{
    m_chart->zoomOut();
}

int QChartView::margin() const
{
    return m_chart->margin();
}

void QChartView::setTitle(const QString& title)
{
    m_chart->setTitle(title);
}

void QChartView::setBackground(const QColor& startColor, const QColor& endColor, QChart::GradientOrientation orientation)
{
    m_chart->setBackground(startColor,endColor,orientation);
}

QTCOMMERCIALCHART_END_NAMESPACE
