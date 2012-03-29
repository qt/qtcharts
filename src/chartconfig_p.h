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

#ifndef CHARTCONFIG_H_
#define CHARTCONFIG_H_

#include "qchartglobal.h"
#include "qchartversion_p.h"


QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartConfig {

private:
    ChartConfig(){
    #ifndef QT_NO_DEBUG
        qDebug()<<"buildTime" << buildTime;
        qDebug()<<"gitHead" << gitHead;
    #endif
        m_instance = this;
    }
public:
    static ChartConfig* instance(){
        if(!m_instance){
            m_instance= new ChartConfig();
        }
        return m_instance;
    }

    QString compilationTime(){
        return buildTime;
    }

    QString compilationHead(){
        return gitHead;
    }

private:
    static ChartConfig* m_instance;
};


ChartConfig* ChartConfig::m_instance=0;

#endif

QTCOMMERCIALCHART_END_NAMESPACE
