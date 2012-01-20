#ifndef CHART_H
#define CHART_H

#include <qchartglobal.h>
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Axis;
class XYGrid;
class QChartSeries;
class XYPlotDomain;
class QChartPrivate;

class QTCOMMERCIALCHART_EXPORT QChart : public QGraphicsItem
{

public:
    QChart(QGraphicsItem* parent = 0);
    virtual ~QChart();

    //from QGraphicsItem
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};

    void addSeries(QChartSeries* series);

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
