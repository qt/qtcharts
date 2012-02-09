#include "qxychartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QXYChartSeries::QXYChartSeries(QObject* parent):QChartSeries(parent)
{
}

QXYChartSeries::~QXYChartSeries()
{
}

QXYChartSeries* QXYChartSeries::create(QObject* parent)
{
    //TODO: here we take QChartData when it is ready
    // return null if malformed;
    return new QXYChartSeries(parent);
}

int QXYChartSeries::add(qreal x,qreal y)
{
    m_x<<x;
    m_y<<y;
    return m_x.size()-1;
}

void QXYChartSeries::set(int index,qreal x,qreal y)
{
    m_x[index]=x;
    m_y[index]=y;
    emit changed(index);
}

void QXYChartSeries::clear()
{
    m_x.clear();
    m_y.clear();
}

qreal QXYChartSeries::x(int pos) const
{
   return m_x.at(pos);
}

qreal QXYChartSeries::y(int pos) const
{
   return m_y.at(pos);
}

int QXYChartSeries::count() const
{
	Q_ASSERT(m_x.size() == m_y.size());

	return m_x.size();

}

void QXYChartSeries::setPen(const QPen& pen)
{
    m_pen=pen;
}

QDebug operator<< (QDebug debug, const QXYChartSeries series)
{
	Q_ASSERT(series.m_x.size() == series.m_y.size());

    int size = series.m_x.size();

    for (int i=0;i<size;i++) {
    debug.nospace() << "(" << series.m_x.at(i) << ','<< series.m_y.at(i) << ") ";
    }
    return debug.space();
}

#include "moc_qxychartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
