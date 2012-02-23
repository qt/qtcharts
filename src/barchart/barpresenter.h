#ifndef BARPRESENTER_H
#define BARPRESENTER_H

#include "qchartglobal.h"
#include "barpresenterbase.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarChartSeries;

// Presenter for parallel bars. Grouping of bars is done on category basis.
class BarPresenter : public BarPresenterBase
{
    Q_OBJECT
public:
    explicit BarPresenter(QBarChartSeries *series, QGraphicsItem *parent = 0);

private:

    // From BarPresenterBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:
    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARPRESENTER_H
