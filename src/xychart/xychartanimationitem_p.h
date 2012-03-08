#ifndef XYCHARTANIMATIONITEM_P_H_
#define XYCHARTANIMATIONITEM_P_H_
#include "qchartglobal.h"
#include "xychartanimator_p.h"
#include <QPointF>
#include <QTimer>
#include <QGraphicsItem>

Q_DECLARE_METATYPE(QVector<QPointF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE


const static int duration = 1000;

template <class T , class U>
class XYChartAnimationItem : public T {

public:
	XYChartAnimationItem(U *series, QGraphicsItem *parent = 0);
	virtual ~XYChartAnimationItem();

	void animationStarted();

protected:
	 virtual void updatePoints(QVector<QPointF>& newPoints);
	 virtual void updatePoint(QVector<QPointF>& newPoints);

private:
    XYChartAnimator<T,U> *m_animation;
    QVector<QPointF> m_points;
    bool m_dirty;
};

template <class T, class U>
XYChartAnimationItem<T,U>::XYChartAnimationItem(U *series,QGraphicsItem *parent):
T(series,parent),
m_animation(new XYChartAnimator<T,U>(this,this)),
m_dirty(false)
{
}

template <class T, class U>
XYChartAnimationItem<T,U>::~XYChartAnimationItem()
{
}

template <class T, class U>
void XYChartAnimationItem<T,U>::updatePoints(QVector<QPointF>& newPoints)
{
    QVector<QPointF> oldPoints = T::points();

    if(newPoints.count()==0) return;

    bool empty = oldPoints.count()==0;
    oldPoints.resize(newPoints.size());

    if(m_animation->state()!=QAbstractAnimation::Stopped){
       m_animation->stop();
    }

    m_animation->setDuration(duration);
    if(!empty)
        m_animation->setAnimationType(XYChartAnimator<T,U>::MoveDownAnimation);
    else
        m_animation->setAnimationType(XYChartAnimator<T,U>::LineDrawAnimation);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);
    m_animation->setKeyValueAt(0.0, qVariantFromValue(oldPoints));
    m_animation->setKeyValueAt(1.0, qVariantFromValue(newPoints));
    QTimer::singleShot(0,m_animation,SLOT(start()));

    m_points = newPoints;
    m_dirty=false;
}

template <class T, class U>
void XYChartAnimationItem<T,U>::updatePoint(QVector<QPointF>& newPoints)
{

	if(m_animation->state()!=QAbstractAnimation::Stopped) {
		m_animation->stop();
		m_dirty=true;
	}

	if(m_dirty) {
		m_points=newPoints;
		m_dirty=false;
	}

    m_animation->setDuration(duration);
    m_animation->setAnimationType(XYChartAnimator<T,U>::MoveDownAnimation);
    m_animation->setEasingCurve(QEasingCurve::OutQuart);
    m_animation->setKeyValueAt(0.0, qVariantFromValue(m_points));
    m_animation->setKeyValueAt(1.0, qVariantFromValue(newPoints));

    QTimer::singleShot(0,m_animation,SLOT(start()));
}

template <class T, class U>
void XYChartAnimationItem<T,U>::animationStarted()
{
	m_dirty=true;
}

QTCOMMERCIALCHART_END_NAMESPACE

#endif
