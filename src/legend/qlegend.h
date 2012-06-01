/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#ifndef QLEGEND_H
#define QLEGEND_H

#include <QChartGlobal>
#include <QGraphicsWidget>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain;
class LegendMarker;
class QPieSlice;
class QXYSeries;
class QBarSet;
class QBarSeries;
class QPieSeries;
class QAreaSeries;
class LegendScrollButton;
class QChart;
class QLegendPrivate;

class QTCOMMERCIALCHART_EXPORT QLegend : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment NOTIFY alignmentChanged)

private:
    explicit QLegend(QChart *chart);

public:
    ~QLegend();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void detachFromChart();
    void attachToChart();
    bool isAttachedToChart();

    qreal minWidth() const;
    qreal minHeight() const;

    void setBackgroundVisible(bool visible = true);
    bool isBackgroundVisible() const;

    void setOffset(const QPointF& point);
    QPointF offset() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

Q_SIGNALS:
    void alignmentChanged();

private:
    QScopedPointer<QLegendPrivate> d_ptr;
    Q_DISABLE_COPY(QLegend);
    friend class LegendScroller;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
