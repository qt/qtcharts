#ifndef XYCHARTANIMATOR_P_H_
#define XYCHARTANIMATOR_P_H_
#include "qchartglobal.h"
#include <QVariantAnimation>
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

template <class T, class U>
class XYChartAnimationItem;


template <class T, class U>
class XYChartAnimator : public QVariantAnimation
{
public:
	enum Animation { LineDrawAnimation, MoveDownAnimation, MoveUpAnimation };
    XYChartAnimator(XYChartAnimationItem<T,U> *item, QObject *parent = 0 );
    ~XYChartAnimator();

protected:
    QVariant interpolated(const QVariant &start, const QVariant & end, qreal progress ) const;
    void updateCurrentValue (const QVariant & value );
    void updateState ( QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

private:
    XYChartAnimationItem<T,U> *m_item;
    Animation m_type;
};

template <class T, class U>
XYChartAnimator<T,U>::XYChartAnimator(XYChartAnimationItem<T,U> *item , QObject *parent):QVariantAnimation(parent),
    m_item(item),
    m_type(MoveDownAnimation)
{
}

template <class T,class U>
XYChartAnimator<T,U>::~XYChartAnimator()
{
}

template <class T, class U>
QVariant XYChartAnimator<T,U>::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
{
	QVector<QPointF> startVector = qVariantValue<QVector<QPointF> >(start);
	QVector<QPointF> endVector = qVariantValue<QVector<QPointF> >(end);
	QVector<QPointF> result;

	switch(m_type) {

		case MoveDownAnimation: {

			Q_ASSERT(startVector.count() == endVector.count());
			for(int i =0;i< startVector.count();i++) {
				qreal x = startVector[i].x() + ((endVector[i].x()- startVector[i].x()) * progress);
				qreal y = startVector[i].y() + ((endVector[i].y()- startVector[i].y()) * progress);
				result << QPointF(x,y);
			}

		}
			break;
		case LineDrawAnimation:{
			for(int i =0;i< endVector.count()* qBound(0.0, progress, 1.0);i++) {
				result << endVector[i];
			}
		}
			break;
		default:
			qWarning()<<"Unknow type of animation";
			break;
	}

	return qVariantFromValue(result);
}

template <class T, class U>
void XYChartAnimator<T,U>::updateCurrentValue (const QVariant & value )
{
	QVector<QPointF> vector = qVariantValue<QVector<QPointF> >(value);
	if(state()!=QAbstractAnimation::Stopped){ //workaround
    m_item->setGeometry(vector);
	}
}

template <class T, class U>
void XYChartAnimator<T,U>::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
	Q_UNUSED(oldState)
	if (newState==QAbstractAnimation::Running) m_item->animationStarted();
	QVariantAnimation::updateState(newState,oldState);
}

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* XYCHARTANIMATOR_P_H_ */
