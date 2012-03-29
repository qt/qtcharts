#ifndef QAREASERIES_H_
#define QAREASERIES_H_

#include <qchartglobal.h>
#include <qseries.h>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QLineSeries;

class QTCOMMERCIALCHART_EXPORT QAreaSeries : public QSeries
{
    Q_OBJECT
public:
    QAreaSeries(QLineSeries *upperSeries, QLineSeries *lowerSeries = 0);
    virtual ~QAreaSeries();

public: // from QChartSeries
    virtual QSeriesType type() const { return QSeries::SeriesTypeArea; }

    QLineSeries* upperSeries() const { return m_upperSeries; }
    QLineSeries* lowerSeries() const { return m_lowerSeries; }

    void setPen(const QPen &pen);
    QPen pen() const { return m_pen;}

    void setBrush(const QBrush &brush);
    QBrush brush() const { return m_brush;}

    void setPointsVisible(bool visible);
    bool pointsVisible() const { return m_pointsVisible; }

//    bool setModel(QAbstractItemModel* model);
//    void setModelMappingUpper(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);
//    void setModelMappingLower(int modelX, int modelY, Qt::Orientation orientation = Qt::Vertical);

Q_SIGNALS:
    void updated();
    void clicked(const QPointF &point);

private:
    QBrush m_brush;
    QPen m_pen;
    QLineSeries* m_upperSeries;
    QLineSeries* m_lowerSeries;
    bool m_pointsVisible;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
