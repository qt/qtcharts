#ifndef PIESERIES_H
#define PIESERIES_H

#include "qseries.h"
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

class QTCOMMERCIALCHART_EXPORT QPieSeries : public QSeries
{
    Q_OBJECT

public:

    enum PiePositionFlag {
        PiePositionLeft = 0x1,
        PiePositionRight = 0x2,
        PiePositionHCenter = 0x4,
        PiePositionTop = 0x10,
        PiePositionBottom = 0x20,
        PiePositionVCenter = 0x40,
        PiePositionCenter = PiePositionHCenter | PiePositionVCenter
    };

    Q_DECLARE_FLAGS(PiePosition, PiePositionFlag)

    enum PieSizePolicyFlag {
        PieSizePolicyMaximized = 0,
        PieSizePolicyReserveSpaceForLabels = 0x1,
        PieSizePolicyReserveSpaceForExploding = 0x2,
        PieSizePolicyReserveSpaceForAll = PieSizePolicyReserveSpaceForLabels | PieSizePolicyReserveSpaceForExploding
    };

    Q_DECLARE_FLAGS(PieSizePolicy, PieSizePolicyFlag)

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
    QSeriesType type() const;

public:

    // slice setters
    void add(QPieSlice* slice);
    void add(QList<QPieSlice*> slices);
    void replace(QList<QPieSlice*> slices);
    void remove(QPieSlice* slice);
    void clear();

    // sluce getters
    QList<QPieSlice*> slices() const;

    // calculated data
    int count() const;
    qreal total() const;

    // pie customization
    void setPosition(PiePosition position);
    PiePosition position() const;
    void setSizePolicy(PieSizePolicy policy);
    PieSizePolicy sizePolicy() const;
    void setSizeFactor(qreal sizeFactor);
    qreal sizeFactor() const;
    void setStartAngle(qreal startAngle);
    qreal startAngle() const;
    void setEndAngle(qreal endAngle);
    qreal endAngle() const;

    // convenience function
    QPieSeries& operator << (QPieSlice* slice);
    QPieSlice* add(qreal value, QString name);
    void setLabelsVisible(bool visible = true);

    // TODO: find slices?
    // QList<QPieSlice*> findByValue(qreal value);
    // ...

    // TODO: sorting slices?
    // void sort(QPieSeries::SortByValue|label|??)

    // TODO: general graphics customization
    // setDrawStyle(2d|3d)
    // setDropShadows

Q_SIGNALS:

    void changed(const QPieSeries::ChangeSet& changeSet);

    void clicked(QPieSlice* slice);
    void hoverEnter(QPieSlice* slice);
    void hoverLeave(QPieSlice* slice);

    void sizeFactorChanged();
    void positionChanged();
    void sizePolicyChanged();

private Q_SLOTS: // TODO: should be private and not visible in the interface at all
    void sliceChanged();
    void sliceClicked();
    void sliceHoverEnter();
    void sliceHoverLeave();

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
    PieSizePolicy m_sizePolicy;
    qreal m_total;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
