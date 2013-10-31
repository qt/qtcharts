/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "declarativechart.h"
#include <QPainter>
#include "declarativelineseries.h"
#include "declarativeareaseries.h"
#include "declarativebarseries.h"
#include "declarativepieseries.h"
#include "declarativesplineseries.h"
#include "declarativeboxplotseries.h"
#include "declarativescatterseries.h"
#include "qbarcategoryaxis.h"
#include "qvalueaxis.h"
#include "qlogvalueaxis.h"
#include "qcategoryaxis.h"
#include "qabstractseries_p.h"
#include "declarativemargins.h"
#include "chartdataset_p.h"
#include "declarativeaxes.h"
#include "qchart_p.h"
#include "qpolarchart.h"

#ifndef QT_ON_ARM
    #include "qdatetimeaxis.h"
#endif

#ifdef CHARTS_FOR_QUICK2
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QApplication>
#include <QTimer>
#include <QThread>
#endif

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#ifdef QDOC_QT5
/*!
    \qmltype ChartView
    \instantiates DeclarativeChart
    \inqmlmodule QtCommercial.Chart

    \include doc/src/chartview.qdocinc
*/
#else
/*!
    \qmlclass ChartView DeclarativeChart

    \include ../doc/src/chartview.qdocinc
*/
#endif

/*!
  \qmlproperty Theme ChartView::theme
  Theme defines the visual appearance of the chart, including for example colors, fonts, line
  widths and chart background.
*/

/*!
  \qmlproperty Animation ChartView::animationOptions
  Animation configuration of the chart. One of ChartView.NoAnimation, ChartView.GridAxisAnimations,
  ChartView.SeriesAnimations or ChartView.AllAnimations.
*/

/*!
  \qmlproperty Font ChartView::titleFont
  The title font of the chart.

  See the Qt documentation for more details of Font.
*/

/*!
  \qmlproperty string ChartView::title
  The title of the chart, shown on top of the chart.
  \sa ChartView::titleColor
*/

/*!
  \qmlproperty color ChartView::titleColor
  The color of the title text.
*/

/*!
  \qmlproperty Legend ChartView::legend
  The legend of the chart. Legend lists all the series, pie slices and bar sets added on the chart.
*/

/*!
  \qmlproperty int ChartView::count
  The count of series added to the chart.
*/

/*!
  \qmlproperty color ChartView::backgroundColor
  The color of the chart's background. By default background color is defined by chart theme.
  \sa ChartView::theme
*/

/*!
  \qmlproperty real ChartView::backgroundRoundness
  The diameter of the rounding cirle at the corners of the chart background.
*/

/*!
  \qmlproperty color ChartView::plotAreaColor
  The color of the background of the chart's plot area. By default plot area background uses chart's
  background color.
  \sa ChartView::backgroundColor
*/

/*!
  \qmlproperty bool ChartView::dropShadowEnabled
  The chart's border drop shadow. Set to true to enable drop shadow.
*/

/*!
  \qmlproperty real ChartView::topMargin
  Deprecated; use margins instead.
*/

/*!
  \qmlproperty real ChartView::bottomMargin
  Deprecated; use margins instead.
*/

/*!
  \qmlproperty real ChartView::leftMargin
  Deprecated; use margins instead.
*/

/*!
  \qmlproperty real ChartView::rightMargin
  Deprecated; use margins instead.
*/

/*!
  \qmlproperty Margins ChartView::minimumMargins
  Deprecated; use margins instead.
  The minimum margins allowed between the outer bounds and the plotArea of the ChartView. Margins
  area of ChartView is used for drawing title, axes and legend. Please note that setting the
  properties of minimumMargins may be bigger than the defined value, depending on other ChartView
  properties that affect it's layout. If you need to know the actual plotting area used at any
  given time, you can check ChartView::plotArea instead.
*/

/*!
  \qmlproperty rect ChartView::plotArea
  The area on the ChartView that is used for drawing series. This is the ChartView rect without the
  margins.
  \sa ChartView::minimumMargins
*/

