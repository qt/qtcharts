#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartconfig.h"
#include "qchart.h"
#include <QWidget>

QCHART_BEGIN_NAMESPACE

class QXYSeries;
class QChartWidgetPrivate;

class QCHART_EXPORT QChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();
    // TODO: replace QXYSeries list with a charts data API
    // TODO: return QChartDataSeries
    void addDataSeries(QChart::DataSeriesType dataSeriesType, QList<QXYSeries*> dataset);

signals:

public slots:

private:
    friend class QChartWidgetPrivate;
    Q_DISABLE_COPY(QChartWidget)
//    Q_DECLARE_PRIVATE(QChartWidget)
    QChartWidgetPrivate * const d;
};

QCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
