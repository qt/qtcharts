#ifndef PLOTDOMAIN_H_
#define PLOTDOMAIN_H_
#include "qchartconfig.h"
#include <QRect>

QCHART_BEGIN_NAMESPACE

class XYPlotDomain {
public:
	XYPlotDomain();
	virtual ~XYPlotDomain();

	qreal spanX() const;
	qreal spanY() const;
	int ticksX() const { return m_ticksX; }
	int ticksY() const { return m_ticksY; }

public:
	int m_ticksX;
	int m_ticksY;
	qreal m_minX;
	qreal m_maxX;
	qreal m_minY;
	qreal m_maxY;
	QRect m_viewportRect;
};

QCHART_END_NAMESPACE

#endif /* PLOTTER_H_ */
