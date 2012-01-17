#include "qxyseries.h"

QCHART_BEGIN_NAMESPACE

QXYSeries::QXYSeries():
    m_color(Qt::black)
{
}

QXYSeries::~QXYSeries()
{
}


void QXYSeries::setColor(const QColor& color)
{
	m_color = color;
}


void QXYSeries::add(qreal x,qreal y)
{
    m_x<<x;
    m_y<<y;
}

void QXYSeries::clear()
{
    m_x.clear();
    m_y.clear();
}

qreal QXYSeries::x(int pos) const
{
   return m_x.at(pos);
}

qreal QXYSeries::y(int pos) const
{
   return m_y.at(pos);
}

int QXYSeries::count() const
{
	Q_ASSERT(m_x.size() == m_y.size());

	return m_x.size();

}

QDebug operator<< (QDebug debug, const QXYSeries series)
{
	Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}

QCHART_END_NAMESPACE
