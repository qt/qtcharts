#include "declarativexypoint.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXyPoint::DeclarativeXyPoint(QObject *parent) :
    QObject(parent)
{
    setX(0.0);
    setY(0.0);
}

#include "moc_declarativexypoint.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
