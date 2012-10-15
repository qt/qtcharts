#include "xyseriesiodevice.h"
#include <QXYSeries>

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
    qint64 range = 8000;
    QList<QPointF> oldPoints = m_series->points();
    QList<QPointF> points;

    if (oldPoints.count() < range) {
        points = m_series->points();
    } else {
        for (int i = maxSize; i < oldPoints.count(); i++)
            points.append(QPointF(i - maxSize, oldPoints.at(i).y()));
    }

    qint64 size = points.count();
    for (int k = 0; k < maxSize; k++)
        points.append(QPointF(k + size, (quint8)data[k]));

    m_series->replace(points);
    return maxSize;
}
