#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsObject>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Axis;
class XYGrid;
class QChartSeries;
class XYPlotDomain;
class XYLineChartItem;
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

    virtual void setSize(const QSizeF& rect);
    void setMargin(int margin);
    int margin() const;
    void setTheme(QChart::ChartTheme theme);

signals:
    void sizeChanged(QRectF rect);
    void scaleChanged(qreal xscale, qreal yscale);

private:
    Q_DISABLE_COPY(QChart)
    Axis* m_axisX;
    Axis* m_axisY;
    XYGrid* m_grid;
    QRect m_rect;
    QList<const QChartSeries*> m_series;
    QList<XYPlotDomain> m_plotDomainList;
    QList<XYLineChartItem*> m_xyLineChartItems;
    QList<QGraphicsItem*> m_items;
    int m_plotDataIndex;
    int m_marginSize;
    QList<QColor> m_themeColors;

    QList<BarGroup*> m_BarGroupItems;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
