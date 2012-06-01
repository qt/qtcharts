#ifndef QBARMODELMAPPER_H
#define QBARMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarModelMapperPrivate;
class QBarSeries;
class QChart;

class QTCOMMERCIALCHART_EXPORT QBarModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QBarSeries *series READ series WRITE setSeries)
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel)
    Q_PROPERTY(int first READ first WRITE setFirst)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_ENUMS(Qt::Orientation)

protected:
    explicit QBarModelMapper(QObject *parent = 0);

public:
    QAbstractItemModel* model() const;
    void setModel(QAbstractItemModel *model);

    QBarSeries* series() const;
    void setSeries(QBarSeries *series);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    void reset();

protected:
    int firstBarSetSection() const;
    void setFirstBarSetSection(int firstBarSetSection);

    int lastBarSetSection() const;
    void setLastBarSetSection(int lastBarSetSection);

    int categoriesSection() const;
    void setCategoriesSection(int categoriesSection);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);    

protected:
    QBarModelMapperPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QBarModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARMODELMAPPER_H