/*!
  \qmlproperty Margins ChartView::margins
  The minimum margins allowed between the outer bounds and the plotArea of the ChartView. Margins
  area of ChartView is used for drawing title, axes and legend.
*/

/*!
  \qmlmethod AbstractSeries ChartView::series(int index)
  Returns the series with \a index on the chart. This allows you to loop through the series of a chart together with
  the count property of the chart.
*/

/*!
  \qmlmethod AbstractSeries ChartView::series(string name)
  Returns the first series on the chart with \a name. If there is no series with that name, returns null.
*/

/*!
  \qmlmethod AbstractSeries ChartView::createSeries(SeriesType type, string name, AbstractAxis axisX, AbstractAxis axisY)
  Creates a series object of \a type to the chart with name \a name, optional axis \a axisX and
  optional axis \a axisY. For example:
  \code
    // lineSeries is a LineSeries object that has already been added to the ChartView; re-use it's axes
    var myAxisX = chartView.axisX(lineSeries);
    var myAxisY = chartView.axisY(lineSeries);
    var scatter = chartView.createSeries(ChartView.SeriesTypeScatter, "scatter series", myAxisX, myAxisY);
  \endcode
*/

/*!
  \qmlmethod ChartView::removeSeries(AbstractSeries series)
  Removes the \a series from the chart. The series object is also destroyed.
*/

/*!
  \qmlmethod ChartView::removeAllSeries()
  Removes all series from the chart. All the series objects are also destroyed.
*/

/*!
  \qmlmethod Axis ChartView::axisX(AbstractSeries series)
  The x-axis of the series.
*/

/*!
  \qmlmethod Axis ChartView::axisY(AbstractSeries series)
  The y-axis of the series.
*/

/*!
  \qmlmethod ChartView::zoomY(real factor)
  Zooms in by \a factor on the center of the chart.
*/

/*!
  \qmlmethod ChartView::scrollLeft(real pixels)
  Scrolls to left by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollRight(real pixels)
  Scrolls to right by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollUp(real pixels)
  Scrolls up by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlmethod ChartView::scrollDown(real pixels)
  Scrolls down by \a pixels. This is a convenience function that suits for example for key navigation.
*/

/*!
  \qmlsignal ChartView::onPlotAreaChanged(rect plotArea)
  The plot area of the chart has changed. This may happen for example, if you modify minimumMargins
  or if you resize the chart, or if you modify font size related properties of the legend or chart
  title.
*/

/*!
  \qmlsignal ChartView::seriesAdded(AbstractSeries series)
  The \a series has been added to the chart.
*/

/*!
  \qmlsignal ChartView::seriesRemoved(AbstractSeries series)
  The \a series has been removed from the chart. Please note that \a series is no longer a valid
  object after the signal handler has completed.
*/

DeclarativeChart::DeclarativeChart(QDECLARATIVE_ITEM *parent)
    : QDECLARATIVE_PAINTED_ITEM(parent)
{
    initChart(QChart::ChartTypeCartesian);
}

DeclarativeChart::DeclarativeChart(QChart::ChartType type, QDECLARATIVE_ITEM *parent)
    : QDECLARATIVE_PAINTED_ITEM(parent)
{
    initChart(type);
}

