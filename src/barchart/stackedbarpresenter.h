#ifndef STACKEDBARPRESENTER_H
#define STACKEDBARPRESENTER_H

#include "barpresenterbase.h"
#include "qstackedbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarPresenter : public BarPresenterBase
{
    Q_OBJECT
public:
    StackedBarPresenter(QBarChartSeries *series, QGraphicsItem *parent = 0);

private:
    // From BarPresenterBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARPRESENTER_H
