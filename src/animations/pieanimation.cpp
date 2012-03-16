#include "pieanimation_p.h"
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

void PieAnimation::updateValues(const PieLayout &newValues)
{
    foreach (QPieSlice* s, newValues.keys())
        updateValue(s, newValues.value(s));
}

void PieAnimation::updateValue(QPieSlice *slice, const PieSliceLayout &endLayout)
{
    PieSliceAnimation *animation = m_animations.value(slice);
    Q_ASSERT(animation);
    animation->stop();

    animation->updateValue(endLayout);
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);

    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::addSlice(QPieSlice *slice, const PieSliceLayout &endLayout, bool isEmpty)
{
    PieSliceAnimation *animation = new PieSliceAnimation(m_item, slice);
    m_animations.insert(slice, animation);

    PieSliceLayout startLayout = endLayout;
    startLayout.m_radius = 0;
    if (isEmpty)
        startLayout.m_startAngle = 0;
    else
        startLayout.m_startAngle = endLayout.m_startAngle + (endLayout.m_angleSpan/2);
    startLayout.m_angleSpan = 0;
    animation->setValue(startLayout, endLayout);

    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutQuart);
    QTimer::singleShot(0, animation, SLOT(start()));
}

void PieAnimation::removeSlice(QPieSlice *slice)
{
    PieSliceAnimation *animation = m_animations.value(slice);
    Q_ASSERT(animation);
    animation->stop();

    PieSliceLayout endLayout = animation->currentSliceValue();
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
