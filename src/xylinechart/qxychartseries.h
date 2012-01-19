#ifndef QXYSERIES_H_
#define QXYSERIES_H_

#include "qchartglobal.h"
#include "qchartseries.h"
#include <QDebug>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYChartSeries : public QChartSeries
{
private:
    QXYChartSeries(QObject* parent=0);
public:
    virtual ~QXYChartSeries();

    //implemented from QChartSeries
    static QXYChartSeries* create(QObject* parent=0);
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeLine;}

    void add(qreal x, qreal y);
    void clear();
    void setColor(const QColor& color);
    const QColor& color() const { return m_color;}
    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    friend QDebug operator<< (QDebug d, const QXYChartSeries series);

private:
    QColor m_color;
    QList<qreal> m_x;
    QList<qreal> m_y;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