void DeclarativeChart::initChart(QChart::ChartType type)
{
#ifdef CHARTS_FOR_QUICK2
    m_currentSceneImage = 0;
    m_guiThreadId = QThread::currentThreadId();
    m_paintThreadId = 0;
    m_updatePending = false;

    if (type == QChart::ChartTypePolar)
        m_chart = new QPolarChart();
    else
        m_chart = new QChart();

    m_scene = new QGraphicsScene(this);
    m_scene->addItem(m_chart);

    setAntialiasing(QQuickItem::antialiasing());
    connect(m_scene, SIGNAL(changed(QList<QRectF>)), this, SLOT(sceneChanged(QList<QRectF>)));
    connect(this, SIGNAL(antialiasingChanged(bool)), this, SLOT(handleAntialiasingChanged(bool)));

    setAcceptedMouseButtons(Qt::AllButtons);
    setAcceptHoverEvents(true);
#else
    if (type == QChart::ChartTypePolar)
        m_chart = new QPolarChart(this);
    else
        m_chart = new QChart(this);

    setFlag(QGraphicsItem::ItemHasNoContents, false);
#endif

    m_margins = new DeclarativeMargins(this);
    m_margins->setTop(m_chart->margins().top());
    m_margins->setLeft(m_chart->margins().left());
    m_margins->setRight(m_chart->margins().right());
    m_margins->setBottom(m_chart->margins().bottom());
    connect(m_margins, SIGNAL(topChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(bottomChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(leftChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_margins, SIGNAL(rightChanged(int,int,int,int)), this, SLOT(changeMinimumMargins(int,int,int,int)));
    connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesAdded(QAbstractSeries*)), this, SLOT(handleSeriesAdded(QAbstractSeries*)));
    connect(m_chart->d_ptr->m_dataset, SIGNAL(seriesRemoved(QAbstractSeries*)), this, SIGNAL(seriesRemoved(QAbstractSeries*)));
}

void DeclarativeChart::handleSeriesAdded(QAbstractSeries *series)
{
    emit seriesAdded(series);
}

void DeclarativeChart::changeMinimumMargins(int top, int bottom, int left, int right)
{
    m_chart->setMargins(QMargins(left, top, right, bottom));
    emit minimumMarginsChanged();
    emit plotAreaChanged(m_chart->plotArea());
}

DeclarativeChart::~DeclarativeChart()
{
    delete m_chart;
#ifdef CHARTS_FOR_QUICK2
    m_sceneImageLock.lock();
    delete m_currentSceneImage;
    m_currentSceneImage = 0;
    m_sceneImageLock.unlock();
#endif
}

void DeclarativeChart::childEvent(QChildEvent *event)
{
    if (event->type() == QEvent::ChildAdded) {
        if (qobject_cast<QAbstractSeries *>(event->child())) {
            m_chart->addSeries(qobject_cast<QAbstractSeries *>(event->child()));
        }
    }
}

void DeclarativeChart::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<QAbstractSeries *>(child)) {
            // Add series to the chart
            QAbstractSeries *series = qobject_cast<QAbstractSeries *>(child);
            m_chart->addSeries(series);

            // Connect to axis changed signals (unless this is a pie series)
            if (!qobject_cast<DeclarativePieSeries *>(series)) {
                connect(series, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SLOT(handleAxisXTopSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
                connect(series, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SLOT(handleAxisYRightSet(QAbstractAxis*)));
            }

            initializeAxes(series);
        }
    }

    QDECLARATIVE_ITEM::componentComplete();
}

void DeclarativeChart::handleAxisXSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Horizontal).contains(axis))
            m_chart->setAxisX(axis, s);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisX to null.";
    }
}

void DeclarativeChart::handleAxisXTopSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Horizontal).contains(axis)) {
            QList<QAbstractAxis *> oldAxes = m_chart->axes(Qt::Horizontal, s);
            foreach (QAbstractAxis* a, oldAxes) {
                    m_chart->removeAxis(a);
                    delete a;
            }
            m_chart->addAxis(axis, Qt::AlignTop);
        }
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisXTop to null.";
    }
}

void DeclarativeChart::handleAxisYSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Vertical).contains(axis))
            m_chart->setAxisY(axis, s);
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisY to null.";
    }
}

void DeclarativeChart::handleAxisYRightSet(QAbstractAxis *axis)
{
    QAbstractSeries *s = qobject_cast<QAbstractSeries *>(sender());
    if (axis && s) {
        if (!m_chart->axes(Qt::Vertical).contains(axis)) {
            QList<QAbstractAxis *> oldAxes = m_chart->axes((Qt::Vertical), s);
            foreach (QAbstractAxis* a, oldAxes) {
                m_chart->removeAxis(a);
                delete a;
            }
            m_chart->addAxis(axis, Qt::AlignRight);
        }
        if (!s->attachedAxes().contains(axis))
            s->attachAxis(axis);
    } else {
        qWarning() << "Trying to set axisYRight to null.";
    }
}

