#include "qvxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QVXYModelMapper::QVXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
}

int QVXYModelMapper::xColumn() const
{
    return QXYModelMapper::xSection();
}

void QVXYModelMapper::setXColumn(int xColumn)
{
    return QXYModelMapper::setXSection(xColumn);
}

int QVXYModelMapper::yColumn() const
{
    return QXYModelMapper::ySection();
}

void QVXYModelMapper::setYColumn(int yColumn)
{
    return QXYModelMapper::setYSection(yColumn);
}

#include "moc_qvxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
