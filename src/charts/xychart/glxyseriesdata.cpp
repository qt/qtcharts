/****************************************************************************
 **
 ** Copyright (C) 2015 The Qt Company Ltd
 ** All rights reserved.
 ** For any questions to The Qt Company, please use contact form at http://qt.io
 **
 ** This file is part of the Qt Charts module.
 **
 ** Licensees holding valid commercial license for Qt may use this file in
 ** accordance with the Qt License Agreement provided with the Software
 ** or, alternatively, in accordance with the terms contained in a written
 ** agreement between you and The Qt Company.
 **
 ** If you have questions regarding the use of this file, please use
 ** contact form at http://qt.io
 **
 ****************************************************************************/

#include "private/glxyseriesdata_p.h"
#include "private/abstractdomain_p.h"
#include <QtCharts/QScatterSeries>

QT_CHARTS_BEGIN_NAMESPACE

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
        QColor sc;
        if (data->type == QAbstractSeries::SeriesTypeScatter) {
            QScatterSeries *scatter = static_cast<QScatterSeries *>(series);
            data->width = float(scatter->markerSize());
            sc = scatter->color(); // Scatter overwrites color property
        } else {
            data->width = float(series->pen().widthF());
            sc = series->color();
        }
        data->color = QVector3D(float(sc.redF()), float(sc.greenF()), float(sc.blueF()));
        connect(series, &QXYSeries::penChanged, this,
                &GLXYSeriesDataManager::handleSeriesPenChange);
        connect(series, &QXYSeries::useOpenGLChanged, this,
                &GLXYSeriesDataManager::handleSeriesOpenGLChange);
        m_seriesDataMap.insert(series, data);
        m_mapDirty = true;
    }
    QVector<float> &array = data->array;

    bool logAxis = false;
    foreach (QAbstractAxis* axis, series->attachedAxes()) {
        if (axis->type() == QAbstractAxis::AxisTypeLogValue) {
            logAxis = true;
            break;
        }
    }

    int count = series->count();
    int index = 0;
    array.resize(count * 2);
    if (logAxis) {
        // Use domain to resolve geometry points. Not as fast as shaders, but simpler that way
        QVector<QPointF> geometryPoints = domain->calculateGeometryPoints(series->pointsVector());
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
        // Regular value axes, so we can do the math easily on shaders.
        QVector<QPointF> seriesPoints = series->pointsVector();
        for (int i = 0; i < count; i++) {
            const QPointF &point = seriesPoints.at(i);
            array[index++] = float(point.x());
            array[index++] = float(point.y());
        }
        data->min = QVector2D(domain->minX(), domain->minY());
        data->delta = QVector2D((domain->maxX() - domain->minX()) / 2.0f,
                                (domain->maxY() - domain->minY()) / 2.0f);
    }
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
        }
    }
}

void GLXYSeriesDataManager::handleSeriesOpenGLChange()
{
    QXYSeries *series = qobject_cast<QXYSeries *>(sender());
    if (!series->useOpenGL())
        removeSeries(series);
}

QT_CHARTS_END_NAMESPACE
