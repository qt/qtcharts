#ifndef BARSERIES_H
#define BARSERIES_H

#include <qseries.h>
#include <QStringList>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QStringList QBarCategories;

class QBarSet;
class BarChartModel;
class BarCategory;

// Container for series
class QTCOMMERCIALCHART_EXPORT QBarSeries : public QSeries
{
    Q_OBJECT
public:
    QBarSeries(QStringList categories, QObject* parent=0);

    virtual QSeriesType type() const { return QSeries::SeriesTypeBar; }

    void addBarSet(QBarSet *set);               // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    void insertBarSet(int i, QBarSet *set);
    void insertCategory(int i, QString category);
    void removeCategory(int i);
    int barsetCount();
    int categoryCount();
    QList<QBarSet*> barSets();
    QBarCategories categories() const;


    bool setModel(QAbstractItemModel* model);
    QAbstractItemModel* modelExt() {return m_model;}
    void setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation = Qt::Vertical);

public:
    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it
    // TODO: TO PIMPL --->
    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal maxCategorySum();
    BarChartModel& model();
    // <--- TO PIMPL

signals:
    //void changed(int index);
    void clicked(QBarSet* barset, QString category);        // Up to user of api, what to do with these signals
    void rightClicked(QBarSet* barset, QString category);

    //
    void updatedBars();
    void restructuredBar(int);

    // TODO: internal signals, these to private implementation.
    // TODO: TO PIMPL --->
    void showToolTip(QPoint pos, QString tip);
    // <--- TO PIMPL

public Q_SLOTS:
    void setToolTipEnabled(bool enabled=true);           // enables tooltips

    // TODO: TO PIMPL --->
    void barsetClicked(QString category);
    void barsetRightClicked(QString category);
    // <--- TO PIMPL

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);
    void barsetChanged();

protected:
    BarChartModel* mModel;

//    QAbstractItemModel* m_model;
    int m_mapCategories;
    int m_mapBarBottom;
    int m_mapBarTop;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // BARSERIES_H
