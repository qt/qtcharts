// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/scatterchartitem_p.h>
#include <QtCharts/QScatterSeries>
#include <private/qscatterseries_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractdomain_p.h>
#include <QtCharts/QChart>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsScene>
#include <QtCore/QDebug>
#include <QtWidgets/QGraphicsSceneMouseEvent>

QT_BEGIN_NAMESPACE

namespace {
constexpr short STAR_SPIKES = 5;
}

ScatterChartItem::ScatterChartItem(QScatterSeries *series, QGraphicsItem *item)
    : XYChart(series,item),
      m_series(series),
      m_items(this),
      m_visible(true),
      m_markerShape(QScatterSeries::MarkerShapeRectangle),
      m_pointsVisible(true),
      m_pointLabelsVisible(false),
      m_markerSize(series->markerSize()),
      m_pointLabelsFormat(series->pointLabelsFormat()),
      m_pointLabelsFont(series->pointLabelsFont()),
      m_pointLabelsColor(series->pointLabelsColor()),
      m_pointLabelsClipping(true),
      m_lastHoveredPoint(QPointF(qQNaN(), qQNaN())),
      m_mousePressed(false)
{
    connect(series->d_func(), &QXYSeriesPrivate::seriesUpdated,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::lightMarkerChanged, this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::selectedLightMarkerChanged, this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::markerSizeChanged, this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::visibleChanged, this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::opacityChanged, this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::pointLabelsFormatChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::pointLabelsVisibilityChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::pointLabelsFontChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::pointLabelsColorChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::pointLabelsClippingChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::selectedColorChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QXYSeries::selectedPointsChanged,
            this, &ScatterChartItem::handleSeriesUpdated);
    connect(series, &QScatterSeries::pointsConfigurationChanged,
            this, &ScatterChartItem::handleSeriesUpdated);

    setZValue(ChartPresenter::ScatterSeriesZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape | QGraphicsItem::ItemIsSelectable);

    handleSeriesUpdated();

    m_items.setHandlesChildEvents(false);
}

QRectF ScatterChartItem::boundingRect() const
{
    return m_rect;
}

