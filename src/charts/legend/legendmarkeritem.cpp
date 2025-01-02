// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "legendmarkeritem_p.h"
#include "qlegendmarker_p.h"
#include "chartpresenter_p.h"
#include "qlegend.h"
#include "qlegend_p.h"
#include "qlegendmarker.h"
#if QT_CONFIG(charts_scatter_chart)
#include "qscatterseries.h"
#include "scatterchartitem_p.h"
#endif
#if QT_CONFIG(charts_line_chart)
#include "qlineseries.h"
#endif
#if QT_CONFIG(charts_spline_chart)
#include "qsplineseries.h"
#endif
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QGraphicsTextItem>
#include <QtWidgets/QGraphicsEllipseItem>
#include <QtWidgets/QGraphicsRectItem>
#include <QtWidgets/QGraphicsLineItem>
#include <QtGui/QTextDocument>
#include <QtCore/QtMath>

QT_BEGIN_NAMESPACE

LegendMarkerItem::LegendMarkerItem(QLegendMarkerPrivate *marker, QGraphicsObject *parent) :
    QGraphicsObject(parent),
    m_marker(marker),
    m_defaultMarkerRect(0.0, 0.0, 10.0, 10.0),
    m_markerRect(0.0, 0.0, -1.0, -1.0),
    m_boundingRect(0,0,0,0),
    m_textItem(new QGraphicsTextItem(this)),
    m_markerItem(nullptr),
    m_margin(3),
    m_space(4),
    m_markerShape(QLegend::MarkerShapeDefault),
    m_hovering(false),
    m_itemType(TypeRect)
{
    m_textItem->document()->setDocumentMargin(ChartPresenter::textMargin());
    setAcceptHoverEvents(true);
}

LegendMarkerItem::~LegendMarkerItem()
{
    if (m_hovering) {
        emit m_marker->q_ptr->hovered(false);
    }
}

void LegendMarkerItem::setPen(const QPen &pen)
{
    m_pen = pen;
    setItemBrushAndPen();
}

QPen LegendMarkerItem::pen() const
{
    return m_pen;
}

void LegendMarkerItem::setBrush(const QBrush &brush)
{
    m_brush = brush;
    setItemBrushAndPen();
}

QBrush LegendMarkerItem::brush() const
{
    return m_brush;
}

void LegendMarkerItem::setSeriesPen(const QPen &pen)
{
    m_seriesPen = pen;
    setItemBrushAndPen();
}

void LegendMarkerItem::setSeriesBrush(const QBrush &brush)
{
    m_seriesBrush = brush;
    setItemBrushAndPen();
}

void LegendMarkerItem::setSeriesLightMarker(const QImage &image)
{
    m_seriesLightMarker = image;

    if (m_markerItem) {
        if (image.isNull()) {
            m_markerItem->setFlag(QGraphicsItem::ItemStacksBehindParent, false);
        } else {
            m_markerItem->setFlag(QGraphicsItem::ItemStacksBehindParent,
                (effectiveMarkerShape() == QLegend::MarkerShapeFromSeries));
        }
    }
    updateMarkerShapeAndSize();
}

void LegendMarkerItem::setFont(const QFont &font)
{
    QFontMetrics fn(font);
    m_font = font;

    m_defaultMarkerRect = QRectF(0, 0, fn.height() / 2, fn.height() / 2);
    if (effectiveMarkerShape() != QLegend::MarkerShapeFromSeries)
        updateMarkerShapeAndSize();
    m_marker->invalidateLegend();
}

QFont LegendMarkerItem::font() const
{
    return m_font;
}

void LegendMarkerItem::setLabel(const QString label)
{
    m_label = label;
    m_marker->invalidateLegend();
}

QString LegendMarkerItem::label() const
{
    return m_label;
}

void LegendMarkerItem::setLabelBrush(const QBrush &brush)
{
    m_textItem->setDefaultTextColor(brush.color());
}

QBrush LegendMarkerItem::labelBrush() const
{
    return QBrush(m_textItem->defaultTextColor());
}

