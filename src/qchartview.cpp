#include "qchartview.h"
#include "qchart.h"
#include "qchartaxis.h"
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
m_verticalRubberBand(false),
m_horizonalRubberBand(false)
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
    m_chart->resize(size());
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

void QChartView::setChartBackgroundBrush(const QBrush& brush)
{
    m_chart->setChartBackgroundBrush(brush);
}
void QChartView::setChartBackgroundPen(const QPen& pen)
{
    m_chart->setChartBackgroundPen(pen);
}

void QChartView::setRubberBandPolicy(const RubberBandPolicy policy)
{
    switch(policy) {
        case VerticalRubberBand:
        m_verticalRubberBand = true;
        m_horizonalRubberBand = false;
        break;
        case HorizonalRubberBand:
        m_verticalRubberBand = false;
        m_horizonalRubberBand = true;
        break;
        case RectangleRubberBand:
        m_verticalRubberBand = true;
        m_horizonalRubberBand = true;
        break;
        case NoRubberBand:
        default:
        delete m_rubberBand;
        m_rubberBand=0;
        m_horizonalRubberBand = false;
        m_verticalRubberBand = false;
        return;
    }
    if(!m_rubberBand) {
        m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        m_rubberBand->setEnabled(true);
    }
}

QChartView::RubberBandPolicy QChartView::rubberBandPolicy() const
{
    if(m_horizonalRubberBand && m_verticalRubberBand) return RectangleRubberBand;
    if(m_horizonalRubberBand) return HorizonalRubberBand;
    if(m_verticalRubberBand) return VerticalRubberBand;
    return NoRubberBand;
}

void QChartView::mousePressEvent(QMouseEvent *event)
{
    if(m_rubberBand && m_rubberBand->isEnabled() && event->button() == Qt::LeftButton) {

        int margin = m_chart->margin();
        QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);

        if (rect.contains(event->pos())) {
            m_rubberBandOrigin = event->pos();
            m_rubberBand->setGeometry(QRect(m_rubberBandOrigin, QSize()));
            m_rubberBand->show();
            event->accept();
        }
    }
}

void QChartView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_rubberBand && m_rubberBand->isVisible()) {
        int margin = m_chart->margin();
        QRect rect(margin, margin, width() - 2 * margin, height() - 2 * margin);
        int width = event->pos().x() - m_rubberBandOrigin.x();
        int height = event->pos().y() - m_rubberBandOrigin.y();
        if(!m_verticalRubberBand) {
            m_rubberBandOrigin.setY(rect.top());
            height = rect.height();
        }
        if(!m_horizonalRubberBand) {
            m_rubberBandOrigin.setX(rect.left());
            width= rect.width();
        }
        m_rubberBand->setGeometry(QRect(m_rubberBandOrigin.x(),m_rubberBandOrigin.y(), width,height).normalized());
    }
    else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void QChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_rubberBand) {
        if (event->button() == Qt::LeftButton && m_rubberBand->isVisible()) {
            m_rubberBand->hide();
            QRect rect = m_rubberBand->geometry();
            m_chart->zoomInToRect(rect);
            event->accept();
        }

        if(event->button()==Qt::RightButton)
        m_chart->zoomReset();
    }
    else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void QChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Plus:
        zoomIn();
        break;
        case Qt::Key_Minus:
        zoomOut();
        break;
        default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void QChartView::setChartTheme(QChart::ChartTheme theme)
{
    m_chart->setChartTheme(theme);
}

QChart::ChartTheme QChartView::chartTheme() const
{
    return m_chart->chartTheme();
}

void QChartView::setDefaultAxisX(const QChartAxis& axis)
{
    m_chart->setDefaultAxisX(axis);
}

void QChartView::setDefaultAxisY(const QChartAxis& axis)
{
    m_chart->setDefaultAxisY(axis);
}

QChartAxis QChartView::defaultAxisX() const
{
    return m_chart->defaultAxisX();
}

QChartAxis QChartView::defaultAxisY() const
{
    return m_chart->defaultAxisY();
}

int QChartView::addAxisY(const QChartAxis& axis)
{
    return m_chart->addAxisY(axis);
}

QChartAxis QChartView::axisY(int id) const
{
    return m_chart->axisY(id);
}

void QChartView::removeAxisY(int id)
{
    m_chart->removeAxisY(id);
}
QTCOMMERCIALCHART_END_NAMESPACE
