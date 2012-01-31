#ifndef CHARTITEMCONTROL_H
#define CHARTITEMCONTROL_H

#include "plotdomain_p.h"
#include <qchartglobal.h>
#include <QSize>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartTheme;
class PlotDomain;

class ChartItemControl
{
public:
    virtual void setPos (const QPointF & pos) = 0;
    virtual void resize(const QSize &size) = 0;
    virtual void setTheme(ChartTheme *theme) = 0;
    virtual void setPlotDomain(const PlotDomain& data) = 0;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // CHARTITEMCONTROL_H
