#include "qsplineseries.h"

QSplineSeries::QSplineSeries(QObject *parent) :
    QObject(parent)
{
}

QSplineSeries& QSplineSeries::operator << (const QPointF &value)
{
    d->m_data.append(value);
    emit changed();
    return *this;
}
