#include "qpiemodelmapper_p.h"
#include "qvpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QVPieModelMapper::QVPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    QPieModelMapper::setOrientation(Qt::Vertical);
}

int QVPieModelMapper::valuesColumn() const
{
    return QPieModelMapper::valuesIndex();
}

void QVPieModelMapper::setValuesColumn(int valuesColumn)
{
    QPieModelMapper::setValuesIndex(valuesColumn);
}

int QVPieModelMapper::labelsColumn() const
{
    return QPieModelMapper::labelsIndex();
}

void QVPieModelMapper::setLabelsColumn(int labelsColumn)
{
    QPieModelMapper::setLabelsIndex(labelsColumn);
}

#include "moc_qvpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
