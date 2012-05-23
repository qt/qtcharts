#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapperPrivate;

class QTCOMMERCIALCHART_EXPORT QPieModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mapValues READ mapValues WRITE setMapValues)
    Q_PROPERTY(int mapLabels READ mapLabels WRITE setMapLabels)
    Q_PROPERTY(int first READ first WRITE setFirst)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_ENUMS(Qt::Orientation)

public:
    QPieModelMapper(QObject *parent = 0);

//    QAbstractItemModel* model() const;
//    void setModel(QAbstractItemModel *model);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int mapValues() const;
    void setMapValues(int mapValues);

    int mapLabels() const;
    void setMapLabels(int mapLabels);

    void reset();

private:
    QScopedPointer<QPieModelMapperPrivate> d_ptr;
    Q_DECLARE_PRIVATE(QPieModelMapper)
    friend class QPieSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
