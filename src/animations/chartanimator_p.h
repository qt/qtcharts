#ifndef CHARTANIMATOR_P_H_
#define CHARTANIMATOR_P_H_
#include "qchartglobal.h"
#include "chartanimation_p.h"
#include "piechartitem_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class AxisItem;
class AreaChartItem;
class SplineChartItem;
class ScatterChartItem;
class LineChartItem;
class XYChartItem;

class ChartAnimator : public QObject {

public:
	//TODO: this should be flags in case of two state at the time
	enum State{ShowState, ScrollUpState, ScrollDownState, ScrollLeftState,ScrollRightState,ZoomInState,ZoomOutState};
    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(AxisItem* item);
    void addAnimation(PieChartItem* item);
    void addAnimation(ScatterChartItem* item);
    void addAnimation(LineChartItem* item);
    void addAnimation(SplineChartItem* item);
    void removeAnimation(ChartItem* item);

    void animationStarted();
    void updateLayout(XYChartItem* item, QVector<QPointF>& oldLayout,QVector<QPointF>& newLayout,int index);
    void updateLayout(SplineChartItem* item,  QVector<QPointF>& oldPoints , QVector<QPointF>& newPoints, QVector<QPointF>& oldControlPoints, QVector<QPointF>& newContorlPoints,int index);
    void applyLayout(AxisItem* item, QVector<qreal>& layout);

    void addAnimation(PieChartItem* item, QPieSlice *slice, PieSliceLayout &layout);
    void removeAnimation(PieChartItem* item, QPieSlice *slice);
    void updateLayout(PieChartItem* item, QVector<PieSliceLayout> &layout);
    void updateLayout(PieChartItem* item, PieSliceLayout &layout);

    void setState(State state,const QPointF& point = QPointF());

private:
     QMap<ChartItem*,ChartAnimation*> m_animations;
     State m_state;
     QPointF m_point;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
