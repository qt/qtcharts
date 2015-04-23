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

#include "xyseriesiodevice.h"
#include <QtCharts/QXYSeries>

XYSeriesIODevice::XYSeriesIODevice(QXYSeries * series, QObject *parent) :
    QIODevice(parent),
    m_series(series)
{
}

qint64 XYSeriesIODevice::readData(char * data, qint64 maxSize)
{
    Q_UNUSED(data)
    Q_UNUSED(maxSize)
    return -1;
}

qint64 XYSeriesIODevice::writeData(const char * data, qint64 maxSize)
{
    qint64 range = 2000;
    QList<QPointF> oldPoints = m_series->points();
    QList<QPointF> points;
    int resolution = 4;

    if (oldPoints.count() < range) {
        points = m_series->points();
    } else {
        for (int i = maxSize/resolution; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize/resolution, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize/resolution; k++)
        points.append(QPointF(k + size, ((quint8)data[resolution * k] - 128)/128.0));

    m_series->replace(points);
    return maxSize;
}
