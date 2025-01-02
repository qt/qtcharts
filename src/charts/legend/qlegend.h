// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QLEGEND_H
#define QLEGEND_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsWidget>
#include <QtGui/QPen>
#include <QtGui/QBrush>

QT_BEGIN_NAMESPACE

class QChart;
class QLegendPrivate;
class QLegendMarker;
class QAbstractSeries;

class Q_CHARTS_EXPORT QLegend : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible NOTIFY backgroundVisibleChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)
    Q_PROPERTY(bool reverseMarkers READ reverseMarkers WRITE setReverseMarkers NOTIFY reverseMarkersChanged)
    Q_PROPERTY(bool showToolTips READ showToolTips WRITE setShowToolTips NOTIFY showToolTipsChanged)
    Q_PROPERTY(MarkerShape markerShape READ markerShape WRITE setMarkerShape NOTIFY markerShapeChanged)

private:
    explicit QLegend(QChart *chart);

public:
    enum MarkerShape {
        MarkerShapeDefault,
        MarkerShapeRectangle,
        MarkerShapeCircle,
        MarkerShapeFromSeries,
        MarkerShapeRotatedRectangle,
        MarkerShapeTriangle,
        MarkerShapeStar,
        MarkerShapePentagon
    };
    Q_ENUMS(MarkerShape)

    ~QLegend();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setColor(QColor color);
    QColor color();

    void setPen(const QPen &pen);
    QPen pen() const;
    void setBorderColor(QColor color);
    QColor borderColor();

    void setFont(const QFont &font);
    QFont font() const;
    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelColor(QColor color);
    QColor labelColor() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void detachFromChart();
    void attachToChart();
    bool isAttachedToChart();

    void setBackgroundVisible(bool visible = true);
    bool isBackgroundVisible() const;

    QList <QLegendMarker*> markers(QAbstractSeries *series = nullptr) const;

    bool reverseMarkers();
    void setReverseMarkers(bool reverseMarkers = true);

    bool showToolTips() const;
    void setShowToolTips(bool show);

    bool isInteractive() const;
    void setInteractive(bool interactive);

    MarkerShape markerShape() const;
    void setMarkerShape(MarkerShape shape);

protected:
    void hideEvent(QHideEvent *event) override;
    void showEvent(QShowEvent *event) override;

Q_SIGNALS:
    void backgroundVisibleChanged(bool visible);
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void fontChanged(QFont font);
    void labelColorChanged(QColor color);
    void reverseMarkersChanged(bool reverseMarkers);
    void showToolTipsChanged(bool showToolTips);
    void markerShapeChanged(MarkerShape shape);
    Q_REVISION(6, 2) void attachedToChartChanged(bool attachedToChart);
    void interactiveChanged(bool interactive);

private:
    QScopedPointer<QLegendPrivate> d_ptr;
    Q_DISABLE_COPY(QLegend)
    friend class LegendScroller;
    friend class LegendLayout;
    friend class LegendMoveResizeHandler;
    friend class ChartLayout;
    friend class LegendMarkerItem;
    friend class QLegendMarkerPrivate;
};

QT_END_NAMESPACE

#endif // QLEGEND_H