void DeclarativeChart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (newGeometry.isValid()) {
        if (newGeometry.width() > 0 && newGeometry.height() > 0) {
            m_chart->resize(newGeometry.width(), newGeometry.height());
        }
    }
    QDECLARATIVE_ITEM::geometryChanged(newGeometry, oldGeometry);

    // It would be better to trigger the plotAreaChanged signal from QChart::plotAreaChanged or
    // similar. Since that kind of a signal is not clearly needed in the C++ API the work-around is
    // to implement it here for the QML API purposes.
    emit plotAreaChanged(m_chart->plotArea());
}

#ifdef CHARTS_FOR_QUICK2
void DeclarativeChart::sceneChanged(QList<QRectF> region)
{
    Q_UNUSED(region);

    if (m_guiThreadId == m_paintThreadId) {
        // Rendering in gui thread, no need for shenannigans, just update
        update();
    } else {
        // Multi-threaded rendering, need to ensure scene is actually rendered in gui thread
        if (!m_updatePending) {
            m_updatePending = true;
            // Do async render to avoid some unnecessary renders.
            QTimer::singleShot(0, this, SLOT(renderScene()));
        }
    }
}

void DeclarativeChart::renderScene()
{
    m_updatePending = false;
    m_sceneImageLock.lock();
    delete m_currentSceneImage;
    m_currentSceneImage = new QImage(m_chart->size().toSize(), QImage::Format_ARGB32);
    m_currentSceneImage->fill(Qt::transparent);
    QPainter painter(m_currentSceneImage);
    if (antialiasing())
        painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    QRect renderRect(QPoint(0, 0), m_chart->size().toSize());
    m_scene->render(&painter, renderRect, renderRect);
    m_sceneImageLock.unlock();

    update();
}

void DeclarativeChart::paint(QPainter *painter)
{
    if (!m_paintThreadId) {
        m_paintThreadId = QThread::currentThreadId();
        if (m_guiThreadId == m_paintThreadId) {
            // No need for scene image in single threaded rendering, so delete
            // the one that got made by default before the rendering type was
            // detected.
            delete m_currentSceneImage;
            m_currentSceneImage = 0;
        }
    }

    if (m_guiThreadId == m_paintThreadId) {
        QRectF renderRect(QPointF(0, 0), m_chart->size());
        m_scene->render(painter, renderRect, renderRect);
    } else {
        m_sceneImageLock.lock();
        if (m_currentSceneImage) {
            QRect imageRect(QPoint(0, 0), m_currentSceneImage->size());
            QRect itemRect(QPoint(0, 0), QSize(width(), height()));
            painter->drawImage(itemRect, *m_currentSceneImage, imageRect);
        }
        m_sceneImageLock.unlock();
    }
}

void DeclarativeChart::mousePressEvent(QMouseEvent *event)
{
    m_mousePressScenePoint = event->pos();
    m_mousePressScreenPoint = event->globalPos();
    m_lastMouseMoveScenePoint = m_mousePressScenePoint;
    m_lastMouseMoveScreenPoint = m_mousePressScreenPoint;
    m_mousePressButton = event->button();
    m_mousePressButtons = event->buttons();

    QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMousePress);
    mouseEvent.setWidget(0);
    mouseEvent.setButtonDownScenePos(m_mousePressButton, m_mousePressScenePoint);
    mouseEvent.setButtonDownScreenPos(m_mousePressButton, m_mousePressScreenPoint);
    mouseEvent.setScenePos(m_mousePressScenePoint);
    mouseEvent.setScreenPos(m_mousePressScreenPoint);
    mouseEvent.setLastScenePos(m_lastMouseMoveScenePoint);
    mouseEvent.setLastScreenPos(m_lastMouseMoveScreenPoint);
    mouseEvent.setButtons(m_mousePressButtons);
    mouseEvent.setButton(m_mousePressButton);
    mouseEvent.setModifiers(event->modifiers());
    mouseEvent.setAccepted(false);

    QApplication::sendEvent(m_scene, &mouseEvent);
}

