#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qseries.h"
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

    void addSeries(QSeries* series,QChartAxis* axisY=0);// takes series ownership , takes axis ownership
    void removeSeries(QSeries* series); //returns ownership , deletes axis if no series attached
    void removeAllSeries(); // deletes series and axis
    int margin() const;

    void setChartTitle(const QString& title);
    QString chartTitle() const;
    void setChartTitleFont(const QFont& font);
    void setChartTitleBrush(const QBrush &brush);
    QBrush chartTitleBrush();
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomIn();
    void zoomIn(const QRect& rect);
    void zoomOut();

    void setRubberBandPolicy(const RubberBandPolicy );
    RubberBandPolicy rubberBandPolicy() const;

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setAnimationOptions(QChart::AnimationOptions options);
    QChart::AnimationOptions animationOptions() const;

    QChartAxis* axisX() const;
    QChartAxis* axisY() const;

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
