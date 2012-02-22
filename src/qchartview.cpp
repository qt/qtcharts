#include "qchartview.h"
#include "qchart.h"
#include "qchartaxis.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRubberBand>
#include <QResizeEvent>
#include <QDebug>

/*!
    \class QChartView
    \brief Chart widget

    QChartView is a standalone widget that can display charts. It does not require QGraphicsScene to work. It manages the graphical
    representation of different types of QChartSeries and other chart related objects like
    QChartAxis and QChartLegend. If you want to display a chart in your existing QGraphicsScene, you can use the QChart class instead.

    \sa QChart
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartView::QChartView(QWidget *parent) :
QGraphicsView(parent),
m_scene(new QGraphicsScene(this)),
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

/*!
    Adds the series and optional y axis onto the chart and takes the ownership of the objects.
    If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
    the y axis).
    \sa removeSeries, removeAllSeries
*/
void QChartView::addSeries(QChartSeries* series,QChartAxis *axisY)
{
    m_chart->addSeries(series,axisY);
}

/*!
    Removes the QChartSeries specified in a perameter from the QChartView.
    It releses its ownership of the specified QChartSeries object.
    It does not delete the pointed QChartSeries data object
    \sa removeSeries(), removeAllSeries()
*/
void QChartView::removeSeries(QChartSeries* series)
{
    m_chart->removeSeries(series);
}

/*!
    Removes all the QChartSeries that have been added to the QChartView
    It also deletes the pointed QChartSeries data objects
    \sa addSeries(), removeSeries()
*/
void QChartView::removeAllSeries()
{
    m_chart->removeAllSeries();
}

void QChartView::zoomIn()
{
    m_chart->zoomIn();
}

void QChartView::zoomIn(const QRect& rect)
{
    m_chart->zoomIn(rect);
}

void QChartView::zoomOut()
{
    m_chart->zoomOut();
}

/*!
    Returns the chart margin, which is the distance between the widget edge and the axis lines or the chart.
*/
int QChartView::margin() const
{
    return m_chart->margin();
}

/*!
    Sets the title description text that is rendered above the chart.
*/
void QChartView::setChartTitle(const QString& title)
{
    m_chart->setChartTitle(title);
}

/*!
    Sets the font that is used for rendering the description text that is rendered above the chart.
*/
void QChartView::setChartTitleFont(const QFont& font)
{
    m_chart->setChartTitleFont(font);
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
            m_chart->zoomIn(rect);
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

/*!
    Returns the pointer to the x axis object of the chart
*/
QChartAxis* QChartView::axisX() const
{
    return m_chart->axisX();
}

/*!
    Returns the pointer to the y axis object of the chart
*/
QChartAxis* QChartView::axisY() const
{
    return m_chart->axisY();
}

QTCOMMERCIALCHART_END_NAMESPACE
