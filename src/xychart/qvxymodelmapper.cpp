#include "qvxymodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVXYModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

/*!
    \property QVXYModelMapper::xColumn
    \brief Defines which column of the model is kept in sync with the x values of QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QVXYModelMapper::yColumn
    \brief Defines which column of the model is kept in sync with the y values of QXYSeries

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
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
