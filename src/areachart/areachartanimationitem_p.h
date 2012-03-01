#ifndef LINECHARTANIMATIONITEM_P_H_
#define LINECHARTANIMATIONITEM_P_H_

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include "domain_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class LineChartItem;

class LineChartAnimationItem : public LineChartItem {
    Q_OBJECT
    Q_PROPERTY(int a_addPoints READ ar_addPoints WRITE aw_addPoints);
   // Q_PROPERTY(QPointF a_setPoint READ ar_setPoint WRITE aw_setPoint);
public:
	LineChartAnimationItem(ChartPresenter* presenter, QLineSeries *series, QGraphicsItem *parent = 0);
	virtual ~LineChartAnimationItem();

	void addPoints(const QVector<QPointF>& points);
	void setPoint(int index,const QPointF& point);
	//void removePoint(const QPointF& point){};
	//void setPoint(const QPointF& oldPoint, const QPointF& newPoint){};

	int ar_addPoints() const { return m_addPoints;}
	void aw_addPoints(int points);
	const QPointF& ar_setPoint() const { return m_setPoint;}
    void aw_setPoint(int index,const QPointF& point);

private:
	QVector<QPointF> m_data;
	Domain m_domain;
	int m_addPoints;
	QPointF m_setPoint;
	int m_setPoint_index;
};

class AnimationHelper: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPointF point READ point WRITE setPoint);
public:
    AnimationHelper(LineChartAnimationItem* item,int index):m_item(item),m_index(index){};
    void setPoint(const QPointF& point){
        m_item->aw_setPoint(m_index,point);
    }
    QPointF point(){return m_point;}
    QPointF m_point;
    LineChartAnimationItem* m_item;
    int m_index;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
