#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "qchartglobal.h"
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain {
public:
	Domain(qreal minX=0, qreal maxX=0, qreal minY=0, qreal maxY=0);
	virtual ~Domain();

	qreal spanX() const;
	qreal spanY() const;

	friend bool operator== (const Domain &domain1, const Domain &domain2);
	friend bool operator!= (const Domain &domain1, const Domain &domain2);
	friend QDebug operator<<(QDebug dbg, const Domain &domain);

	Domain subDomain(const QRectF& rect, qreal maxWidth, qreal maxHeight) const;

public:
	qreal m_minX;
	qreal m_maxX;
	qreal m_minY;
	qreal m_maxY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