void LegendMarkerItem::setGeometry(const QRectF &rect)
{
    if (!m_markerItem)
        updateMarkerShapeAndSize();

    const qreal width = rect.width();
    const qreal markerWidth = effectiveMarkerWidth();
    const qreal x = m_margin + markerWidth + m_space + m_margin;
    QRectF truncatedRect;
    const QString html = ChartPresenter::truncatedText(m_font, m_label, qreal(0.0),
                                                       width - x, rect.height(), truncatedRect);
    m_textItem->setHtml(html.compare(QLatin1String("...")) ? html : QString());
#if QT_CONFIG(tooltip)
    if (m_marker->m_legend->showToolTips() && html != m_label) {
        m_textItem->setToolTip(m_label);
        m_markerItem->setToolTip(m_label);
    } else {
        m_textItem->setToolTip(QString());
        m_markerItem->setToolTip(QString());
    }
#endif
    m_textItem->setFont(m_font);
    m_textItem->setTextWidth(truncatedRect.width());

    qreal y = qMax(m_markerRect.height() + 2 * m_margin, truncatedRect.height() + 2 * m_margin);

    const QRectF &textRect = m_textItem->boundingRect();

    m_textItem->setPos(x - m_margin, y / 2 - textRect.height() / 2);
    setItemRect();

    // The textMargin adjustments to position are done to make default case rects less blurry with anti-aliasing
    m_markerItem->setPos(m_margin - ChartPresenter::textMargin()
                         + (markerWidth - m_markerRect.width()) / 2.0,
                         y / 2.0  - m_markerRect.height() / 2.0 + ChartPresenter::textMargin());

    prepareGeometryChange();
    m_boundingRect = QRectF(0, 0, x + textRect.width() + m_margin, y);
}

QRectF LegendMarkerItem::boundingRect() const
{
    return m_boundingRect;
}

QRectF LegendMarkerItem::markerRect() const
{
    return m_markerRect;
}

void LegendMarkerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw the light marker, if it is present.
    if (!m_seriesLightMarker.isNull()) {
        QRectF rect(m_markerItem->pos(), m_markerRect.size());

        // shrink the image so the line is visible behind the marker
        if (m_itemType == TypeLine && rect.width() > 4 && rect.height() > 4)
            rect.adjust(1.0, 1.0, -1.0, -1.0);

        painter->drawImage(rect, m_seriesLightMarker);
    }
}

QSizeF LegendMarkerItem::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint);

    QSizeF sh;
    const qreal markerWidth = effectiveMarkerWidth();

    switch (which) {
    case Qt::MinimumSize: {
        const QRectF labelRect = ChartPresenter::textBoundingRect(m_font, QStringLiteral("..."));
        sh = QSizeF(labelRect.width() + (2.0 * m_margin) + m_space + markerWidth,
                    qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin));
        break;
    }
    case Qt::PreferredSize: {
        const QRectF labelRect = ChartPresenter::textBoundingRect(m_font, m_label);
        sh = QSizeF(labelRect.width() + (2.0 * m_margin) + m_space + markerWidth + 1,
                    qMax(m_markerRect.height(), labelRect.height()) + (2.0 * m_margin));
        break;
    }
    default:
        break;
    }

    return sh;
}

void LegendMarkerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->setAccepted(false);
    m_hovering = true;
    emit m_marker->q_ptr->hovered(true);

    QGraphicsObject::hoverEnterEvent(event);
}

void LegendMarkerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->setAccepted(false);
    m_hovering = false;
    emit m_marker->q_ptr->hovered(false);

    QGraphicsObject::hoverLeaveEvent(event);
}

QString LegendMarkerItem::displayedLabel() const
{
    return m_textItem->toHtml();
}

void LegendMarkerItem::setToolTip(const QString &tip)
{
#if QT_CONFIG(tooltip)
    m_textItem->setToolTip(tip);
    m_markerItem->setToolTip(tip);
#endif
}

QLegend::MarkerShape LegendMarkerItem::markerShape() const
{
    return m_markerShape;
}

void LegendMarkerItem::setMarkerShape(QLegend::MarkerShape shape)
{
    m_markerShape = shape;
}