void ScatterChartItem::createPoints(int count)
{
    for (int i = 0; i < count; ++i) {

        QGraphicsItem *item = 0;

        switch (m_markerShape) {
        case QScatterSeries::MarkerShapeCircle: {
            item = new ChartMarker<QGraphicsEllipseItem>(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        case QScatterSeries::MarkerShapeRectangle: {
            item = new ChartMarker<QGraphicsRectItem>(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        case QScatterSeries::MarkerShapeRotatedRectangle: {
            item = new RotatedRectangleMarker(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        case QScatterSeries::MarkerShapeTriangle: {
            item = new TriangleMarker(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        case QScatterSeries::MarkerShapeStar: {
            item = new StarMarker(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        case QScatterSeries::MarkerShapePentagon: {
            item = new PentagonMarker(0, 0, m_markerSize, m_markerSize, this);
            break;
        }
        default:
            qWarning() << "Unsupported marker type";
            break;
        }

        m_items.addToGroup(item);
    }
}

void ScatterChartItem::deletePoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        QGraphicsItem *item = items.takeLast();
        m_markerMap.remove(item);
        delete(item);
    }
}

void ScatterChartItem::resizeMarker(QGraphicsItem *marker, const int size)
{
    switch (m_markerShape) {
    case QScatterSeries::MarkerShapeCircle: {
        QGraphicsEllipseItem *item = static_cast<QGraphicsEllipseItem *>(marker);
        item->setRect(0, 0, size, size);
        break;
    }
    case QScatterSeries::MarkerShapeRectangle: {
        QGraphicsRectItem *item = static_cast<QGraphicsRectItem *>(marker);
        item->setRect(0, 0, size, size);
        break;
    }
    case QScatterSeries::MarkerShapeRotatedRectangle: {
        QGraphicsPolygonItem *item = static_cast<QGraphicsPolygonItem *>(marker);
        item->setPolygon(RotatedRectangleMarker::polygon(0, 0, size, size));
        break;
    }
    case QScatterSeries::MarkerShapeTriangle: {
        QGraphicsPolygonItem *item = static_cast<QGraphicsPolygonItem *>(marker);
        item->setPolygon(TriangleMarker::polygon(0, 0, size, size));
        break;
    }
    case QScatterSeries::MarkerShapeStar: {
        QGraphicsPolygonItem *item = static_cast<QGraphicsPolygonItem *>(marker);
        item->setPolygon(StarMarker::polygon(0, 0, size, size));
        break;
    }
    case QScatterSeries::MarkerShapePentagon: {
        QGraphicsPolygonItem *item = static_cast<QGraphicsPolygonItem *>(marker);
        item->setPolygon(PentagonMarker::polygon(0, 0, size, size));
        break;
    }
    default:
        qWarning() << "Unsupported marker type";
        break;
    }
}

void ScatterChartItem::markerSelected(QGraphicsItem *marker)
{
    emit XYChart::clicked(m_markerMap[marker]);
}

void ScatterChartItem::markerHovered(QGraphicsItem *marker, bool state)
{
    emit XYChart::hovered(m_markerMap[marker], state);
}

void ScatterChartItem::markerPressed(QGraphicsItem *marker)
{
    emit XYChart::pressed(m_markerMap[marker]);
}

void ScatterChartItem::markerReleased(QGraphicsItem *marker)
{
    emit XYChart::released(m_markerMap[marker]);
}

void ScatterChartItem::markerDoubleClicked(QGraphicsItem *marker)
{
    emit XYChart::doubleClicked(m_markerMap[marker]);
}

void ScatterChartItem::updateGeometry()
{
    if (m_series->useOpenGL()) {
        if (m_items.childItems().size())
            deletePoints(m_items.childItems().size());
        if (!m_rect.isEmpty()) {
            prepareGeometryChange();
            // Changed signal seems to trigger even with empty region
            m_rect = QRectF();
        }
        update();
        return;
    }

    const QList<QPointF> &points = geometryPoints();

    if (points.size() == 0) {
        deletePoints(m_items.childItems().size());
        return;
    }

    int diff = m_items.childItems().size() - points.size();

    if (diff > 0)
        deletePoints(diff);
    else if (diff < 0)
        createPoints(-diff);

    if (diff != 0)
        handleSeriesUpdated();

    QList<QGraphicsItem *> items = m_items.childItems();

    QRectF clipRect(QPointF(0,0),domain()->size());

    // Only zoom in if the clipRect fits inside int limits. QWidget::update() uses
    // a region that has to be compatible with QRect.
    if (clipRect.height() <= INT_MAX
            && clipRect.width() <= INT_MAX) {
        const QList<bool> offGridStatus = offGridStatusVector();
        const int seriesLastIndex = m_series->count() - 1;

        for (int i = 0; i < points.size(); i++) {
            QAbstractGraphicsShapeItem *item =
                    static_cast<QAbstractGraphicsShapeItem *>(items.at(i));
            const QPointF &point = points.at(i);

            if (m_pointsConfiguration.contains(i)) {
                const auto &conf = m_pointsConfiguration[i];
                if (conf.contains(QXYSeries::PointConfiguration::Size))
                    resizeMarker(
                            item,
                            m_pointsConfiguration[i][QXYSeries::PointConfiguration::Size].toReal());
            }

            const QRectF &rect = item->boundingRect();
            // During remove animation series may have different number of points,
            // so ensure we don't go over the index. Animation handling itself ensures that
            // if there is actually no points in the series, then it won't generate a fake point,
            // so we can be assured there is always at least one point in m_series here.
            // Note that marker map values can be technically incorrect during the animation,
            // if it was caused by an insert, but this shouldn't be a problem as the points are
            // fake anyway. After remove animation stops, geometry is updated to correct one.
            m_markerMap[item] = m_series->at(qMin(seriesLastIndex, i));
            QPointF position;
            position.setX(point.x() - rect.width() / 2);
            position.setY(point.y() - rect.height() / 2);
            item->setPos(position);

            if (!m_visible || offGridStatus.at(i)) {
                item->setVisible(false);
            } else {
                bool drawPoint = m_pointsVisible;
                if (m_pointsConfiguration.contains(i)) {
                    const auto &conf = m_pointsConfiguration[i];

                    if (conf.contains(QXYSeries::PointConfiguration::Visibility)) {
                        drawPoint
                                = m_pointsConfiguration[i][QXYSeries::PointConfiguration::Visibility]
                                .toBool();
                    }

                    if (drawPoint && conf.contains(QXYSeries::PointConfiguration::Color)) {
                        item->setBrush(
                                m_pointsConfiguration[i][QXYSeries::PointConfiguration::Color]
                                        .value<QColor>());
                    }
                }

                if (m_series->isPointSelected(i)) {
                    drawPoint = m_series->selectedLightMarker().isNull();
                    if (drawPoint && m_selectedColor.isValid())
                        item->setBrush(m_selectedColor);
                }

                item->setVisible(drawPoint);
            }
        }

        prepareGeometryChange();
        m_rect = clipRect;
    }
}

void ScatterChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF matchedP = matchForLightMarker(event->pos());
    if (!qIsNaN(matchedP.x())) {
        emit XYChart::pressed(matchedP);
        m_lastMousePos = event->pos();
        m_mousePressed = true;
    } else {
        event->ignore();
    }

    QGraphicsItem::mousePressEvent(event);
}

void ScatterChartItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF matchedP = matchForLightMarker(event->pos());
    if (!qIsNaN(matchedP.x())) {
        if (matchedP != m_lastHoveredPoint) {
            if (!qIsNaN(m_lastHoveredPoint.x()))
                emit XYChart::hovered(m_lastHoveredPoint, false);

            m_lastHoveredPoint = matchedP;
            emit XYChart::hovered(matchedP, true);
        }
    } else if (!qIsNaN(m_lastHoveredPoint.x())) {
        emit XYChart::hovered(m_lastHoveredPoint, false);
        m_lastHoveredPoint = QPointF(qQNaN(), qQNaN());
    }

    QGraphicsItem::hoverMoveEvent(event);
}

void ScatterChartItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF result;
    QPointF matchedP = matchForLightMarker(m_lastMousePos);
    if (!qIsNaN(matchedP.x()) && m_mousePressed) {
        result = matchedP;
        emit XYChart::released(result);
        emit XYChart::clicked(result);
    }

    m_mousePressed = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

void ScatterChartItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF matchedP = matchForLightMarker(event->pos());
    if (!qIsNaN(matchedP.x()))
        emit XYChart::doubleClicked(matchedP);
    else
        emit XYChart::doubleClicked(domain()->calculateDomainPoint(m_lastMousePos));

    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ScatterChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (m_series->useOpenGL())
        return;

    QRectF clipRect = QRectF(QPointF(0, 0), domain()->size());

    painter->save();
    painter->setClipRect(clipRect);

    // Draw markers if a marker or marker for selected points only has been
    // set (set to QImage() to disable)
    if (!m_series->lightMarker().isNull() || !m_series->selectedLightMarker().isNull()) {
        const QImage &marker = m_series->lightMarker();
        const QImage &selectedMarker = m_series->selectedLightMarker();
        qreal markerHalfSize = m_markerSize / 2.0;

        for (int i = 0; i < m_points.size(); ++i) {
            // Documentation of light markers says that points visibility and
            // light markers are independent features. Therefore m_pointsVisible
            // is not used here as light markers are drawn if lightMarker is not null.
            // However points visibility configuration can be still used here.
            bool drawPoint = !m_series->lightMarker().isNull();
            if (m_pointsConfiguration.contains(i)) {
                const auto &conf = m_pointsConfiguration[i];

                if (conf.contains(QXYSeries::PointConfiguration::Visibility)) {
                    drawPoint = m_pointsConfiguration[i][QXYSeries::PointConfiguration::Visibility]
                                        .toBool();
                }
            }

            bool drawSelectedPoint = false;
            if (m_series->isPointSelected(i)) {
                drawPoint = true;
                drawSelectedPoint = !selectedMarker.isNull();
            }
            if (drawPoint) {
                const QRectF rect(m_points[i].x() - markerHalfSize,
                                  m_points[i].y() - markerHalfSize,
                                  m_markerSize, m_markerSize);
                painter->drawImage(rect, drawSelectedPoint ? selectedMarker : marker);
            }
        }
    }

    if (m_series->bestFitLineVisible())
        m_series->d_func()->drawBestFitLine(painter, clipRect);

    m_series->d_func()->drawPointLabels(painter, m_points, m_series->markerSize() / 2 + m_series->pen().width());

    painter->restore();
}

void ScatterChartItem::setPen(const QPen &pen)
{
    QPen penToUse(pen);
    if (!m_series->lightMarker().isNull())
        penToUse.setColor(Qt::transparent);

    const auto &items = m_items.childItems();
    for (auto item : items)
        static_cast<QAbstractGraphicsShapeItem*>(item)->setPen(penToUse);
}

void ScatterChartItem::setBrush(const QBrush &brush)
{
    const auto &items = m_items.childItems();
    for (auto item : items) {
        if (m_series->lightMarker().isNull()) {
            if (m_markerMap.contains(item)) {
                auto index = m_series->points().indexOf(m_markerMap[item]);
                if (m_selectedPoints.contains(index) && m_selectedColor.isValid()) {
                    static_cast<QAbstractGraphicsShapeItem *>(item)->setBrush(m_selectedColor);
                } else {
                    bool useBrush = true;
                    if (m_pointsConfiguration.contains(index)) {
                        const auto &conf = m_pointsConfiguration[index];
                        if (conf.contains(QXYSeries::PointConfiguration::Color))
                            useBrush = false;
                    }

                    if (useBrush)
                        static_cast<QAbstractGraphicsShapeItem *>(item)->setBrush(brush);
                }
            } else {
                static_cast<QAbstractGraphicsShapeItem *>(item)->setBrush(brush);
            }
        } else {
            QBrush brushToUse;
            brushToUse.setColor(Qt::transparent);
            static_cast<QAbstractGraphicsShapeItem *>(item)->setBrush(brushToUse);
        }
    }
}

void ScatterChartItem::handleSeriesUpdated()
{
    if (m_series->useOpenGL()) {
        if ((m_series->isVisible() != m_visible)) {
            m_visible = m_series->isVisible();
            refreshGlChart();
        }
        return;
    }

    int count = m_items.childItems().size();
    if (count == 0)
        return;

    const bool pointsConfigurationDirty =
            m_series->pointsConfiguration() != m_pointsConfiguration;

    bool recreate = m_visible != m_series->isVisible()
                    || m_pointsVisible != m_series->pointsVisible()
                    || m_markerSize != m_series->markerSize()
                    || m_markerShape != m_series->markerShape()
                    || m_selectedColor != m_series->selectedColor()
                    || m_selectedPoints != m_series->selectedPoints()
                    || pointsConfigurationDirty;
    m_visible = m_series->isVisible();
    m_markerSize = m_series->markerSize();
    m_markerShape = m_series->markerShape();
    setVisible(m_visible);
    setOpacity(m_series->opacity());
    m_pointsVisible = m_series->pointsVisible();
    m_pointLabelsFormat = m_series->pointLabelsFormat();
    m_pointLabelsVisible = m_series->pointLabelsVisible();
    m_pointLabelsFont = m_series->pointLabelsFont();
    m_pointLabelsColor = m_series->pointLabelsColor();
    m_selectedColor = m_series->selectedColor();
    m_selectedPoints = m_series->selectedPoints();
    m_pointsConfiguration = m_series->pointsConfiguration();
    bool labelClippingChanged = m_pointLabelsClipping != m_series->pointLabelsClipping();
    m_pointLabelsClipping = m_series->pointLabelsClipping();

    if (recreate) {
        deletePoints(count);
        createPoints(count);

        // Updating geometry is now safe, because it won't call handleSeriesUpdated unless it
        // creates/deletes points
        updateGeometry();
    }

    // Only accept hover events when light/selection markers are in use so we don't unnecessarily
    // eat the events in the regular case
    setAcceptHoverEvents(!(m_series->lightMarker().isNull()
                           && (m_series->selectedLightMarker().isNull()
                               || m_series->selectedPoints().isEmpty())));

    setPen(m_series->pen());
    setBrush(m_series->brush());
    // Update whole chart in case label clipping changed as labels can be outside series area
    if (labelClippingChanged)
        m_series->chart()->update();
    else
        update();
}

void ScatterChartItem::handleMarkerMouseReleaseEvent(QGraphicsItem *item)
{
    markerReleased(item);
    if (mousePressed())
        markerSelected(item);
    setMousePressed(false);
}

template<class T>
ChartMarker<T>::ChartMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
    : T(x, y, w, h, parent)
    , m_parent(parent)
{
    T::setAcceptHoverEvents(true);
    T::setFlag(QGraphicsItem::ItemIsSelectable);
}

template<class T>
ChartMarker<T>::ChartMarker(ScatterChartItem *parent)
    : T(parent)
    , m_parent(parent)
{
    T::setAcceptHoverEvents(true);
    T::setFlag(QGraphicsItem::ItemIsSelectable);
}

template<class T>
void ChartMarker<T>::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    T::mousePressEvent(event);
    m_parent->markerPressed(this);
    m_parent->setMousePressed();
}

template<class T>
void ChartMarker<T>::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    T::hoverEnterEvent(event);
    m_parent->markerHovered(this, true);
}

template<class T>
void ChartMarker<T>::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    T::hoverLeaveEvent(event);
    m_parent->markerHovered(this, false);
}

template<class T>
void ChartMarker<T>::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    T::mouseReleaseEvent(event);
    m_parent->handleMarkerMouseReleaseEvent(this);
}

template<class T>
void ChartMarker<T>::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    T::mouseDoubleClickEvent(event);
    m_parent->markerDoubleClicked(this);
}

