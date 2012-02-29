#ifndef LINECHARTANIMATIONITEM_P_H_
#define LINECHARTANIMATIONITEM_P_H_

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class LineChartItem;

class LineChartAnimationItem : public LineChartItem {

public:
	LineChartAnimationItem(ChartPresenter* presenter, QLineSeries *series, QGraphicsItem *parent = 0);
	virtual ~LineChartAnimationItem();

	void addPoints(const QVector<QPointF>& points);
	void replacePoint(int index,const QPointF& point);

private:
	QVector<QPointF> m_data;
	Domain m_domain;
	int m_addPoints;
	QPointF m_setPoint;
	int m_setPoint_index;
};

class LineChartAnimatator: public QVariantAnimation
{

public:
    LineChartAnimatator(LineChartItem *item, int index , QObject *parent = 0 ):m_item(item),m_index(index){};

    QPointF m_point;
    LineChartAnimationItem* m_item;
    int m_index;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
