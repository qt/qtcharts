#ifndef QXYSERIES_H_
#define QXYSERIES_H_

#include "qchartglobal.h"
#include "qchartseries.h"
#include <QDebug>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QXYChartSeries : public QChartSeries
{
    //TODO:
//    Q_OBJECT
private:
    QXYChartSeries(QObject* parent=0);
public:
    virtual ~QXYChartSeries();

    //implemented from QChartSeries
    static QXYChartSeries* create(QObject* parent=0);
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeLine;}

    void add(qreal x, qreal y);
    void clear();

    void setPen(const QPen& pen);
    const QPen& pen() const { return m_pen;}
    void setBrush(const QBrush& brush);
    const QBrush& brush() const { return m_brush;}

    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    friend QDebug operator<< (QDebug d, const QXYChartSeries series);

private:
    QList<qreal> m_x;
    QList<qreal> m_y;
    QBrush m_brush;
    QPen m_pen;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
