#include "qchartaxis.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QChartAxis::QChartAxis(QObject* parent):QObject(parent),
m_axisVisible(true),
m_gridVisible(true),
m_labelsVisible(true),
m_labelsAngle(0),
m_shadesVisible(true),
m_shadesOpacity(1.0),
m_min(0),
m_max(0),
m_ticksCount(5)
{

}

QChartAxis::~QChartAxis()
{
}

void QChartAxis::setAxisPen(const QPen& pen)
{
    m_axisPen=pen;
    emit update(this);
}

void QChartAxis::setAxisVisible(bool visible)
{
    m_axisVisible=visible;
    emit update(this);
}

void QChartAxis::setGridVisible(bool visible)
{
    m_gridVisible=visible;
    emit update(this);
}

void QChartAxis::setGridPen(const QPen& pen)
{
    m_gridPen=pen;
    emit update(this);
}

void QChartAxis::setLabelsVisible(bool visible)
{
    m_labelsVisible=visible;
    emit update(this);
}

void QChartAxis::setLabelsPen(const QPen& pen)
{
    m_labelsPen=pen;
    emit update(this);
}

void QChartAxis::setLabelsBrush(const QBrush& brush)
{
    m_labelsBrush=brush;
    emit update(this);
}

void QChartAxis::setLabelsFont(const QFont& font)
{
    m_labelsFont=font;
    emit update(this);
}

void QChartAxis::setLabelsAngle(int angle)
{
	m_labelsAngle=angle;
	 emit update(this);
}

void QChartAxis::setShadesVisible(bool visible)
{
    m_shadesVisible=visible;
    emit update(this);
}

void QChartAxis::setShadesPen(const QPen& pen)
{
    m_shadesPen=pen;
    emit update(this);
}

void QChartAxis::setShadesBrush(const QBrush& brush)
{
    m_shadesBrush=brush;
    emit update(this);
}

void QChartAxis::setShadesOpacity(qreal opacity)
{
    m_shadesOpacity=opacity;
    emit update(this);
}

void QChartAxis::setMin(qreal min)
{
	if(m_min!=min){
		m_min=min;
		emit minChanged(m_min);
	}
}

void QChartAxis::setMax(qreal max)
{
	if(m_max!=max){
		m_max=max;
		emit maxChanged(m_max);
	}
}

void QChartAxis::setRange(qreal min, qreal max)
{
	setMin(min);
	setMax(max);
}

void QChartAxis::setTicksCount(int count)
{
	m_ticksCount=count;
	emit ticksChanged(this);
}

void QChartAxis::addAxisTickLabel(qreal value,const QString& label)
{
	m_ticks.insert(value,label);
	emit ticksChanged(this);
}

void QChartAxis::removeAxisTickLabel(qreal value)
{
	m_ticks.remove(value);
	emit ticksChanged(this);
}

QString QChartAxis::axisTickLabel(qreal value) const
{
	return m_ticks.value(value);
}

void QChartAxis::clearAxisTickLabels()
{
	m_ticks.clear();
	emit ticksChanged(this);
}

#include "moc_qchartaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