void LegendMarkerItem::updateMarkerShapeAndSize()
{
    const QLegend::MarkerShape shape = effectiveMarkerShape();

    ItemType itemType = TypeRect;
    QRectF newRect = m_defaultMarkerRect;
    QXYSeries *xySeries = qobject_cast<QXYSeries *>(m_marker->series());

    switch (shape) {
    case QLegend::MarkerShapeFromSeries: {
        if (xySeries) {
            m_seriesLightMarker = xySeries->lightMarker();
            switch (xySeries->type()) {
#if QT_CONFIG(charts_scatter_chart)
            case QAbstractSeries::SeriesTypeScatter: {
                newRect.setSize(QSizeF(xySeries->markerSize(), xySeries->markerSize()));

                QScatterSeries *scatter = qobject_cast<QScatterSeries *>(m_marker->series());
                Q_ASSERT(scatter != nullptr);
                switch (scatter->markerShape()) {
                case QScatterSeries::MarkerShapeRectangle:
                    itemType = TypeRect;
                    break;
                case QScatterSeries::MarkerShapeCircle:
                    itemType = TypeCircle;
                    break;
                case QScatterSeries::MarkerShapeRotatedRectangle:
                    itemType = TypeRotatedRect;
                    break;
                case QScatterSeries::MarkerShapeTriangle:
                    itemType = TypeTriangle;
                    break;
                case QScatterSeries::MarkerShapeStar:
                    itemType = TypeStar;
                    break;
                case QScatterSeries::MarkerShapePentagon:
                    itemType = TypePentagon;
                    break;
                default:
                    qWarning() << "Unsupported marker type, TypeRect used";
                    break;
                }
            }
                break;
#endif
#if QT_CONFIG(charts_line_chart)
            case QAbstractSeries::SeriesTypeLine:
            case QAbstractSeries::SeriesTypeSpline: {
                if (m_seriesLightMarker.isNull()) {
                    newRect.setHeight(m_seriesPen.width());
                    newRect.setWidth(qRound(m_defaultMarkerRect.width() * 1.5));
                } else {
                    newRect.setSize(QSizeF(xySeries->markerSize(), xySeries->markerSize()));
                }
                itemType = TypeLine;
            }
                break;
#endif
            default:
                // Use defaults specified above.
                break;
            }
        }
    }
        break;
    case QLegend::MarkerShapeCircle:
        itemType = TypeCircle;
        break;
    case QLegend::MarkerShapeRotatedRectangle:
        itemType = TypeRotatedRect;
        break;
    case QLegend::MarkerShapeTriangle:
        itemType = TypeTriangle;
        break;
    case QLegend::MarkerShapeStar:
        itemType = TypeStar;
        break;
    case QLegend::MarkerShapePentagon:
        itemType = TypePentagon;
        break;
    default:
        break;
    }

    if (!m_markerItem || m_itemType != itemType) {
        m_itemType = itemType;
        QPointF oldPos;
        if (m_markerItem) {
            oldPos = m_markerItem->pos();
            delete m_markerItem;
        }

        switch (itemType) {
        case LegendMarkerItem::TypeRect: {
            m_markerItem = new QGraphicsRectItem(this);
            break;
        }
        case LegendMarkerItem::TypeCircle: {
            m_markerItem = new QGraphicsEllipseItem(this);
            break;
        }
#if QT_CONFIG(charts_scatter_chart)
        case LegendMarkerItem::TypeRotatedRect: {
            QGraphicsPolygonItem *item = new QGraphicsPolygonItem(this);
            item->setPolygon(RotatedRectangleMarker::polygon());
            m_markerItem = item;
            break;
        }
        case LegendMarkerItem::TypeTriangle: {
            QGraphicsPolygonItem *item = new QGraphicsPolygonItem(this);
            item->setPolygon(TriangleMarker::polygon());
            m_markerItem = item;
            break;
        }
        case LegendMarkerItem::TypeStar: {
            QGraphicsPolygonItem *item = new QGraphicsPolygonItem(this);
            item->setPolygon(StarMarker::polygon());
            m_markerItem = item;
            break;
        }
        case LegendMarkerItem::TypePentagon: {
            QGraphicsPolygonItem *item = new QGraphicsPolygonItem(this);
            item->setPolygon(PentagonMarker::polygon());
            m_markerItem = item;
            break;
        }
#endif
        default:
            m_markerItem =  new QGraphicsLineItem(this);
            break;
        }

        if (xySeries && shape == QLegend::MarkerShapeFromSeries
            && !m_seriesLightMarker.isNull()) {
                m_markerItem->setFlag(QGraphicsItem::ItemStacksBehindParent, true);
        }

        // Immediately update the position to the approximate correct position to avoid marker
        // jumping around when changing markers
        m_markerItem->setPos(oldPos);
    }
    setItemBrushAndPen();

    if (newRect != m_markerRect) {
        if (useMaxWidth() && m_marker->m_legend->d_ptr->maxMarkerWidth() < newRect.width())
            m_marker->invalidateAllItems();
        m_markerRect = newRect;
        setItemRect();
        emit markerRectChanged();
        updateGeometry();
    }
}

