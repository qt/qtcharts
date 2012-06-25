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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LEGENDMARKER_P_H
#define LEGENDMARKER_P_H

#include "qchartglobal.h"
#include <QGraphicsObject>
#include <QBrush>
#include <QPen>
#include <QGraphicsSimpleTextItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractSeries;
class QAreaSeries;
class QXYSeries;
class QBarSet;
class QBarSeries;
class QPieSlice;
class QLegend;
class QPieSeries;

class LegendMarker : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit LegendMarker(QAbstractSeries *m_series, QLegend *parent);

    void setPen(const QPen &pen);
    QPen pen() const;
    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setFont(const QFont &font);
    QFont font() const;

    void setSize(const QSize& size);

    void setLabel(const QString label);
    QString label() const;
    void setLabelBrush(const QBrush &brush);
    QBrush labelBrush() const;
    void setLabelPen(const QPen &pen);
    QPen labelPen() const;

    QAbstractSeries *series() const { return m_series;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    QRectF boundingRect() const;

    void updateLayout();

protected:
    // From QGraphicsObject
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public Q_SLOTS:
    virtual void updated() = 0;

protected:
    QAbstractSeries *m_series;
    QRectF m_markerRect;
    QRectF m_boundingRect;
    QLegend* m_legend;
    QGraphicsSimpleTextItem *m_textItem;
    QGraphicsRectItem *m_rectItem;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class XYLegendMarker : public LegendMarker
{
public:
    XYLegendMarker(QXYSeries *series, QLegend *legend);
protected:
    void updated();
private:
    QXYSeries *m_series;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AreaLegendMarker : public LegendMarker
{
public:
    AreaLegendMarker(QAreaSeries *series, QLegend *legend);
protected:
    void updated();
private:
    QAreaSeries *m_series;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class BarLegendMarker : public LegendMarker
{
public:
    BarLegendMarker(QBarSeries *barseries, QBarSet *barset,QLegend *legend);
protected:
    void updated();
private:
    QBarSet *m_barset;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PieLegendMarker : public LegendMarker
{
public:
    PieLegendMarker(QPieSeries *pieSeries, QPieSlice *pieslice, QLegend *legend);
protected:
    void updated();
private:
    QPieSlice *m_pieslice;
};

QTCOMMERCIALCHART_END_NAMESPACE
#endif // LEGENDMARKER_P_H
