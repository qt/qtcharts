#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarSet::QBarSet()
{
}

void QBarSet::setName(QString name)
{
    mName = name;
}

QBarSet& QBarSet::operator << (const qreal &value)
{
    mValues.append(value);
    return *this;
}

QTCOMMERCIALCHART_END_NAMESPACE
