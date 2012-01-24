#ifndef PIESERIES_H
#define PIESERIES_H

#include "qchartseries.h"
#include <QObject>
#include <QRectF>
#include <QColor>

class QGraphicsObject;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PieSlice;

class QTCOMMERCIALCHART_EXPORT QPieSeries : public QChartSeries
{
    Q_OBJECT

public:
    // TODO: use a generic data class instead of x and y
    QPieSeries(QGraphicsObject *parent = 0);
    ~QPieSeries();
    QColor randomColor();
    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor() { return m_sizeFactor; }

public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypePie; }
    bool setData(QList<qreal> data);

public Q_SLOTS:
    void chartSizeChanged(QRectF rect);

private:
    void resizeSlices(QRectF rect);
    //Q_DECLARE_PRIVATE(QPieSeries)
    Q_DISABLE_COPY(QPieSeries)
    // TODO: move the followin to internal impl
    QList<qreal> m_data;
    QList<PieSlice*> m_slices;
    QRectF m_chartSize;
    qreal m_sizeFactor;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
