/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <qchartglobal.h>
#include <qxyseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QXYSeries
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(MarkerShape markerShape READ markerShape WRITE setMarkerShape)
    Q_PROPERTY(qreal markerSize READ markerSize WRITE setMarkerSize)
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

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
