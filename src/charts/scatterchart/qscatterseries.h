// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/qxyseries.h>

QT_BEGIN_NAMESPACE

class QScatterSeriesPrivate;

class Q_CHARTS_EXPORT QScatterSeries : public QXYSeries
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(MarkerShape markerShape READ markerShape WRITE setMarkerShape NOTIFY markerShapeChanged)
    Q_PROPERTY(qreal markerSize READ markerSize WRITE setMarkerSize NOTIFY markerSizeChanged)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_ENUMS(MarkerShape)

public:
    enum MarkerShape {
        MarkerShapeCircle,
        MarkerShapeRectangle,
        MarkerShapeRotatedRectangle,
        MarkerShapeTriangle,
        MarkerShapeStar,
        MarkerShapePentagon
    };

public:
    explicit QScatterSeries(QObject *parent = nullptr);
    ~QScatterSeries();
    QAbstractSeries::SeriesType type() const override;
    void setPen(const QPen &pen) override;
    void setBrush(const QBrush &brush) override;
    QBrush brush() const;
    void setColor(const QColor &color) override;
    QColor color() const override;
    void setBorderColor(const QColor &color);
    QColor borderColor() const;
    MarkerShape markerShape() const;
    void setMarkerShape(MarkerShape shape);
    qreal markerSize() const;
    void setMarkerSize(qreal size);

Q_SIGNALS:
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void markerShapeChanged(MarkerShape shape);
    void markerSizeChanged(qreal size);

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    friend class ScatterChartItem;
};

QT_END_NAMESPACE

#endif // QSCATTERSERIES_H
