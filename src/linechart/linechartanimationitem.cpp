#include "linechartanimationitem_p.h"
#include "linechartitem_p.h"
#include <QPropertyAnimation>
#include <QTimer>

Q_DECLARE_METATYPE(QVector<QPointF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;

LineChartAnimationItem::LineChartAnimationItem(QLineSeries* series,QGraphicsItem *parent):
LineChartItem(series,parent),
m_animation(new LineChartAnimatator(this,this)),
m_dirty(false)
{
}

LineChartAnimationItem::~LineChartAnimationItem()
{
}

void LineChartAnimationItem::updateAllPoints()
{
    QVector<QPointF> oldPoints = points();
    LineChartItem::updateAllPoints();
    QVector<QPointF> newPoints = points();

    if(newPoints.count()==0) return;
    oldPoints.resize(newPoints.size());

    if(m_animation->state()!=QAbstractAnimation::Stopped){
       m_animation->stop();
    }

    m_animation->setDuration(duration);
    m_animation->setEasingCurve(QEasingCurve::InOutBack);
    m_animation->setKeyValueAt(0.0, qVariantFromValue(oldPoints));
    m_animation->setKeyValueAt(1.0, qVariantFromValue(newPoints));
    QTimer::singleShot(0,m_animation,SLOT(start()));


    m_points = newPoints;
    m_dirty=false;

}

void LineChartAnimationItem::updatePoint(int index,QPointF& newPoint)
{

    if(m_animation->state()!=QAbstractAnimation::Stopped){
       m_animation->stop();
       m_dirty=true;
    }

    if(m_dirty){
    	m_points=points();
    	m_dirty=false;
    }

    LineChartItem::updatePoint(index,newPoint);

    m_animation->setDuration(duration);
    m_animation->setEasingCurve(QEasingCurve::InOutBack);
    m_animation->setKeyValueAt(0.0, qVariantFromValue(m_points));
    m_animation->setKeyValueAt(1.0, qVariantFromValue( points()));

    QTimer::singleShot(0,this,SLOT(startAnimation()));


}

void LineChartAnimationItem::startAnimation()
{
	 m_dirty=true;
	 m_animation->start();
}

LineChartAnimatator::LineChartAnimatator(LineChartAnimationItem *item , QObject *parent):QVariantAnimation(parent),
    m_item(item)
{
}

LineChartAnimatator::~LineChartAnimatator()
{
}

QVariant LineChartAnimatator::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
{
	QVector<QPointF> startVector = qVariantValue<QVector<QPointF> >(start);
	QVector<QPointF> endVecotr = qVariantValue<QVector<QPointF> >(end);
	QVector<QPointF> result;
    Q_ASSERT(startVector.count() == endVecotr.count());

    for(int i =0 ;i< startVector.count();i++){
           qreal x = startVector[i].x() + ((endVecotr[i].x()- startVector[i].x()) * progress);//qBound(0.0, progress, 1.0));
           qreal y = startVector[i].y() + ((endVecotr[i].y()- startVector[i].y()) * progress);//qBound(0.0, progress, 1.0));
           result << QPointF(x,y);
    }
    return qVariantFromValue(result);
}

void LineChartAnimatator::updateCurrentValue (const QVariant & value )
{
	QVector<QPointF> vector = qVariantValue<QVector<QPointF> >(value);
	if(state()!=QAbstractAnimation::Stopped){ //workaround
    m_item->setGeometry(vector);
	}
}

#include "moc_linechartanimationitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
