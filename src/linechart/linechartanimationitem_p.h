#ifndef LINECHARTANIMATIONITEM_P_H_
#define LINECHARTANIMATIONITEM_P_H_

#include "qchartglobal.h"
#include "linechartitem_p.h"
#include "domain_p.h"
#include <QVariantAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class LineChartAnimatator;

class LineChartAnimationItem : public LineChartItem {

	Q_OBJECT

public:
	LineChartAnimationItem(QLineSeries *series, QGraphicsItem *parent = 0);
	virtual ~LineChartAnimationItem();

protected:
	 virtual void updateAllPoints();
	 virtual void updatePoint(int index,QPointF& newPoint);

private slots:
	void startAnimation();

private:
    LineChartAnimatator *m_animation;
    QVector<QPointF> m_points;
    bool m_dirty;
};

class LineChartAnimatator: public QVariantAnimation
{
public:
    LineChartAnimatator(LineChartAnimationItem *item, QObject *parent = 0 );
    ~LineChartAnimatator();

protected:
    QVariant interpolated(const QVariant &start, const QVariant & end, qreal progress ) const;
    void updateCurrentValue (const QVariant & value );

private:
    LineChartAnimationItem* m_item;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
