#ifndef PIESERIES_H
#define PIESERIES_H

#include "qchartseries.h"
#include <QObject>
#include <QRectF>
#include <QColor>
#include <QPen>
#include <QBrush>

class QGraphicsObject;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PiePresenter;
class PieSlice;

typedef quint64 QPieSliceId;

class QPieSlice
{
public:
    QPieSlice()
        :m_id(-1), m_value(0), m_isLabelVisible(true), m_isExploded(false), m_percentage(0)  {}

    QPieSlice(qreal value, QString label = QString(), bool labelVisible = true, bool exploded = false, QPen pen = QPen(), QBrush brush = QBrush())
        :m_id(-1), m_value(value), m_label(label), m_isLabelVisible(labelVisible), m_isExploded(exploded), m_pen(pen), m_brush(brush), m_percentage(0) {}

    QPieSliceId id() const { return m_id; }

    void setValue(qreal value) { m_value = value; }
    qreal value() const { return m_value; }

    void setLabel(QString label) { m_label = label; }
    QString label() const { return m_label; }

    void setLabelVisible(bool visible) { m_isLabelVisible = visible; }
    bool isLabelVisible() const { return m_isLabelVisible; }

    void setExploded(bool exploded) { m_isExploded = exploded; }
    bool isExploded() const { return m_isExploded; }

    void setPen(QPen pen) { m_pen = pen; }
    QPen pen() const { return m_pen; }

    void setBrush(QBrush brush) { m_brush = brush; }
    QBrush brush() const { return m_brush; }

    qreal percentage() const { return m_percentage; }

private:

    // TODO: use private class
    friend class QPieSeries;

    QPieSliceId m_id;
    qreal m_value;
    QString m_label;
    bool m_isLabelVisible;
    bool m_isExploded;

    QPen m_pen;
    QBrush m_brush;

    qreal m_percentage; // generated content
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

    class ChangeSet
    {
    public:
        QList<QPieSliceId> m_added;
        QList<QPieSliceId> m_removed;
        QList<QPieSliceId> m_changed;
    };

public:
    QPieSeries(QObject *parent = 0);
    ~QPieSeries();

public: // from QChartSeries
    QChartSeriesType type() const { return QChartSeries::SeriesTypePie; }
    virtual bool setData(QList<qreal> data);  // TODO: remove this

public:
    // TODO: should we return id/bool or what?
    // TODO: should we prefer passing a modifiable reference?
    bool set(const QList<QPieSlice>& slices);
    bool add(const QList<QPieSlice>& slices);
    bool add(const QPieSlice& slice);
    bool update(const QPieSlice& slice);
    bool remove(QPieSliceId id);

    int count() const { return m_slices.count(); }

    QList<QPieSlice> slices() const { return m_slices.values(); }
    QList<QPieSliceId> ids() const { return m_slices.keys(); }
    QPieSlice slice(QPieSliceId id) const;

    // TODO: sorting?

    // TODO: convenience functions
    //void updateValue(int sliceIndex, qreal value);
    //void updateLabel(int sliceIndex, QString label);
    //void updateColor(int sliceIndex, QColor color);
    //void updateExploded(int slizeIndex, bool exploded);

    // TODO: customization
    // set/get pen/brush
    // - for label
    // - for whole pie/slice

    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor() const { return m_sizeFactor; }

    void setPosition(PiePosition position);
    PiePosition position() const { return m_position; }

Q_SIGNALS:
    void changed(const QPieSeries::ChangeSet& changeSet);
    void sizeFactorChanged();
    void positionChanged();
    //void sliceClicked(QPieSliceId id);
    //void sliceHoverEnter(QPieSliceId id);
    //void sliceHoverLeave(QPieSliceId id);

private:
    QPieSliceId generateSliceId();
    void updateDerivativeData();

private:
    Q_DISABLE_COPY(QPieSeries)

    // TODO: use PIML
    friend class PiePresenter;
    friend class PieSlice;

    QHash<QPieSliceId, QPieSlice> m_slices;
    qreal m_sizeFactor;
    PiePosition m_position;
    qreal m_total;
    QPieSliceId m_sliceIdSeed;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
