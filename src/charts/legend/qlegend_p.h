/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QLEGEND_P_H
#define QLEGEND_P_H

#include <QtCharts/QLegend>

QT_CHARTS_BEGIN_NAMESPACE

class QChart;
class ChartPresenter;
class QAbstractSeries;
class LegendLayout;
class QLegendMarker;

class QLegendPrivate : public QObject
{
    Q_OBJECT
public:
    QLegendPrivate(ChartPresenter *presenter, QChart *chart, QLegend *q);
    ~QLegendPrivate();

    void setOffset(const QPointF &offset);
    QPointF offset() const;
    int roundness(qreal size);

    QGraphicsItemGroup* items() { return m_items; }

    QList<QLegendMarker*> markers(QAbstractSeries *series = 0);

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleSeriesVisibleChanged();
    void handleCountChanged();

private:
    // Internal helpers
    void addMarkers(QList<QLegendMarker *> markers);
    void removeMarkers(QList<QLegendMarker *> markers);
    void decorateMarkers(QList<QLegendMarker *> markers);

private:
    QLegend *q_ptr;
    ChartPresenter *m_presenter;
    LegendLayout *m_layout;
    QChart *m_chart;
    QGraphicsItemGroup *m_items;
    Qt::Alignment m_alignment;
    QBrush m_brush;
    QPen m_pen;
    QFont m_font;
    QBrush m_labelBrush;

    qreal m_diameter;
    bool m_attachedToChart;
    bool m_backgroundVisible;
    bool m_reverseMarkers;

    QList<QLegendMarker *> m_markers;
    QList<QAbstractSeries *> m_series;

    QHash<QGraphicsItem *, QLegendMarker *> m_markerHash;

    friend class QLegend;
    friend class LegendMarkerItem;
    friend class LegendLayout;
    friend class QLegendMarkerPrivate;
    friend class LegendScroller;
};

QT_CHARTS_END_NAMESPACE

#endif
