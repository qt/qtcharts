#include "qhxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

QHXYModelMapper::QHXYModelMapper(QObject *parent) :
    QXYModelMapper(parent)
{
    QXYModelMapper::setOrientation(Qt::Horizontal);
}

int QHXYModelMapper::xRow() const
{
    return QXYModelMapper::xSection();
}

void QHXYModelMapper::setXRow(int xRow)
{
    return QXYModelMapper::setXSection(xRow);
}

int QHXYModelMapper::yRow() const
{
    return QXYModelMapper::ySection();
}

void QHXYModelMapper::setYRow(int yRow)
{
    return QXYModelMapper::setYSection(yRow);
}

#include "moc_qhxymodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
