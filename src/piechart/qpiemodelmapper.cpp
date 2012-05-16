#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieModelMapper::QPieModelMapper(QObject *parent) :
    QObject(parent),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_mapValues(-1),
    m_mapLabels(-1)
{
}

int QPieModelMapper::first() const
{
    return m_first;
}

void QPieModelMapper::setFirst(int first)
{
    m_first = qMax(first, 0);
    emit updated();
}

int QPieModelMapper::count() const
{
    return m_count;
}

void QPieModelMapper::setCount(int count)
{
    m_count = qMax(count, -1);
    emit updated();
}

Qt::Orientation QPieModelMapper::orientation() const
{
    return m_orientation;
}

void QPieModelMapper::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
    emit updated();
}

int QPieModelMapper::mapValues() const
{
    return m_mapValues;
}

void QPieModelMapper::setMapValues(int mapValues)
{
    m_mapValues = mapValues;
    emit updated();
}

int QPieModelMapper::mapLabels() const
{
    return m_mapLabels;
}

void QPieModelMapper::setMapLabels(int mapLabels)
{
    m_mapLabels = mapLabels;
    emit updated();
}

void QPieModelMapper::reset()
{
    m_first = 0;
    m_count = -1;
    m_orientation = Qt::Vertical;
    m_mapValues = -1;
    m_mapLabels = -1;
    emit updated();
}

#include "moc_qpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
