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
    void setPositionFactors(qreal horizontalFactor, qreal verticalFactor);
    qreal horizontalPositionFactor() const;
    qreal verticalPositionFactor() const;
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
    qreal m_hPositionFactor;
    qreal m_vPositionFactor;
    qreal m_pieSizeFactor;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_total;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
