#include "qchartview.h"
#include "qchart.h"
#include "qchartaxis.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRubberBand>
#include <QResizeEvent>
#include <QDebug>

/*!
    \enum QChartView::RubberBandPolicy

    This enum describes the different types of rubber bands that can be used for zoom rect selection

    \value NoRubberBand
    \value VerticalRubberBand
    \value HorizonalRubberBand
    \value RectangleRubberBand
*/

/*!
    \class QChartView
    \brief Standalone charting widget.

    QChartView is a standalone widget that can display charts. It does not require separate
    QGraphicsScene to work. It manages the graphical representation of different types of
    QChartSeries and other chart related objects like QChartAxis and QChartLegend. If you want to
    display a chart in your existing QGraphicsScene, you can use the QChart class instead.

    \sa QChart
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a chartView object which is a child of a\a parent.
*/
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


/*!
    Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
*/
QChartView::~QChartView()
{
}

/*!
    Resizes and updates the chart area using the \a event data
*/
void QChartView::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(0,0,size().width(),size().height());
    m_chart->resize(size());
    QWidget::resizeEvent(event);
}

/*!
    Adds the \a series and optional \a axisY onto the chart and takes the ownership of the objects.
    If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
    the y axis).
    \sa removeSeries(), removeAllSeries()
*/
void QChartView::addSeries(QSeries* series,QChartAxis *axisY)
{
    m_chart->addSeries(series,axisY);
}

/*!
    Removes the \a series specified in a perameter from the QChartView.
    It releses its ownership of the specified QChartSeries object.
    It does not delete the pointed QChartSeries data object
    \sa addSeries(), removeAllSeries()
*/
void QChartView::removeSeries(QSeries* series)
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

/*!
    Zooms in the view by a factor of 2
*/
void QChartView::zoomIn()
{
    m_chart->zoomIn();
}

/*!
    Zooms in the view to a maximum level at which \a rect is still fully visible.
*/
void QChartView::zoomIn(const QRect& rect)
{
    m_chart->zoomIn(rect);
}

/*!
    Restores the view zoom level to the previous one.
*/
void QChartView::zoomOut()
{
    m_chart->zoomOut();
}

/*!
    Returns the chart margin, which is the distance between the widget edge and the part of the chart where the actual data can be displayed.
*/
int QChartView::margin() const
{
    return m_chart->margin();
}

/*!
    Sets the chart \a title. A description text that is drawn above the chart.
*/
void QChartView::setChartTitle(const QString& title)
{
    m_chart->setChartTitle(title);
}

/*!
    Returns the chart's title. A description text that is drawn above the chart.
*/
QString QChartView::chartTitle() const
{
    return m_chart->chartTitle();
}

/*!
    Sets the \a font that is used for rendering the description text that is rendered above the chart.
*/
void QChartView::setChartTitleFont(const QFont& font)
{
    m_chart->setChartTitleFont(font);
}

/*!
    Sets the \a brush used for rendering the title text.
*/
void QChartView::setChartTitleBrush(const QBrush &brush)
{
    m_chart->setChartTitleBrush(brush);
}

/*!
    Returns the brush used for rendering the title text.
*/
QBrush QChartView::chartTitleBrush()
{
    return m_chart->chartTitleBrush();
}

/*!
    Sets the \a brush that is used for painting the background of the chart area of the QChartView widget.
*/
void QChartView::setChartBackgroundBrush(const QBrush& brush)
{
    m_chart->setChartBackgroundBrush(brush);
}

/*!
    Sets the \a pen that is used for painting the background of the chart area of the QChartView widget.
*/
void QChartView::setChartBackgroundPen(const QPen& pen)
{
    m_chart->setChartBackgroundPen(pen);
}

/*!
    Sets the RubberBandPlicy to \a policy. Selected policy determines the way zooming is performed.
*/
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

/*!
    Returns the RubberBandPolicy that is currently being used by the widget.
*/
QChartView::RubberBandPolicy QChartView::rubberBandPolicy() const
{
    if(m_horizonalRubberBand && m_verticalRubberBand) return RectangleRubberBand;
    if(m_horizonalRubberBand) return HorizonalRubberBand;
    if(m_verticalRubberBand) return VerticalRubberBand;
    return NoRubberBand;
}

/*!
    If Left mouse button is pressed and the RubberBandPolicy is enabled the \a event is accepted and the rubber band is displayed on the screen allowing the user to select the zoom area.
    If different mouse button is pressed and/or the RubberBandPolicy is disabled then the \a event is passed to QGraphicsView::mousePressEvent() implementation.
*/
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
    else {
        QGraphicsView::mousePressEvent(event);
    }
}

/*!
    If RubberBand rectange specification has been initiated in pressEvent then \a event data is used to update RubberBand geometry.
    In other case the defualt QGraphicsView::mouseMoveEvent implementation is called.
*/
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

/*!
    If left mouse button is release and RubberBand is enabled then \a event is accepted and the view is zoomed in to rect specified by RubberBand
    If it is the right mouse button \a event then RubberBand is dissmissed and zoom is canceled.
*/
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

/*!
    Pressing + and - keys performs zoomIn() and zoomOut() respectivly.
    In other \a event is passed to the QGraphicsView::keyPressEvent() implementation
*/
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

/*!
    Sets the \a theme used by the chart for rendering the graphical representation of the data
    \sa QChart::ChartTheme, chartTheme()
*/
void QChartView::setChartTheme(QChart::ChartTheme theme)
{
    m_chart->setChartTheme(theme);
}

/*!
    Returns the theme enum used by the chart.
    \sa setChartTheme()
*/
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

/*!
    Returns the pointer to legend object of the chart
*/
QLegend* QChartView::legend() const
{
    return m_chart->legend();
}


/*!
    Sets animation \a options for the chart
*/
void QChartView::setAnimationOptions(QChart::AnimationOptions options)
{
    m_chart->setAnimationOptions(options);
}

/*!
    Returns animation options for the chart
*/
QChart::AnimationOptions QChartView::animationOptions() const
{
    return m_chart->animationOptions();
}

void QChartView::scroll(int dx,int dy)
{
	m_chart->scroll(dx,dy);
}

QTCOMMERCIALCHART_END_NAMESPACE
