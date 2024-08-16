// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef XYCHART_H
#define XYCHART_H

#include <QtCharts/QChartGlobal>
#include <private/chartitem_p.h>
#include <private/xyanimation_p.h>
#include <QtCharts/QValueAxis>
#include <QtCharts/QXYSeries>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtGui/QPen>

QT_BEGIN_NAMESPACE

class ChartPresenter;

class Q_CHARTS_EXPORT XYChart :  public ChartItem
{
    Q_OBJECT
public:
    explicit XYChart(QXYSeries *series,QGraphicsItem *item = 0);
    ~XYChart() {}

    void setGeometryPoints(const QList<QPointF> &points);
    QList<QPointF> geometryPoints() const { return m_points; }

    void setAnimation(XYAnimation *animation);
    ChartAnimation *animation() const override { return m_animation; }
    virtual void updateGeometry() = 0;

    bool isDirty() const { return m_dirty; }
    void setDirty(bool dirty);

    void getSeriesRanges(qreal &minX, qreal &maxX, qreal &minY, qreal &maxY);
    QList<bool> offGridStatusVector();

public Q_SLOTS:
    void handlePointAdded(int index);
    void handlePointRemoved(int index);
    void handlePointsRemoved(int index, int count);
    void handlePointReplaced(int index);
    void handlePointsReplaced();
    void handleDomainUpdated() override;

    virtual void handleSeriesUpdated();

Q_SIGNALS:
    void clicked(const QPointF &point);
    void hovered(const QPointF &point, bool state);
    void pressed(const QPointF &point);
    void released(const QPointF &point);
    void doubleClicked(const QPointF &point);

protected:
    virtual void updateChart(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints,
                             int index = -1);
    virtual void updateGlChart();
    virtual void refreshGlChart();

    QPointF matchForLightMarker(const QPointF &eventPos) const;

private:
    inline bool isEmpty();

protected:
    QPointF hoverPoint(const QPointF &eventPos) const;
    static bool fuzzyComparePointF(const QPointF &p1, const QPointF &p2);

    QXYSeries *m_series;
    QList<QPointF> m_points;
    QList<int> m_selectedPoints;
    QColor m_selectedColor;
    XYAnimation *m_animation;
    bool m_dirty;

    QHash<int, QHash<QXYSeries::PointConfiguration, QVariant>> m_pointsConfiguration;

    friend class AreaChartItem;
};

QT_END_NAMESPACE

#endif
