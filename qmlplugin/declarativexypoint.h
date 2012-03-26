#ifndef DECLARATIVE_XY_POINT_H
#define DECLARATIVE_XY_POINT_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeXyPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX /*NOTIFY dataXChanged*/)
    Q_PROPERTY(qreal y READ y WRITE setY /*NOTIFY dataYChanged*/)

public:
    explicit DeclarativeXyPoint(QObject *parent = 0);

    void setX(qreal x) {m_x = x;}
    qreal x() {return m_x;}
    void setY(qreal y) {m_y = y;}
    qreal y() {return m_y;}

public:
    qreal m_x;
    qreal m_y;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_XY_POINT_H