QLegend::MarkerShape LegendMarkerItem::effectiveMarkerShape() const
{
    QLegend::MarkerShape shape = m_markerShape;
    if (shape == QLegend::MarkerShapeDefault)
        shape = m_marker->m_legend->markerShape();
    return shape;
}

qreal LegendMarkerItem::effectiveMarkerWidth() const
{
    return useMaxWidth() ? m_marker->m_legend->d_ptr->maxMarkerWidth()
                         : m_markerRect.width();
}

void LegendMarkerItem::setItemBrushAndPen()
{
    if (m_markerItem) {
        QAbstractGraphicsShapeItem *shapeItem =
                qgraphicsitem_cast<QGraphicsRectItem *>(m_markerItem);
        if (!shapeItem)
            shapeItem = qgraphicsitem_cast<QGraphicsEllipseItem *>(m_markerItem);

        if (!shapeItem)
            shapeItem = qgraphicsitem_cast<QGraphicsPolygonItem *>(m_markerItem);

        if (shapeItem) {
            if (effectiveMarkerShape() == QLegend::MarkerShapeFromSeries) {
                QPen pen = m_seriesPen;
                QBrush brush = m_seriesBrush;
                if (!m_seriesLightMarker.isNull()) {
                    // If there's a light marker set, don't draw the regular marker.
                    pen.setColor(Qt::transparent);
                    brush = QBrush();
                    brush.setColor(Qt::transparent);
                }

                shapeItem->setPen(pen);
                shapeItem->setBrush(brush);
            } else {
                shapeItem->setPen(m_pen);
                shapeItem->setBrush(m_brush);
            }
        } else {
            // Must be line item, it has no brush.
            QGraphicsLineItem *lineItem =
                    qgraphicsitem_cast<QGraphicsLineItem *>(m_markerItem);
            if (lineItem)
                lineItem->setPen(m_seriesPen);
        }
    }
}

void LegendMarkerItem::setItemRect()
{
    switch (m_itemType) {
    case LegendMarkerItem::TypeRect: {
        static_cast<QGraphicsRectItem *>(m_markerItem)->setRect(m_markerRect);
        break;
    }
    case LegendMarkerItem::TypeCircle: {
        static_cast<QGraphicsEllipseItem *>(m_markerItem)->setRect(m_markerRect);
        break;
    }
#if QT_CONFIG(charts_scatter_chart)
    case LegendMarkerItem::TypeRotatedRect: {
        static_cast<QGraphicsPolygonItem *>(m_markerItem)
                ->setPolygon(RotatedRectangleMarker::polygon(m_markerRect.x(), m_markerRect.y(),
                                                             m_markerRect.width(),
                                                             m_markerRect.height()));
        break;
    }
    case LegendMarkerItem::TypeTriangle: {
        static_cast<QGraphicsPolygonItem *>(m_markerItem)
                ->setPolygon(TriangleMarker::polygon(m_markerRect.x(), m_markerRect.y(),
                                                     m_markerRect.width(), m_markerRect.height()));
        break;
    }
    case LegendMarkerItem::TypeStar: {
        static_cast<QGraphicsPolygonItem *>(m_markerItem)
                ->setPolygon(StarMarker::polygon(m_markerRect.x(), m_markerRect.y(),
                                                 m_markerRect.width(), m_markerRect.height()));
        break;
    }
    case LegendMarkerItem::TypePentagon: {
        static_cast<QGraphicsPolygonItem *>(m_markerItem)
                ->setPolygon(PentagonMarker::polygon(m_markerRect.x(), m_markerRect.y(),
                                                     m_markerRect.width(), m_markerRect.height()));
        break;
    }
#endif
    default: {
        qreal y = m_markerRect.height() / 2.0;
        QLineF line(0.0, y, m_markerRect.width(), y);
        static_cast<QGraphicsLineItem *>(m_markerItem)->setLine(line);
        break;
    }
    }
}

bool LegendMarkerItem::useMaxWidth() const
{
    return (m_marker->m_legend->alignment() == Qt::AlignLeft
            || m_marker->m_legend->alignment() == Qt::AlignRight);
}

QT_END_NAMESPACE

#include "moc_legendmarkeritem_p.cpp"
