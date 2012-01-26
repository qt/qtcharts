#include "qchartwidget.h"
#include "qchartseries.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartWidget::QChartWidget(QWidget *parent) :
    QGraphicsView(parent),
    m_rubberBand(QRubberBand::Rectangle, this)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(m_scene);

    m_chart = new QChart();
    m_scene->addItem(m_chart);
    m_rubberBand.setEnabled(true); // TODO: should zoom be enabled by default?
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

void QChartWidget::mousePressEvent(QMouseEvent *event)
{
    if(m_rubberBand.isEnabled() && event->button() == Qt::LeftButton) {
        int margin = m_chart->margin();
        QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);
        m_origin = event->pos();

        if (rect.contains(m_origin)) {
            m_rubberBand.setGeometry(QRect(m_origin, QSize()));
            m_rubberBand.show();
            event->accept();
        }
    }
}

void QChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_rubberBand.isVisible())
        m_rubberBand.setGeometry(QRect(m_origin, event->pos()).normalized());
}

void QChartWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_rubberBand.isVisible()) {
        m_rubberBand.hide();
        QRect rect = m_rubberBand.geometry();
        m_chart->zoomInToRect(rect);
        event->accept();
    }

    if(event->button()==Qt::RightButton) {
        m_chart->zoomOut();
    }
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

void QChartWidget::setZoomEnabled(bool enabled)
{
    m_rubberBand.setEnabled(enabled);
}

#include "moc_qchartwidget.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
