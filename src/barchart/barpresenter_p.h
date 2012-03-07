#ifndef BARPRESENTER_H
#define BARPRESENTER_H

#include "qchartglobal.h"
#include "barpresenterbase_p.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarSeries;

// Presenter for parallel bars. Grouping of bars is done on category basis.
class BarPresenter : public BarPresenterBase
{
    Q_OBJECT
public:
    explicit BarPresenter(QBarSeries *series, QChart *parent = 0);

private:

    // From BarPresenterBase
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:
    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARPRESENTER_H
