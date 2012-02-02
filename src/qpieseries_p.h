#ifndef PIESERIESPRIVATE_H
#define PIESERIESPRIVATE_H

#include "chartitem_p.h"
#include "charttheme_p.h"
#include "qpieseries.h"
#include <QRectF>
#include <QColor>

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieSlice;

class QPieSeriesPrivate : public ChartItem, public ChartThemeObserver
{
public:
    // TODO: use a generic data class instead of x and y
    QPieSeriesPrivate(QGraphicsItem *parent);
    ~QPieSeriesPrivate();

public: // from ChartItem
    void setSize(const QSizeF &size);
    void setPlotDomain(const PlotDomain& data);
    // This is a dummy QGraphicsItem; dummy implementation
    QRectF boundingRect() const { return parentItem()->boundingRect(); }
    // This is a dummy QGraphicsItem; no implementation
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) {}

public: // from ChartThemeObserver
    void themeChanged(ChartTheme *theme);

public:
    bool setData(QList<qreal> data);
    void resizeSlices(QRectF rect);
    QList<qreal> m_data;
    QList<PieSlice*> m_slices;
    QRectF m_chartSize;
    qreal m_sizeFactor;
    QPieSeries::PiePosition m_position;
    ChartTheme *m_chartTheme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIESPRIVATE_H
