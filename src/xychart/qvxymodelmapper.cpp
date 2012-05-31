#include "qvxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

QVXYModelMapper::QVXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Vertical);
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
