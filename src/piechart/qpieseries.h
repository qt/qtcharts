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
class PieChartItem;
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
    void setPiePosition(qreal relativeHorizontalPosition, qreal relativeVerticalPosition);
    qreal pieHorizontalPosition() const;
    qreal pieVerticalPosition() const;
    void setPieSize(qreal relativeSize);
    qreal pieSize() const;
    void setPieStartAngle(qreal startAngle);
    qreal pieStartAngle() const;
    void setPieEndAngle(qreal endAngle);
    qreal pieEndAngle() const;

    // convenience function
    QPieSeries& operator << (QPieSlice* slice);
    QPieSlice* add(qreal value, QString name);
    void setLabelsVisible(bool visible = true);

    // data from model
    bool setModel(QAbstractItemModel* model);
    void setModelMapping(int modelValuesLine, int modelLabelsLine, Qt::Orientation orientation = Qt::Vertical);

    // TODO: find slices?
    // QList<QPieSlice*> findByValue(qreal value);
    // ...

    // TODO: sorting slices?
    // void sort(QPieSeries::SortByValue|label|??)

    // TODO: general graphics customization
    // setDrawStyle(2d|3d)
    // setDropShadows

Q_SIGNALS:
    void clicked(QPieSlice* slice);
    void hoverEnter(QPieSlice* slice);
    void hoverLeave(QPieSlice* slice);
    void changed(); // TODO: hide this in PIMPL

private Q_SLOTS: // TODO: should be private and not visible in the interface at all
    void sliceChanged();
    void sliceClicked();
    void sliceHoverEnter();
    void sliceHoverLeave();

    // slots for updating pie when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);

private:
    void updateDerivativeData();

private:
    Q_DISABLE_COPY(QPieSeries)

    // TODO: use PIML
    friend class PieChartItem;
    friend class PieSlice;

    QList<QPieSlice*> m_slices;
    qreal m_pieRelativeHorPos;
    qreal m_pieRelativeVerPos;
    qreal m_pieRelativeSize;
    qreal m_pieStartAngle;
    qreal m_pieEndAngle;
    qreal m_total;

    // model map
    int m_mapValues;
    int m_mapLabels;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
