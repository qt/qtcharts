// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <private/xychart_p.h>
#include <QtCharts/QXYSeries>
#include <private/qxyseries_p.h>
#include <private/chartpresenter_p.h>
#include <private/abstractdomain_p.h>
#include <private/chartdataset_p.h>
#include <private/glxyseriesdata_p.h>
#include <QtCharts/QXYModelMapper>
#include <private/qabstractaxis_p.h>
#include <QtGui/QPainter>
#include <QtCore/QAbstractItemModel>


QT_BEGIN_NAMESPACE

XYChart::XYChart(QXYSeries *series, QGraphicsItem *item):
      ChartItem(series->d_func(),item),
      m_series(series),
      m_animation(0),
      m_dirty(true)
{
    connect(series->d_func(), &QXYSeriesPrivate::seriesUpdated,
            this, &XYChart::handleSeriesUpdated);
    connect(series, &QXYSeries::pointReplaced, this, &XYChart::handlePointReplaced);
    connect(series, &QXYSeries::pointsReplaced, this, &XYChart::handlePointsReplaced);
    connect(series, &QXYSeries::pointAdded, this, &XYChart::handlePointAdded);
    connect(series, &QXYSeries::pointRemoved, this, &XYChart::handlePointRemoved);
    connect(series, &QXYSeries::pointsRemoved, this, &XYChart::handlePointsRemoved);
    connect(this, &XYChart::clicked, series, &QXYSeries::clicked);
    connect(this, &XYChart::hovered, series, &QXYSeries::hovered);
    connect(this, &XYChart::pressed, series, &QXYSeries::pressed);
    connect(this, &XYChart::released, series, &QXYSeries::released);
    connect(this, &XYChart::doubleClicked, series, &QXYSeries::doubleClicked);
    connect(series, &QAbstractSeries::useOpenGLChanged, this, &XYChart::handleDomainUpdated);
}

void XYChart::setGeometryPoints(const QList<QPointF> &points)
{
    m_points = points;
}

void XYChart::setAnimation(XYAnimation *animation)
{
    m_animation = animation;
}

void XYChart::setDirty(bool dirty)
{
    m_dirty = dirty;
}

// Returns a list with same size as geometryPoints list, indicating
// the off grid status of points.
QList<bool> XYChart::offGridStatusVector()
{
    qreal minX = domain()->minX();
    qreal maxX = domain()->maxX();
    qreal minY = domain()->minY();
    qreal maxY = domain()->maxY();

    QList<bool> returnVector;
    returnVector.resize(m_points.size());
    // During remove animation series may have different number of points,
    // so ensure we don't go over the index. No need to check for zero points, this
    // will not be called in such a situation.
    const int seriesLastIndex = m_series->count() - 1;

    for (int i = 0; i < m_points.size(); i++) {
        const QPointF &seriesPoint = m_series->at(qMin(seriesLastIndex, i));
        if (seriesPoint.x() < minX
            || seriesPoint.x() > maxX
            || seriesPoint.y() < minY
            || seriesPoint.y() > maxY) {
            returnVector[i] = true;
        } else {
            returnVector[i] = false;
        }
    }
    return returnVector;
}

void XYChart::updateChart(const QList<QPointF> &oldPoints, const QList<QPointF> &newPoints,
                          int index)
{

    if (m_animation) {
        m_animation->setup(oldPoints, newPoints, index);
        m_points = newPoints;
        setDirty(false);
        presenter()->startAnimation(m_animation);
    } else {
        m_points = newPoints;
        updateGeometry();
    }
}

void XYChart::updateGlChart()
{
    dataSet()->glXYSeriesDataManager()->setPoints(m_series, domain());
    presenter()->updateGLWidget();
    updateGeometry();
}

// Doesn't update gl geometry, but refreshes the chart
void XYChart::refreshGlChart()
{
    if (presenter())
        presenter()->updateGLWidget();
}

//handlers

