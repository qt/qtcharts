#include "qchartaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxis::QChartAxis():
m_axisVisible(true),
m_gridVisible(true),
m_labelsVisible(true),
m_shadesVisible(true)
{
    // TODO Auto-generated constructor stub

}

QChartAxis::~QChartAxis()
{
    // TODO Auto-generated destructor stub
}

void QChartAxis::setAxisPen(const QPen& pen)
{
    m_axisPen=pen;
}

void QChartAxis::setAxisVisible(bool visible)
{
    m_axisVisible=visible;
}

void QChartAxis::setGridVisible(bool visible)
{
    m_gridVisible=visible;
}

void QChartAxis::setGridPen(const QPen& pen)
{
    m_gridPen=pen;
}

void QChartAxis::setLabelsVisible(bool visible)
{
    m_labelsVisible=visible;
}

void QChartAxis::setLabelsPen(const QPen& pen)
{
    m_labelsPen=pen;
}

void QChartAxis::setLabelsBrush(const QBrush& brush)
{
    m_labelsBrush=brush;
}

void QChartAxis::setLabelsFont(const QFont& font)
{
    m_labelsFont=font;
}

void QChartAxis::setLabelsOrientation(LabelsOrientation orientation)
{
    m_labelsOrientation=orientation;
}

void QChartAxis::setShadesVisible(bool visible)
{
    m_shadesVisible=visible;
}

void QChartAxis::setShadesPen(const QPen& pen)
{
    m_shadesPen=pen;
}

void QChartAxis::setShadesBrush(const QBrush& brush)
{
    m_shadesBrush=brush;
}


QTCOMMERCIALCHART_END_NAMESPACE
