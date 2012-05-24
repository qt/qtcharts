#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapperPrivate;
class QPieSeries;

class QTCOMMERCIALCHART_EXPORT QPieModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int valuesIndex READ valuesIndex WRITE setValuesIndex)
    Q_PROPERTY(int labelsIndex READ labelsIndex WRITE setLabelsIndex)
    Q_PROPERTY(int first READ first WRITE setFirst)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_ENUMS(Qt::Orientation)

public:
    QPieModelMapper(QObject *parent = 0);

    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QPieSeries* series() const;
    void setSeries(QPieSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int valuesIndex() const;
    void setValuesIndex(int valuesIndex);

    int labelsIndex() const;
    void setLabelsIndex(int labelsIndex);

    void reset();

protected:
    QPieModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QPieModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
