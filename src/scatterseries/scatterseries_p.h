#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartglobal.h"
#include "qseries.h"
#include <QObject>
#include <QPen>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate : public QObject
{
    Q_OBJECT

public:
    QScatterSeriesPrivate(QObject *parent);
    void emitChanged();

Q_SIGNALS:
    // TODO: more finegrained signaling for performance reasons
    // (see for example QPieSeries implementation with change sets)
    void changed();

public:
    QList<QPointF> m_data;
    QPen m_markerPen;
    QBrush m_markerBrush;
    int m_markerShape;
    qreal m_markerSize;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIESPRIVATE_H
