#include "xyplotdata_p.h"

QCHART_BEGIN_NAMESPACE

XYPlotData::XYPlotData()
{

}

XYPlotData::~XYPlotData()
{
	// TODO Auto-generated destructor stub
}

qreal XYPlotData::spanX() const
{
	Q_ASSERT(m_maxX >= m_minX);
	return m_maxX - m_minX;
}

qreal XYPlotData::spanY() const
{
	Q_ASSERT(m_maxY >= m_minY);
	return m_maxY - m_minY;
}

QCHART_END_NAMESPACE
