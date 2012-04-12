#ifndef QBARSERIES_P_H
#define QBARSERIES_P_H

#include "qbarseries.h"
#include "qabstractseries_p.h"
#include <QStringList>
#include <QAbstractSeries>

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// Container for series
class QBarSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT
public:
    QBarSeriesPrivate(QBarCategories categories, QBarSeries *parent);

    void scaleDomain(Domain& domain);
    Chart* createGraphics(ChartPresenter* presenter);
    QList<LegendMarker*> createLegendMarker(QLegend* legend);

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

Q_SIGNALS:
    void clicked(QBarSet *barset, QString category);
    void updatedBars();
    void restructuredBars();

private Q_SLOTS:
    // slots for updating bars when data in model changes
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void barsetChanged();

protected:
    QList<QBarSet *> m_barSets;
    QBarCategories m_categories;

    QAbstractItemModel* m_model;
    int m_mapCategories;
    int m_mapBarBottom;
    int m_mapBarTop;
    Qt::Orientation m_mapOrientation;
private:
    Q_DECLARE_PUBLIC(QBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSERIESPRIVATE_P_H
