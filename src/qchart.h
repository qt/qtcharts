#ifndef CHART_H
#define CHART_H

#include <qchartconfig.h>
#include <qxyseries.h>
#include <QGraphicsItem>

QCHART_BEGIN_NAMESPACE

class QCHART_EXPORT QChart : public QGraphicsItem
{
public:
    enum DataSeriesType {
        DataSeriesTypeLine = 0,
        DataSeriesTypeArea,
        DataSeriesTypeBar,
        DataSeriesTypePie,
        DataSeriesTypeScatter,
        DataSeriesTypeSpline
    };

protected:
    QChart(QGraphicsItem* parent =0);

public:
    virtual ~QChart();

    static QChart* createXYLineChart(const QList<QXYSeries*>& dataset);

    virtual void setSize(const QSizeF& rect)=0;
    void setMargin(int margin);
    int margin() const { return m_marginSize;}

private:
    int m_marginSize;
};

QCHART_END_NAMESPACE

#endif
