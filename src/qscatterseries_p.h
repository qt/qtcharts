#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartglobal.h"
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate
{
public:
    QScatterSeriesPrivate();

public:

    // TODO: use the chart data class instead of list of x and y values?
    QList<QPointF> m_data;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIESPRIVATE_H
