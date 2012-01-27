#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchart.h"
#include <QGraphicsView>
#include <QRubberBand>

class QGraphicsScene;
class QRubberBand;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChartSeries;
class QChartWidgetPrivate;

class QTCOMMERCIALCHART_EXPORT QChartWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QChartWidget(QWidget *parent = 0);
    ~QChartWidget();

    // TODO: addSeries and createSeries are optional solutions
    // TODO: currently createSeries assumes x, y value pairs. This isn't case with all charts. So is there another createSeries for other types (for example one list of ints)?
public Q_SLOTS:
    void addSeries(QChartSeries* series);
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    /*!
     * Set color theme for the chart. Themes define harmonic colors for the graphical elements of
     * the chart.
     */
    void setTheme(QChart::ChartThemeId theme);

    void setZoomEnabled(bool enabled);

private: // From QWidget TODO: should these be protected instead? Is QChartWidget meant to be extened by the user?
    void resizeEvent(QResizeEvent *event);
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Q_DISABLE_COPY(QChartWidget)
    // TODO: move the following to pimpl
    QGraphicsScene *m_scene;
    QChart* m_chart;
    QRubberBand m_rubberBand;
    int m_originX;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
