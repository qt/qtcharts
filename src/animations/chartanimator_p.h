#ifndef CHARTANIMATOR_P_H_
#define CHARTANIMATOR_P_H_
#include "qchartglobal.h"
#include "chartanimation_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartItem;
class XYChartItem;
class AxisItem;


class ChartAnimator : public QObject {

public:
    ChartAnimator(QObject *parent = 0);
    virtual ~ChartAnimator();

    void addAnimation(AxisItem* item);
    void addAnimation(XYChartItem* item);

    void removeAnimation(ChartItem* item);

    void animationStarted();
    void applyLayout(XYChartItem* item, QVector<QPointF>& layout);
    void updateLayout(XYChartItem* item, QVector<QPointF>& layout);
    void applyLayout(AxisItem* item, QVector<qreal>& layout);

private:
     QMap<ChartItem*,ChartAnimation*> m_animations;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
