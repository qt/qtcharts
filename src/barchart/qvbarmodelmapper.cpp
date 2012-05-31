#include "qvbarmodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QVBarModelMapper::QVBarModelMapper(QObject *parent) :
    QBarModelMapper(parent)
{
    QBarModelMapper::setOrientation(Qt::Vertical);
}

int QVBarModelMapper::firstBarColumn() const
{
    return QBarModelMapper::firstBarSection();
}

void QVBarModelMapper::setFirstBarColumn(int firstBarColumn)
{
    return QBarModelMapper::setFirstBarSection(firstBarColumn);
}

int QVBarModelMapper::lastBarColumn() const
{
    return QBarModelMapper::lastBarSection();
}

void QVBarModelMapper::setLastBarColumn(int lastBarColumn)
{
    return QBarModelMapper::setLastBarSection(lastBarColumn);
}

int QVBarModelMapper::categoriesColumn() const
{
    return QBarModelMapper::categoriesSection();
}

void QVBarModelMapper::setCategoriesColumn(int categoriesColumn)
{
    return QBarModelMapper::setCategoriesSection(categoriesColumn);
}

#include "moc_qvbarmodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
