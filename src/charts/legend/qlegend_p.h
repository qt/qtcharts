/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
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
#include <QtCharts/private/qchartglobal_p.h>

QT_BEGIN_NAMESPACE

class QChart;
class ChartPresenter;
class QAbstractSeries;
class LegendLayout;
class LegendMoveResizeHandler;
class QLegendMarker;

class Q_CHARTS_PRIVATE_EXPORT QLegendPrivate : public QObject
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
    qreal maxMarkerWidth() const;

    static QObject *relatedObject(const QLegendMarker *l);

public Q_SLOTS:
    void handleSeriesAdded(QAbstractSeries *series);
    void handleSeriesRemoved(QAbstractSeries *series);
    void handleSeriesVisibleChanged();
    void handleCountChanged();

private:
    // Internal helpers
    void insertMarkerHelper(QLegendMarker *marker);
    void addMarkers(const QList<QLegendMarker *> &markers);
    void removeMarkerHelper(QLegendMarker *marker);
    void removeMarkers(const QList<QLegendMarker *> &markers);
    void decorateMarker(QLegendMarker *marker);
    void decorateMarkers(const QList<QLegendMarker *> &markers);
    void updateToolTips();

private:
    QLegend *q_ptr;
    ChartPresenter *m_presenter;
    LegendLayout *m_layout;
    LegendMoveResizeHandler *m_resizer;
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
    bool m_showToolTips;
    bool m_interactive;
    QLegend::MarkerShape m_markerShape;

    QList<QLegendMarker *> m_markers;
    QList<QAbstractSeries *> m_series;

    QHash<QGraphicsItem *, QLegendMarker *> m_markerHash;

    friend class QLegend;
    friend class LegendMarkerItem;
    friend class LegendLayout;
    friend class QLegendMarkerPrivate;
    friend class LegendScroller;
    friend class LegendMoveResizeHandler;
};

QT_END_NAMESPACE

#endif
