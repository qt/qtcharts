#ifndef QLINECHARTSERIES_H_
#define QLINECHARTSERIES_H_

#include "qchartglobal.h"
#include "qchartseries.h"
#include <QDebug>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QLineChartSeries : public QChartSeries
{
    Q_OBJECT
private:
    QLineChartSeries(QObject* parent=0);
public:
    virtual ~QLineChartSeries();

public: // from QChartSeries
    static QLineChartSeries* create(QObject* parent=0);
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeLine;}

public:
    int add(qreal x, qreal y);
    void set(int index,qreal x,qreal y);
    void clear();

    void setPen(const QPen& pen);
    const QPen& pen() const { return m_pen;}

    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    friend QDebug operator<< (QDebug d, const QLineChartSeries series);

signals:
    void changed(int index);

private:
    QVector<qreal> m_x;
    QVector<qreal> m_y;
    QPen m_pen;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
