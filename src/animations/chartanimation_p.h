#ifndef CHARTANIMATION_H_
#define CHARTANIMATION_H_

#include "qchartglobal.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimation: public QVariantAnimation
{
public:
    enum Animation { LineDrawAnimation, MoveDownAnimation, MoveUpAnimation };
    ChartAnimation(QObject* parent=0):QVariantAnimation(parent), m_type(MoveDownAnimation){}
    void setAnimationType(Animation type){
        m_type=type;
    }
protected:
    Animation m_type;

};

QTCOMMERCIALCHART_END_NAMESPACE



#endif /* AXISITEM_H_ */
