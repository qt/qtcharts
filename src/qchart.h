#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem;
class QChartSeries;
class PlotDomain;
class ChartItem;
class BarGroup;

// TODO: We don't need to have QChart tied to QGraphicsItem:
//class QTCOMMERCIALCHART_EXPORT QChart
//class QTCOMMERCIALCHART_EXPORT QChartGraphicsItem : public QGraphicsItem {
// public: QChartGraphicsItem(QChart &chart);

/*!
 * TODO: define the responsibilities
 */
class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsObject
{
    Q_OBJECT
public:
    enum ChartTheme {
        ChartThemeVanilla = 0,
        ChartThemeIcy,
        ChartThemeGrayscale
    };

public:
    QChart(QGraphicsObject* parent = 0);
    ~QChart();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

    void addSeries(QChartSeries* series);
    //TODO: QChartSeries* createSeries(QSeriesData *data, QChartSeries::QChartSeriesType type);
    // TODO: who owns the series now? maybe owned by chart and returned a reference instead...
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    void setSize(const QSize& size);
    void setMargin(int margin);
    int margin() const;
    void setTheme(QChart::ChartTheme theme);

    void zoomInToRect(const QRect& rectangle);
    void zoomIn();
    void zoomOut();

signals:
    //TODO chage to const QSize& size
    void sizeChanged(QRectF rect);
    void scaleChanged(qreal xscale, qreal yscale);

private:
    Q_DISABLE_COPY(QChart)
    AxisItem* m_axisX;
    AxisItem* m_axisY;
    QRect m_rect;
    QList<const QChartSeries*> m_series;
    QVector<PlotDomain> m_plotDomainList;
    QList<ChartItem*> m_chartItems;
    //TODO: remove
    QList<QGraphicsItem*> m_items;
    int m_plotDataIndex;
    int m_marginSize;
    QList<QColor> m_themeColors;

    QList<BarGroup*> m_BarGroupItems;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
