#ifndef CHARTANIMATOR_P_H_
#define CHARTANIMATOR_P_H_
#include "qchartglobal.h"
#include "chartanimation_p.h"
#include "piechartitem_p.h"
#include "barchartitem_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class Axis;
class AreaChartItem;
class SplineChartItem;
class ScatterChartItem;
class LineChartItem;
class XYChartItem;

class ChartAnimator : public QObject {

public:
	enum State{ShowState, ScrollUpState, ScrollDownState, ScrollLeftState,ScrollRightState,ZoomInState,ZoomOutState};
	Q_DECLARE_FLAGS(States, State);

    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(Axis* item);
    void addAnimation(PieChartItem* item);
    void addAnimation(ScatterChartItem* item);
    void addAnimation(LineChartItem* item);
    void addAnimation(SplineChartItem* item);
    void addAnimation(BarChartItem* item);
    void removeAnimation(Chart* item);

    void animationStarted();
    void updateLayout(XYChartItem* item, QVector<QPointF>& oldLayout,QVector<QPointF>& newLayout,int index);
    void updateLayout(SplineChartItem* item,  QVector<QPointF>& oldPoints , QVector<QPointF>& newPoints, QVector<QPointF>& oldControlPoints, QVector<QPointF>& newContorlPoints,int index);
    void updateLayout(Axis* item, QVector<qreal>& layout);

    void addAnimation(PieChartItem* item, QPieSlice *slice, const PieSliceData &sliceData, bool isEmpty);
    void removeAnimation(PieChartItem* item, QPieSlice *slice);
    void updateLayout(PieChartItem* item, const PieLayout &layout);
    void updateLayout(PieChartItem* item, QPieSlice *slice, const PieSliceData &sliceData);

    void updateLayout(BarChartItem* item, const BarLayout &layout);

    void setState(State state,const QPointF& point = QPointF());

private:
     QMap<Chart*,ChartAnimation*> m_animations;
     State m_state;
     QPointF m_point;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
