#ifndef CHART_OBJECT_INTERFACE_H
#define CHART_OBJECT_INTERFACE_H

#include "plotdomain_p.h"
#include <qchartglobal.h>
#include <QSize>

class QGraphicsItem;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartTheme;
class PlotDomain;

/*!
 * Internal abstract interface for passing updates on chart related properties.
 */
class ChartObjectInterface
{
public:
// TODO: move setSize and setPlotDomain back to ChartItem. This interface should be only about handling themes.
    virtual void setSize(const QSize &size) = 0;
    virtual void setTheme(ChartTheme *theme) = 0;
    virtual void setPlotDomain(const PlotDomain& data) = 0;
    // TODO: this is a hack; integration ongoing:
    virtual QGraphicsItem *graphicsItem() { return 0; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHART_OBJECT_INTERFACE_H
