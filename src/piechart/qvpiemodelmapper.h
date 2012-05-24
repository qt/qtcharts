#ifndef QVPIEMODELMAPPER_H
#define QVPIEMODELMAPPER_H

#include "qpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVPieModelMapper : public QPieModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int valuesColumn READ valuesColumn WRITE setValuesColumn)
    Q_PROPERTY(int labelsColumn READ labelsColumn WRITE setLabelsColumn)

public:
    explicit QVPieModelMapper(QObject *parent = 0);

    int valuesColumn() const;
    void setValuesColumn(int valuesColumn);

    int labelsColumn() const;
    void setLabelsColumn(int labelsColumn);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVPIEMODELMAPPER_H
