#include "qhbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHBarModelMapper::QHBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
}

int QHBarModelMapper::firstBarRow() const
{
    return QBarModelMapper::firstBarSection();
}

void QHBarModelMapper::setFirstBarRow(int firstBarRow)
{
    return QBarModelMapper::setFirstBarSection(firstBarRow);
}

int QHBarModelMapper::lastBarRow() const
{
    return QBarModelMapper::lastBarSection();
}

void QHBarModelMapper::setLastBarRow(int lastBarRow)
{
    return QBarModelMapper::setLastBarSection(lastBarRow);
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
