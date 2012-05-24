#include "qhpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QHPieModelMapper::QHPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    QPieModelMapper::setOrientation(Qt::Horizontal);
}

int QHPieModelMapper::valuesRow() const
{
    return QPieModelMapper::valuesIndex();
}

void QHPieModelMapper::setValuesRow(int valuesRow)
{
    QPieModelMapper::setValuesIndex(valuesRow);
}

int QHPieModelMapper::labelsRow() const
{
    return QPieModelMapper::labelsIndex();
}

void QHPieModelMapper::setLabelsRow(int labelsRow)
{
    QPieModelMapper::setLabelsIndex(labelsRow);
}

#include "moc_qhpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
