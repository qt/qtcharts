#ifndef PLOTDOMAIN_H_
#define PLOTDOMAIN_H_
#include "qchartglobal.h"
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class PlotDomain {
public:
	PlotDomain();
	virtual ~PlotDomain();

	qreal spanX() const;
	qreal spanY() const;

	PlotDomain subDomain(const QRect& rect, qreal maxWidth, qreal maxHeight) const;


public:
	qreal m_minX;
	qreal m_maxX;
	qreal m_minY;
	qreal m_maxY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* PLOTTER_H_ */
