#ifndef QLINESERIES_H_
#define QLINESERIES_H_

#include "qchartglobal.h"
#include "qseries.h"
#include <QDebug>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QLineSeries : public QSeries
{
    Q_OBJECT
public:
    QLineSeries(QObject* parent=0);
    virtual ~QLineSeries();

public: // from QChartSeries
    virtual QSeriesType type() const { return QSeries::SeriesTypeLine;}
    void add(qreal x, qreal y);
    void add(const QPointF& point);
    void replace(qreal x,qreal y);
    void replace(const QPointF& point);
    void remove(qreal x);
    void remove(const QPointF& point);
    void clear();

    void setPen(const QPen& pen);
    QPen pen() const { return m_pen;}

    void setPointsVisible(bool visible);
    bool pointsVisible() const {return m_pointsVisible;}

    int count() const;
    qreal x(int pos) const;
    qreal y(int pos) const;
    friend QDebug operator<< (QDebug d, const QLineSeries series);

signals:
    void changed(int index);

private:
    QVector<qreal> m_x;
    QVector<qreal> m_y;
    QPen m_pen;
    bool m_pointsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
