#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchart.h"
#include <QWidget>

class QGraphicsView;
class QGraphicsScene;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartSeries;
class QChartWidgetPrivate;

class QTCOMMERCIALCHART_EXPORT QChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);
    QSize sizeHint() const;

    // TODO: addSeries and createSeries are optional solutions
    void addSeries(QChartSeries* series);
    QChartSeries* createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type);

private:
    Q_DISABLE_COPY(QChartWidget)
    QGraphicsView *m_view;
    QGraphicsScene *m_scene;
    QChart* m_chart;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
