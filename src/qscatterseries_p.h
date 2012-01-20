#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate : public QGraphicsItem
{
public:
    QScatterSeriesPrivate(QList<qreal> x, QList<qreal> y, QGraphicsItem *parent);

public: // from QGraphicsItem
    void resize(QRectF rect, qreal xscale, qreal yscale);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // TODO: use the chart data class instead of list of x and y values?
    QList<qreal> m_x;
    QList<qreal> m_y;
    QList<qreal> m_scenex;
    QList<qreal> m_sceney;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
