
#include "qchartaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxis::QChartAxis():
m_axisVisible(true),
m_girdVisible(true),
m_labelsVisible(true),
m_rowShadesVisible(true)
{
    // TODO Auto-generated constructor stub

}

QChartAxis::~QChartAxis()
{
    // TODO Auto-generated destructor stub
}

void QChartAxis::setAxisVisible(bool visible)
{
    m_axisVisible=visible;
}

void QChartAxis::setGridVisible(bool visible)
{
    m_girdVisible=visible;
}

void QChartAxis::setLabelsVisible(bool visible)
{
    m_labelsVisible=visible;
}

void QChartAxis::setRowShadesVisible(bool visible)
{
    m_rowShadesVisible=visible;
}



QTCOMMERCIALCHART_END_NAMESPACE
