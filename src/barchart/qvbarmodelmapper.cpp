#include "qvbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QVBarModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
*/

/*!
    \property QVBarModelMapper::firstBarSetColumn
    \brief Defines which column of the model is used as the data source for the first bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    \property QVBarModelMapper::lastBarSetColumn
    \brief Defines which column of the model is used as the data source for the last bar set

    Default value is: -1 (invalid mapping)
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QVBarModelMapper::QVBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Vertical);
}

int QVBarModelMapper::firstBarSetColumn() const
{
    return QBarModelMapper::firstBarSetSection();
}

void QVBarModelMapper::setFirstBarSetColumn(int firstBarSetColumn)
{
    return QBarModelMapper::setFirstBarSetSection(firstBarSetColumn);
}

int QVBarModelMapper::lastBarSetColumn() const
{
    return QBarModelMapper::lastBarSetSection();
}

void QVBarModelMapper::setLastBarSetColumn(int lastBarSetColumn)
{
    return QBarModelMapper::setLastBarSetSection(lastBarSetColumn);
}

#include "moc_qvbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
