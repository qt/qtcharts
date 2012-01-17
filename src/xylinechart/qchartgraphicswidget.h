#ifndef QCHARTGRAPHICSWIDGET_H
#define QCHARTGRAPHICSWIDGET_H

#include <qchartconfig.h>
#include <QGraphicsWidget>

class QGraphicsItem;

QCHART_BEGIN_NAMESPACE

class QChart;
class QChartGraphicsWidgetPrivate;

class QCHART_EXPORT QChartGraphicsWidget : public QGraphicsWidget
{

public:
    explicit QChartGraphicsWidget(QGraphicsItem *parent = 0,Qt::WindowFlags wFlags = 0);
    ~QChartGraphicsWidget();

    QChart* chart() const;
    void addChart(QChart* chart);

    virtual void setGeometry(const QRectF & rect);

private:
    Q_DISABLE_COPY(QChartGraphicsWidget)
    Q_DECLARE_PRIVATE(QChartGraphicsWidget)
    QChartGraphicsWidgetPrivate * const d_ptr;
};

QCHART_END_NAMESPACE

#endif
