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
        MarkerShapePoint,
        MarkerShapeX,
        MarkerShapeRectangle,
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
    bool removeAt(int pointIndex);
    int removeAll(QPointF point);
    void clear();
    int closestPoint(QPointF coordinate);
    //TODO: insert, replace...?

    QPen pen();
    void setPen(QPen pen);
    QBrush brush();
    void setBrush(QBrush brush);
    MarkerShape shape();
    void setShape(MarkerShape shape);
    // TODO: marker size?

Q_SIGNALS:
    void clicked(QPointF coordinate);
    // TODO: move to PIMPL for simplicity or does the user ever need changed signals?
    // TODO: more finegrained signaling for performance reasons
    // (check QPieSeries implementation with change sets)
    void changed();

private:
    Q_DECLARE_PRIVATE(QScatterSeries)
    Q_DISABLE_COPY(QScatterSeries)
    QScatterSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