RotatedRectangleMarker::RotatedRectangleMarker(qreal x, qreal y, qreal w, qreal h,
                                               ScatterChartItem *parent)
    : ChartMarker<QGraphicsPolygonItem>(parent)
{
    setPolygon(RotatedRectangleMarker::polygon(x, y, w, h));
}

QPolygonF RotatedRectangleMarker::polygon(qreal x, qreal y, qreal w, qreal h)
{
    QPolygonF rotatedRectPoly;
    rotatedRectPoly << QPointF(x, y + h / 2.0);
    rotatedRectPoly << QPointF(x + w / 2.0, y + h);
    rotatedRectPoly << QPointF(x + w, y + h / 2.0);
    rotatedRectPoly << QPointF(x + w / 2.0, y);

    return rotatedRectPoly;
}

TriangleMarker::TriangleMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
    : ChartMarker<QGraphicsPolygonItem>(parent)
{
    setPolygon(TriangleMarker::polygon(x, y, w, h));
}

QPolygonF TriangleMarker::polygon(qreal x, qreal y, qreal w, qreal h)
{
    QPolygonF trianglePoly;
    trianglePoly << QPointF(x, y + h);
    trianglePoly << QPointF(x + w, y + h);
    trianglePoly << QPointF(x + w / 2.0, y);

    return trianglePoly;
}

