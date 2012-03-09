#ifndef CHARTANIMATION_H_
#define CHARTANIMATION_H_

#include "qchartglobal.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimation: public QVariantAnimation
{
public:
    ChartAnimation(QObject* parent=0):QVariantAnimation(parent){};
};

QTCOMMERCIALCHART_END_NAMESPACE



#endif /* AXISITEM_H_ */
