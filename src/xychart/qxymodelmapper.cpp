#include "qxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QXYModelMapper::QXYModelMapper(QObject *parent):
    QObject(parent),
    m_first(0),
    m_count(-1),
    m_orientation(Qt::Vertical),
    m_xSection(-1),
    m_ySection(-1)
{
}

int QXYModelMapper::first() const
{
    return m_first;
}

void QXYModelMapper::setFirst(int first)
{
    m_first = qMax(first, 0);
//    emit updated();
}

int QXYModelMapper::count() const
{
    return m_count;
}

void QXYModelMapper::setCount(int count)
{
    m_count = qMax(count, -1);
//    emit updated();
}

Qt::Orientation QXYModelMapper::orientation() const
{
    return m_orientation;
}

void QXYModelMapper::setOrientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
//    emit updated();
}

int QXYModelMapper::xSection() const
{
    return m_xSection;
}

void QXYModelMapper::setXSection(int xSection)
{
    m_xSection = xSection;
//    emit updated();
}

int QXYModelMapper::ySection() const
{
    return m_ySection;
}

void QXYModelMapper::setYSection(int ySection)
{
    m_ySection = ySection;
//    emit updated();
}

void QXYModelMapper::reset()
{
    m_first = 0;
    m_count = -1;
    m_orientation = Qt::Vertical;
    m_xSection = -1;
    m_ySection = -1;
}

#include "moc_qxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
