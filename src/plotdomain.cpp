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

PlotDomain PlotDomain::subDomain(const QRect& rect, qreal maxWidth,qreal maxHeight) const
{
  PlotDomain domain;

  qreal dx = spanX() / maxWidth;
  qreal dy = spanY() / maxHeight;

  domain.m_minX = m_minX + dx * rect.left();
  domain.m_maxX = m_minX + dx * rect.right();
  domain.m_minY = m_maxY - dy * rect.bottom();
  domain.m_maxY = m_maxY - dy * rect.top();

  return domain;
}
QTCOMMERCIALCHART_END_NAMESPACE
