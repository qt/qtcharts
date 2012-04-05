#ifndef QBARSERIESPRIVATE_P_H
#define QBARSERIESPRIVATE_P_H

#include "qbarseries.h"
#include <QStringList>
#include <QSeries>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

typedef QStringList QBarCategories;

class QBarSeries;
class QBarSet;
class BarChartModel;
class BarCategory;

// Container for series
class QBarSeriesPrivate : public QObject
{
    Q_OBJECT
    Q_DECLARE_PUBLIC(QBarSeries)
public:
    QBarSeriesPrivate(QStringList categories, QBarSeries *parent);

    virtual QSeries::QSeriesType type() const { return QSeries::SeriesTypeBar; }

    void appendBarSet(QBarSet *set);            // Takes ownership of set
    void removeBarSet(QBarSet *set);            // Releases ownership, doesn't delete set
    void appendBarSets(QList<QBarSet* > sets);
    void removeBarSets(QList<QBarSet* > sets);
    void insertBarSet(int i, QBarSet *set);
    void insertCategory(int i, QString category);
    void removeCategory(int i);
    int barsetCount() const;
    int categoryCount() const;
    QList<QBarSet*> barSets() const;
    QBarCategories categories() const;

    void setLabelsVisible(bool visible = true);

    bool setModel(QAbstractItemModel *model);
    void setModelMapping(int categories, int bottomBoundry, int topBoundry, Qt::Orientation orientation = Qt::Vertical);

    QBarSet* barsetAt(int index);
    QString categoryName(int category);
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal percentageAt(int set, int category);
    qreal categorySum(int category);
    qreal absoluteCategorySum(int category);
    qreal maxCategorySum();
    BarChartModel& modelInternal();

    static QBarSeriesPrivate &data(QBarSeries *barseries)
    {
        Q_ASSERT(barseries);
        return *barseries->d_ptr;
    }

Q_SIGNALS:
    void clicked(QBarSet *barset, QString category, Qt::MouseButtons button);        // Up to user of api, what to do with these signals
    void selected();
    void updatedBars();
    void restructuredBars();
    void showToolTip(QPoint pos, QString tip);

public Q_SLOTS:
    void setToolTipEnabled(bool enabled = true);           // enables tooltips
    void barsetClicked(QString category, Qt::MouseButtons button);

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelDataAdded(QModelIndex parent, int start, int end);
    void modelDataRemoved(QModelIndex parent, int start, int end);
    void barsetChanged();

protected:
    QBarSeries * const q_ptr;

    BarChartModel *m_internalModel;     // TODO: this may change... current "2 models" situation doesn't look good.
    QAbstractItemModel* m_model;
    int m_mapCategories;
    int m_mapBarBottom;
    int m_mapBarTop;
    int m_mapFirst;
    int m_mapCount;
    Qt::Orientation m_mapOrientation;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSERIESPRIVATE_P_H
