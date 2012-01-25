#include "plotdomain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PlotDomain::PlotDomain():
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0)
{

}

PlotDomain::~PlotDomain()
{
	// TODO Auto-generated destructor stub
}

qreal PlotDomain::spanX() const
{
	Q_ASSERT(m_maxX >= m_minX);
	return m_maxX - m_minX;
}

qreal PlotDomain::spanY() const
{
	Q_ASSERT(m_maxY >= m_minY);
	return m_maxY - m_minY;
}

QTCOMMERCIALCHART_END_NAMESPACE
