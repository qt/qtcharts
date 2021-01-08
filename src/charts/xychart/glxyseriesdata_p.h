/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef GLXYSERIESDATA_H
#define GLXYSERIESDATA_H

#include <QtCore/QMap>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtGui/QVector3D>
#include <QtGui/QVector2D>
#include <QtGui/QMatrix4x4>

QT_CHARTS_BEGIN_NAMESPACE

class AbstractDomain;

struct GLXYSeriesData {
    QVector<float> array;
    bool dirty;
    QVector3D color;
    float width;
    QAbstractSeries::SeriesType type;
    QVector2D min;
    QVector2D delta;
    bool visible;
    QMatrix4x4 matrix;
public:
    GLXYSeriesData &operator=(const GLXYSeriesData &data) {
        array = data.array;
        dirty = data.dirty;
        color = data.color;
        width = data.width;
        type = data.type;
        min = data.min;
        delta = data.delta;
        visible = data.visible;
        matrix = data.matrix;
        return *this;
    }
};

typedef QMap<const QXYSeries *, GLXYSeriesData *> GLXYDataMap;

class Q_CHARTS_PRIVATE_EXPORT GLXYSeriesDataManager : public QObject
{
    Q_OBJECT

public:
    GLXYSeriesDataManager(QObject *parent = 0);
    ~GLXYSeriesDataManager();

    void setPoints(QXYSeries *series, const AbstractDomain *domain);

    void removeSeries(const QXYSeries *series);

    GLXYDataMap &dataMap() { return m_seriesDataMap; }

    // These functions are needed by qml side, so they must be inline
    bool mapDirty() const { return m_mapDirty; }
    void clearAllDirty() {
        m_mapDirty = false;
        foreach (GLXYSeriesData *data, m_seriesDataMap.values())
            data->dirty = false;
    }
    void handleAxisReverseChanged(const QList<QAbstractSeries *> &seriesList);

public Q_SLOTS:
    void cleanup();
    void handleSeriesPenChange();
    void handleSeriesOpenGLChange();
    void handleSeriesVisibilityChange();
    void handleScatterColorChange();
    void handleScatterMarkerSizeChange();

Q_SIGNALS:
    void seriesRemoved(const QXYSeries *series);

private:
    GLXYDataMap m_seriesDataMap;
    bool m_mapDirty;
};

QT_CHARTS_END_NAMESPACE

#endif
