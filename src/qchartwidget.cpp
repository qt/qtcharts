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

QChartSeries* QChartWidget::createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type)
{
    return m_chart->createSeries(x, y, type);
}
#include "moc_qchartwidget.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
