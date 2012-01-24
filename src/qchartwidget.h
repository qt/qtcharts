#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchart.h"
#include <QGraphicsView>

class QGraphicsScene;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartSeries;
class QChartWidgetPrivate;

class QTCOMMERCIALCHART_EXPORT QChartWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);
    QSize sizeHint() const;

    // TODO: addSeries and createSeries are optional solutions
    // TODO: currently createSeries assumes x, y value pairs. This isn't case with all charts. So is there another createSeries for other types (for example one list of ints)?
    void addSeries(QChartSeries* series);
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

private:
    Q_DISABLE_COPY(QChartWidget)
    QGraphicsScene *m_scene;
    QChart* m_chart;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
