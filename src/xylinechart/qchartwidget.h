#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include <qchartconfig.h>
#include <QGraphicsWidget>

class QGraphicsItem;

QCHART_BEGIN_NAMESPACE

class QChart;
class QChartWidgetPrivate;

class QCHART_EXPORT QChartWidget : public QGraphicsWidget
{

public:
    explicit QChartWidget(QGraphicsItem *parent = 0,Qt::WindowFlags wFlags = 0);
    ~QChartWidget();

    QChart* chart() const;
    void addChart(QChart* chart);

    virtual void setGeometry(const QRectF & rect);

private:
    Q_DISABLE_COPY(QChartWidget)
    Q_DECLARE_PRIVATE(QChartWidget)
    QChartWidgetPrivate * const d_ptr;
};

QCHART_END_NAMESPACE

#endif
