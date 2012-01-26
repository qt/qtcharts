#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsObject>
#include <QLinearGradient>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem;
class QChartSeries;
class PlotDomain;
class ChartItem;
class BarGroup;
class QChartAxis;

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
    enum ChartThemeId {
        /*! The default theme follows the GUI style of the Operating System */
        ChartThemeDefault = 0,
        ChartThemeVanilla,
        ChartThemeIcy,
        ChartThemeGrayscale,
        //ChartThemeScientific,
        ChartThemeUnnamed1
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
    void setTheme(QChart::ChartThemeId theme);

    void setTitle(const QString& title);
    void setBackgroundColor(const QColor& color);

    void zoomInToRect(const QRect& rectangle);
    void zoomIn();
    void zoomOut();

    void setAxisX(QChartAxis* axis){};
    void setAxisY(QChartAxis* axis){};
    void setAxisY(QList<QChartAxis*> axis){};


signals:
    //TODO chage to const QSize& size
    void sizeChanged(QRectF rect);
    void scaleChanged(qreal xscale, qreal yscale);

private:
    QColor nextColor();

    Q_DISABLE_COPY(QChart)
    QGraphicsRectItem* m_background;
    QLinearGradient m_backgroundGradient;
    QGraphicsTextItem* m_title;
    AxisItem* m_axisX;
    AxisItem* m_axisY;
    QRect m_rect;
    QList<QChartSeries*> m_chartSeries;
    QVector<PlotDomain> m_plotDomainList;
    QList<ChartItem*> m_chartItems;
    int m_plotDataIndex;
    int m_marginSize;
    QList<QColor> m_themeColors;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
