#ifndef CHART_H_
#define CHART_H_

#include "qchartglobal.h"
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimator;
class ChartPresenter;

class Chart: public QObject
{
    Q_OBJECT
public:
    explicit Chart(ChartPresenter *presenter);

public slots:
    virtual void handleGeometryChanged(const QRectF& rect);
    virtual void handleDomainChanged(qreal minX,qreal maxX,qreal minY,qreal maxY);
    virtual void rangeXChanged(qreal min, qreal max, int tickXCount);
    virtual void rangeYChanged(qreal min, qreal max, int tickYCount);

    void setAnimator(ChartAnimator* animator);
    ChartAnimator* animator() const;
    ChartPresenter* presenter() const;

private:
    ChartAnimator* m_animator;
    ChartPresenter* m_presenter;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
