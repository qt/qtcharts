#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchartseries.h"
#include "qchart.h"
#include <QGraphicsView>

class QGraphicsScene;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class QTCOMMERCIALCHART_EXPORT QChartView : public QGraphicsView
{
public:
    explicit QChartView(QWidget *parent = 0);
    ~QChartView();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);

    void addSeries(QChartSeries* series);
    // Convenience function
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    int margin() const;
    void setTitle(const QString& title);
    void setBackground(const QColor& startColor, const QColor& endColor = Qt::white, QChart::GradientOrientation orientation = QChart::VerticalGradientOrientation);
    void zoomInToRect(const QRect& rectangle);
    void zoomIn();
    void zoomOut();

private:
    QGraphicsScene *m_scene;
    QChart* m_chart;
    QPoint m_origin;
    Q_DISABLE_COPY(QChartView)


};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
