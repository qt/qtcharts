#ifndef QHXYMODELMAPPER_H
#define QHXYMODELMAPPER_H

#include <QXYModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHXYModelMapper : public QXYModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int xRow READ xRow WRITE setXRow)
    Q_PROPERTY(int yRow READ yRow WRITE setYRow)

public:
    explicit QHXYModelMapper(QObject *parent = 0);
    
    int xRow() const;
    void setXRow(int xRow);

    int yRow() const;
    void setYRow(int yRow);
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHXYMODELMAPPER_H
