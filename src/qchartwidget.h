#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartconfig.h"
#include "qchart.h"
#include <QWidget>

QCHART_BEGIN_NAMESPACE

class QChartSeries;
class QChartWidgetPrivate;

class QCHART_EXPORT QChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);
    QSize sizeHint() const;

    void addSeries(QChartSeries* series);
protected:
    QChartWidgetPrivate * const d_ptr;

private:
    Q_DISABLE_COPY(QChartWidget)
    Q_DECLARE_PRIVATE(QChartWidget)

};

QCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