StarMarker::StarMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
    : ChartMarker<QGraphicsPolygonItem>(parent)
{
    setPolygon(StarMarker::polygon(x, y, w, h));
}

QPolygonF StarMarker::polygon(qreal x, qreal y, qreal w, qreal h)
{
    QPolygonF starPoly;

    constexpr qreal step = M_PI / STAR_SPIKES;
    const qreal radius = w / 2.0;
    const qreal innerRadius = radius * 0.5;
    const QPointF &center = QPointF(x + w / 2.0, y + h / 2.0);
    qreal rot = M_PI / 2 * 3;

    for (int i = 0; i < STAR_SPIKES; ++i) {
        starPoly << QPointF(center.x() + std::cos(rot) * radius,
                            center.y() + std::sin(rot) * radius);
        rot += step;

        starPoly << QPointF(center.x() + std::cos(rot) * innerRadius,
                            center.y() + std::sin(rot) * innerRadius);
        rot += step;
    }

    return starPoly;
}

PentagonMarker::PentagonMarker(qreal x, qreal y, qreal w, qreal h, ScatterChartItem *parent)
    : ChartMarker<QGraphicsPolygonItem>(parent)
{
    setPolygon(PentagonMarker::polygon(x, y, w, h));
}

QPolygonF PentagonMarker::polygon(qreal x, qreal y, qreal w, qreal h)
{
    QPolygonF pentagonPoly;

    constexpr qreal step = 2 * M_PI / 5;
    const qreal radius = w / 2.0;
    const QPointF &center = QPointF(x + w / 2.0, y + h / 2.0);
    qreal rot = M_PI / 2 * 3;

    for (int i = 0; i < 5; ++i) {
        pentagonPoly << QPointF(center.x() + std::cos(rot) * radius,
                                center.y() + std::sin(rot) * radius);
        rot += step;
    }

    return pentagonPoly;
}

QT_END_NAMESPACE

#include "moc_scatterchartitem_p.cpp"
