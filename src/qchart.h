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
class QChartPrivate;

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
    QChart(QGraphicsObject* parent = 0);
    ~QChart();

    //from QGraphicsItem
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

    void addSeries(QChartSeries* series);
    //TODO: QChartSeries* createSeries(QSeriesData *data, QChartSeries::QChartSeriesType type);
    // TODO: who owns the series now? maybe owned by chart and returned a reference instead...
    QChartSeries* createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type);

    virtual void setSize(const QSizeF& rect);
    void setMargin(int margin);
    int margin() const;

signals:
    void sizeChanged(QRectF rect, qreal xscale, qreal yscale);

private:
//    Q_DECLARE_PRIVATE(QChart)
    Q_DISABLE_COPY(QChart)
    QChartPrivate *d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
