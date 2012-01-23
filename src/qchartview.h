#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchartseries.h"
#include <QGraphicsView>

class QGraphicsScene;
class QRubberBand;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class QTCOMMERCIALCHART_EXPORT QChartView : public QGraphicsView
{
public:
    explicit QChartView(QWidget *parent = 0);
    ~QChartView();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);

    // TODO: addSeries and createSeries are optional solutions
    void addSeries(QChartSeries* series);
    QChartSeries* createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type);

protected:
    void mouseMoveEvent (QMouseEvent *event);
    void mousePressEvent (QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent *event);

private:
    QGraphicsScene *m_scene;
    QChart* m_chart;
    QRubberBand *m_rubberBand;
    QPoint m_origin;
    bool m_showRubberBand;
    Q_DISABLE_COPY(QChartView)


};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
