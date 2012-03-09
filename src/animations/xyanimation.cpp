#include "xyanimation_p.h"
#include "xychartitem_p.h"

Q_DECLARE_METATYPE(QVector<QPointF>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE

XYAnimation::XYAnimation(XYChartItem *item):ChartAnimation(item),
    m_item(item),
    m_type(MoveDownAnimation),
    m_dirty(false)
{
}

XYAnimation::~XYAnimation()
{
}

void XYAnimation::setAnimationType(Animation type)
{
    m_type=type;
}

void XYAnimation::setValues(QVector<QPointF>& oldPoints,QVector<QPointF>& newPoints)
{
    setKeyValueAt(0.0, qVariantFromValue(oldPoints));
    setKeyValueAt(1.0, qVariantFromValue(newPoints));
    m_points = newPoints;
    m_dirty=false;
}

void XYAnimation::updateValues(QVector<QPointF>& newPoints)
{
    if(state()!=QAbstractAnimation::Stopped) {
        stop();
        m_dirty=true;
    }

    if(m_dirty) {
        m_points=newPoints;
        m_dirty=false;
    }

    setKeyValueAt(0.0, qVariantFromValue(m_points));
    setKeyValueAt(1.0, qVariantFromValue(newPoints));
}

QVariant XYAnimation::interpolated(const QVariant &start, const QVariant & end, qreal progress ) const
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

void XYAnimation::updateCurrentValue (const QVariant & value )
{
    if(state()!=QAbstractAnimation::Stopped){ //workaround
        QVector<QPointF> vector = qVariantValue<QVector<QPointF> >(value);
        m_item->setGeometry(vector);
    }
}

void XYAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    Q_UNUSED(oldState)
    if (newState==QAbstractAnimation::Running)  m_dirty=true;
    QVariantAnimation::updateState(newState,oldState);
}

QTCOMMERCIALCHART_END_NAMESPACE