void DeclarativeChart::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseRelease);
    mouseEvent.setWidget(0);
    mouseEvent.setButtonDownScenePos(m_mousePressButton, m_mousePressScenePoint);
    mouseEvent.setButtonDownScreenPos(m_mousePressButton, m_mousePressScreenPoint);
    mouseEvent.setScenePos(event->pos());
    mouseEvent.setScreenPos(event->globalPos());
    mouseEvent.setLastScenePos(m_lastMouseMoveScenePoint);
    mouseEvent.setLastScreenPos(m_lastMouseMoveScreenPoint);
    mouseEvent.setButtons(event->buttons());
    mouseEvent.setButton(event->button());
    mouseEvent.setModifiers(event->modifiers());
    mouseEvent.setAccepted(false);

    QApplication::sendEvent(m_scene, &mouseEvent);

    m_mousePressButtons = event->buttons();
    m_mousePressButton = Qt::NoButton;
}

void DeclarativeChart::hoverMoveEvent(QHoverEvent *event)
{
    // Convert hover move to mouse move, since we don't seem to get actual mouse move events.
    // QGraphicsScene generates hover events from mouse move events, so we don't need
    // to pass hover events there.
    QGraphicsSceneMouseEvent mouseEvent(QEvent::GraphicsSceneMouseMove);
    mouseEvent.setWidget(0);
    mouseEvent.setButtonDownScenePos(m_mousePressButton, m_mousePressScenePoint);
    mouseEvent.setButtonDownScreenPos(m_mousePressButton, m_mousePressScreenPoint);
    mouseEvent.setScenePos(event->pos());
    // Hover events do not have global pos in them, and the screen position doesn't seem to
    // matter anyway in this use case, so just pass event pos instead of trying to
    // calculate the real screen position.
    mouseEvent.setScreenPos(event->pos());
    mouseEvent.setLastScenePos(m_lastMouseMoveScenePoint);
    mouseEvent.setLastScreenPos(m_lastMouseMoveScreenPoint);
    mouseEvent.setButtons(m_mousePressButtons);
    mouseEvent.setButton(m_mousePressButton);
    mouseEvent.setModifiers(event->modifiers());
    m_lastMouseMoveScenePoint = mouseEvent.scenePos();
    m_lastMouseMoveScreenPoint = mouseEvent.screenPos();
    mouseEvent.setAccepted(false);

    QApplication::sendEvent(m_scene, &mouseEvent);
}

void DeclarativeChart::handleAntialiasingChanged(bool enable)
{
    setAntialiasing(enable);
}
#endif

void DeclarativeChart::setTheme(DeclarativeChart::Theme theme)
{
    QChart::ChartTheme chartTheme = (QChart::ChartTheme) theme;
    if (chartTheme != m_chart->theme())
        m_chart->setTheme(chartTheme);
}

DeclarativeChart::Theme DeclarativeChart::theme()
{
    return (DeclarativeChart::Theme) m_chart->theme();
}

void DeclarativeChart::setAnimationOptions(DeclarativeChart::Animation animations)
{
    QChart::AnimationOption animationOptions = (QChart::AnimationOption) animations;
    if (animationOptions != m_chart->animationOptions())
        m_chart->setAnimationOptions(animationOptions);
}

DeclarativeChart::Animation DeclarativeChart::animationOptions()
{
    if (m_chart->animationOptions().testFlag(QChart::AllAnimations))
        return DeclarativeChart::AllAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::GridAxisAnimations))
        return DeclarativeChart::GridAxisAnimations;
    else if (m_chart->animationOptions().testFlag(QChart::SeriesAnimations))
        return DeclarativeChart::SeriesAnimations;
    else
        return DeclarativeChart::NoAnimation;
}

void DeclarativeChart::setTitle(QString title)
{
    if (title != m_chart->title())
        m_chart->setTitle(title);
}
QString DeclarativeChart::title()
{
    return m_chart->title();
}

