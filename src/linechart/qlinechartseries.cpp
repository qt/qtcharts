#include "qlinechartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QLineChartSeries::QLineChartSeries(QObject* parent):QChartSeries(parent)
{
}

QLineChartSeries::~QLineChartSeries()
{
}

int QLineChartSeries::add(qreal x,qreal y)
{
    m_x<<x;
    m_y<<y;
    return m_x.size()-1;
}

void QLineChartSeries::set(int index,qreal x,qreal y)
{
    m_x[index]=x;
    m_y[index]=y;
    emit changed(index);
}

void QLineChartSeries::clear()
{
    m_x.clear();
    m_y.clear();
}

qreal QLineChartSeries::x(int pos) const
{
   return m_x.at(pos);
}

qreal QLineChartSeries::y(int pos) const
{
   return m_y.at(pos);
}

int QLineChartSeries::count() const
{
	Q_ASSERT(m_x.size() == m_y.size());

	return m_x.size();

}

void QLineChartSeries::setPen(const QPen& pen)
{
    m_pen=pen;
}

QDebug operator<< (QDebug debug, const QLineChartSeries series)
{
	Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}

#include "moc_qlinechartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
