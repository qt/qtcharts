#ifndef CHARTANIMATOR_P_H_
#define CHARTANIMATOR_P_H_
#include "qchartglobal.h"
#include "chartanimation_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class XYChartItem;
class AxisItem;
class AreaChartItem;


class ChartAnimator : public QObject {

public:
	//TODO: this should be flags in case of two state at the time
	enum State{ShowState, ScrollUpState, ScrollDownState, ScrollLeftState,ScrollRightState,ZoomInState,ZoomOutState};
    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(AxisItem* item);
    void addAnimation(XYChartItem* item);

    void removeAnimation(ChartItem* item);

    void animationStarted();
    void applyLayout(XYChartItem* item, QVector<QPointF>& layout);
    void updateLayout(XYChartItem* item, QVector<QPointF>& layout);
    void applyLayout(AxisItem* item, QVector<qreal>& layout);

    void setState(State state,const QPointF& point = QPointF());

private:
     QMap<ChartItem*,ChartAnimation*> m_animations;
     State m_state;
     QPointF m_point;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
