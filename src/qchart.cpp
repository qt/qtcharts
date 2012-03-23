#include "qchart.h"
#include "qchartaxis.h"
#include "qlegend.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartbackground_p.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \enum QChart::ChartTheme

    This enum describes the theme used by the chart.

    \value ChartThemeDefault Follows the GUI style of the Operating System
    \value ChartThemeLight
    \value ChartThemeBlueCerulean
    \value ChartThemeDark
    \value ChartThemeBrownSand
    \value ChartThemeBlueNcs
    \value ChartThemeIcy
    \value ChartThemeScientific
    \value ChartThemeCount Not really a theme; the total count of themes.
*/

/*!
    \enum QChart::AnimationOption

    For enabling/disabling animations. Defaults to NoAnimation.

    \value NoAnimation
    \value GridAxisAnimations
    \value SeriesAnimations
    \value AllAnimations
*/

/*!
    \class QChart
    \brief QtCommercial chart API.

    QChart is a QGraphicsWidget that you can show in a QGraphicsScene. It manages the graphical
    representation of different types of QChartSeries and other chart related objects like
    QChartAxis and QChartLegend. If you simply want to show a chart in a layout, you can use the
    convenience class QChartView instead of QChart.
    \sa QChartView
*/

/*!
    Constructs a chart object which is a child of a\a parent. Parameter \a wFlags is passed to the QGraphicsWidget constructor.
*/
QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    m_backgroundItem(0),
    m_titleItem(0),
    m_legend(new QLegend(this)),
    m_dataset(new ChartDataSet(this)),
    m_presenter(new ChartPresenter(this,m_dataset)),
    m_padding(50),
    m_backgroundPadding(10)
{
    connect(m_dataset,SIGNAL(seriesAdded(QSeries*,Domain*)),m_legend,SLOT(handleSeriesAdded(QSeries*,Domain*)));
    connect(m_dataset,SIGNAL(seriesRemoved(QSeries*)),m_legend,SLOT(handleSeriesRemoved(QSeries*)));
}

/*!
    Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
*/
QChart::~QChart()
{
    //delete first presenter , since this is a root of all the graphical items
    delete m_presenter;
    m_presenter=0;
}

/*!
    Adds the \a series and optional \a axisY onto the chart and takes the ownership of the objects.
    If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
    the y axis).
*/
void QChart::addSeries(QSeries* series, QChartAxis* axisY)
{
    m_dataset->addSeries(series, axisY);
}

/*!
    Removes the \a series specified in a perameter from the QChartView.
    It releses its ownership of the specified QChartSeries object.
    It does not delete the pointed QChartSeries data object
    \sa addSeries(), removeAllSeries()
*/
void QChart::removeSeries(QSeries* series)
{
    m_dataset->removeSeries(series);
}

/*!
    Removes all the QChartSeries that have been added to the QChartView
    It also deletes the pointed QChartSeries data objects
    \sa addSeries(), removeSeries()
*/
void QChart::removeAllSeries()
{
    m_dataset->removeAllSeries();
}

/*!
    Sets the \a brush that is used for painting the background of the chart area.
*/
void QChart::setBackgroundBrush(const QBrush& brush)
{
    createChartBackgroundItem();
    m_backgroundItem->setBrush(brush);
    m_backgroundItem->update();
}

QBrush QChart::backgroundBrush() const
{
    if(!m_backgroundItem) return QBrush();
    return m_backgroundItem->brush();
}

/*!
    Sets the \a pen that is used for painting the background of the chart area.
*/
void QChart::setBackgroundPen(const QPen& pen)
{
    createChartBackgroundItem();
    m_backgroundItem->setPen(pen);
    m_backgroundItem->update();
}

QPen QChart::backgroundPen() const
{
    if(!m_backgroundItem) return QPen();
    return m_backgroundItem->pen();
}

/*!
    Sets the chart \a title. The description text that is drawn above the chart.
*/
void QChart::setTitle(const QString& title)
{
    createChartTitleItem();
    m_titleItem->setText(title);
    updateLayout();
}

/*!
    Returns the chart title. The description text that is drawn above the chart.
*/
QString QChart::title() const
{
    if(m_titleItem)
    return m_titleItem->text();
    else
    return QString();
}

/*!
    Sets the \a font that is used for rendering the description text that is rendered above the chart.
*/
void QChart::setTitleFont(const QFont& font)
{
    createChartTitleItem();
    m_titleItem->setFont(font);
    updateLayout();
}

/*!
    Sets the \a brush used for rendering the title text.
*/
void QChart::setTitleBrush(const QBrush &brush)
{
    createChartTitleItem();
    m_titleItem->setBrush(brush);
    updateLayout();
}

/*!
    Returns the brush used for rendering the title text.
*/
QBrush QChart::titleBrush() const
{
    if(!m_titleItem) return QBrush();
    return m_titleItem->brush();
}

