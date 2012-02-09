#include "linechartanimationitem_p.h"
#include "linechartitem_p.h"
#include <QPropertyAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;


LineChartAnimationItem::LineChartAnimationItem(ChartPresenter* presenter, QLineChartSeries* series,QGraphicsItem *parent):
LineChartItem(presenter,series,parent)
{

}

LineChartAnimationItem::~LineChartAnimationItem()
{
}

void LineChartAnimationItem::addPoints(const QVector<QPointF>& points)
{
    m_data=points;
    clearView();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "a_addPoints", parent());
    animation->setDuration(duration);
    //animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0.0, 0);
    animation->setKeyValueAt(1.0, m_data.size());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LineChartAnimationItem::setPoint(int index,const QPointF& point)
{
    AnimationHelper* helper = new AnimationHelper(this,index);
    QPropertyAnimation *animation = new QPropertyAnimation(helper, "point", parent());
    animation->setDuration(duration);
    //animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0.0, points().value(index));
    animation->setKeyValueAt(1.0, point);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LineChartAnimationItem::aw_addPoints(int points)
{
    int index = count();
    for(int i = index;i< points ;i++){
        LineChartItem::addPoint(m_data.at(i));
    }
    updateGeometry();
    update();
}

void LineChartAnimationItem::aw_setPoint(int index,const QPointF& point)
{
    LineChartItem::setPoint(index,point);
    updateGeometry();
    update();
}


#include "moc_linechartanimationitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
