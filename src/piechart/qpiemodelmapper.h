#ifndef QPIEMODELMAPPER_H
#define QPIEMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

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
    explicit QPieModelMapper(QObject *parent = 0);

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

Q_SIGNALS:
    void updated();

private:
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_mapValues;
    int m_mapLabels;
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_H
