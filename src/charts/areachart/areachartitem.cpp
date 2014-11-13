/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/areachartitem_p.h>
#include <QtCharts/QAreaSeries>
#include <private/qareaseries_p.h>
#include <QtCharts/QLineSeries>
#include <private/chartpresenter_p.h>
#include <private/abstractdomain_p.h>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtCore/QDebug>


QT_CHARTS_BEGIN_NAMESPACE

AreaChartItem::AreaChartItem(QAreaSeries *areaSeries, QGraphicsItem* item)
    : ChartItem(areaSeries->d_func(),item),
      m_series(areaSeries),
      m_upper(0),
      m_lower(0),
      m_pointsVisible(false),
      m_pointLabelsVisible(false),
      m_pointLabelsFormat(areaSeries->pointLabelsFormat()),
      m_pointLabelsFont(areaSeries->pointLabelsFont()),
      m_pointLabelsColor(areaSeries->pointLabelsColor()),
      m_mousePressed(false)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setZValue(ChartPresenter::LineChartZValue);
    if (m_series->upperSeries())
        m_upper = new AreaBoundItem(this, m_series->upperSeries());
    if (m_series->lowerSeries())
        m_lower = new AreaBoundItem(this, m_series->lowerSeries());

    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));
    QObject::connect(this, SIGNAL(clicked(QPointF)), areaSeries, SIGNAL(clicked(QPointF)));
    QObject::connect(this, SIGNAL(hovered(QPointF,bool)), areaSeries, SIGNAL(hovered(QPointF,bool)));
    QObject::connect(this, SIGNAL(pressed(QPointF)), areaSeries, SIGNAL(pressed(QPointF)));
    QObject::connect(this, SIGNAL(released(QPointF)), areaSeries, SIGNAL(released(QPointF)));
    QObject::connect(this, SIGNAL(doubleClicked(QPointF)),
                     areaSeries, SIGNAL(doubleClicked(QPointF)));
    QObject::connect(areaSeries, SIGNAL(pointLabelsFormatChanged(QString)),
                     this, SLOT(handleUpdated()));
    QObject::connect(areaSeries, SIGNAL(pointLabelsVisibilityChanged(bool)),
                     this, SLOT(handleUpdated()));
    QObject::connect(areaSeries, SIGNAL(pointLabelsFontChanged(QFont)),
                     this, SLOT(handleUpdated()));
    QObject::connect(areaSeries, SIGNAL(pointLabelsColorChanged(QColor)),
                     this, SLOT(handleUpdated()));

    handleUpdated();
}

AreaChartItem::~AreaChartItem()
{
    delete m_upper;
    delete m_lower;
}

void AreaChartItem::setPresenter(ChartPresenter *presenter)
{
    if (m_upper)
        m_upper->setPresenter(presenter);
    if (m_lower) {
        m_lower->setPresenter(presenter);
    }
	ChartItem::setPresenter(presenter);
}

QRectF AreaChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath AreaChartItem::shape() const
{
    return m_path;
}

void AreaChartItem::updatePath()
{
    QPainterPath path;
    QRectF rect(QPointF(0,0),domain()->size());

    path = m_upper->path();

    if (m_lower) {
        // Note: Polarcharts always draw area correctly only when both series have equal width or are
        // fully displayed. If one series is partally off-chart, the connecting line between
        // the series does not attach to the end of the partially hidden series but to the point
        // where it intersects the axis line. The problem is especially noticeable when one of the series
        // is entirely off-chart, in which case the connecting line connects two ends of the
        // visible series.
        // This happens because we get the paths from linechart, which omits off-chart segments.
        // To properly fix, linechart would need to provide true full path, in right, left, and the rest
        // portions to enable proper clipping. However, combining those to single visually unified area
        // would be a nightmare, since they would have to be painted separately.
        path.connectPath(m_lower->path().toReversed());
    } else {
        QPointF first = path.pointAtPercent(0);
        QPointF last =  path.pointAtPercent(1);
        if (presenter()->chartType() == QChart::ChartTypeCartesian) {
            path.lineTo(last.x(), rect.bottom());
            path.lineTo(first.x(), rect.bottom());
        } else { // polar
            path.lineTo(rect.center());
        }
    }
    path.closeSubpath();

    // Only zoom in if the bounding rect of the path fits inside int limits. QWidget::update() uses
    // a region that has to be compatible with QRect.
    if (path.boundingRect().height() <= INT_MAX
            && path.boundingRect().width() <= INT_MAX) {
        prepareGeometryChange();
        m_path = path;
        m_rect = path.boundingRect();
        update();
    }
}

void AreaChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_brush = m_series->brush();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2 * m_pointPen.width());
    setOpacity(m_series->opacity());
    m_pointLabelsFormat = m_series->pointLabelsFormat();
    m_pointLabelsVisible = m_series->pointLabelsVisible();
    m_pointLabelsFont = m_series->pointLabelsFont();
    m_pointLabelsColor = m_series->pointLabelsColor();
    update();
}

void AreaChartItem::handleDomainUpdated()
{
    if (m_upper) {
        AbstractDomain* d = m_upper->domain();
        d->setSize(domain()->size());
        d->setRange(domain()->minX(),domain()->maxX(),domain()->minY(),domain()->maxY());
        m_upper->handleDomainUpdated();
    }

    if (m_lower) {
        AbstractDomain* d = m_lower->domain();
        d->setSize(domain()->size());
        d->setRange(domain()->minX(),domain()->maxX(),domain()->minY(),domain()->maxY());
        m_lower->handleDomainUpdated();
    }
}

void AreaChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)
    painter->save();
    painter->setPen(m_linePen);
    painter->setBrush(m_brush);
    QRectF clipRect = QRectF(QPointF(0, 0), domain()->size());
    if (presenter()->chartType() == QChart::ChartTypePolar)
        painter->setClipRegion(QRegion(clipRect.toRect(), QRegion::Ellipse));
    else
        painter->setClipRect(clipRect);
    painter->drawPath(m_path);
    if (m_pointsVisible) {
        painter->setPen(m_pointPen);
        painter->drawPoints(m_upper->geometryPoints());
        if (m_lower)
            painter->drawPoints(m_lower->geometryPoints());
    }

    // Draw series point label
    if (m_pointLabelsVisible) {
        static const QString xPointTag(QLatin1String("@xPoint"));
        static const QString yPointTag(QLatin1String("@yPoint"));
        const int labelOffset = 2;

        painter->setFont(m_pointLabelsFont);
        painter->setPen(QPen(m_pointLabelsColor));
        QFontMetrics fm(painter->font());

        QString pointLabel = m_pointLabelsFormat;

        if (m_series->upperSeries()) {
            for (int i(0); i < m_series->upperSeries()->count(); i++) {
                pointLabel.replace(xPointTag,
                                   presenter()->numberToString(m_series->upperSeries()->at(i).x()));
                pointLabel.replace(yPointTag,
                                   presenter()->numberToString(m_series->upperSeries()->at(i).y()));

                // Position text in relation to the point
                int pointLabelWidth = fm.width(pointLabel);
                QPointF position(m_upper->geometryPoints().at(i));
                position.setX(position.x() - pointLabelWidth / 2);
                position.setY(position.y() - m_series->upperSeries()->pen().width() / 2 - labelOffset);

                painter->drawText(position, pointLabel);
            }
        }

        if (m_series->lowerSeries()) {
            for (int i(0); i < m_series->lowerSeries()->count(); i++) {
                pointLabel.replace(xPointTag,
                                   presenter()->numberToString(m_series->lowerSeries()->at(i).x()));
                pointLabel.replace(yPointTag,
                                   presenter()->numberToString(m_series->lowerSeries()->at(i).y()));

                // Position text in relation to the point
                int pointLabelWidth = fm.width(pointLabel);
                QPointF position(m_lower->geometryPoints().at(i));
                position.setX(position.x() - pointLabelWidth / 2);
                position.setY(position.y() - m_series->lowerSeries()->pen().width() / 2 - labelOffset);

                painter->drawText(position, pointLabel);
            }
        }
    }

    painter->restore();
}

void AreaChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit pressed(m_upper->domain()->calculateDomainPoint(event->pos()));
    m_lastMousePos = event->pos();
    m_mousePressed = true;
    ChartItem::mousePressEvent(event);
}

void AreaChartItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovered(domain()->calculateDomainPoint(event->pos()), true);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

void AreaChartItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hovered(domain()->calculateDomainPoint(event->pos()), false);
    event->accept();
//    QGraphicsItem::hoverEnterEvent(event);
}

void AreaChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit released(m_upper->domain()->calculateDomainPoint(m_lastMousePos));
    if (m_mousePressed)
        emit clicked(m_upper->domain()->calculateDomainPoint(m_lastMousePos));
    m_mousePressed = false;
    ChartItem::mouseReleaseEvent(event);
}

void AreaChartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit doubleClicked(m_upper->domain()->calculateDomainPoint(m_lastMousePos));
    ChartItem::mouseDoubleClickEvent(event);
}

#include "moc_areachartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
