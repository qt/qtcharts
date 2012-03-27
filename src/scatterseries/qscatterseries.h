#ifndef QSCATTERSERIES_H
#define QSCATTERSERIES_H

#include <qchartglobal.h>
#include <qxyseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QScatterSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QScatterSeries : public QXYSeries
{

public:
    enum MarkerShape {
        MarkerShapeCircle,
        MarkerShapeRectangle
    };

public:
    QScatterSeries(QObject *parent = 0);
    ~QScatterSeries();

public: // from QChartSeries
    QSeriesType type() const { return QSeries::SeriesTypeScatter; }

public:
    MarkerShape shape() const;
    void setShape(MarkerShape shape);
    qreal size() const;
    void setSize(qreal size);

private:
    MarkerShape m_shape;
    qreal m_size;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSCATTERSERIES_H
