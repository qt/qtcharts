#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartseries.h"
#include "charttheme_p.h"
#include "chartitemcontrol.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate : public QGraphicsItem, public ChartItemControl
{
public:
    QScatterSeriesPrivate(QGraphicsItem *parent);

public: // from QGraphicsItem
    void setPos(const QPointF & pos);
    void resize(QRectF rect);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public: // from ChartItemControl
    void resize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

public:
    // TODO: use the chart data class instead of list of x and y values?
    QList<qreal> m_x;
    QList<qreal> m_y;
    qreal m_scalex;
    qreal m_scaley;
    QList<qreal> m_scenex;
    QList<qreal> m_sceney;
    QColor m_markerColor;
    SeriesTheme m_theme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIESPRIVATE_H
