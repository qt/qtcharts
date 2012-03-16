#include "PieAnimation_p.h"
#include "piesliceanimation_p.h"
#include "piechartitem_p.h"
#include <QParallelAnimationGroup>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieAnimation::PieAnimation(PieChartItem *item)
    :ChartAnimation(item),
    m_item(item)
{
}

PieAnimation::~PieAnimation()
{
}

void PieAnimation::setValues(QVector<PieSliceLayout>& newValues)
{
    PieSliceAnimation *animation = 0;

    foreach (PieSliceLayout endLayout, newValues) {
        animation = m_animations.value(endLayout.m_data);
        if (animation) {
            // existing slice
            animation->stop();
            animation->updateValue(endLayout);
        } else {
            // new slice
            animation = new PieSliceAnimation(m_item);
            m_animations.insert(endLayout.m_data, animation);
            PieSliceLayout startLayout = endLayout;
            startLayout.m_radius = 0;
            //startLayout.m_startAngle = 0;
            //startLayout.m_angleSpan = 0;
            animation->setValue(startLayout, endLayout);
        }
        animation->setDuration(1000);
        animation->setEasingCurve(QEasingCurve::OutQuart);
        QTimer::singleShot(0, animation, SLOT(start())); // TODO: use sequential animation?
    }

    foreach (QPieSlice *s, m_animations.keys()) {
        bool isFound = false;
        foreach (PieSliceLayout layout, newValues) {
            if (s == layout.m_data)
                isFound = true;
        }
        if (!isFound) {
            // slice has been deleted
            animation = m_animations.value(s);
            animation->stop();
            PieSliceLayout endLayout = m_animations.value(s)->currentSliceValue();
            endLayout.m_radius = 0;
            // TODO: find the actual angle where this slice disappears
            endLayout.m_startAngle = endLayout.m_startAngle + endLayout.m_angleSpan;
            endLayout.m_angleSpan = 0;
            animation->updateValue(endLayout);
            animation->setDuration(1000);
            animation->setEasingCurve(QEasingCurve::OutQuart);
            connect(animation, SIGNAL(finished()), this, SLOT(destroySliceAnimationComplete()));
            QTimer::singleShot(0, animation, SLOT(start()));
        }
    }
}

void PieAnimation::updateValue(PieSliceLayout& endLayout)
{
    PieSliceAnimation *animation = m_animations.value(endLayout.m_data);
    Q_ASSERT(animation);
    animation->stop();
    animation->updateValue(endLayout);
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);
    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::updateCurrentValue(const QVariant &)
{
    // nothing to do...
}

void PieAnimation::destroySliceAnimationComplete()
{
    PieSliceAnimation *animation = static_cast<PieSliceAnimation*>(sender());
    QPieSlice *slice = m_animations.key(animation);
    m_item->destroySlice(slice);
    delete m_animations.take(slice);
}

#include "moc_pieanimation_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
