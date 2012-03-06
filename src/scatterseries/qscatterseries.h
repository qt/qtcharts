#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include "qchartglobal.h"
#include "qxyseries.h"
#include <QRectF>
#include <QColor>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QXYSeries
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
    //int closestPoint(QPointF coordinate);

    MarkerShape shape() const;
    void setShape(MarkerShape shape);
    qreal size() const;
    void setSize(qreal size);

signals:
    void clicked(QPointF coordinate);

private:
    MarkerShape m_shape;
    qreal m_size;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
