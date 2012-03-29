/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

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
