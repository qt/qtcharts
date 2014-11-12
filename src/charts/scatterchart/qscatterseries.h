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

#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/qxyseries.h>

QT_CHARTS_BEGIN_NAMESPACE

class QScatterSeriesPrivate;

class QT_CHARTS_EXPORT QScatterSeries : public QXYSeries
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(MarkerShape markerShape READ markerShape WRITE setMarkerShape)
    Q_PROPERTY(qreal markerSize READ markerSize WRITE setMarkerSize)
    Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
    Q_ENUMS(MarkerShape)

public:
    enum MarkerShape {
        MarkerShapeCircle,
        MarkerShapeRectangle
    };

public:
    explicit QScatterSeries(QObject *parent = 0);
    ~QScatterSeries();
    QAbstractSeries::SeriesType type() const;
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    QBrush brush() const;
    void setColor(const QColor &color);
    QColor color() const;
    void setBorderColor(const QColor &color);
    QColor borderColor() const;
    MarkerShape markerShape() const;
    void setMarkerShape(MarkerShape shape);
    qreal markerSize() const;
    void setMarkerSize(qreal size);

Q_SIGNALS:
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    friend class ScatterChartItem;
};

QT_CHARTS_END_NAMESPACE

#endif // QSCATTERSERIES_H
