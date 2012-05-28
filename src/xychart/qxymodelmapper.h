#ifndef QXYMODELMAPPER_H
#define QXYMODELMAPPER_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int xSection READ xSection WRITE setXSection)
    Q_PROPERTY(int ySection READ ySection WRITE setYSection)
    Q_PROPERTY(int first READ first WRITE setFirst)
    Q_PROPERTY(int count READ count WRITE setCount)
    Q_PROPERTY(Qt::Orientation orientation READ orientation WRITE setOrientation)
    Q_ENUMS(Qt::Orientation)

public:
    int first() const;
    void setFirst(int first);

    int count() const;
    void setCount(int count);

protected:
    explicit QXYModelMapper(QObject *parent = 0);

    Qt::Orientation orientation() const;
    void setOrientation(Qt::Orientation orientation);

    int xSection() const;
    void setXSection(int xSection);

    int ySection() const;
    void setYSection(int ySection);

    void reset();

Q_SIGNALS:
    void updated();

private:
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_xSection;
    int m_ySection;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QXYMODELMAPPER_H
