#ifndef PIESERIES_H
#define PIESERIES_H

#include "qchartseries.h"
#include <QObject>
#include <QRectF>
#include <QColor>

class QGraphicsObject;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PiePresentation;
class PieSlice;

class QPieSlice
{
public:
    QPieSlice()
        :m_value(0), m_label("<empty>"), m_color(Qt::white), m_isExploded(false) {}

    QPieSlice(qreal value, QString label, QColor color, bool exploded = false)
        :m_value(value), m_label(label), m_color(color), m_isExploded(exploded) {}
public:
    qreal m_value;
    QString m_label;
    QColor m_color;
    bool m_isExploded;
};

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
    QPieSeries(QObject *parent = 0);
    ~QPieSeries();

public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypePie; }

public:
    void set(QList<QPieSlice> slices);
    void add(QList<QPieSlice> slices);
    void add(QPieSlice slice);

    int count() const { return m_slices.count(); }

    QList<QPieSlice> slices() const { return m_slices; }
    QPieSlice slice(int index) const;
    bool update(int index, QPieSlice slice);

    // TODO: convenience functions
    //void updateValue(int sliceIndex, qreal value);
    //void updateLabel(int sliceIndex, QString label);
    //void updateColor(int sliceIndex, QColor color);
    //void updateExploded(int slizeIndex, bool exploded);

    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor() const { return m_sizeFactor; }

    void setPosition(PiePosition position);
    PiePosition position() const { return m_position; }

private:
    Q_DISABLE_COPY(QPieSeries)
    // TODO: use PIML
    friend class ChartPresenter;
    friend class ChartDataSet;
    friend class PiePresentation;
    PiePresentation *m_piePresentation;
    QList<QPieSlice> m_slices;
    qreal m_sizeFactor;
    PiePosition m_position;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