QAbstractAxis *DeclarativeChart::axisX(QAbstractSeries *series)
{
    QList<QAbstractAxis *> axes = m_chart->axes(Qt::Horizontal, series);
    if (axes.count())
        return axes[0];
    return 0;
}

QAbstractAxis *DeclarativeChart::axisY(QAbstractSeries *series)
{
    QList<QAbstractAxis *> axes = m_chart->axes(Qt::Vertical, series);
    if (axes.count())
        return axes[0];
    return 0;
}

QLegend *DeclarativeChart::legend()
{
    return m_chart->legend();
}

void DeclarativeChart::setTitleColor(QColor color)
{
    QBrush b = m_chart->titleBrush();
    if (color != b.color()) {
        b.setColor(color);
        m_chart->setTitleBrush(b);
        emit titleColorChanged(color);
    }
}

QFont DeclarativeChart::titleFont() const
{
    return m_chart->titleFont();
}

void DeclarativeChart::setTitleFont(const QFont &font)
{
    m_chart->setTitleFont(font);
}

QColor DeclarativeChart::titleColor()
{
    return m_chart->titleBrush().color();
}

void DeclarativeChart::setBackgroundColor(QColor color)
{
    QBrush b = m_chart->backgroundBrush();
    if (b.style() != Qt::SolidPattern || color != b.color()) {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        m_chart->setBackgroundBrush(b);
        emit backgroundColorChanged();
    }
}

QColor DeclarativeChart::backgroundColor()
{
    return m_chart->backgroundBrush().color();
}

void QtCommercialChart::DeclarativeChart::setPlotAreaColor(QColor color)
{
    QBrush b = m_chart->plotAreaBackgroundBrush();
    if (b.style() != Qt::SolidPattern || color != b.color()) {
        b.setStyle(Qt::SolidPattern);
        b.setColor(color);
        m_chart->setPlotAreaBackgroundBrush(b);
        m_chart->setPlotAreaBackgroundVisible(true);
        emit plotAreaColorChanged();
    }
}

QColor QtCommercialChart::DeclarativeChart::plotAreaColor()
{
    return m_chart->plotAreaBackgroundBrush().color();
}

int DeclarativeChart::count()
{
    return m_chart->series().count();
}

void DeclarativeChart::setDropShadowEnabled(bool enabled)
{
    if (enabled != m_chart->isDropShadowEnabled()) {
        m_chart->setDropShadowEnabled(enabled);
        dropShadowEnabledChanged(enabled);
    }
}

bool DeclarativeChart::dropShadowEnabled()
{
    return m_chart->isDropShadowEnabled();
}

qreal DeclarativeChart::backgroundRoundness() const
{
    return m_chart->backgroundRoundness();
}

void DeclarativeChart::setBackgroundRoundness(qreal diameter)
{
    if (m_chart->backgroundRoundness() != diameter) {
        m_chart->setBackgroundRoundness(diameter);
        emit backgroundRoundnessChanged(diameter);
    }
}

qreal DeclarativeChart::topMargin()
{
    qWarning() << "ChartView.topMargin is deprecated. Use margins instead.";
    return m_chart->margins().top();
}

qreal DeclarativeChart::bottomMargin()
{
    qWarning() << "ChartView.bottomMargin is deprecated. Use margins instead.";
    return m_chart->margins().bottom();
}

qreal DeclarativeChart::leftMargin()
{
    qWarning() << "ChartView.leftMargin is deprecated. Use margins instead.";
    return m_chart->margins().left();
}

qreal DeclarativeChart::rightMargin()
{
    qWarning() << "ChartView.rightMargin is deprecated. Use margins instead.";
    return m_chart->margins().right();
}

void DeclarativeChart::zoom(qreal factor)
{
    m_chart->zoom(factor);
}

void DeclarativeChart::scrollLeft(qreal pixels)
{
    m_chart->scroll(-pixels, 0);
}

void DeclarativeChart::scrollRight(qreal pixels)
{
    m_chart->scroll(pixels, 0);
}

void DeclarativeChart::scrollUp(qreal pixels)
{
    m_chart->scroll(0, pixels);
}

