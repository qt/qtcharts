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
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)
    Q_PROPERTY(bool backgroundVisible READ isBackgroundVisible WRITE setBackgroundVisible NOTIFY backgroundVisibleChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor labelColor READ labelColor WRITE setLabelColor NOTIFY labelColorChanged)
// TODO?
//    Q_PROPERTY(QColor labelBorderColor READ labelBorderColor WRITE setLabelBorderColor NOTIFY labelBorderColorChanged)

private:
    explicit QLegend(QChart *chart);

public:
    ~QLegend();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

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
    void setLabelPen(const QPen &pen);
    QPen labelPen() const;
    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;

    void setLabelColor(QColor color);
    QColor labelColor() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    void detachFromChart();
    void attachToChart();
    bool isAttachedToChart();

    qreal minWidth() const;
    qreal minHeight() const;

    void setBackgroundVisible(bool visible = true);
    bool isBackgroundVisible() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

Q_SIGNALS:
    void backgroundVisibleChanged(bool visible);
    void colorChanged(QColor color);
    void borderColorChanged(QColor color);
    void fontChanged(QFont font);
    void labelPenChanged(QPen pen);
    void labelBrushChanged(QBrush brush);
    void labelColorChanged(QColor color);
// TODO?
//    void labelBorderColorChanged(QColor color);

private:
    QScopedPointer<QLegendPrivate> d_ptr;
    Q_DISABLE_COPY(QLegend)
    friend class LegendScroller;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
