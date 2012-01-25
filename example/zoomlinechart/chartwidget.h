#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H
#include <qchartview.h>
#include <QRubberBand>

QTCOMMERCIALCHART_USE_NAMESPACE

class ChartWidget : public QChartView
{
    Q_OBJECT

public:
    ChartWidget(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    bool rubberBandIsShown;
    QRubberBand m_rubberBand;
    QPoint m_origin;

};

#endif
