#include "xyplotdomain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYPlotDomain::XYPlotDomain():
m_ticksX(0),
m_ticksY(0),
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0)
{

}

XYPlotDomain::~XYPlotDomain()
{
	// TODO Auto-generated destructor stub
}

qreal XYPlotDomain::spanX() const
{
	Q_ASSERT(m_maxX >= m_minX);
	return m_maxX - m_minX;
}

qreal XYPlotDomain::spanY() const
{
	Q_ASSERT(m_maxY >= m_minY);
	return m_maxY - m_minY;
}

QTCOMMERCIALCHART_END_NAMESPACE
