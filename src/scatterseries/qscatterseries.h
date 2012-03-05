#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include "qseries.h"
#include <QRectF>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QSeries
{
    Q_OBJECT

public:
    enum MarkerShape {
        // TODO: to be defined by the graphics design
        // TODO: marker shapes: "x", star, rectangle, tilted rect, triangle, circle, dot
        MarkerShapeDefault = 0,
        MarkerShapeX,
        MarkerShapeRectangle,
        MarkerShapeRoundedRectangle,
        MarkerShapeTiltedRectangle,
        MarkerShapeTriangle,
        MarkerShapeCircle
    };

public:
    QScatterSeries(QObject *parent = 0);
    ~QScatterSeries();

public: // from QChartSeries
    QSeriesType type() const { return QSeries::SeriesTypeScatter; }

public:
    void add(qreal x, qreal y);
    void add(QPointF value);
    void add(QList<QPointF> points);
    void setData(QList<QPointF> points);
    QScatterSeries& operator << (const QPointF &value);
    QScatterSeries& operator << (QList<QPointF> points);
    QList<QPointF> data();
    bool replace(int index, QPointF newPoint);
    bool removeAt(int index);
    int removeAll(QPointF point);
    void clear();
    int closestPoint(QPointF coordinate);
    //TODO: insert, replace...?

    QPen pen() const;
    void setPen(const QPen &pen);
    QBrush brush() const;
    void setBrush(const QBrush &brush);
    MarkerShape shape() const;
    void setShape(MarkerShape shape);
    qreal size() const;
    void setSize(qreal size);

Q_SIGNALS:
    void clicked(QPointF coordinate);

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    friend class ScatterPresenter;
    QScatterSeriesPrivate *d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
