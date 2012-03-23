#ifndef PIESERIES_H
#define PIESERIES_H

#include <qseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
class QPieSeriesPrivate;
class QPieSlice;

class QTCOMMERCIALCHART_EXPORT QPieSeries : public QSeries
{
    Q_OBJECT

public:
    QPieSeries(QObject *parent = 0);
    virtual ~QPieSeries();

public: // from QChartSeries
    QSeriesType type() const;

public:

    // slice setters
    void add(QPieSlice* slice);
    void add(QList<QPieSlice*> slices);
    void insert(int i, QPieSlice* slice);
    void replace(QList<QPieSlice*> slices);
    void remove(QPieSlice* slice);
    void clear();

    // slice getters
    QList<QPieSlice*> slices() const;

    // calculated data
    int count() const;
    bool isEmpty() const;
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

Q_SIGNALS:
    void clicked(QPieSlice* slice, Qt::MouseButtons buttons);
    void hoverEnter(QPieSlice* slice);
    void hoverLeave(QPieSlice* slice);
    void added(QList<QPieSlice*> slices);
    void removed(QList<QPieSlice*> slices);
    void piePositionChanged();
    void pieSizeChanged();

private:
    QPieSeriesPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QPieSeries)
    Q_DISABLE_COPY(QPieSeries)

public:
    typedef QPieSeriesPrivate * const DataPtr;
    inline DataPtr &data_ptr() { return d_ptr; }
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // PIESERIES_H
