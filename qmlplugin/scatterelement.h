#ifndef SCATTERELEMENT_H
#define SCATTERELEMENT_H

#include "qchartglobal.h"
#include <QObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ScatterElement : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX /*NOTIFY dataXChanged*/)
    Q_PROPERTY(qreal y READ y WRITE setY /*NOTIFY dataYChanged*/)

public:
    explicit ScatterElement(QObject *parent = 0);

    void setX(qreal x) {m_x = x;}
    qreal x() {return m_x;}
    void setY(qreal y) {m_y = y;}
    qreal y() {return m_y;}

public:
    qreal m_x;
    qreal m_y;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // SCATTERELEMENT_H
