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

#ifndef QLEGEND_H
#define QLEGEND_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsWidget>
#include <QtGui/QPen>
#include <QtGui/QBrush>

QT_CHARTS_BEGIN_NAMESPACE

class QChart;
class QLegendPrivate;
class QLegendMarker;
class QAbstractSeries;

class QT_CHARTS_EXPORT QLegend : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible NOTIFY backgroundVisibleChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)
    Q_PROPERTY(bool reverseMarkers READ reverseMarkers WRITE setReverseMarkers NOTIFY reverseMarkersChanged)

private:
    explicit QLegend(QChart *chart);

public:
    ~QLegend();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

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

    QList <QLegendMarker*> markers(QAbstractSeries *series = 0) const;

    bool reverseMarkers();
    void setReverseMarkers(bool reverseMarkers = true);

protected:
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

Q_SIGNALS:
    void backgroundVisibleChanged(bool visible);
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void fontChanged(QFont font);
    void labelColorChanged(QColor color);
    void reverseMarkersChanged(bool reverseMarkers);

private:
    QScopedPointer<QLegendPrivate> d_ptr;
    Q_DISABLE_COPY(QLegend)
    friend class LegendScroller;
    friend class LegendLayout;
    friend class ChartLayout;
    friend class LegendMarkerItem;
    friend class QLegendMarkerPrivate;
};

QT_CHARTS_END_NAMESPACE

#endif // QLEGEND_H
