#include "qhxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

/*!
    \property QHXYModelMapper::xRow
    \brief Defines which row of the model is kept in sync with the x values of the QXYSeries
    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHXYModelMapper::yRow
    \brief Defines which row of the model is kept in sync with the  y values of the QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
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
