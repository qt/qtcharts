#include "qhbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHBarModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

/*!
    \property QHBarModelMapper::firstBarSetRow
    \brief Defines which column of the model is used as the data source for the first bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHBarModelMapper::lastBarSetRow
    \brief Defines which column of the model is used as the data source for the last bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHBarModelMapper::QHBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Horizontal);
}

int QHBarModelMapper::firstBarSetRow() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QHBarModelMapper::setFirstBarSetRow(int firstBarSetRow)
{
    return QBarModelMapper::setFirstBarSetSection(firstBarSetRow);
}

int QHBarModelMapper::lastBarSetRow() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QHBarModelMapper::setLastBarSetRow(int lastBarSetRow)
{
    return QBarModelMapper::setLastBarSetSection(lastBarSetRow);
}

#include "moc_qhbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
