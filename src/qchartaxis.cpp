
#include "qchartaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxis::QChartAxis(QObject* parent):QObject(parent),
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

void QChartAxis::setAxisPen(const QPen& pen)
{
    m_axisPen = pen;
}

void QChartAxis::setAxisBrush(const QBrush& brush)
{
    m_axisBrush = brush;
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

#include "moc_qchartaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