void DeclarativeChart::scrollDown(qreal pixels)
{
    m_chart->scroll(0, -pixels);
}

QDECLARATIVE_LIST_PROPERTY<QAbstractAxis> DeclarativeChart::axes()
{
    return QDECLARATIVE_LIST_PROPERTY<QAbstractAxis>(this, 0,
                &DeclarativeChart::axesAppendFunc,
                &DeclarativeChart::axesCountFunc,
#ifdef CHARTS_FOR_QUICK2
                &DeclarativeChart::axesAtFunc,
                &DeclarativeChart::axesClearFunc);
#else
                &DeclarativeChart::axesAtFunc);
#endif
}

void DeclarativeChart::axesAppendFunc(QDECLARATIVE_LIST_PROPERTY<QAbstractAxis> *list, QAbstractAxis *element)
{
    // Empty implementation
    Q_UNUSED(list);
    Q_UNUSED(element);
}

int DeclarativeChart::axesCountFunc(QDECLARATIVE_LIST_PROPERTY<QAbstractAxis> *list)
{
    if (qobject_cast<DeclarativeChart *>(list->object)) {
        DeclarativeChart *chart = qobject_cast<DeclarativeChart *>(list->object);
        return chart->m_chart->axes(Qt::Horizontal | Qt::Vertical).count();
    }
    return 0;
}

QAbstractAxis *DeclarativeChart::axesAtFunc(QDECLARATIVE_LIST_PROPERTY<QAbstractAxis> *list, int index)
{
    if (qobject_cast<DeclarativeChart *>(list->object)) {
        DeclarativeChart *chart = qobject_cast<DeclarativeChart *>(list->object);
        QList<QAbstractAxis *> axes = chart->m_chart->axes(Qt::Horizontal | Qt::Vertical, chart->m_chart->series()[0]);
        return axes.at(index);
    }
    return 0;
}

void DeclarativeChart::axesClearFunc(QDECLARATIVE_LIST_PROPERTY<QAbstractAxis> *list)
{
    // Empty implementation
    Q_UNUSED(list);
}


