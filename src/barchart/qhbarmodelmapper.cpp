#include "qhbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHBarModelMapper
    \brief part of QtCommercial chart API.
    \mainclass

    Nothing here yet
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

int QHBarModelMapper::categoriesRow() const
{
    return QBarModelMapper::categoriesSection();
}

void QHBarModelMapper::setCategoriesRow(int categoriesRow)
{
    return QBarModelMapper::setCategoriesSection(categoriesRow);
}

#include "moc_qhbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
