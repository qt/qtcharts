#include "qchartwidget.h"
#include "qchartseries.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartWidget::QChartWidget(QWidget *parent) :
QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_scene);

    m_chart = new QChart();
    m_scene->addItem(m_chart);
    show();
}

QChartWidget::~QChartWidget()
{
}

void QChartWidget::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0,0,size().width(),size().height());
    m_chart->setSize(size());
    QWidget::resizeEvent(event);
}

QSize QChartWidget::sizeHint() const
{
    // TODO: calculate size hint based on contents?
    return QSize(100, 100);
}

void QChartWidget::addSeries(QChartSeries* series)
{
    m_chart->addSeries(series);
}

QChartSeries* QChartWidget::createSeries(QChartSeries::QChartSeriesType type)
{
    return m_chart->createSeries(type);
}

void QChartWidget::setTheme(QChart::ChartThemeId theme)
{
    m_chart->setTheme(theme);
}

#include "moc_qchartwidget.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
