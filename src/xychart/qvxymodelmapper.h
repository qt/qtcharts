#ifndef QVXYMODELMAPPER_H
#define QVXYMODELMAPPER_H

#include <QXYModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QVXYModelMapper : public QXYModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int xColumn READ xColumn WRITE setXColumn)
    Q_PROPERTY(int yColumn READ yColumn WRITE setYColumn)

public:
    explicit QVXYModelMapper(QObject *parent = 0);
    
    int xColumn() const;
    void setXColumn(int xColumn);

    int yColumn() const;
    void setYColumn(int yColumn);
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QVXYMODELMAPPER_H
