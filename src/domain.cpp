#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

Domain::Domain(QObject* parent):QObject(parent),
m_minX(0),
m_maxX(0),
m_minY(0),
m_maxY(0),
m_tickXCount(5),
m_tickYCount(5)
{
}

Domain::~Domain()
{
}

void Domain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
	setRange(minX, maxX, minY, maxY, m_tickXCount, m_tickYCount);
}

void Domain::setRange(qreal minX, qreal maxX, qreal minY, qreal maxY, int tickXCount,int tickYCount)
{
	bool changed = false;

	if(m_minX!=minX || m_maxX!=maxX || m_tickXCount!=tickXCount)
	{
		 m_minX=minX;
		 m_maxX=maxX;
		 m_tickXCount=tickXCount;
		 changed=true;
		 emit rangeXChanged(minX,maxX, m_tickXCount);
	}

	if(m_minY!=minY || m_maxY!=maxY || m_tickYCount!=tickYCount){
		 m_minY=minY;
		 m_maxY=maxY;
		 m_tickYCount=tickYCount;
		 changed=true;
		 emit rangeYChanged(minY,maxY, m_tickYCount);
	}

  if(changed){
    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
  }
}
void Domain::setRangeX(qreal min, qreal max)
{
    setRange(min,max,m_minY, m_maxY);
}
void Domain::setRangeY(qreal min, qreal max)
{
	setRange(m_minX, m_maxX, min, max);
}

void Domain::setMinX(qreal min)
{
	setRange(min, m_maxX, m_minY, m_maxY);
}

void Domain::setMaxX(qreal max)
{
	setRange(m_minX, max, m_minY, m_maxY);
}

void Domain::setMinY(qreal min)
{
	setRange(m_minX, m_maxX, min, m_maxY);
}

void Domain::setMaxY(qreal max)
{
    setRange(m_minX, m_maxX, m_minY, max);

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

void Domain::zoomIn(const QRectF& rect, const QSizeF& size)
{
    qreal dx = spanX() / size.width();
    qreal dy = spanY() / size.height();

    m_maxX = m_minX + dx * rect.right();
    m_minX = m_minX + dx * rect.left();
    m_minY = m_maxY - dy * rect.bottom();
    m_maxY = m_maxY - dy * rect.top();

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
}

void Domain::zoomOut(const QRectF& rect, const QSizeF& size)
{
    qreal dx = spanX() / rect.width();
    qreal dy = spanY() / rect.height();

    m_minX = m_maxX - dx * rect.right();
    m_maxX = m_minX + dx * size.width();
    m_maxY = m_minY + dy * rect.bottom();
    m_minY = m_maxY - dy * size.height();

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
    emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
}

void Domain::move(int dx,int dy,const QSizeF& size)
{
    qreal x = spanX() / size.width();
    qreal y = spanY() / size.height();

    if(dx!=0){
    m_minX = m_minX + x * dx;
    m_maxX = m_maxX + x * dx;
    emit rangeXChanged(m_minX, m_maxX, m_tickXCount);
    }
    if(dy!=0){
    m_minY = m_minY + y * dy;
    m_maxY = m_maxY + y * dy;
    emit rangeYChanged(m_minY, m_maxY, m_tickYCount);
    }

    emit domainChanged(m_minX, m_maxX, m_minY, m_maxY);
}

void Domain::handleAxisRangeXChanged(qreal min,qreal max,int tickCount)
{
	 setRange(min,max,m_minY, m_maxY,tickCount,m_tickYCount);
}

void Domain::handleAxisRangeYChanged(qreal min,qreal max,int tickCount)
{
	 setRange(m_minX, m_maxX, min, max,m_tickXCount, tickCount);
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

#include "moc_domain_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
