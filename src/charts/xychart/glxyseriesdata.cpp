// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#undef QT_NO_FOREACH // this file contains unported legacy Q_FOREACH uses

#include "private/glxyseriesdata_p.h"
#include "private/abstractdomain_p.h"
#if QT_CONFIG(charts_scatter_chart)
#include <QtCharts/QScatterSeries>
#endif

QT_BEGIN_NAMESPACE

GLXYSeriesDataManager::GLXYSeriesDataManager(QObject *parent)
    : QObject(parent),
      m_mapDirty(false)
{
}

GLXYSeriesDataManager::~GLXYSeriesDataManager()
{
    cleanup();
}

void GLXYSeriesDataManager::setPoints(QXYSeries *series, const AbstractDomain *domain)
{
    GLXYSeriesData *data = m_seriesDataMap.value(series);
    if (!data) {
        data = new GLXYSeriesData;
        data->type = series->type();
        data->visible = series->isVisible();
        QColor sc;
#if QT_CONFIG(charts_scatter_chart)
        if (data->type == QAbstractSeries::SeriesTypeScatter) {
            QScatterSeries *scatter = static_cast<QScatterSeries *>(series);
            data->width = float(scatter->markerSize());
            sc = scatter->color(); // Scatter overwrites color property
            connect(scatter, &QScatterSeries::colorChanged, this,
                    &GLXYSeriesDataManager::handleScatterColorChange);
            connect(scatter, &QScatterSeries::markerSizeChanged, this,
                    &GLXYSeriesDataManager::handleScatterMarkerSizeChange);
        } else
#endif
        {
            data->width = float(series->pen().widthF());
            sc = series->color();
            connect(series, &QXYSeries::penChanged, this,
                    &GLXYSeriesDataManager::handleSeriesPenChange);
        }
        data->color = QVector3D(float(sc.redF()), float(sc.greenF()), float(sc.blueF()));
        connect(series, &QXYSeries::useOpenGLChanged, this,
                &GLXYSeriesDataManager::handleSeriesOpenGLChange);
        connect(series, &QXYSeries::visibleChanged, this,
                &GLXYSeriesDataManager::handleSeriesVisibilityChange);
        m_seriesDataMap.insert(series, data);
        m_mapDirty = true;
    }
    QList<float> &array = data->array;

    bool logAxis = false;
    bool reverseX = false;
    bool reverseY = false;
    const auto attached = series->attachedAxes();
    for (QAbstractAxis *axis : attached) {
        if (axis->type() == QAbstractAxis::AxisTypeLogValue) {
            logAxis = true;
            break;
        }
        if (axis->isReverse()) {
            if (axis->orientation() == Qt::Horizontal)
                reverseX = true;
            else
                reverseY = true;
            if (reverseX && reverseY)
                break;
        }
    }
    int count = series->count();
    int index = 0;
    array.resize(count * 2);
    QMatrix4x4 matrix;
    if (logAxis) {
        // Use domain to resolve geometry points. Not as fast as shaders, but simpler that way
        QList<QPointF> geometryPoints = domain->calculateGeometryPoints(series->points());
        const float height = domain->size().height();
        if (geometryPoints.size()) {
            for (int i = 0; i < count; i++) {
                const QPointF &point = geometryPoints.at(i);
                array[index++] = float(point.x());
                array[index++] = float(height - point.y());
            }
        } else {
            // If there are invalid log values, geometry points generation fails
            for (int i = 0; i < count; i++) {
                array[index++] = 0.0f;
                array[index++] = 0.0f;
            }
        }
        data->min = QVector2D(0, 0);
        data->delta = QVector2D(domain->size().width() / 2.0f, domain->size().height() / 2.0f);
    } else {
        // Regular value axes, so we can optimize it a bit.
        if (reverseX)
            matrix.scale(-1.0, 1.0);
        if (reverseY)
            matrix.scale(1.0, -1.0);

        const qreal mx = domain->minX();
        const qreal my = domain->minY();
        const qreal xd = domain->maxX() - mx;
        const qreal yd = domain->maxY() - my;

        if (!qFuzzyIsNull(xd) && !qFuzzyIsNull(yd)) {
            const QList<QPointF> seriesPoints = series->points();
            for (const QPointF &point : seriesPoints) {
                array[index++] = float((point.x() - mx) / xd);
                array[index++] = float((point.y() - my) / yd);
            }
        }
        data->min = QVector2D(0.0f, 0.0f);
        data->delta = QVector2D(0.5f, 0.5f);
    }
    data->matrix = matrix;
    data->dirty = true;
}

