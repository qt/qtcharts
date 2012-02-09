#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchartseries.h"
#include "qchart.h"
#include <QGraphicsView>

class QGraphicsScene;
class QRubberBand;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class QTCOMMERCIALCHART_EXPORT QChartView : public QGraphicsView
{
public:
    enum  RubberBandPolicy { NoRubberBand, VerticalRubberBand, HorizonalRubberBand, RectangleRubberBand };

    explicit QChartView(QWidget *parent = 0);
    ~QChartView();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);

    void addSeries(QChartSeries* series);

    // Convenience function
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    int margin() const;

    void setTitle(const QString& title);
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomInToRect(const QRect& rectangle);
    void zoomIn();
    void zoomOut();

    void setRubberBandPolicy(const RubberBandPolicy );
    RubberBandPolicy rubberBandPolicy() const;

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    QChartAxis* axisX();
    QChartAxis* axisY();
    QChartAxis* addAxisX();
    QChartAxis* addAxisY();
    void removeAxis(QChartAxis* axis);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:
    QGraphicsScene *m_scene;
    QChart* m_chart;
    QPoint m_rubberBandOrigin;
    QRubberBand* m_rubberBand;
    bool m_verticalRubberBand;
    bool m_horizonalRubberBand;
    Q_DISABLE_COPY(QChartView)


};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
