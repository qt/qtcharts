#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsWidget>
#include <QLinearGradient>
#include <QFont>

class QGraphicsSceneResizeEvent;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class AxisItem;
class QChartSeries;
class PlotDomain;
class BarGroup;
class QChartAxis;
class ChartTheme;
class ChartItem;

// TODO: We don't need to have QChart tied to QGraphicsItem:
//class QTCOMMERCIALCHART_EXPORT QChart
//class QTCOMMERCIALCHART_EXPORT QChartGraphicsItem : public QGraphicsItem {
// public: QChartGraphicsItem(QChart &chart);

/*!
 * TODO: define the responsibilities
 */
class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    enum GradientOrientation {
        HorizonatlGradientOrientation,
        VerticalGradientOrientation
    };
    enum ChartThemeId {
        ChartThemeInvalid = -1,
        /*! The default theme follows the GUI style of the Operating System */
        ChartThemeDefault,
        ChartThemeVanilla,
        ChartThemeIcy,
        ChartThemeGrayscale,
        ChartThemeScientific,
        ChartThemeUnnamed1
    };

public:
    QChart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~QChart();

    void addSeries(QChartSeries* series);
    //TODO: QChartSeries* createSeries(QSeriesData *data, QChartSeries::QChartSeriesType type);
    // TODO: who owns the series now? maybe owned by chart and returned a reference instead...
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    void setMargin(int margin);
    int margin() const;
    void setTheme(QChart::ChartThemeId theme);
    QChart::ChartThemeId theme();

    void setTitle(const QString& title,const QFont& font = QFont());
    void setBackground(const QColor& startColor, const QColor& endColor = Qt::white, GradientOrientation orientation = VerticalGradientOrientation);

    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomInToRect(const QRectF& rectangle);
    void zoomIn();
    void zoomOut();
    void zoomReset();

    void setAxisX(const QChartAxis& axis);
    void setAxisY(const QChartAxis& axis);
    void setAxisY(const QList<QChartAxis>& axis);

protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

private:
    void setAxis(AxisItem *item, const QChartAxis& axis);

private:
    Q_DISABLE_COPY(QChart)
    QGraphicsRectItem* m_backgroundItem;
    QLinearGradient m_backgroundGradient;
    GradientOrientation m_bacgroundOrinetation;
    QGraphicsTextItem* m_titleItem;
    AxisItem* m_axisXItem;
    QList<AxisItem*> m_axisYItem;
    QRectF m_rect;
    QList<QChartSeries *> m_chartSeries;
    QList<ChartItem *> m_chartItems;
    QVector<PlotDomain> m_plotDomainList;
    int m_plotDataIndex;
    int m_marginSize;
    ChartTheme *m_chartTheme;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
