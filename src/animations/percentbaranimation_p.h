//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef PERCENTBARANIMATION_P_H
#define PERCENTBARANIMATION_P_H

#include "chartanimation_p.h"
#include "abstractbaranimation_p.h"
#include "barchartitem_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PercentBarChartItem;
class QBarSet;
class BarSetAnimation;

class PercentBarAnimation : public AbstractBarAnimation
{
    Q_OBJECT
public:
    PercentBarAnimation(PercentBarChartItem *item);
    ~PercentBarAnimation();

    virtual QVariant interpolated(const QVariant &from, const QVariant &to, qreal progress) const;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PERCENTBARANIMATION_P_H
