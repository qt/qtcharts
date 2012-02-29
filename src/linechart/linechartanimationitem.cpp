#include "linechartanimationitem_p.h"
#include "linechartitem_p.h"
#include <QPropertyAnimation>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const static int duration = 500;


LineChartAnimationItem::LineChartAnimationItem(ChartPresenter* presenter, QLineSeries* series,QGraphicsItem *parent):
LineChartItem(presenter,series,parent)
{

}

LineChartAnimationItem::~LineChartAnimationItem()
{
}

void LineChartAnimationItem::addPoints(const QVector<QPointF>& points)
{
    QVector<qreal> vector0 = vector1;
    calculateLayout(vector1);
    if(vector1.count()==0) return;
    vector0.resize(vector1.size());


    LineChartAnimatator *animation = new LineChartAnimatator(this,this);
    animation->setDuration(duration);
    animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0.0, qVariantFromValue(vector0));
    animation->setKeyValueAt(1.0, qVariantFromValue(vector1));
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *animation = new QPropertyAnimation(this, "a_addPoints", parent());
    animation->setDuration(duration);
    //animation->setEasingCurve(QEasingCurve::InOutBack);
    animation->setKeyValueAt(0.0, 0);
    animation->setKeyValueAt(1.0, m_data.size());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void LineChartAnimationItem::replacePoint(int index,const QPointF& point)
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
    LineChartItem::replacePoint(index,point);
    updateGeometry();
    update();
}

LineChartAnimatator::LineChartAnimatator(LineChartItem *item, int index , QObject *parent = 0 ):QVariantAnimation(parent),
    m_item(item),
    m_index(index)
{
};

LineChartAnimatator::~LineChartAnimatator()
{
}

QVariant LineChartAnimatator::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
{
    QVector<qreal> startVector = qVariantValue<QVector<qreal> >(start);
    QVector<qreal> endVecotr = qVariantValue<QVector<qreal> >(end);
    QVector<qreal> result;
    Q_ASSERT(startVector.count() == endVecotr.count());

    for(int i =0 ;i< startVector.count();i++){
           qreal value = startVector[i] + ((endVecotr[i]- startVector[i]) * progress);//qBound(0.0, progress, 1.0));
           result << value;
    }
    return qVariantFromValue(result);
}


void LineChartAnimatator::updateCurrentValue (const QVariant & value )
{
    QVector<qreal> vector = qVariantValue<QVector<qreal> >(value);
    m_axis->applyLayout(vector);
}


#include "moc_linechartanimationitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
