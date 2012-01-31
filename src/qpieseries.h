#ifndef PIESERIES_H
#define PIESERIES_H

#include "qchartseries.h"
#include <QObject>
#include <QRectF>
#include <QColor>

class QGraphicsObject;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSeriesPrivate;
class PieSlice;

class QTCOMMERCIALCHART_EXPORT QPieSeries : public QChartSeries
{
    Q_OBJECT

public:
    enum PiePosition {
        PiePositionMaximized = 0,
        PiePositionTopLeft,
        PiePositionTopRight,
        PiePositionBottomLeft,
        PiePositionBottomRight
    };

public:
    // TODO: use a generic data class instead of x and y
    QPieSeries(QGraphicsObject *parent = 0);
    ~QPieSeries();

public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypePie; }
    bool setData(QList<qreal> data);

public:
    void setSliceColor(int index, QColor color);
    QColor sliceColor(int index);
    int sliceCount();
    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor();
    void setPosition(PiePosition position);

private:
    Q_DECLARE_PRIVATE(QPieSeries)
    Q_DISABLE_COPY(QPieSeries)
    friend class QChart;
    QPieSeriesPrivate *const d;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
