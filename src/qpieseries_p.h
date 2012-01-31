#ifndef PIESERIESPRIVATE_H
#define PIESERIESPRIVATE_H

#include "chartobjectinterface_p.h"
#include "qpieseries.h"
#include <QRectF>
#include <QColor>

class QGraphicsItem;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieSlice;

class QPieSeriesPrivate : public ChartObjectInterface
{
public:
    // TODO: use a generic data class instead of x and y
    QPieSeriesPrivate();
    ~QPieSeriesPrivate();

public: // from ChartObjectInterface
    void setSize(const QSize &size);
    void setTheme(ChartTheme *theme);
    void setPlotDomain(const PlotDomain& data);

public:
    bool setData(QList<qreal> data);
    void resizeSlices(QRectF rect);
    QGraphicsItem *m_parentItem;
    QList<qreal> m_data;
    QList<PieSlice*> m_slices;
    QRectF m_chartSize;
    qreal m_sizeFactor;
    QPieSeries::PiePosition m_position;
    ChartTheme *m_chartTheme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIESPRIVATE_H
