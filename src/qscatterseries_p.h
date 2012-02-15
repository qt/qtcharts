#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartglobal.h"
#include "qchartseries.h"
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate
{
public:
    QScatterSeriesPrivate();

public:
    QList<QPointF> m_data;
    QPen m_markerPen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIESPRIVATE_H
