#ifndef QVBARMODELMAPPER_H
#define QVBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarSetColumn READ firstBarSetColumn WRITE setFirstBarSetColumn)
    Q_PROPERTY(int lastBarSetColumn READ lastBarSetColumn WRITE setLastBarSetColumn)
    Q_PROPERTY(int categoriesColumn READ categoriesColumn WRITE setCategoriesColumn)

public:
    explicit QVBarModelMapper(QObject *parent = 0);

    int firstBarSetColumn() const;
    void setFirstBarSetColumn(int firstBarSetColumn);

    int lastBarSetColumn() const;
    void setLastBarSetColumn(int lastBarSetColumn);

    int categoriesColumn() const;
    void setCategoriesColumn(int categoriesColumn);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVBARMODELMAPPER_H
