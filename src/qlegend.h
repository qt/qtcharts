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
#include "private/scroller_p.h" //TODO fixme

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
class QSeries;
class QChart;

class QTCOMMERCIALCHART_EXPORT QLegend : public QGraphicsWidget
{
    Q_OBJECT
public:

    // We only support these alignments (for now)
    enum Alignment {
        AlignmentTop = Qt::AlignTop,
        AlignmentBottom = Qt::AlignBottom,
        AlignmentLeft = Qt::AlignLeft,
        AlignmentRight = Qt::AlignRight
    };

    Q_DECLARE_FLAGS(Alignments, Alignment)

private:
    explicit QLegend(QChart *chart);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;

    void setBrush(const QBrush &brush);
    QBrush brush() const;

    void setPen(const QPen &pen);
    QPen pen() const;

    void setAlignmnent(QLegend::Alignments alignment);
    QLegend::Alignments alignment() const;


    void detachFromChart();
    void attachToChart();
    bool isAttachedToChart();

    qreal minWidht() const { return m_minWidth;}
    qreal minHeight() const { return m_minHeight;}

    void setBackgroundVisible(bool visible);
    bool isBackgroundVisible() const;

    void setOffset(const QPointF& point);
    QPointF offset() const;

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

public Q_SLOTS:
    // PIMPL --->
    void handleSeriesAdded(QSeries *series, Domain *domain);
    void handleSeriesRemoved(QSeries *series);
    void handleAdded(QList<QPieSlice *> slices);
    void handleRemoved(QList<QPieSlice *> slices);
    // PIMPL <---

private:
    // PIMPL --->
    void appendMarkers(QAreaSeries *series);
    void appendMarkers(QXYSeries *series);
    void appendMarkers(QBarSeries *series);
    void appendMarkers(QPieSeries *series);
    void deleteMarkers(QSeries *series);




private Q_SLOTS:
    void updateLayout();

private:
    qreal m_margin;

    QRectF m_rect;
    qreal m_offsetX;
    qreal m_offsetY;

    //QList<LegendMarker *> m_markers;

    QBrush m_brush;
    QPen m_pen;
    QLegend::Alignments m_alignment;
    QGraphicsItemGroup* m_markers;


    bool m_attachedToChart;

    QChart *m_chart;
    qreal m_minWidth;
    qreal m_minHeight;
    qreal m_width;
    qreal m_height;
    bool m_visible;
    bool m_dirty;
    friend class ScrolledQLegend;
    // <--- PIMPL
};

class ScrolledQLegend: public QLegend, public Scroller
{

public:
    ScrolledQLegend(QChart *chart):QLegend(chart)
    {
    }

    void setOffset(const QPointF& point)
    {
        QLegend::setOffset(point);
    }
    QPointF offset() const
    {
        return QLegend::offset();
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event){
        Scroller::mousePressEvent(event);
        //QLegend::mousePressEvent(event);
    }
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event){
        Scroller::mouseMoveEvent(event);
        //QLegend::mouseMoveEvent(event);
    }
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
        Scroller::mouseReleaseEvent(event);
        //QLegend::mouseReleaseEvent(event);
    }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QLEGEND_H