QAbstractSeries *DeclarativeChart::series(int index)
{
    if (index < m_chart->series().count()) {
        return m_chart->series().at(index);
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::series(QString seriesName)
{
    foreach (QAbstractSeries *series, m_chart->series()) {
        if (series->name() == seriesName)
            return series;
    }
    return 0;
}

QAbstractSeries *DeclarativeChart::createSeries(int type, QString name, QAbstractAxis *axisX, QAbstractAxis *axisY)
{
    QAbstractSeries *series = 0;

    switch (type) {
    case DeclarativeChart::SeriesTypeLine:
        series = new DeclarativeLineSeries();
        break;
    case DeclarativeChart::SeriesTypeArea: {
        DeclarativeAreaSeries *area = new DeclarativeAreaSeries();
        area->setUpperSeries(new DeclarativeLineSeries());
        series = area;
        break;
    }
    case DeclarativeChart::SeriesTypeStackedBar:
        series = new DeclarativeStackedBarSeries();
        break;
    case DeclarativeChart::SeriesTypePercentBar:
        series = new DeclarativePercentBarSeries();
        break;
    case DeclarativeChart::SeriesTypeBar:
        series = new DeclarativeBarSeries();
        break;
    case DeclarativeChart::SeriesTypeHorizontalBar:
        series = new DeclarativeHorizontalBarSeries();
        break;
    case DeclarativeChart::SeriesTypeHorizontalPercentBar:
        series = new DeclarativeHorizontalPercentBarSeries();
        break;
    case DeclarativeChart::SeriesTypeHorizontalStackedBar:
        series = new DeclarativeHorizontalStackedBarSeries();
        break;
    case DeclarativeChart::SeriesTypeBoxPlot:
        series = new DeclarativeBoxPlotSeries();
        break;
    case DeclarativeChart::SeriesTypePie:
        series = new DeclarativePieSeries();
        break;
    case DeclarativeChart::SeriesTypeScatter:
        series = new DeclarativeScatterSeries();
        break;
    case DeclarativeChart::SeriesTypeSpline:
        series = new DeclarativeSplineSeries();
        break;
    default:
        qWarning() << "Illegal series type";
    }

    if (series) {
        // Connect to axis changed signals (unless this is a pie series)
        if (!qobject_cast<DeclarativePieSeries *>(series)) {
            connect(series, SIGNAL(axisXChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisXTopChanged(QAbstractAxis*)), this, SLOT(handleAxisXSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisYChanged(QAbstractAxis*)), this, SLOT(handleAxisYSet(QAbstractAxis*)));
            connect(series, SIGNAL(axisYRightChanged(QAbstractAxis*)), this, SLOT(handleAxisYRightSet(QAbstractAxis*)));
        }

        series->setName(name);
        m_chart->addSeries(series);

        if (axisX)
            setAxisX(axisX, series);
        if (axisY)
            setAxisY(axisY, series);

        if (series->attachedAxes().count() < 2)
            initializeAxes(series);
    }

    return series;
}

void DeclarativeChart::removeSeries(QAbstractSeries *series)
{
    if (series)
        m_chart->removeSeries(series);
    else
        qWarning("removeSeries: cannot remove null");
}

void DeclarativeChart::setAxisX(QAbstractAxis *axis, QAbstractSeries *series)
{
    if (axis)
        m_chart->setAxisX(axis, series);
}

void DeclarativeChart::setAxisY(QAbstractAxis *axis, QAbstractSeries *series)
{
    if (axis)
        m_chart->setAxisY(axis, series);
}

void DeclarativeChart::createDefaultAxes()
{
    qWarning() << "ChartView.createDefaultAxes() is deprecated. Axes are created automatically.";
}

QAbstractAxis *DeclarativeChart::defaultAxis(Qt::Orientation orientation, QAbstractSeries *series)
{
    if (!series) {
        qWarning() << "No axis type defined for null series";
        return 0;
    }

    foreach (QAbstractAxis *existingAxis, m_chart->axes(orientation)) {
        if (existingAxis->type() == series->d_ptr->defaultAxisType(orientation))
            return existingAxis;
    }

    switch (series->d_ptr->defaultAxisType(orientation)) {
    case QAbstractAxis::AxisTypeValue:
        return new QValueAxis(this);
    case QAbstractAxis::AxisTypeBarCategory:
        return new QBarCategoryAxis(this);
    case QAbstractAxis::AxisTypeCategory:
        return new QCategoryAxis(this);
#ifndef QT_ON_ARM
    case QAbstractAxis::AxisTypeDateTime:
        return new QDateTimeAxis(this);
#endif
    case QAbstractAxis::AxisTypeLogValue:
        return new QLogValueAxis(this);
    default:
        // assume AxisTypeNoAxis
        return 0;
    }
}

void DeclarativeChart::initializeAxes(QAbstractSeries *series)
{
    if (qobject_cast<DeclarativeLineSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeLineSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeScatterSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeScatterSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeSplineSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeSplineSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeAreaSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeAreaSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeStackedBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeStackedBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativePercentBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativePercentBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalStackedBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalStackedBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeHorizontalPercentBarSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeHorizontalPercentBarSeries *>(series)->m_axes);
    else if (qobject_cast<DeclarativeBoxPlotSeries *>(series))
        doInitializeAxes(series, qobject_cast<DeclarativeBoxPlotSeries *>(series)->m_axes);
    // else: do nothing
}

void DeclarativeChart::doInitializeAxes(QAbstractSeries *series, DeclarativeAxes *axes)
{
    // Initialize axis X
    if (axes->axisX())
        axes->emitAxisXChanged();
    else if (axes->axisXTop())
        axes->emitAxisXTopChanged();
    else
        axes->setAxisX(defaultAxis(Qt::Horizontal, series));

    // Initialize axis Y
    if (axes->axisY())
        axes->emitAxisYChanged();
    else if (axes->axisYRight())
        axes->emitAxisYRightChanged();
    else
        axes->setAxisY(defaultAxis(Qt::Vertical, series));
}

#include "moc_declarativechart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
