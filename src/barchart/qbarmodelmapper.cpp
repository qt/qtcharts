#include "qbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarModelMapper::QBarModelMapper(QObject *parent) :
    QObject(parent),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_mapBarBottom(-1),
    m_mapBarTop(-1),
    m_mapCategories(-1)
{
}

int QBarModelMapper::first() const
{
    return m_first;
}

void QBarModelMapper::setFirst(int first)
{
    m_first = qMax(first, 0);
    emit updated();
}

int QBarModelMapper::count() const
{
    return m_count;
}

void QBarModelMapper::setCount(int count)
{
    m_count = qMax(count, -1);
    emit updated();
}

Qt::Orientation QBarModelMapper::orientation() const
{
    return m_orientation;
}

void QBarModelMapper::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
    emit updated();
}

int QBarModelMapper::mapBarBottom() const
{
    return m_mapBarBottom;
}

void QBarModelMapper::setMapBarBottom(int mapValues)
{
    m_mapBarBottom = mapValues;
    emit updated();
}

int QBarModelMapper::mapBarTop() const
{
    return m_mapBarTop;
}

void QBarModelMapper::setMapBarTop(int mapLabels)
{
    m_mapBarTop = mapLabels;
    emit updated();
}

int QBarModelMapper::mapCategories() const
{
    return m_mapCategories;
}

void QBarModelMapper::setMapCategories(int mapCategories)
{
    m_mapCategories = mapCategories;
    emit updated();
}

void QBarModelMapper::reset()
{
    m_first = 0;
    m_count = -1;
    m_orientation = Qt::Vertical;
    m_mapBarBottom = -1;
    m_mapBarTop = -1;
    m_mapCategories = -1;
    emit updated();
}

#include "moc_qbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
