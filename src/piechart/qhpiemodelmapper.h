#ifndef QHPIEMODELMAPPER_H
#define QHPIEMODELMAPPER_H

#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int valuesRow READ valuesRow WRITE setValuesRow)
    Q_PROPERTY(int labelsRow READ labelsRow WRITE setLabelsRow)

public:
    QHPieModelMapper(QObject *parent = 0);

    int valuesRow() const;
    void setValuesRow(int valuesRow);

    int labelsRow() const;
    void setLabelsRow(int labelsRow);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHPIEMODELMAPPER_H
