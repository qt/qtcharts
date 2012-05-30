#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarColumn READ firstBarColumn WRITE setFirstBarColumn)
    Q_PROPERTY(int lastBarColumn READ lastBarColumn WRITE setLastBarColumn)

public:
    explicit QVBarModelMapper(QObject *parent = 0);

    int firstBarColumn() const;
    void setFirstBarColumn(int firstBarColumn);

    int lastBarColumn() const;
    void setLastBarColumn(int lastBarColumn);

    int categoriesColumn() const;
    void setCategoriesColumn(int categoriesColumn);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
