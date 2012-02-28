#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Domain::Domain(qreal minX, qreal maxX, qreal minY, qreal maxY):
m_minX(minX),
m_maxX(maxX),
m_minY(minY),
m_maxY(maxY)
{
}

Domain::~Domain()
{
}

qreal Domain::spanX() const
{
	Q_ASSERT(m_maxX >= m_minX);
	return m_maxX - m_minX;
}

qreal Domain::spanY() const
{
	Q_ASSERT(m_maxY >= m_minY);
	return m_maxY - m_minY;
}

bool Domain::isEmpty() const
{
    return spanX()==0 || spanY()==0;
}

Domain Domain::subDomain(const QRectF& rect, qreal maxWidth,qreal maxHeight) const
{
  Domain domain;

  qreal dx = spanX() / maxWidth;
  qreal dy = spanY() / maxHeight;

  domain.m_minX = m_minX + dx * rect.left();
  domain.m_maxX = m_minX + dx * rect.right();
  domain.m_minY = m_maxY - dy * rect.bottom();
  domain.m_maxY = m_maxY - dy * rect.top();

  return domain;
}

bool operator== (const Domain &domain1, const Domain &domain2)
{
    return (domain1.m_maxX == domain2.m_maxX &&
            domain1.m_maxY == domain2.m_maxY &&
            domain1.m_minX == domain2.m_minX &&
            domain1.m_minY == domain2.m_minY);
}

bool operator!= (const Domain &domain1, const Domain &domain2)
{
    return !(domain1 == domain2);
}


QDebug operator<<(QDebug dbg, const Domain &domain)
{
    dbg.nospace() << "Domain("<<domain.m_minX<<','<<domain.m_maxX<<','<<domain.m_minY<<','<<domain.m_maxY<<')';
    return dbg.maybeSpace();
}

QTCOMMERCIALCHART_END_NAMESPACE
