#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QBarSet::QBarSet()
{
}

void QBarSet::setName(QString name)
{
    mName = name;
}
QString QBarSet::name()
{
    return mName;
}

QBarSet& QBarSet::operator << (const qreal &value)
{
    mValues.append(value);
    return *this;
}

int QBarSet::count()
{
    return mValues.count();
}

qreal QBarSet::valueAt(int index)
{
    return mValues.at(index);
}


QTCOMMERCIALCHART_END_NAMESPACE
