#ifndef QBARMODELMAPPER_H
#define QBARMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarModelMapper : public QObject
{
    Q_OBJECT
public:
    explicit QBarModelMapper(QObject *parent = 0);
    
    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int mapBarBottom() const;
    void setMapBarBottom(int mapBarBottom);

    int mapBarTop() const;
    void setMapBarTop(int mapBarTop);

    int mapCategories() const;
    void setMapCategories(int mapCategories);

    void reset();

Q_SIGNALS:
    void updated();

private:
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_mapBarBottom;
    int m_mapBarTop;
    int m_mapCategories;
    
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARMODELMAPPER_H
