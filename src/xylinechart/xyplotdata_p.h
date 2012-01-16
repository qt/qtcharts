#ifndef PLOTTER_H_
#define PLOTTER_H_
#include "qchartconfig.h"
#include <QtGlobal>

QCHART_BEGIN_NAMESPACE

class XYPlotData {
public:
	XYPlotData();
	virtual ~XYPlotData();

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


};

QCHART_END_NAMESPACE

#endif /* PLOTTER_H_ */
