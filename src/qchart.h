#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <qchartseries.h>
#include <QGraphicsItem>

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
class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsItem, public QObject
{

public:
    QChart(QGraphicsItem* parent = 0);
    virtual ~QChart();

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

    void addSeries(QChartSeries* series);
    //TODO: QChartSeries* createSeries(QSeriesData *data, QChartSeries::QChartSeriesType type);
    // TODO: who owns the series now? maybe owned by chart and returned a reference instead...
    QChartSeries* createSeries(QList<qreal> x, QList<qreal> y, QChartSeries::QChartSeriesType type);

    virtual void setSize(const QSizeF& rect);
    void setMargin(int margin);
    int margin() const;

protected:
    QChartPrivate * const d_ptr;

private:
    Q_DISABLE_COPY(QChart)
    Q_DECLARE_PRIVATE(QChart)

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
