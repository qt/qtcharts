#ifndef QSCATTERSERIESPRIVATE_H
#define QSCATTERSERIESPRIVATE_H

#include "qchartseries.h"
#include "charttheme_p.h"
#include "chartitem_p.h"
#include "plotdomain_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
 * The PIMPL class of QScatterSeries.
 */
class QScatterSeriesPrivate : public ChartItem
{
public:
    QScatterSeriesPrivate(QGraphicsItem *parent);

public: // from ChartObjectInterface
    void setSize(const QSizeF &size);
    void setPlotDomain(const PlotDomain& data);

public: // from ChartThemeObserver
    void themeChanged(ChartTheme *theme);

public: // from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    void changeGeometry();

    QRectF m_boundingRect;
    // TODO: use the chart data class instead of list of x and y values?
    QList<qreal> m_x;
    QList<qreal> m_y;
    QList<qreal> m_scenex;
    QList<qreal> m_sceney;
    QColor m_markerColor;
    //SeriesTheme m_theme;
    PlotDomain m_visibleChartArea;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIESPRIVATE_H
