#ifndef PERCENTBARPRESENTER_H
#define PERCENTBARPRESENTER_H

#include "chartitem_p.h"
#include "bar_p.h"
#include "qpercentbarseries.h"
#include "barpresenterbase.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarPresenter : public BarPresenterBase
{
    Q_OBJECT
public:
    PercentBarPresenter(QBarSeries *series, QGraphicsItem *parent = 0);

private:

    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARPRESENTER_H
