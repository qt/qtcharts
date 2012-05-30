#ifndef QHBARMODELMAPPER_H
#define QHBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarRow READ firstBarRow WRITE setFirstBarRow)
    Q_PROPERTY(int lastBarRow READ lastBarRow WRITE setLastBarRow)

public:
    explicit QHBarModelMapper(QObject *parent = 0);

    int firstBarRow() const;
    void setFirstBarRow(int firstBarRow);

    int lastBarRow() const;
    void setLastBarRow(int lastBarRow);

    int categoriesRow() const;
    void setCategoriesRow(int categoriesRow);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHBARMODELMAPPER_H