void QChart::createChartBackgroundItem()
{
    if(!m_backgroundItem) {
        m_backgroundItem = new ChartBackground(this);
        m_backgroundItem->setPen(Qt::NoPen);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void QChart::createChartTitleItem()
{
    if(!m_titleItem) {
        m_titleItem = new QGraphicsSimpleTextItem(this);
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

/*!
    Sets the \a theme used by the chart for rendering the graphical representation of the data
    \sa ChartTheme, chartTheme()
*/
void QChart::setChartTheme(QChart::ChartTheme theme)
{
    m_presenter->setChartTheme(theme);
}

/*!
    Returns the theme enum used by the chart.
    \sa ChartTheme, setChartTheme()
*/
QChart::ChartTheme QChart::chartTheme() const
{
    return m_presenter->chartTheme();
}

/*!
    Zooms in the view by a factor of 2
*/
void QChart::zoomIn()
{
    m_presenter->zoomIn();
}

/*!
    Zooms in the view to a maximum level at which \a rect is still fully visible.
*/
void QChart::zoomIn(const QRectF& rect)
{

    if(!rect.isValid()) return;
    m_presenter->zoomIn(rect);
}

/*!
    Restores the view zoom level to the previous one.
*/
void QChart::zoomOut()
{
    m_presenter->zoomOut();
}

/*!
    Returns the pointer to the x axis object of the chart
*/
QChartAxis* QChart::axisX() const
{
    return m_dataset->axisX();
}

/*!
    Returns the pointer to the y axis object of the chart
*/
QChartAxis* QChart::axisY() const
{
    return m_dataset->axisY();
}

/*!
    Returns the legend object of the chart. Ownership stays in chart.
*/
QLegend* QChart::legend() const
{
    return m_legend;
}

/*!
    Resizes and updates the chart area using the \a event data
*/
void QChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{

    m_rect = QRectF(QPoint(0,0),event->newSize());
    updateLayout();
    QGraphicsWidget::resizeEvent(event);
    update();
}

/*!
    Sets animation \a options for the chart
*/
void QChart::setAnimationOptions(AnimationOptions options)
{
    m_presenter->setAnimationOptions(options);
}

/*!
    Returns animation options for the chart
*/
QChart::AnimationOptions QChart::animationOptions() const
{
    return m_presenter->animationOptions();
}

void QChart::scrollLeft()
{
    m_presenter->scroll(-m_presenter->geometry().width()/(axisX()->ticksCount()-1),0);
}

void QChart::scrollRight()
{
    m_presenter->scroll(m_presenter->geometry().width()/(axisX()->ticksCount()-1),0);
}
void QChart::scrollUp()
{
    m_presenter->scroll(0,m_presenter->geometry().width()/(axisY()->ticksCount()-1));
}
void QChart::scrollDown()
{
	 m_presenter->scroll(0,-m_presenter->geometry().width()/(axisY()->ticksCount()-1));
}

void QChart::updateLayout()
{
    if(!m_rect.isValid()) return;

    QRectF rect = m_rect.adjusted(m_padding,m_padding, -m_padding, -m_padding);

    // recalculate title position
    if (m_titleItem) {
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),m_rect.top()/2 + m_padding/2);
    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(m_rect.adjusted(m_backgroundPadding,m_backgroundPadding, -m_backgroundPadding, -m_backgroundPadding));
    }

    // recalculate legend position
    if (m_legend) {
        if (m_legend->parentObject() == this) {
            updateLegendLayout();
        }
    }
}

void QChart::updateLegendLayout()
{
    QRectF plotRect = m_rect.adjusted(m_padding,m_padding, -m_padding, -m_padding);
    QRectF legendRect;

    switch (m_legend->preferredLayout())
    {
    case QLegend::PreferredLayoutTop:{
        legendRect = m_rect.adjusted(m_padding,0,-m_padding,-m_padding - plotRect.height());
        break;
    }
    case QLegend::PreferredLayoutBottom: {
        legendRect = m_rect.adjusted(m_padding,m_padding + plotRect.height(),-m_padding,0);
        break;
    }
    case QLegend::PreferredLayoutLeft: {
        legendRect = m_rect.adjusted(0,m_padding,-m_padding - plotRect.width(),-m_padding);
        break;
    }
    case QLegend::PreferredLayoutRight: {
        legendRect = m_rect.adjusted(m_padding + plotRect.width(),m_padding,0,-m_padding);
        break;
    }
    default: {
        legendRect = plotRect;
        break;
    }
    }

    m_legend->setMaximumSize(legendRect.size());
    m_legend->setPos(legendRect.topLeft());
}


int QChart::padding() const
{
    return m_padding;
}

void QChart::setPadding(int padding)
{
    if(m_padding==padding){
    m_padding = padding;
    m_presenter->handleGeometryChanged();
    updateLayout();
    }
}

void QChart::setBackgroundPadding(int padding)
{
    if(m_backgroundPadding!=padding){
    m_backgroundPadding = padding;
    updateLayout();
    }
}

void QChart::setBackgroundDiameter(int diameter)
{
    createChartBackgroundItem();
    m_backgroundItem->setDimeter(diameter);
    m_backgroundItem->update();
}

void QChart::setBackgroundVisible(bool visible)
{
    createChartBackgroundItem();
    m_backgroundItem->setVisible(visible);
}

bool QChart::isBackgroundVisible() const
{
    if(!m_backgroundItem) return false;
    return m_backgroundItem->isVisible();
}


#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
