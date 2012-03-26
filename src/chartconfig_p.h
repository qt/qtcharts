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
