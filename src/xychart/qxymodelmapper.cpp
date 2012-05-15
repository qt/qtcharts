#include "qxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QXYModelMapper::QXYModelMapper(QObject *parent):
    QObject(parent),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_mapX(-1),
    m_mapY(-1)
{
}

int QXYModelMapper::first() const
{
    return m_first;
}

void QXYModelMapper::setFirst(int first)
{
    m_first = qMax(first, 0);
    emit updated();
}

int QXYModelMapper::count() const
{
    return m_count;
}

void QXYModelMapper::setCount(int count)
{
    m_count = qMax(count, -1);
    emit updated();
}

Qt::Orientation QXYModelMapper::orientation() const
{
    return m_orientation;
}

void QXYModelMapper::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
    emit updated();
}

int QXYModelMapper::mapX() const
{
    return m_mapX;
}

void QXYModelMapper::setMapX(int mapX)
{
    m_mapX = mapX;
    emit updated();
}

int QXYModelMapper::mapY() const
{
    return m_mapY;
}

void QXYModelMapper::setMapY(int mapY)
{
    m_mapY = mapY;
    emit updated();
}

void QXYModelMapper::reset()
{
    m_first = 0;
    m_count = -1;
    m_orientation = Qt::Vertical;
    m_mapX = -1;
    m_mapY = -1;
}

#include "moc_qxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
