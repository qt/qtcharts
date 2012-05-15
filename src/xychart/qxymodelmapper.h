#ifndef QXYMODELMAPPER_H
#define QXYMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>
#include <Qt>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYModelMapper : public QObject
{
    Q_OBJECT

public:
    explicit QXYModelMapper(QObject *parent = 0);

    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int mapX() const;
    void setMapX(int mapX);

    int mapY() const;
    void setMapY(int mapY);

    void reset();

Q_SIGNALS:
    void updated();

private:
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_mapX;
    int m_mapY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYMODELMAPPER_H
