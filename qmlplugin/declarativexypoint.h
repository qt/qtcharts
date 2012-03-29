#ifndef DECLARATIVE_XY_POINT_H
#define DECLARATIVE_XY_POINT_H

#include "qchartglobal.h"
#include <QObject>
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativeXyPoint : public QObject, public QPointF
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX /*NOTIFY dataXChanged*/)
    Q_PROPERTY(qreal y READ y WRITE setY /*NOTIFY dataYChanged*/)

public:
    explicit DeclarativeXyPoint(QObject *parent = 0);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVE_XY_POINT_H
