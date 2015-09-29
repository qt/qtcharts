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
#include <QtGui/QVector3D>
#include <QtGui/QVector2D>

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
};

typedef QMap<const QXYSeries *, GLXYSeriesData *> GLXYDataMap;
typedef QMapIterator<const QXYSeries *, GLXYSeriesData *> GLXYDataMapIterator;

class GLXYSeriesDataManager : public QObject
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

public Q_SLOTS:
    void cleanup();
    void handleSeriesPenChange();
    void handleSeriesOpenGLChange();
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
