#include "qpieseries.h"
#include "piepresenter.h"
#include "pieslice.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPieSeries::QPieSeries(QObject *parent) :
    QChartSeries(parent),
    m_sizeFactor(1.0),
    m_position(PiePositionMaximized)
{
}

QPieSeries::~QPieSeries()
{

}

bool QPieSeries::setData(QList<qreal> data)
{
    QList<QPieSlice> slices;
    foreach (int value, data)
        slices << QPieSlice(value, QString::number(value));
    return set(slices);
}

bool QPieSeries::set(QList<QPieSlice> slices)
{
    if (!slices.count())
        return false;

    PieChangeSet changeSet;

    for (int i=slices.count(); i<m_slices.count(); i++)
        changeSet.m_removed << i;

    for (int i=0; i<slices.count(); i++) {
        if (i < m_slices.count())
            changeSet.m_changed << i;
        else
            changeSet.m_added << i;
    }

    m_slices = slices;
    emit changed(changeSet);
    return true;
}

bool QPieSeries::add(QList<QPieSlice> slices)
{
    if (!slices.count())
        return false;

    PieChangeSet changeSet;
    for (int i=0; i<slices.count(); i++)
        changeSet.m_added << m_slices.count() + i;

    m_slices += slices;
    emit changed(changeSet);
    return true;
}

bool QPieSeries::add(QPieSlice slice)
{
    return add(QList<QPieSlice>() << slice);
}

QPieSlice QPieSeries::slice(int index) const
{
    if ((index >= 0) && (index < m_slices.count()))
        return m_slices.at(index);
    return QPieSlice();
}

bool QPieSeries::update(int index, QPieSlice slice)
{
    if ((index >= 0) && (index < m_slices.count())) {
        m_slices[index] = slice;
        PieChangeSet changeSet;
        changeSet.m_changed << index;
        emit changed(changeSet);
        return true;
    }
    return false;
}

void QPieSeries::setSizeFactor(qreal factor)
{
    if (factor < 0.0)
        return;

    if (m_sizeFactor != factor) {
        m_sizeFactor = factor;
        emit sizeFactorChanged();
    }
}

void QPieSeries::setPosition(PiePosition position)
{
    if (m_position != position) {
        m_position = position;
        emit positionChanged();
    }
}

#include "moc_qpieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