void XYChart::handlePointAdded(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        QList<QPointF> points;
        if (m_dirty || m_points.isEmpty()) {
            points = domain()->calculateGeometryPoints(m_series->points());
        } else {
            points = m_points;
            QPointF point =
                    domain()->calculateGeometryPoint(m_series->points().at(index), m_validData);
            if (!m_validData)
                m_points.clear();
            else
                points.insert(index, point);
        }
        updateChart(m_points, points, index);
    }
}

void XYChart::handlePointRemoved(int index)
{
    Q_ASSERT(index <= m_series->count());
    Q_ASSERT(index >= 0);

    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        QList<QPointF> points;
        if (m_dirty || m_points.isEmpty()) {
            points = domain()->calculateGeometryPoints(m_series->points());
        } else {
            points = m_points;
            points.remove(index);
        }
        updateChart(m_points, points, index);
    }
}

void XYChart::handlePointsRemoved(int index, int count)
{
    Q_ASSERT(index <= m_series->count());
    Q_ASSERT(index >= 0);

    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        QList<QPointF> points;
        if (m_dirty || m_points.isEmpty()) {
            points = domain()->calculateGeometryPoints(m_series->points());
        } else {
            points = m_points;
            points.remove(index, count);
        }
        updateChart(m_points, points, index);
    }
}

void XYChart::handlePointReplaced(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        QList<QPointF> points;
        if (m_dirty || m_points.isEmpty()) {
            points = domain()->calculateGeometryPoints(m_series->points());
        } else {
            QPointF point =
                    domain()->calculateGeometryPoint(m_series->points().at(index), m_validData);
            if (!m_validData)
                m_points.clear();
            points = m_points;
            if (m_validData)
                points.replace(index, point);
        }
        updateChart(m_points, points, index);
    }
}

void XYChart::handlePointsReplaced()
{
    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        // All the points were replaced -> recalculate
        QList<QPointF> points = domain()->calculateGeometryPoints(m_series->points());
        updateChart(m_points, points, -1);
    }
}

void XYChart::handleDomainUpdated()
{
    if (m_series->useOpenGL()) {
        updateGlChart();
    } else {
        if (isEmpty()) return;
        QList<QPointF> points = domain()->calculateGeometryPoints(m_series->points());
        updateChart(m_points, points);
    }
}

void XYChart::handleSeriesUpdated()
{
}

bool XYChart::isEmpty()
{
    return domain()->isEmpty() || m_series->points().isEmpty();
}

QPointF XYChart::matchForLightMarker(const QPointF &eventPos)
{
    if (m_series->lightMarker().isNull()
            && (m_series->selectedLightMarker().isNull()
                || m_series->selectedPoints().isEmpty()))
        return QPointF(qQNaN(), qQNaN()); // 0,0 could actually be in points()

    const bool useSelectedMarker = m_series->lightMarker().isNull();

    QList<QPointF> points;
    if (useSelectedMarker) {
        const auto selectedPoints = m_series->selectedPoints();
        for (const int &selectedPointIndex : selectedPoints)
            points << m_series->at(selectedPointIndex);
    } else {
        points = m_series->points();
    }

    for (const QPointF &dp : points) {
        bool ok;
        const QPointF gp = domain()->calculateGeometryPoint(dp, ok);
        if (ok) {
            // '+2' and '+4': There is an addRect for the (mouse-)shape
            // in LineChartItem::updateGeometry()
            // This has a margin of 1 to make sure a press in the icon will always be detected,
            // but as there is a bunch of 'translations' and therefore inaccuracies,
            // so it is necessary to increase that margin to 2
            // (otherwise you can click next to an icon, get a click event but not match it)
            QRectF r(gp.x() - (m_series->markerSize() / 2 + 2),
                     gp.y() - (m_series->markerSize() / 2 + 2),
                     m_series->markerSize() + 4, m_series->markerSize() + 4);

            if (r.contains(eventPos))
                return dp;
        }
    }
    return QPointF(qQNaN(), qQNaN()); // 0,0 could actually be in points()
}

QT_END_NAMESPACE

#include "moc_xychart_p.cpp"
