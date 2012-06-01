#ifndef QHBARMODELMAPPER_H
#define QHBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarSetRow READ firstBarSetRow WRITE setFirstBarSetRow)
    Q_PROPERTY(int lastBarSetRow READ lastBarSetRow WRITE setLastBarSetRow)

public:
    explicit QHBarModelMapper(QObject *parent = 0);

    int firstBarSetRow() const;
    void setFirstBarSetRow(int firstBarSetRow);

    int lastBarSetRow() const;
    void setLastBarSetRow(int lastBarSetRow);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHBARMODELMAPPER_H