void GLXYSeriesDataManager::removeSeries(const QXYSeries *series)
{
    GLXYSeriesData *data = m_seriesDataMap.take(series);
    if (data) {
        disconnect(series, 0, this, 0);
        delete data;
        emit seriesRemoved(series);
        m_mapDirty = true;
    }
}

void GLXYSeriesDataManager::cleanup()
{
    foreach (GLXYSeriesData *data, m_seriesDataMap.values())
        delete data;
    m_seriesDataMap.clear();
    m_mapDirty = true;
    // Signal all series removal by using zero as parameter
    emit seriesRemoved(0);
}

void GLXYSeriesDataManager::handleSeriesPenChange()
{
    QXYSeries *series = qobject_cast<QXYSeries *>(sender());
    if (series) {
        GLXYSeriesData *data = m_seriesDataMap.value(series);
        if (data) {
            QColor sc = series->color();
            data->color = QVector3D(float(sc.redF()), float(sc.greenF()), float(sc.blueF()));
            data->width = float(series->pen().widthF());
            data->dirty = true;
        }
    }
}

void GLXYSeriesDataManager::handleSeriesOpenGLChange()
{
    QXYSeries *series = qobject_cast<QXYSeries *>(sender());
    if (!series->useOpenGL())
        removeSeries(series);
}

void GLXYSeriesDataManager::handleSeriesVisibilityChange()
{
    QXYSeries *series = qobject_cast<QXYSeries *>(sender());
    if (series) {
        GLXYSeriesData *data = m_seriesDataMap.value(series);
        if (data) {
            data->visible = series->isVisible();
            data->dirty = true;
        }
    }
}

#if QT_CONFIG(charts_scatter_chart)
void GLXYSeriesDataManager::handleScatterColorChange()
{
    QScatterSeries *series = qobject_cast<QScatterSeries *>(sender());
    if (series) {
        GLXYSeriesData *data = m_seriesDataMap.value(series);
        if (data) {
            QColor sc = series->color();
            data->color = QVector3D(float(sc.redF()), float(sc.greenF()), float(sc.blueF()));
            data->dirty = true;
        }
    }
}

void GLXYSeriesDataManager::handleScatterMarkerSizeChange()
{
    QScatterSeries *series = qobject_cast<QScatterSeries *>(sender());
    if (series) {
        GLXYSeriesData *data = m_seriesDataMap.value(series);
        if (data) {
            data->width =float(series->markerSize());
            data->dirty = true;
        }
    }
}
#endif

void GLXYSeriesDataManager::handleAxisReverseChanged(const QList<QAbstractSeries *> &seriesList)
{
    bool reverseX = false;
    bool reverseY = false;
    foreach (QAbstractSeries *series, seriesList) {
        if (QXYSeries *xyseries = qobject_cast<QXYSeries *>(series)) {
            GLXYSeriesData *data = m_seriesDataMap.value(xyseries);
            if (data) {
                foreach (QAbstractAxis* axis, xyseries->attachedAxes()) {
                    if (axis->isReverse()) {
                        if (axis->orientation() == Qt::Horizontal)
                            reverseX = true;
                        else
                            reverseY = true;
                    }
                    if (reverseX && reverseY)
                        break;
                }
                QMatrix4x4 matrix;
                if (reverseX)
                    matrix.scale(-1.0, 1.0);
                if (reverseY)
                    matrix.scale(1.0, -1.0);
                data->matrix = matrix;
                data->dirty = true;
            }
        }
    }
}

QT_END_NAMESPACE

