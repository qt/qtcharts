#ifndef PIESERIES_H
#define PIESERIES_H

#include "qchartseries.h"
#include <QObject>
#include <QRectF>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QSignalMapper>

class QGraphicsObject;
QTCOMMERCIALCHART_BEGIN_NAMESPACE
class PiePresenter;
class PieSlice;
class QPieSlice;

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

        // TODO: these should not really be exposed to the public API
        void appendAdded(QPieSlice* slice);
        void appendAdded(QList<QPieSlice*> slices);
        void appendChanged(QPieSlice* slice);
        void appendRemoved(QPieSlice* slice);

        QList<QPieSlice*> added() const;
        QList<QPieSlice*> changed() const;
        QList<QPieSlice*> removed() const;

        bool isEmpty() const;

    private:
        QList<QPieSlice*> m_added;
        QList<QPieSlice*> m_changed;
        QList<QPieSlice*> m_removed;
    };

public:
    QPieSeries(QObject *parent = 0);
    virtual ~QPieSeries();

public: // from QChartSeries
    QChartSeriesType type() const;
    virtual bool setData(QList<qreal> data);  // TODO: remove this

public:
    void set(QList<QPieSlice*> slices);
    void add(QList<QPieSlice*> slices);
    void add(QPieSlice* slice);
    QPieSlice* add(qreal value, QString name);
    void remove(QPieSlice* slice);
    void clear();

    int count() const;

    QList<QPieSlice*> slices() const;

    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor() const;

    void setPosition(PiePosition position);
    PiePosition position() const;

    void setSpan(qreal startAngle, qreal angleSpan);

    void setLabelsVisible(bool visible);
    void enableClickExplodes(bool enable);
    void enableHoverHighlight(bool enable);

    // TODO: find slices?
    // QList<QPieSlice*> findByValue(qreal value);
    // ...

    // TODO: sorting slices?
    // void sort(QPieSeries::SortByValue|label|??)

    // TODO: general graphics customization
    // setDrawStyle(2d|3d)
    // setDropShadows(bool)

Q_SIGNALS:
    void changed(const QPieSeries::ChangeSet& changeSet);
    void clicked(QPieSlice* slice);
    void hoverEnter(QPieSlice* slice);
    void hoverLeave(QPieSlice* slice);
    void sizeFactorChanged();
    void positionChanged();

private Q_SLOTS: // TODO: should be private and not visible in the interface at all
    void sliceChanged();
    void sliceClicked();
    void sliceHoverEnter();
    void sliceHoverLeave();
    void toggleExploded(QPieSlice* slice);
    void highlightOn(QPieSlice* slice);
    void highlightOff(QPieSlice* slice);

private:
    void updateDerivativeData();

private:
    Q_DISABLE_COPY(QPieSeries)

    // TODO: use PIML
    friend class PiePresenter;
    friend class PieSlice;

    QList<QPieSlice*> m_slices;
    qreal m_sizeFactor;
    PiePosition m_position;
    qreal m_total;
    qreal m_pieStartAngle;
    qreal m_pieAngleSpan;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
